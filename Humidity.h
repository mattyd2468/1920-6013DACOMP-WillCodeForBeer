#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include <arduino.h>
#include "LED.h"
class Humidity {

public:
	int potVal = 0;
	int potPin = A1;
	LED *led;

	Humidity();
	Humidity(int potPin);
	int readSensor(int potPin, int potVal);
	void setLEDColour(int potVal, LED* led);
	void setColour(int red, int blue, int green);
};
#endif
