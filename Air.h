#ifndef AIR_H_
#define AIR_H_

#include <arduino.h>
#include "LED.h"
class Air {

public:
	int potVal = 0;
	int potPin = A2;
	LED *led;

	Air();
	Air(int potPin);
	int readSensor(int potPin, int potVal);
	void setLEDColour(int potVal, LED* led);
	void setColour(int red, int blue, int green);
};
#endif
