#include "PIR.h"
#include "LED.h"
#include <Arduino.h>

PIR::PIR()
{
	// do nothing
}

PIR::PIR(int MOTION_SENSOR)
{
	this->MOTION_SENSOR = MOTION_SENSOR;

	pinMode(MOTION_SENSOR, INPUT);
	digitalWrite(MOTION_SENSOR, LOW);

	// Waiting for the PIR Sensor to initialise
	Serial.print("Initialising PIR Sensor ");
	for (int i = 0; i < this->calibrationTime; i++)
	{
		Serial.print(".");
		delay(1000);
	}
	Serial.println("|");
	Serial.println("SENSOR ACTIVE");
	delay(50);
}

/**
 * This method reads the PIR sensor to see if movement has been detected and updates the status accordingly
 */
void PIR::motionSensor(SDCard* sdcard, vector<String> logging)
{

	if (digitalRead(MOTION_SENSOR) == HIGH)
	{

		// Ensures we don't output OCCUPIED until the sensor has since been LOW
		if (this->isDelayActive)
		{
			this->isDelayActive = false;
			this->motionSensorStatus = PIRStatus::OCCUPIED;
			Serial.println("---");
			Serial.println("OCCUPIED at ");
			Serial.print(millis() / 1000);
			Serial.println(" sec");
			sdcard->storePIRReadings("OCCUPIED", logging);
			delay(50);
		}
		this->getLowTime = true;
	}

	if (digitalRead(MOTION_SENSOR) == LOW)
	{

		// Getting the time where motion stopped being picked up.
		if (this->getLowTime)
		{
			this->lowTime = millis();
			this->getLowTime = false; // make sure this is only done at the start of a LOW phase
		}
		// if motion isn't picked up for more than the given pauseTime, the room is assumed to be VACANT.
		if (!this->isDelayActive && (millis() - this->lowTime) > this->pauseTime)
		{
			// Ensures we don't output VACANT until the sensor has since been HIGH
			this->isDelayActive = true;
			this->motionSensorStatus = PIRStatus::VACANT;
			Serial.println("VACANT at ");
			Serial.print((millis()) / 1000);
			Serial.println(" sec");
			sdcard->storePIRReadings("VACANT", logging);
			delay(50);
		}
	}
}

/**
 * This method will return the current PIR status as a string
 */
String PIR::getPIRStatus()
{
	if (motionSensorStatus == PIRStatus::OCCUPIED)
	{
		return "OCCUPIED";
	}
	else
	{
		return "VACANT";
	}
}
