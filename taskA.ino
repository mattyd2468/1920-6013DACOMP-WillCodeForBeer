#include "Arduino.h"
#include "Thermometer.h"
#include "Humidity.h"
#include "LED.h"
#include <DHTesp.h>

#define DHTPIN 4 // the pin value for the DHT11 sensor
#define DHTTYPE DHT11
bool firstLoop = true; //Variable to store if it is the first loop or not
int potVal = 0; // Variable to store temperature value
int humVal = 0; // Variable to store the humidity value

//taskD variables
long unsigned int lowTime;
const long unsigned int pauseTime = 5000;	//TODO: 600,000 is 10 mins

boolean isDelayActive = true;	// Prevents duplicate output to console
boolean getLowTime;

const int MOTION_SENSOR = 18;    	// PIR sensor pin
const int MOTION_INDICATOR = 12;	// TODO: LED pin, LED is not needed for task D!
const int calibrationTime = 30; 	// 30 seconds for initialising the PIR Sensor

Thermometer *thermometer = NULL;
Humidity *humidity = NULL;
DHTesp dht; // object to store the DHT11 sensor
TempAndHumidity tempHum; // the object to store the temperature and humidity values
LED *led = new LED(23, 22, 21); // the LED which shows the status of the sensors, pins 23,22,21

TemperatureStatus tempStatus; // object to store the temperature status
HumidityStatus humStatus; // object to store the humidity status

//taskD method
void motionSensor() {
	if (digitalRead(MOTION_SENSOR) == HIGH) {
		digitalWrite(MOTION_INDICATOR, HIGH); // TODO: LED is on while motion is sensed

		// Ensures we don't output OCCUPIED until the sensor has since been LOW
		if (isDelayActive) {
			isDelayActive = false;
			Serial.println("---");
			Serial.print("OCCUPIED at ");
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
			Serial.print("VACANT at ");
			Serial.print((millis()) / 1000);
			Serial.println(" sec");
			delay(50);
		}
	}
}

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
		tempStatus = thermometer->calculateStatus(tempHum.temperature, led);
		humStatus = humidity->calculateStatus(tempHum.humidity, led);

		led->setLEDColour(tempStatus, humStatus);
		delay(2000); // delay for 2 seconds - this is needed for the DHT11 sensor as a minimum
		motionSensor(); //Call taskD code
	}
}
