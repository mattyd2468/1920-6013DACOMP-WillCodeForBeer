#ifndef SDCARD_H_
#define SDCARD_H_
#include <Vector.h>
#include <arduino.h>
#include "enums/PIRStatus.h"

using namespace std;

class SDCard
{
public:
    int CS_PIN;
    const int DELAY = 120000; // this is 2 minutes
    int MILLIS = 0; // seconds since last write
    vector<String> logging; // where our readings will be stored

    SDCard();
    SDCard(int CS_PIN);
    void storeDHT11Readings(String temp, String humidity);
    void storePIRReadings(String pirStatus);
    void writeToSDCard();

private:
    boolean timeDiff(unsigned long start, int delay);
};
#endif
