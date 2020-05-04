#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#include <Arduino.h>
#include "LED.h"
#include "Buzzer.h"
#include "../enums/TemperatureStatus.h"

class Thermometer {
public:
	double potVal = 0;
	int potPin = 35;
	LED* led;
	BUZZER* buzzer;

	Thermometer();
	Thermometer(int potPin, LED *led, BUZZER* buzzer);
	TemperatureStatus calculateStatus(double potVal, LED *led);
	String getTempStatus(TemperatureStatus currentStatus);
};
#endif
