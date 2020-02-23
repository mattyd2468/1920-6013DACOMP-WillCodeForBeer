#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include <arduino.h>
#include "LED.h"

class Humidity {
public:

	int potVal = 0;
	int potPin = 4;
	LED* led;

	Humidity();
	Humidity(int potPin, LED *led);
	HumidityStatus calculateStatus(int potVal, LED *led);
};
#endif
