#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include <arduino.h>
#include "LED.h"
#include "TemperatureStatus.h"

class Thermometer {
public:
	int potVal = 0;
	int potPin = 35;
	LED* led;

	Thermometer();
	Thermometer(int potPin, LED *led);
	TemperatureStatus calculateStatus(int potVal, LED *led);
	String getTempStatus(TemperatureStatus currentStatus);
};
#endif
