#ifndef BUTTON_H_
#define BUTTON_H_

#include <arduino.h>
#include <../src/main/enums/ButtonState.h>

class Button {
public:

    int PUSH_BUTTON_PIN = 14;		// Push button pin
    ButtonState outputButtonCurrent;	// The current state of the button
    int BOUNCE_DELAY_MS = 1000;	// Delays the button reading by 1 second for debouncing. 
    ButtonState debouncedState = OFF;	// The debounced state of the button, defaults to off.
    ButtonState bouncedState = OFF;		// The bounced state of the button, defaults to off.
    long buttonLastChange;				// The duration since the last change in state of the button.

    Button();
    Button(int PUSH_BUTTON_PIN, int BOUNCE_DELAY_MS, ButtonState bouncedState, ButtonState debouncedState, long buttonLastChange);

    ButtonState getButtonState();

private:
    boolean timeDifference(unsigned long start, int delay);

};
#endif