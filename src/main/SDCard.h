#ifndef SDCARD_H_
#define SDCARD_H_
#include <Vector.h>
#include <arduino.h>
#include "enums/PIRStatus.h"
#include "time.h"

using namespace std;

class SDCard
{
public:
    int CS_PIN;
    const int DELAY = 120000; // this is 2 minutes
    int MILLIS = 0; // seconds since last write
    // vector<String> logging; // where our readings will be stored
    String date;

    SDCard();
    SDCard(int CS_PIN, String date);
    void storeDHT11Readings(String temp, String humidity);
    void storePIRReadings(String pirStatus, vector<String> logging);
    void writeToSDCard(vector<String> logging);

private:
    boolean timeDiff(unsigned long start, int delay);
    String formatMonth(String date);
    void formatDate(String date);
};
#endif
