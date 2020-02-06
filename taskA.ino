#include <Arduino.h>
#include <pins_arduino.h>

enum State {
  LED_ON,
  LED_OFF
};

State current;
const int LED_PIN = LED_BUILTIN;
const int LED_DELAY = 1000;
unsigned long lastChangeTime;

boolean timeDiff(unsigned long start, int specifiedDelay) {
  return (millis()-start >= specifiedDelay);
}

void setup() {
  current = LED_OFF;
  pinMode(LED_PIN, OUTPUT);
  lastChangeTime=0;
}

void loop() {
  State old = current;
  switch (current){
    case LED_OFF:
      digitalWrite(LED_PIN, LOW);
      if (timeDiff(lastChangeTime, LED_DELAY))
        current = LED_ON;
    break;

    case LED_ON:
      digitalWrite(LED_PIN, HIGH);
      if (timeDiff(lastChangeTime, LED_DELAY))
        current = LED_OFF;
    break;
  }

  if (old != current)
    lastChangeTime = millis();
}

