#ifndef BUZZER_H_
#define BUZZER_H_


#include <arduino.h>
#include "PIR.h"
#include "Thermometer.h"
#include "Humidity.h"

class BUZZER {
    public:
    const int BUZZER_PIN = 25; //Buzzer pin
    const int AMBER_ALERT_SOUND_DELAY = 30000; //Audible alert every 30 secs for amber alert
    const int RED_ALERT_SOUND_DELAY = 5000; // Audible alert every 5 secs for red alert
    int alertMillis = 0; // time in millis since last sound
    const int freq = 2000; //buzzer set up. Doesnt need to change
    const int channel = 3; //buzzer set up. Set to 3 becasue 0,1 & 2 used by LED
    const int resolution = 8; //buzzer set up. Doesnt need to change
    const int dutyCycle = 128; //buzzer 128 means noise. Set to 0 for silence
    PIR *pir;
    Thermometer *thermometer;
    Humidity *humidity;

    BUZZER();
    BUZZER(PIR *pir, Thermometer *thermometer, Humidity *humidity);

    void buzz();
    boolean timeDiff(unsigned long start, int specifiedDelay);
    void audibleAmberAlert();
    void audibleRedAlert();
    void whichAlertToMake(TemperatureStatus tempStatus, HumidityStatus humStatus);
};
#endif