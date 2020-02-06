#include <Arduino.h>
#include <pins_arduino.h>

enum State {
  ON,
  OFF
};

State LEDcurrent;
const int LED_PIN = LED_BUILTIN;


void setup() {
  LEDcurrent = ON;
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Power on! ");

}

void loop() {

	digitalWrite(LED_PIN, HIGH);
}

