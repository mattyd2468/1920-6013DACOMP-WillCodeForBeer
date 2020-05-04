#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include <arduino.h>
#include "LED.h"
#include "Buzzer.h"
#include "../enums/HumidityStatus.h"

class Humidity {
public:

	double potVal = 0;
	int potPin = 4;
	LED* led;
	BUZZER* buzzer;

	Humidity();
	Humidity(int potPin, LED *led, BUZZER* buzzer);
	HumidityStatus calculateStatus(double potVal, LED *led);
	String getHumStatus(HumidityStatus humStatus);
};
#endif
