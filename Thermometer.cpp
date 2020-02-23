#include "Thermometer.h"
#include "LED.h"
#include <Arduino.h>

Thermometer::Thermometer() {
	// do nothing
}

Thermometer::Thermometer(int potPin, LED* led) {
	this->potPin = potPin;
	pinMode(this->potPin, INPUT);
	this->potVal = 0;

	this->led = led;
}

TemperatureStatus Thermometer::calculateStatus(int potVal, LED *led) {
	led->lastTempStatus = led->currentTempStatus;

	if (potVal >= 18 && potVal <= 23) { // If the value is between 18 and 23 degrees - GREEN
		led->currentColour = LEDColour::GREEN;
		led->currentTempStatus = TemperatureStatus::GREEN;
		if (led->tempStatusHasChanged()) {
			Serial.println("Temperature status has changed - status is now green!");
		}
		return TemperatureStatus::GREEN;
	} else if (potVal >= 16 && potVal <= 27) { // If the value is between 16 and 27 degrees - YELLOW
		led->currentColour = LEDColour::YELLOW;
		led->currentTempStatus = TemperatureStatus::AMBER;

		if (led->tempStatusHasChanged()) {
			Serial.println("Temperature status has changed - status is now amber!");
		}
		return TemperatureStatus::AMBER;
	} else { // Otherwise - RED
		led->currentColour = LEDColour::RED;
		led->currentTempStatus = TemperatureStatus::RED;

		if (led->tempStatusHasChanged()) {
			Serial.println("Temperature status has changed - status is now red!");
		}
		return TemperatureStatus::RED;
	}
}
