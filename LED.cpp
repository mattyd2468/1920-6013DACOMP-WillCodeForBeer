#include <Arduino.h>
#include "LED.h"

LED::LED() {
	// do nothing
}

LED::LED(int redPin, int greenPin, int bluePin) {
	this->redPin = redPin;
	this->greenPin = greenPin;
	this->bluePin = bluePin;

	pinMode(this->redPin, OUTPUT);
	pinMode(this->greenPin, OUTPUT);
	pinMode(this->bluePin, OUTPUT);

	currentColour = LEDColour::GREEN;
	lastColour = currentColour;

	greenVal = 0;
	redVal = 0;
	blueVal = 0;
}

void LED::setColour(int redVal, int greenVal, int blueVal) {
	analogWrite(redPin, redVal);
	analogWrite(greenPin, greenVal);
	analogWrite(bluePin, blueVal);

	lastColour = currentColour;
}


boolean LED::colourHasChanged() {
	return lastColour != currentColour;
}

