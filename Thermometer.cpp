#include "Thermometer.h"
#include "LED.h"
#include <Arduino.h>

Thermometer::Thermometer() {
	// do nothing
}

Thermometer::Thermometer(int potPin) {
	this->potPin = potPin;
	pinMode(this->potPin, INPUT);
	this->potVal = 0;

	this->led = new LED(10, 9, 8);
}

int Thermometer::readSensor(int potPin, int potVal) {
	potVal = analogRead(potPin); // read the potentiometer value at the input pin
	return potVal;
}

int calculateTempInCelcius(int potVal) {
	double Temp;
	Temp = log(((10240000 / potVal) - 10000));
	Temp = 1/ (0.001129148+ (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp);
	Temp = Temp - 273.15;              // Convert Kelvin to Celsius
	return Temp;
}

void Thermometer::setLEDColour(int potVal, LED *led) {

	potVal = calculateTempInCelcius(potVal);

	if (potVal >= 34 && potVal <= 60) { // If the value is between 18 and 23 degrees - GREEN
		led->setColour(0, 255, 0); // green
		led->currentColour = LEDColour::GREEN;
		if (led->colourHasChanged()) {
			Serial.println("Colour has changed to green!");
		}
	} else if (potVal >= 25 && potVal <= 75) { // If the value is between 16 and 27 degrees - YELLOW
		led->setColour(255, 255, 0); // yellow
		led->currentColour = LEDColour::YELLOW;
		if (led->colourHasChanged()) {
			Serial.println("Colour has changed to Amber!");
		}
	} else { // Upper third of potentiometer"s range (682-1023) RED
		led->setColour(255, 0, 0); // red
		led->currentColour = LEDColour::RED;
		if (led->colourHasChanged()) {
			Serial.println("Colour has changed to red!");
		}
	}
}
