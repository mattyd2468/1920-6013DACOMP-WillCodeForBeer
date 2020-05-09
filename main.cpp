#include "Arduino.h"
#include "HTTPClient.h"
#include <DHTesp.h>
#include "../main/sensors/Thermometer.h"
#include "../main/sensors/Humidity.h"
#include "../main/sensors/LED.h"
#include "../main/sensors/PIR.h"
#include "../src/main/sensors/Buzzer.h"
#include <WiFi.h>
#include <WiFiType.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include <WString.h>
#include "SDCard.h"
#include <Vector.h>
#include <Adafruit_GFX.h>
#include <SSD1306.h>

//OLED Screen
SSD1306 display(0x3c, 21, 22);			   //OLED display
const unsigned long oledRefreshTime = 250; //250 ms timer to update OLED screen
unsigned long oledChangeTime = 0;		   //Time since OLED screen was last updated
bool isOccupied = false;

//WiFi
const char *SSID = "iPhone";
const char *PASS = "password";
const char *HOST = "http://willcodeforbeer12345.azurewebsites.net/";
const int TIMEOUT = 10000;
const String GROUPNAME = "WillCodeForBeer";
const int WRITE_TO_SERVER_DELAY = 30000; // delay for the status update, must be every 30 seconds
int serverMillis = 0;					 // time in millis since last written to server

//Pin set up
#define DHTPIN 4 // the pin value for the DHT11 sensor
#define DHTTYPE DHT11
const int MOTION_SENSOR = 15;	// PIR sensor pin
LED *led = new LED(26, 33, 32); // the LED which shows the status of the sensors, pins 23,22,21
const int DHT11_DELAY = 2000;	// delay for the DHT11 sensor to take readings, must be 2 seconds
int DHT11Millis = 0;			// time in millis since DHT11 sensor took readings
const int buttonPin = 13;
const int STATUS_UPDATE_DELAY = 5000; // delay for the status update, must be every 5 seconds
int statusMillis = 0;				  // time in millis since last status update

//Variable initialisation
bool firstLoop = true; //Variable to store if it is the first loop or not
double potVal = 0;	   // Variable to store temperature value
double humVal = 0;	   // Variable to store the humidity value
int buttonState = 0;   //Variable for button, is not pressed when it is 0

//debouncing variables
long lastDebounceTime = 0; // the last time the output pin was toggled
long debounceDelay = 50;   // the debounce time; increase if the output flickers
bool snoozeBool = false;

//Setting up the objects
Thermometer *thermometer = NULL;
Humidity *humidity = NULL;
BUZZER *buzzer = NULL;
DHTesp dht;					  // object to store the DHT11 sensor
TempAndHumidity tempHum;	  // the object to store the temperature and humidity values
TemperatureStatus tempStatus; // object to store the temperature status
HumidityStatus humStatus;	  // object to store the humidity status
Connect_WiFi *connect_wifi = NULL;
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
 * This method is used at startup and initialises our sensors and pins
 */
void setup()
{
	Serial.begin(115200); // @suppress("Ambiguous problem")

	pir = new PIR(MOTION_SENSOR);
	pinMode(buttonPin, INPUT);
	buzzer = new BUZZER(pir);
	thermometer = new Thermometer(DHTPIN, led);
	humidity = new Humidity(DHTPIN, led);

	//OLED Screen Initialization & Setup
	display.init();
	display.clear();
	display.flipScreenVertically();
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	display.setFont(ArialMT_Plain_16);
	display.drawString(0, 0, "WillCodeForBeer");
	display.drawString(0, 18, "Running Setup()");
	display.display();

	dht.setup(DHTPIN, DHTesp::DHT11); // set up the DHT11 sensor

	Connect_WiFi->connectToHotspot();
	Connect_WiFi->writeToServer();

	sdcard = new SDCard(SD_PIN, Connect_WiFi->date); // set up SD card, must be done after wifi setup otherwise date and time wont work
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

	if (WiFi.status() != WL_CONNECTED)
	{
		Serial.println("WiFi Error");
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

		sdcard->storeDHT11Readings((String)tempHum.temperature, (String)tempHum.humidity);
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
		Serial.print("Buzzer alert status: ");
		Serial.println(buzzer->getBuzzerStatus());
		Serial.print("Buzzer snooze active: ");
		Serial.println(buzzer->getBuzzerSnooze());
		Serial.println("----------------");
	}
}

void readButton()
{
	//Read button state (pressed or not pressed?)
	buttonState = digitalRead(buttonPin);

	//filter out any noise by setting a time buffer
	if ((millis() - lastDebounceTime) > debounceDelay)
	{

		//if button pressed add 2 mins to the time buzzer will next buzz
		if (buttonState == HIGH) //Because using pullup resistor if button is pressed it will be LOW
		{
			//set snooze flag to true
			snoozeBool = true;
			buzzer->buzzerSnooze = snoozeBool;
			buzzer->alertMillis = 0;
		}
		else
		{
			if (timeDiff(buzzer->alertMillis, 120000))
			{	
				buzzer->alertMillis = millis();
				snoozeBool = false;
				buzzer->buzzerSnooze = snoozeBool;
			}
		}
		lastDebounceTime = millis(); //set the current time
	}
}

void updateScreen(int temp, int hum, bool isOccupied){
	display.clear();
	display.drawString(0, 0, "Temp:"); //Temp Label
	display.drawString(0, 18, "Humidity:"); //Humidity Label
	display.drawString(75,0, String(temp)); //Temp value
	display.drawString(75,18, String(hum)); //Humidity value

	//Occupied/Vacant value
	if(isOccupied){
		display.drawString(0, 36, "Occupied");
	}
	else {
		display.drawString(0, 36, "Vacant");
	}
	display.display();
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
		pir->motionSensor(sdcard); //Call taskD code
		statusUpdate();			   // report status update
		sdcard->writeToSDCard();
		readButton();
		buzzer->whichAlertToMake(tempStatus, humStatus, snoozeBool); // Check if noise should be made
		Connect_WiFi->writeToServer();													   // write to server

		//PIR Sensor Status
		if(pir->getPIRStatus()=="OCCUPIED"){
			isOccupied = true;
		}
		else {
			isOccupied = false;
		}

		// update oled screen every 250 milliseconds to prevent flicker
		if (timeDiff(oledChangeTime, oledRefreshTime)) {
			oledChangeTime = millis();
			updateScreen(tempHum.temperature, tempHum.humidity, isOccupied); // Updating OLED Screen
		}
	}
}
