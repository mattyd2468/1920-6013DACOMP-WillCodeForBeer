#include "Arduino.h"
#include "Thermometer.h"
#include "Humidity.h"
#include "LED.h"
#include <DHTesp.h>
#include "PIRStatus.h"

//Pin set up
#define DHTPIN 4 // the pin value for the DHT11 sensor
#define DHTTYPE DHT11
const int MOTION_SENSOR = 18;    	// PIR sensor pin
const int MOTION_INDICATOR = 12; // TODO: LED pin, LED is not needed for task D! Change to buzzer maybe?
LED *led = new LED(23, 22, 21); // the LED which shows the status of the sensors, pins 23,22,21
const int DHT11_DELAY = 2000; // delay for the DHT11 sensor to take readings, must be 2 seconds
int DHT11Millis = 0; // time in millis since DHT11 sensor took readings

const int STATUS_UPDATE_DELAY = 5000; // delay for the status update, must be every 5 seconds
int statusMillis = 0; // time in millis since last status update

//Variable initialisation
bool firstLoop = true; //Variable to store if it is the first loop or not
int potVal = 0; // Variable to store temperature value
int humVal = 0; // Variable to store the humidity value
long unsigned int lowTime; //Variable for PIR sensor low time
const long unsigned int pauseTime = 5000; //TODO: 600,000 is 10 mins currently 5 secs
boolean isDelayActive = true;	// Prevents duplicate output to console
boolean getLowTime;
const int calibrationTime = 30; // 30 seconds for initialising the PIR Sensor

//Setting up the objects
Thermometer *thermometer = NULL;
Humidity *humidity = NULL;
DHTesp dht; // object to store the DHT11 sensor
TempAndHumidity tempHum; // the object to store the temperature and humidity values
TemperatureStatus tempStatus; // object to store the temperature status
HumidityStatus humStatus; // object to store the humidity status

PIRStatus motionSensorStatus = PIRStatus::VACANT; // object to store the PIR status


/**
 * This method returns a boolean as to whether the time that has passed is longer than the delay specified
 */
boolean timeDiff(unsigned long start, int specifiedDelay) {
	return (millis() - start >= specifiedDelay);
}

/**
 * This method is used at startup and initialises our sensors and pins
 */
void setup() {
	thermometer = new Thermometer(DHTPIN, led);
	humidity = new Humidity(DHTPIN, led);

	Serial.begin(115200); // @suppress("Ambiguous problem")
	dht.setup(DHTPIN, DHTesp::DHT11); // set up the DHT11 sensor

	//taskD setup
	// Setting pins and default values
	pinMode(MOTION_SENSOR, INPUT);
	pinMode(MOTION_INDICATOR, OUTPUT);
	digitalWrite(MOTION_SENSOR, LOW);

	// Waiting for the PIR Sensor to initialise
	Serial.print("Initialising PIR Sensor ");
	for (int i = 0; i < calibrationTime; i++) {
		Serial.print(".");
		delay(1000);
	}
	Serial.println("|");
	Serial.println("SENSOR ACTIVE");
	delay(50);
}

/**
 * This method reads the PIR sensor to see if movement has been detected and updates the status accordingly
 */
void motionSensor() {
	if (digitalRead(MOTION_SENSOR) == HIGH) {
		digitalWrite(MOTION_INDICATOR, HIGH); // TODO: LED is on while motion is sensed

		// Ensures we don't output OCCUPIED until the sensor has since been LOW
		if (isDelayActive) {
			isDelayActive = false;
			motionSensorStatus = PIRStatus::OCCUPIED;
			;
			Serial.println("---");
			Serial.println("OCCUPIED at ");
			Serial.print(millis() / 1000);
			Serial.println(" sec");
			delay(50);
		}
		getLowTime = true;
	}

	if (digitalRead(MOTION_SENSOR) == LOW) {
		digitalWrite(MOTION_INDICATOR, LOW); // LED is off when motion isn't sensed

		// Getting the time where motion stopped being picked up.
		if (getLowTime) {
			lowTime = millis();
			getLowTime = false; // make sure this is only done at the start of a LOW phase
		}
		// if motion isn't picked up for more than the given pauseTime, the room is assumed to be VACANT.
		if (!isDelayActive && (millis() - lowTime) > pauseTime) {
			// Ensures we don't output VACANT until the sensor has since been HIGH
			isDelayActive = true;
			motionSensorStatus = PIRStatus::VACANT;
			Serial.println("VACANT at ");
			Serial.print((millis()) / 1000);
			Serial.println(" sec");
			delay(50);
		}
	}
}

/**
 * This method occurs at startup and tests all sensors and I/O devices are working as expected
 */
void powerOnTest() {
	Serial.println("Power on!");
	tempHum = dht.getTempAndHumidity();
	if (tempHum.temperature == 0 || tempHum.temperature > 100
			|| isnan(tempHum.temperature)) {
		Serial.println("Temperature Error");
	}
	if (tempHum.humidity == 0 || tempHum.humidity == 100
			|| isnan(tempHum.humidity)) {
		Serial.println("Humidity Error");
	}
	firstLoop = false;
}

/**
 * This method will update the temp and hum status if it's been 2 seconds and update the LED according to the new statuses
 */
void tempAndHumSensor() {

	if (timeDiff(DHT11Millis, DHT11_DELAY)) { // only get readings every 2 seconds - this is needed for the DHT11 sensor as a minimum
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
void statusUpdate() {
	if (timeDiff(statusMillis, STATUS_UPDATE_DELAY)) {
		statusMillis = millis();
		Serial.println("----------------");
		Serial.println("Status Update:");
		Serial.print("Current Temperature: ");
		Serial.println(tempHum.temperature);
		Serial.print("Current Humidity: ");
		Serial.println(tempHum.humidity);
		Serial.print("Temperature Status: ");
		Serial.println(getTempStatus());
		Serial.print("Humidity Status: ");
		Serial.println(getHumStatus());
		Serial.print("PIR sensor status: ");
		Serial.println(getPIRStatus());
		Serial.println("----------------");
	}
}

/**
 * This method will return the current temperature status as a string
 */
String getTempStatus() {
	if (tempStatus == TemperatureStatus::GREEN) {
		return "GREEN";
	} else if (tempStatus == TemperatureStatus::AMBER) {
		return "AMBER";
	} else {
		return "RED";
	}
}

/**
 * This method will return the current Humidity status as a string
 */
String getHumStatus() {
	if (humStatus == HumidityStatus::GREEN) {
		return "GREEN";
	} else if (humStatus == HumidityStatus::AMBER) {
		return "AMBER";
	} else {
		return "RED";
	}
}

/**
 * This method will return the current PIR status as a string
 */
String getPIRStatus() {
	if (motionSensorStatus == PIRStatus::OCCUPIED) {
		return "OCCUPIED";
	} else {
		return "VACANT";
	}
}
/**
 * This method is our main loop logic
 */
void loop() {
//If it is the first loop run power on test
	if (firstLoop) {
		powerOnTest();
	}
//Else run normal system
	else {
		// get the temperature and humidity readings from the DHT11 sensor
		tempAndHumSensor();
		motionSensor(); //Call taskD code
		statusUpdate(); // report status update
	}
}
