#include "Thermometer.h"
#include "LED.h"
#include "Buzzer.h"
#include <Arduino.h>

Thermometer::Thermometer()
{
	// do nothing
}

Thermometer::Thermometer(int potPin, LED *led, BUZZER *buzzer)
{
	this->potPin = potPin;
	pinMode(this->potPin, INPUT);
	this->potVal = 0;

	this->led = led;
	this->buzzer = buzzer;
}

TemperatureStatus Thermometer::calculateStatus(double potVal, LED *led)
{
	led->lastTempStatus = led->currentTempStatus;

	if (potVal >= 18 && potVal <= 23)
	{ // If the value is between 18 and 23 degrees - GREEN
		led->currentTempStatus = TemperatureStatus::GREEN;
		if (led->tempStatusHasChanged())
		{
			Serial.println(
				"Temperature status has changed - status is now green!");
		}
		return TemperatureStatus::GREEN;
	}
	else if (potVal >= 16 && potVal <= 27)
	{ // If the value is between 16 and 27 degrees - YELLOW
		led->currentTempStatus = TemperatureStatus::AMBER;

		if (led->tempStatusHasChanged())
		{
			Serial.println(
				"Temperature status has changed - status is now amber!");
				buzzer->buzz();
		}
		return TemperatureStatus::AMBER;
	}
	else
	{ // Otherwise - RED
		led->currentTempStatus = TemperatureStatus::RED;

		if (led->tempStatusHasChanged())
		{
			Serial.println(
				"Temperature status has changed - status is now red!");
				buzzer->buzz();
		}
		return TemperatureStatus::RED;
	}
}

/**
 * This method will return the current temperature status as a string
 */
String Thermometer::getTempStatus(TemperatureStatus currentStatus)
{
	if (currentStatus == TemperatureStatus::GREEN)
	{
		return "GREEN";
	}
	else if (currentStatus == TemperatureStatus::AMBER)
	{
		return "AMBER";
	}
	else
	{
		return "RED";
	}
}
