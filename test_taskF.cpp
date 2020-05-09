// #include "Arduino.h"
// #include <unity.h>
// #include "../src/main/sensors/PIR.cpp"
// #include "../src/main/sensors/Thermometer.cpp"
// #include "../src/main/sensors/Humidity.cpp"
// #include "../src/main/sensors/Buzzer.cpp"
// #include "../src/main/sensors/LED.cpp"
// #include "../src/main/SDCard.cpp"
// #include "../src/main/Connect_WiFi.cpp"

// PIR *pir;
// SDCard *sdcard;
// BUZZER *buzzer;
// Thermometer *temp;
// Humidity *hum;
// LED *led;
// Connect_WiFi *connect_wifi;

// void setup()
// {
//     // NOTE!!! Wait for >2 secs
//     // if board doesn't support software reset via Serial.DTR/RTS
//     delay(2000);

//     UNITY_BEGIN(); // IMPORTANT LINE!
//     pir = new PIR(15);
//     buzzer = new BUZZER(pir);
//     led = new LED(26, 33, 32);
//     temp = new Thermometer(4, led, buzzer);
//     hum = new Humidity(4, led, buzzer);
// }

// /**
//  * SCRIPTS
//  **/

// /**
//  * Test scripts for Task F
//  */

// void test_wifi_connect()
// {
//     connect_wifi->connectToHotspot();
//     TEST_ASSERT_EQUAL(WiFi.status(), WL_CONNECTED);
// }


// /*
// * Run The Tests
// */

// void runWiFIScript()
// {
//     Serial.println("=========================================");
//     Serial.println("Testing WiFi (Task F script)");
//     Serial.println("=========================================");
//     RUN_TEST(test_wifi_connect);
//     delay(1000);
// }