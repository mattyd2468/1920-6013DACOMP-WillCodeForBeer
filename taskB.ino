#include "Arduino.h"
#include <pins_arduino.h>

// This file is commented out as it causes compile errors as only 1 setup and loop method are allowed per project, comment out task A and uncomment this task to test!
// Also this only has 1 led hooked up, we do need 3 for this task so it is still in progress!

//int redPin = 10; // connected to digital pin 10
//int greenPin = 9;// connected to digital pin 9
//int bluePin = 8;// connected to digital pin 8
//
//// Program variables
//int redVal = 0;   // Variables to store the values to send to the pins
//int grnVal = 0;
//int bluVal = 0;
//
//int potPin = A0; // Potentiometer output connected to analog pin A0
//int potVal = 0; // Variable to store the input from the potentiometer
//
//enum LEDColour {
//	RED, YELLOW, GREEN
//};
//
//void setup() {
//	pinMode(redPin, OUTPUT);
//	pinMode(greenPin, OUTPUT);
//	pinMode(bluePin, OUTPUT);
//	Serial.begin(115200);
//}
//
//void loop() {
//	potVal = analogRead(potPin); // read the potentiometer value at the input pin
//	setLEDColour(potVal); // set the colour of the LED based on this
//	delay(5000); // delay for 5 seconds
//}
//
//LEDColour lastColour; // the last colour of the LED
//LEDColour currentColour; // the current colour of the LED
//
//void setLEDColour(int potVal) {
//	potVal = (potVal / 1023.0) * 100; // convert the value of potVal to a percentage
//
//	if (potVal >= 34 && potVal <= 60) { // Between 34% and 60% of the potentiometer's range - GREEN
//		setColor(0, 255, 0); // green
//		currentColour = LEDColour::GREEN;
//		if (colourHasChanged()) {
//			Serial.println("Colour has changed to green!");
//		}
//	} else if (potVal >= 25 && potVal <= 75) { // Between 25% and 75% of the potentiometer's range - YELLOW
//		setColor(255, 255, 0); // yellow
//		currentColour = LEDColour::YELLOW;
//		if (colourHasChanged()) {
//			Serial.println("Colour has changed to Amber!");
//		}
//	} else { // Otherwise it is in the RED
//		setColor(255, 0, 0); // red
//		currentColour = LEDColour::RED;
//		if (colourHasChanged()) {
//			Serial.println("Colour has changed to red!");
//		}
//	}
//	lastColour = currentColour;
//}
//void setColor(int redVal, int greenVal, int blueVal) {
//	analogWrite(redPin, redVal);
//	analogWrite(greenPin, greenVal);
//	analogWrite(bluePin, blueVal);
//}
//
//boolean colourHasChanged() {
//	return lastColour != currentColour;
//}
