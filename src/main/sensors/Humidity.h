#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include <arduino.h>
#include "LED.h"
#include "../enums/HumidityStatus.h"

class Humidity
{
public:
	double potVal = 0;
	int potPin = 4;
	LED *led;

	Humidity();
	Humidity(int potPin, LED *led);
	HumidityStatus calculateStatus(double potVal, LED *led);
	String getHumStatus(HumidityStatus humStatus);
};
#endif
