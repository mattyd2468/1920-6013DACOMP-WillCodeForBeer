#include "Arduino.h"
#include "../src/main/sensors/Thermometer.h"
#include "../src/main/sensors/Humidity.h"
#include "../src/main/sensors/LED.h"
#include <DHTesp.h>
#include "../src/main/sensors/PIR.h"

//Pin set up
#define DHTPIN 4 // the pin value for the DHT11 sensor
#define DHTTYPE DHT11
const int MOTION_SENSOR = 15;   // PIR sensor pin
LED *led = new LED(26, 33, 32); // the LED which shows the status of the sensors, pins 23,22,21
const int DHT11_DELAY = 2000;   // delay for the DHT11 sensor to take readings, must be 2 seconds
int DHT11Millis = 0;			// time in millis since DHT11 sensor took readings

const int STATUS_UPDATE_DELAY = 5000; // delay for the status update, must be every 5 seconds
int statusMillis = 0;				  // time in millis since last status update

//Variable initialisation
bool firstLoop = true; //Variable to store if it is the first loop or not
double potVal = 0;		   // Variable to store temperature value
double humVal = 0;		   // Variable to store the humidity value

//Setting up the objects
Thermometer *thermometer = NULL;
Humidity *humidity = NULL;
DHTesp dht;					  // object to store the DHT11 sensor
TempAndHumidity tempHum;	  // the object to store the temperature and humidity values
TemperatureStatus tempStatus; // object to store the temperature status
HumidityStatus humStatus;	 // object to store the humidity status

PIRStatus motionSensorStatus = PIRStatus::VACANT; // object to store the PIR status
PIR *pir = NULL;

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
	thermometer = new Thermometer(DHTPIN, led);
	humidity = new Humidity(DHTPIN, led);

	Serial.begin(115200);			  // @suppress("Ambiguous problem")
	dht.setup(DHTPIN, DHTesp::DHT11); // set up the DHT11 sensor

	pir = new PIR(MOTION_SENSOR);
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
		pir->motionSensor(); //Call taskD code
		statusUpdate();		 // report status update
	}
}
