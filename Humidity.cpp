#include "Humidity.h"
#include "LED.h"
#include <Arduino.h>

Humidity::Humidity() {
	// do nothing
}

Humidity::Humidity(int potPin) {
	this->potPin = potPin;
	pinMode(this->potPin, INPUT);
	this->potVal = 0;

	this->led = new LED(7, 6, 5);
}

int Humidity::readSensor(int potPin, int potVal) {
	potVal = analogRead(potPin); // read the potentiometer value at the input pin
	return potVal;
}

void Humidity::setLEDColour(int potVal, LED* led) {

	potVal = (potVal / 1023.0) * 100; // convert the value of potVal to a percentage

	if (potVal >= 34 && potVal <= 60) { // Lowest third of the potentiometer's range (34%) GREEN
		led->setColour(0, 255, 0); // green
		led->currentColour = LEDColour::GREEN;
		if (led->colourHasChanged()) {
			Serial.println("Colour has changed to green!");
		}
	} else if (potVal >= 25 && potVal <= 75) { // Middle third of potentiometer's range (341-681) YELLOW
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
