//#include <Arduino.h>
//
//long unsigned int lowTime;
//const long unsigned int pauseTime = 5000;	//TODO: 600,000 is 10 mins
//
//boolean isDelayActive = true;	// Prevents duplicate output to console
//boolean getLowTime;
//
//const int MOTION_SENSOR = 4;    	// PIR sensor pin
//const int MOTION_INDICATOR = 12;	// TODO: LED pin, LED is not needed for task D!
//const int calibrationTime = 30; 	// 30 seconds for initialising the PIR Sensor
//
//void setup() {
//	Serial.begin(115200);
//	// Setting pins and default values
//	pinMode(MOTION_SENSOR, INPUT);
//	pinMode(MOTION_INDICATOR, OUTPUT);
//	digitalWrite(MOTION_SENSOR, LOW);
//
//	// Waiting for the PIR Sensor to initialise
//	Serial.print("Initialising PIR Sensor ");
//	for (int i = 0; i < calibrationTime; i++) {
//		Serial.print(".");
//		delay(1000);
//	}
//	Serial.println("|");
//	Serial.println("SENSOR ACTIVE");
//	delay(50);
//}
//
//void motionSensor() {
//	if (digitalRead(MOTION_SENSOR) == HIGH) {
//		digitalWrite(MOTION_INDICATOR, HIGH); // TODO: LED is on while motion is sensed
//
//		// Ensures we don't output OCCUPIED until the sensor has since been LOW
//		if (isDelayActive) {
//			isDelayActive = false;
//			Serial.println("---");
//			Serial.print("OCCUPIED at ");
//			Serial.print(millis() / 1000);
//			Serial.println(" sec");
//			delay(50);
//		}
//		getLowTime = true;
//	}
//
//	if (digitalRead(MOTION_SENSOR) == LOW) {
//		digitalWrite(MOTION_INDICATOR, LOW); // LED is off when motion isn't sensed
//
//		// Getting the time where motion stopped being picked up.
//		if (getLowTime) {
//			lowTime = millis();
//			getLowTime = false; // make sure this is only done at the start of a LOW phase
//		}
//		// if motion isn't picked up for more than the given pauseTime, the room is assumed to be VACANT.
//		if (!isDelayActive && (millis() - lowTime) > pauseTime) {
//			// Ensures we don't output VACANT until the sensor has since been HIGH
//			isDelayActive = true;
//			Serial.print("VACANT at ");
//			Serial.print((millis()) / 1000);
//			Serial.println(" sec");
//			delay(50);
//		}
//	}
//}
//
//void loop() {
//	motionSensor();
//}
