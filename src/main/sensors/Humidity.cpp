#include "Humidity.h"
#include "LED.h"
#include <Arduino.h>
#include <DHTesp.h>

Humidity::Humidity() {
	// do nothing
}

Humidity::Humidity(int potPin, LED* led) {
	this->potPin = potPin;
	pinMode(this->potPin, INPUT);
	this->potVal = 0;

	this->led = led;
}

HumidityStatus Humidity::calculateStatus(double potVal, LED* led) {
	led->lastHumStatus = led->currentHumStatus;

	if (potVal >= 34 && potVal <= 60) { // Humidity is between 34% and 60% - GREEN
		led->currentColour = LEDColour::GREEN;
		led->currentHumStatus = HumidityStatus::GREEN;
		if (led->humStatusHasChanged()) {
			Serial.println("Humidity status has changed - status is now green!");
		}
		return HumidityStatus::GREEN;
	} else if (potVal >= 25 && potVal <= 75) { // Humidity is between 25% and 75% - YELLOW
		led->currentColour = LEDColour::YELLOW;
		led->currentHumStatus = HumidityStatus::AMBER;

		if (led->humStatusHasChanged()) {
			Serial.println("Humidity status has changed - status is now amber!");
		}
		return HumidityStatus::AMBER;

	} else { // Humidity is in RED level
		led->currentColour = LEDColour::RED;
		led->currentHumStatus = HumidityStatus::RED;

		if (led->humStatusHasChanged()) {
			Serial.println("Humidity status has changed - status is now red!");
		}
		return HumidityStatus::RED;
	}
}


/**
 * This method will return the current Humidity status as a string
 */
String Humidity::getHumStatus(HumidityStatus humStatus) {
	if (humStatus == HumidityStatus::GREEN) {
		return "GREEN";
	} else if (humStatus == HumidityStatus::AMBER) {
		return "AMBER";
	} else {
		return "RED";
	}
}

