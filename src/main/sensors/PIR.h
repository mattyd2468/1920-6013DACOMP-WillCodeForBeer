#ifndef PIR_H_
#define PIR_H_

#include <arduino.h>
#include "../enums/PIRStatus.h"
#include "../SDCard.h"

class PIR {
public:

	const int calibrationTime = 30; // 30 seconds for initialising the PIR Sensor
	long unsigned int lowTime = 0; //Variable for PIR sensor low time
	const long unsigned int pauseTime = 5000; //TODO: 600,000 is 10 mins currently 5 secs
	boolean isDelayActive = true;	// Prevents duplicate output to console
	boolean getLowTime = false;
	int MOTION_SENSOR; // the motion sensor pin
	PIRStatus motionSensorStatus = PIRStatus::VACANT;

	PIR();
	PIR(int potPin);

	void motionSensor(SDCard* sdcard, vector<String> logging);
	String getPIRStatus();
};
#endif
