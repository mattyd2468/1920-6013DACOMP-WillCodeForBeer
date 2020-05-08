#include "Arduino.h"
#include "HTTPClient.h"
#include <DHTesp.h>
#include "../main/sensors/Thermometer.h"
#include "../main/sensors/Humidity.h"
#include "../main/sensors/LED.h"
#include "../main/sensors/PIR.h"
#include "../src/main/sensors/Buzzer.h"
#include "../src/main/sensors/Button.h"
#include <WiFi.h>
#include <WiFiType.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include <WString.h>
#include "SDCard.h"
#include <Vector.h>
#include <../src/main/enums/ButtonState.h>

//WiFi
const char *SSID = "Matt";
const char *PASS = "password";
const char *HOST = "http://willcodeforbeer12345.azurewebsites.net/";
const int TIMEOUT = 10000;
const String GROUPNAME = "WillCodeForBeer";
const int WRITE_TO_SERVER_DELAY = 30000; // delay for the status update, must be every 30 seconds
int serverMillis = 0;				  // time in millis since last written to server

//Pin set up
#define DHTPIN 4 // the pin value for the DHT11 sensor
#define DHTTYPE DHT11
const int MOTION_SENSOR = 15;		// PIR sensor pin
LED *led = new LED(26, 33, 32); 	// the LED which shows the status of the sensors, pins 23,22,21
const int DHT11_DELAY = 2000;		// delay for the DHT11 sensor to take readings, must be 2 seconds
int DHT11Millis = 0;				// time in millis since DHT11 sensor took readings
 
int STATUS_UPDATE_DELAY = 5000; // delay for the status update, must start as 5 seconds
int statusMillis = 0;			// time in millis since last status update
const int STATUS_DELAY_VALUES[6] = {5000, 10000, 30000, 60000, 120000, 300000}; //The values at which output can be logged to the console. 

const int MEMORY_UPDATE_DELAY = 5000; // delay for the volatile memory update, must be every 5 seconds
int memoryMillis = 0;				  // time in millis since last memory update

//Variable initialisation
bool firstLoop = true; 		//Variable to store if it is the first loop or not
double potVal = 0;	   		// Variable to store temperature value
double humVal = 0;	   		// Variable to store the humidity value
vector<String> logging;		// Vector to store reading in volatile memory

//Setting up the objects
Thermometer *thermometer = NULL;
Humidity *humidity = NULL;
BUZZER *buzzer = NULL;
Button *pushButton = NULL;
TempAndHumidity tempHum;	  // the object to store the temperature and humidity values
DHTesp dht;					  // object to store the DHT11 sensor
TemperatureStatus tempStatus; // object to store the temperature status
HumidityStatus humStatus;	  // object to store the humidity status

PIRStatus motionSensorStatus = PIRStatus::VACANT; // object to store the PIR status
PIR *pir = NULL;

SDCard *sdcard = NULL;
const int SD_PIN = 5; // must be pin 5

/**
 * This method returns a boolean as to whether the time that has passed is longer than the delay specified
 */
boolean timeDiff(unsigned long start, int specifiedDelay)
{
	return (millis() - start >= specifiedDelay);
}

/**
 * Method to post to server
 */
void writeToServer()
{
	if (timeDiff(serverMillis, WRITE_TO_SERVER_DELAY))
	{
		serverMillis = millis();
		// url parameters
		String url = HOST;
		url.concat("?groupname=");
		url.concat(GROUPNAME);
		url.concat("&t=");
		url.concat(tempHum.temperature);
		url.concat("&h=");
		url.concat(tempHum.humidity);
		HTTPClient hClient;
		hClient.begin(url);
		const char *headers[] = {"Date"};
		hClient.collectHeaders(headers, 1);
		hClient.setTimeout(TIMEOUT);
		int retCode = hClient.GET();
		if (retCode > 0)
		{
			//a real HTTP code
			Serial.print("HTTP ");
			Serial.println(retCode);
			if (retCode == HTTP_CODE_OK)
			{
				Serial.println("------");
				Serial.println("Date = " + hClient.header("Date"));
				Serial.println("-------");
				Serial.println(hClient.getString());
			}
		}
		else
		{
			Serial.println("Error... ");
			Serial.println(HTTPClient::errorToString(retCode));
		}
	}
}

/**
 * This method is used at startup and initialises our sensors and pins
 */
void setup()
{
	thermometer = new Thermometer(DHTPIN, led);
	humidity = new Humidity(DHTPIN, led);

	Serial.begin(115200);			  // @suppress("Ambiguous problem")
	dht.setup(DHTPIN, DHTesp::DHT11); // set up the DHT11 sensor

	pir = new PIR(MOTION_SENSOR);
	sdcard = new SDCard(SD_PIN);
	buzzer = new BUZZER(pir, thermometer, humidity);
	pushButton = new Button();

	// WiFI
	Serial.print("Connecting to ");
	Serial.println(SSID);
	WiFi.begin(SSID, PASS);
	while (WiFi.status() != WL_CONNECTED)
	{
	delay(250);
		Serial.println(".");
	}
	Serial.print("Connected as :");
	Serial.println(WiFi.localIP());
}

/**
 * This method occurs at startup and tests all sensors and I/O devices are working as expected
 */
void powerOnTest()
{
	Serial.println("Power on!");
	tempHum = dht.getTempAndHumidity();
	if (tempHum.temperature == 0 || tempHum.temperature > 100 || isnan(tempHum.temperature))
	{
		Serial.println("Temperature Error");
	}
	if (tempHum.humidity == 0 || tempHum.humidity == 100 || isnan(tempHum.humidity))
	{
		Serial.println("Humidity Error");
	}
	firstLoop = false;
}

/**
 * This method will update the temp and hum status if it's been 2 seconds and update the LED according to the new statuses
 */
void tempAndHumSensor()
{
	if (timeDiff(DHT11Millis, DHT11_DELAY))
	{							// only get readings every 2 seconds - this is needed for the DHT11 sensor as a minimum
		DHT11Millis = millis(); // reset DHT11 millis
		// get the temperature and humidity readings from the DHT11 sensor
		tempHum = dht.getTempAndHumidity();
		// set LED colours for temp and humidity sensor
		tempStatus = thermometer->calculateStatus(tempHum.temperature, led);
		humStatus = humidity->calculateStatus(tempHum.humidity, led);
		led->setLEDColour(tempStatus, humStatus);


	}
}

/**
 * This method will provide a status update for all of the sensors and print it to the console
 */
void statusUpdate()
{
	if (timeDiff(statusMillis, STATUS_UPDATE_DELAY))
	{
		statusMillis = millis();
		Serial.println("----------------");
		Serial.println("Status Update:");
		Serial.print("Current Temperature: ");
		Serial.println(tempHum.temperature);
		Serial.print("Current Humidity: ");
		Serial.println(tempHum.humidity);
		Serial.print("Temperature Status: ");
		Serial.println(thermometer->getTempStatus(tempStatus));
		Serial.print("Humidity Status: ");
		Serial.println(humidity->getHumStatus(humStatus));
		Serial.print("PIR sensor status: ");
		Serial.println(pir->getPIRStatus());
		Serial.println("----------------");
	}
}

String formatUpdateDelay(int delay)
{

	String response;

	int seconds = delay/1000;

	if(seconds < 60) {
		response = (String)seconds + "s";
	} else {
		int minutes = seconds/60;
		response = (String)minutes + " mins";
	}

	return response;

}

/**
 *	This method will cycle the list of output intervals, 
 *	and increment the value used to be the next in the list.
 */

void updateStatusOutputInterval() 
{
	if(STATUS_UPDATE_DELAY == 300000) {
		STATUS_UPDATE_DELAY = STATUS_DELAY_VALUES[0];
	} else {
		for(int i = 0; i < sizeof(STATUS_DELAY_VALUES); i++) {
			if (STATUS_DELAY_VALUES[i] == STATUS_UPDATE_DELAY) {
				STATUS_UPDATE_DELAY = STATUS_DELAY_VALUES[i+1];
				break;
			}
		}
	}
	Serial.print("Output interval is now " );
	Serial.println(formatUpdateDelay(STATUS_UPDATE_DELAY));
}

/**
 *	This method will check when results were last written to memory, and if >5 seconds ago,	
 *	it will write the most recently recorded values.
 */
void storeToVolatileMemory()
{

	if (timeDiff(memoryMillis, MEMORY_UPDATE_DELAY)) {

		memoryMillis = millis();

		// Stores latest recorded DHT11 readings into a vector in volatile memory.
		logging.push_back("Temperature: " + (String)tempHum.temperature + "°C");
		logging.push_back("Humidity: " + (String)tempHum.humidity + "%");

		// Stores latest recorded PIR readings into a vector in volatile memory.
		logging.push_back("Building Status: " + pir->getPIRStatus());

	}

}

void checkButtonState() {

	ButtonState now = pushButton->getButtonState();
		if (now != pushButton->outputButtonCurrent) {
			pushButton->outputButtonCurrent = now;
			switch (pushButton->outputButtonCurrent) {
				case ON:
					updateStatusOutputInterval();
					delay(250);
					break;
				case OFF:
					break;
			}
		}
}

/**
 * This method is our main loop logic
 */
void loop()
{
	//If it is the first loop run power on test
	if (firstLoop)
	{
		powerOnTest();
	}
	//Else run normal system
	else
	{
		// get the temperature and humidity readings from the DHT11 sensor
		tempAndHumSensor();
		pir->motionSensor(sdcard, logging); //Call taskD code
		statusUpdate(); // report status update
		storeToVolatileMemory();
		sdcard->writeToSDCard(logging);
		buzzer->whichAlertToMake(tempStatus, humStatus); // Check if noise should be made
		writeToServer(); // write to server
		checkButtonState();
	}
}
