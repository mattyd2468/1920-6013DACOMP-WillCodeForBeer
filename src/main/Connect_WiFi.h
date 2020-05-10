#ifndef Connect_WiFi_H_
#define Connect_WiFi_H_

#include <DHTesp.h>
#include <arduino.h>
#include "sensors/Thermometer.h"
#include "sensors/Humidity.h"


class Connect_WiFi {
    public:
    //WiFi
const char *SSID = "iPhone";
const char *PASS = "password";
const char *HOST = "http://willcodeforbeer12345.azurewebsites.net/";
const int TIMEOUT = 10000;
const String GROUPNAME = "WillCodeForBeer";
TempAndHumidity tempHum;	  // the object to store the temperature and humidity values
const int WRITE_TO_SERVER_DELAY = 30000; // delay for the status update, must be every 30 seconds
int serverMillis = 0;					 // time in millis since last written to server   
String date; 

    Connect_WiFi(TempAndHumidity tempHum);

    void connectToHotspot(); 
    void writeToServer();
    boolean timeDiff(unsigned long start, int specifiedDelay);
};
#endif
