//#include "Arduino.h"
//
//enum MotionSensorState {
//	OCCUPIED, VACANT
//};
//
//const int CHECK_DELAY = 10000; // TODO: 10 seconds for demo, 10 minutes for submission
//const int LED_PIN = 13;
//const int MOTION_SENSOR = 2; //TODO: Currently simulated using a button
//MotionSensorState sensorCurrent;
//
//unsigned long int timeSinceOccupied;
//int counter = 0;
//bool occupied;
//
//void setup() {
//	pinMode(LED_PIN, OUTPUT);
//	pinMode(MOTION_SENSOR, INPUT);
//	Serial.begin(115200);
//	sensorCurrent = VACANT;
//	timeSinceOccupied = millis();
//}
//
//boolean timeDiff(unsigned long start, int specifiedDelay) {
//	return (millis() - start >= specifiedDelay);
//}
//
///*
// * TODO: LED is not needed for task D! This is only for demonstration purposes.
// * 	OCCUPIED/VACANT should be output by Task C.
// */
//void ledOn() {
//	digitalWrite(LED_PIN, HIGH);
//	// Sets to VACANT after CHECK_DELAY
//	if (timeDiff(timeSinceOccupied, CHECK_DELAY)) {
//		sensorCurrent = VACANT;
//	}
//	return;
//}
//
//void ledOff() {
//	digitalWrite(LED_PIN, LOW);
//	sensorCurrent = VACANT;
//	return;
//}
//
//void motionSensor(){
//	MotionSensorState sensorOld = sensorCurrent;
//
//		if (digitalRead(MOTION_SENSOR) == 1) {
//			sensorCurrent = OCCUPIED;
//		}
//
//		switch (sensorCurrent) {
//		case OCCUPIED:
//			ledOn();
//			break;
//
//		case VACANT:
//			ledOff();
//			break;
//		}
//
//		if (sensorOld != sensorCurrent) {
//			Serial.println("state change");
//			Serial.println(sensorCurrent);
//			timeSinceOccupied = millis();
//		}
//}
//
//// The loop function is called in an endless loop
//void loop() {
//	motionSensor();
//}
//
