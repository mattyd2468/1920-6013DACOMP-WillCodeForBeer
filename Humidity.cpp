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

	this->led = new LED(19, 18, 17);
}

void Humidity::setLEDColour(int potVal, LED* led) {

	if (potVal >= 34 && potVal <= 60) { // Humidity is between 34% and 60% - GREEN
		led->setColour(0, 255, 0); // green
		led->currentColour = LEDColour::GREEN;
		if (led->colourHasChanged()) {
			Serial.println("Humidity status has changed - status is now green!");
		}
	} else if (potVal >= 25 && potVal <= 75) { // Humidity is between 25% and 75% - YELLOW
		led->setColour(255, 255, 0); // yellow
		led->currentColour = LEDColour::YELLOW;
		if (led->colourHasChanged()) {
			Serial.println("Humidity status has changed - status is now amber!");
		}
	} else { // Humidity is in RED level
		led->setColour(255, 0, 0); // red
		led->currentColour = LEDColour::RED;
		if (led->colourHasChanged()) {
			Serial.println("Humidity status has changed - status is now red!");
		}
	}
}
