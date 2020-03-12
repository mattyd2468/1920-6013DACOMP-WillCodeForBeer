#ifndef LED_H_
#define LED_H_

#include "../enums/TemperatureStatus.h"
#include "../enums/HumidityStatus.h"
#include <DHTesp.h>

enum class LEDColour {
	GREEN, YELLOW, RED
};

class LED {

public:
	unsigned int redPin;
	unsigned int greenPin;
	unsigned int bluePin;

	// Program variables
	int redVal;   // Variables to store the values to send to the pins
	int greenVal;
	int blueVal;

	LEDColour lastColour;
	LEDColour currentColour;

	TemperatureStatus lastTempStatus;
	TemperatureStatus currentTempStatus;
	HumidityStatus lastHumStatus;
	HumidityStatus currentHumStatus;

	LED();
	LED(int redPin, int bluePin, int greenPin);

	boolean tempStatusHasChanged();
	boolean humStatusHasChanged();

	void setLEDColour(TemperatureStatus tempStatus, HumidityStatus humStatus);
private:
	void setColour(int redVal, int blueVal, int greenVal);
};
#endif
