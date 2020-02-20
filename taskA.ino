#include "Arduino.h"
#include "Thermometer.h"
#include "Humidity.h"
#include "LED.h"
#include <DHTesp.h>

#define DHTPIN 4 // the pin value for the DHT11 sensor
#define DHTTYPE DHT11

bool firstLoop = true;
int potVal = 0; // Variable to store temperature value
int humVal = 0; // Variable to store the humidity value

Thermometer *thermometer = NULL;
Humidity *humidity = NULL;
DHTesp dht; // object to store the DHT11 sensor
TempAndHumidity tempHum; // the object to store the temperature and humidity values

void setup() {
	thermometer = new Thermometer(DHTPIN);
	humidity = new Humidity(DHTPIN);

	Serial.begin(115200); // @suppress("Ambiguous problem")
	dht.setup(DHTPIN, DHTesp::DHT11); // set up the DHT11 sensor
}

void loop() {
	//if first loop run power on test
	if (firstLoop) {
		Serial.println("Power on!");
		tempHum = dht.getTempAndHumidity();
		if (tempHum.temperature == 0 || tempHum.temperature > 100){
			Serial.println("Temperature Error");
		}
		if (tempHum.humidity == 0 || tempHum.humidity == 100){
					Serial.println("Humidity Error");
				}
		firstLoop = false;
	}
	//else run normal system
	else {
		// get the temperature and humidity readings from the DHT11 sensor
		tempHum = dht.getTempAndHumidity();

		// set LED colours for temp and humidity sensor
		thermometer->setLEDColour(tempHum.temperature, thermometer->led);
		humidity->setLEDColour(tempHum.humidity, humidity->led);

		delay(2000); // delay for 2 seconds - this is needed for the DHT11 sensor as a minimum
	}
}
