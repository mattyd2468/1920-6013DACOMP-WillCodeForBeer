#include "Air.h"
#include "LED.h"
#include <Arduino.h>

Air::Air() {
	// do nothing
}

Air::Air(int potPin) {
	this->potPin = potPin;
	pinMode(this->potPin, INPUT);
	this->potVal = 0;

	this->led = new LED(4, 3, 2);
}

int Air::readSensor(int potPin, int potVal) {
	potVal = analogRead(potPin); // read the potentiometer value at the input pin
	return potVal;
}

void Air::setLEDColour(int potVal, LED* led) {

	if (potVal <9) { // If the value is less than 9ppm CO -  GREEN
		led->setColour(0, 255, 0); // green
		led->currentColour = LEDColour::GREEN;
		if (led->colourHasChanged()) {
			Serial.println("Colour has changed to green!");
		}
	} else if (potVal <= 25) { // If the value is less than 26ppm CO -  YELLOW
		led->setColour(255, 255, 0); // yellow
		led->currentColour = LEDColour::YELLOW;
		if (led->colourHasChanged()) {
			Serial.println("Colour has changed to Amber!");
		}
	} else { // If the value is greater than 25ppm CO - RED
		led->setColour(255, 0, 0); // red
		led->currentColour = LEDColour::RED;
		if (led->colourHasChanged()) {
			Serial.println("Colour has changed to red!");
		}
	}
}
