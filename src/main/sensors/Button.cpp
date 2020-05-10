#include "Button.h"
#include <../src/main/enums/ButtonState.h>

Button::Button(){};

Button::Button(int PUSH_BUTTON_PIN, int BOUNCE_DELAY_MS, ButtonState bouncedState, ButtonState debouncedState, long buttonLastChange) {
    this->PUSH_BUTTON_PIN = PUSH_BUTTON_PIN;
    this->BOUNCE_DELAY_MS = BOUNCE_DELAY_MS;
    this->bouncedState = bouncedState;
    this->debouncedState = debouncedState;
    this->buttonLastChange = buttonLastChange;
    pinMode(this->PUSH_BUTTON_PIN, INPUT);
}

boolean Button::timeDifference(unsigned long start, int specifiedDelay)
{
	return (millis() - start >= specifiedDelay);
}

/**
 * This method will retrieve the state of the button, 
 * ensuring the button is held down for ~1 second.
 */
ButtonState Button::getButtonState() {
	ButtonState now = OFF;
	if (digitalRead(this->PUSH_BUTTON_PIN)) {
		now = ON;
	}

	if (now != bouncedState) {
		buttonLastChange = millis();
		bouncedState = now;
	}

	if (timeDifference(this->buttonLastChange, this->BOUNCE_DELAY_MS)) {
		debouncedState = now;
	}
	return debouncedState;
}