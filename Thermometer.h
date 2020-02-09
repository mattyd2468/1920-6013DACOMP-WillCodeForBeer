#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include <arduino.h>
#include "LED.h"
class Thermometer {

public:
	int potVal = 0;
	int potPin = A0;
	LED *led;

	Thermometer();
	Thermometer(int potPin);
	int readSensor(int potPin, int potVal);
	void setLEDColour(int potVal, LED* led);
	void setColour(int red, int blue, int green);
};
#endif
