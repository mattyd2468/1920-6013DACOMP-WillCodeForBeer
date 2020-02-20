#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include <arduino.h>
#include "LED.h"
#include "DHTesp.h"
class Thermometer {

public:
	double potVal = 0;
	int potPin = 35;
	LED *led;

	Thermometer();
	Thermometer(int potPin);
	int readSensor(DHTesp dht);
	void setLEDColour(double potVal, LED* led);
	void setColour(int red, int blue, int green);
};
#endif
