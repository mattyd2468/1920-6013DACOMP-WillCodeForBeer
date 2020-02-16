#include "Arduino.h"
#include "Thermometer.h"
#include "Humidity.h"
#include "Air.h"
#include "LED.h"

String errorMsg = "Error | There is an issue with the";
int potPin = A0; // Potentiometer output connected to analog pin A0
int potVal = 0; // Variable to store the input from the potentiometer
Thermometer *thermometer = NULL;

int humPin = A1; // Potentiometer output connected to analog pin A1
int humVal = 0; // Variable to store the input from the potentiometer
Humidity *humidity = NULL;

int airPin = A2; // Potentiometer output connected to analog pin A2
int airVal = 0; // Variable to store the input from the potentiometer
Air *airSensor = NULL;

void setup() {
	thermometer = new Thermometer(potPin);
	humidity = new Humidity(humPin);
	airSensor = new Air(airPin);
	Serial.begin(115200);
	Serial.println("Power on!");
}

void loop() {
	//Check values are being received. Display suitable error
	if (potVal == 0) {
		Serial.println(errorMsg + "Thermometer");
	}
	if (humVal == 0) {
		Serial.println(errorMsg + "Humidity Sensor");
	}
	if (airVal == 0){
			Serial.println(errorMsg + "Air Sensor");
		}

	// thermometer sensor
	potVal = thermometer->readSensor(potPin, potVal); // read the thermometer sensor value at the input pin
	thermometer->setLEDColour(potVal, thermometer->led);

	// humidity sensor
	humVal = humidity->readSensor(humPin, humVal); // read the humidity sensor value at the input pin
	humidity->setLEDColour(humVal, humidity->led);

	// air sensor
	airVal = airSensor->readSensor(airPin, airVal); // read the air sensor value at the input pin
	airSensor->setLEDColour(potVal, airSensor->led);

	delay(1000); // delay for 1 second
}
