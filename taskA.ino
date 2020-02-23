#include "Arduino.h"
#include "Thermometer.h"
#include "Humidity.h"
#include "LED.h"
#include <DHTesp.h>

#define DHTPIN 4 // the pin value for the DHT11 sensor
#define DHTTYPE DHT11

enum MotionSensorState {
	OCCUPIED, VACANT
};

bool firstLoop = true; //Variable to store if it is the first loop or not
int potVal = 0; // Variable to store temperature value
int humVal = 0; // Variable to store the humidity value
const int CHECK_DELAY = 10000; // TODO: 10 seconds for demo, 10 minutes for submission
const int LED_PIN = 13;
const int MOTION_SENSOR = 2; //TODO: Currently simulated using a button
MotionSensorState sensorCurrent;

unsigned long int timeSinceOccupied;
int counter = 0;
bool occupied;

Thermometer *thermometer = NULL;
Humidity *humidity = NULL;
DHTesp dht; // object to store the DHT11 sensor
TempAndHumidity tempHum; // the object to store the temperature and humidity values

void setup() {
	thermometer = new Thermometer(DHTPIN);
	humidity = new Humidity(DHTPIN);

	Serial.begin(115200); // @suppress("Ambiguous problem")
	dht.setup(DHTPIN, DHTesp::DHT11); // set up the DHT11 sensor
	//TASK D setup
	pinMode(LED_PIN, OUTPUT);
	pinMode(MOTION_SENSOR, INPUT);
	sensorCurrent = VACANT;
	timeSinceOccupied = millis();
}

boolean timeDiff(unsigned long start, int specifiedDelay) {
	return (millis() - start >= specifiedDelay);
}

//Below is for TASK D. Can this be put into classes?
/*
 * TODO: LED is not needed for task D! This is only for demonstration purposes.
 * 	OCCUPIED/VACANT should be output by Task C.
 */
void ledOn() {
	digitalWrite(LED_PIN, HIGH);
	// Sets to VACANT after CHECK_DELAY
	if (timeDiff(timeSinceOccupied, CHECK_DELAY)) {
		sensorCurrent = VACANT;
	}
	return;
}

void ledOff() {
	digitalWrite(LED_PIN, LOW);
	sensorCurrent = VACANT;
	return;
}

void motionSensor() {
	MotionSensorState sensorOld = sensorCurrent;

	if (digitalRead(MOTION_SENSOR) == 1) {
		sensorCurrent = OCCUPIED;
	}

	switch (sensorCurrent) {
	case OCCUPIED:
		ledOn();
		break;

	case VACANT:
		ledOff();
		break;
	}

	if (sensorOld != sensorCurrent) {
		Serial.println("state change");
		Serial.println(sensorCurrent);
		timeSinceOccupied = millis();
	}
}

void loop() {
	//If it is the first loop run power on test
	if (firstLoop) {
		Serial.println("Power on!");
		tempHum = dht.getTempAndHumidity();
		if (tempHum.temperature == 0 || tempHum.temperature > 100) {
			Serial.println("Temperature Error");
		}
		if (tempHum.humidity == 0 || tempHum.humidity == 100) {
			Serial.println("Humidity Error");
		}
		firstLoop = false;
	}
	//Else run normal system
	else {
		// get the temperature and humidity readings from the DHT11 sensor
		tempHum = dht.getTempAndHumidity();

		// set LED colours for temp and humidity sensor
		thermometer->setLEDColour(tempHum.temperature, thermometer->led);
		humidity->setLEDColour(tempHum.humidity, humidity->led);

		//Call motion sensor method (TASKD)
		motionSensor();
		delay(2000); // delay for 2 seconds - this is needed for the DHT11 sensor as a minimum
	}
}

