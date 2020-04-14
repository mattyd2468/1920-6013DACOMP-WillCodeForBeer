#include <Arduino.h>
#include "LED.h"

LED::LED()
{
	// do nothing
}
// Setting PWM frequency, channels and bit resolution
const int freq = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
// Bit resolution 2^8 = 256
const int resolution = 8;

LED::LED(int redPin, int greenPin, int bluePin)
{
	this->redPin = redPin;
	this->greenPin = greenPin;
	this->bluePin = bluePin;

	pinMode(this->redPin, OUTPUT);
	pinMode(this->greenPin, OUTPUT);
	pinMode(this->bluePin, OUTPUT);

	ledcSetup(redChannel, freq, resolution);
	ledcSetup(greenChannel, freq, resolution);
	ledcSetup(blueChannel, freq, resolution);

	// attach the channel to the GPIO to be controlled
	ledcAttachPin(redPin, redChannel);
	ledcAttachPin(greenPin, greenChannel);
	ledcAttachPin(bluePin, blueChannel);

	// set the LED colour and temp and hum statuses for setup
	currentColour = LEDColour::GREEN;
	lastColour = currentColour;
	currentTempStatus = TemperatureStatus::GREEN;
	lastTempStatus = currentTempStatus;
	currentHumStatus = HumidityStatus::GREEN;
	lastHumStatus = currentHumStatus;

	greenVal = 0;
	redVal = 0;
	blueVal = 0;
}

void LED::setLEDColour(TemperatureStatus tempStatus, HumidityStatus humStatus)
{

	if (tempStatus == TemperatureStatus::RED || humStatus == HumidityStatus::RED)
	{
		currentColour = LEDColour::RED;
		setColour(255, 0, 0); // set LED to red
	}
	else if (tempStatus == TemperatureStatus::AMBER || humStatus == HumidityStatus::AMBER)
	{
		currentColour = LEDColour::YELLOW;
		setColour(255, 255, 0); // set LED to amber
	}
	else if(tempStatus == TemperatureStatus::GREEN || humStatus == HumidityStatus::GREEN)
	{
		currentColour = LEDColour::GREEN;
		setColour(0, 255, 0); // set LED to green
	}
}

void LED::setColour(int redVal, int greenVal, int blueVal)
{
	ledcWrite(redChannel, redVal);
	ledcWrite(greenChannel, greenVal);
	ledcWrite(blueChannel, blueVal);

	lastColour = currentColour;

}

boolean LED::tempStatusHasChanged()
{
	return lastTempStatus != currentTempStatus;
}

boolean LED::humStatusHasChanged()
{
	return lastHumStatus != currentHumStatus;
}
