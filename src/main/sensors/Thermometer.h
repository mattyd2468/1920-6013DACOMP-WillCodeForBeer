#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include <Arduino.h>
#include "LED.h"
#include "../enums/TemperatureStatus.h"

class Thermometer
{
public:
	double potVal = 0;
	int potPin = 35;
	LED *led;

	Thermometer();
	Thermometer(int potPin, LED *led);
	TemperatureStatus calculateStatus(double potVal, LED *led);
	String getTempStatus(TemperatureStatus currentStatus);
};
#endif
