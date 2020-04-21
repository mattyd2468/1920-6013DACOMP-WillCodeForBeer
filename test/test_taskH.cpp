// #include "Arduino.h"
// #include <unity.h>
// #include "../src/main/sensors/PIR.cpp"
// #include "../src/main/SDCard.cpp"
// #include "../src/main/sensors/Thermometer.cpp"
// #include "../src/main/sensors/Humidity.cpp"
// #include "../src/main/sensors/LED.cpp"

// LED *led;
// Thermometer *temperature;
// Humidity *humidity;
// PIR *pir;
// SDCard *sdcard;
// DHTesp dht; // object to store the DHT11 sensor
// TempAndHumidity tempHum;

// void setup()
// {
//     // NOTE!!! Wait for >2 secs
//     // if board doesn't support software reset via Serial.DTR/RTS
//     delay(2000);

//     UNITY_BEGIN(); // IMPORTANT LINE!
//     led = new LED(26, 33, 32);
//     temperature = new Thermometer(4, led);
//     humidity = new Humidity(4, led);
//     dht.setup(4, DHTesp::DHT11); // set up the DHT11 sensor
//     pir = new PIR(15);
//     String date = "Fri, 10 Apr 2020 12:48:40 GMT";
//     sdcard = new SDCard(5, date);

//     pinMode(15, INPUT);
//     pinMode(4, INPUT);
//     pinMode(26, OUTPUT);
//     pinMode(33, OUTPUT);
//     pinMode(32, OUTPUT);
// }

// /**
//  * SCRIPTS
//  **/

// /**
//  * Test scripts for Task H
//  */

// void test_Writes_To_Vector()
// {
//     tempHum = dht.getTempAndHumidity();
//     sdcard->storeDHT11Readings((String)tempHum.temperature, (String)tempHum.humidity);

//     bool isEmpty = sdcard->logging.empty();

//     TEST_ASSERT_EQUAL(false, isEmpty); // tests that the vector now has elements in it
// }

// void test_SD_Card_File_Created_Correctly()
// {

//     // opens the appropriate file
//     File myFile = SD.open("/10-04-2020", FILE_APPEND);

//     bool fileExist = false;
//     if (myFile)
//     {
//         fileExist = true;
//     }

//     TEST_ASSERT_EQUAL(true, fileExist); // tests that upon initialisation a file is created with the current date
// }

// /*
// * Run The Tests
// */

// void runSDCardScript()
// {
//     Serial.println("=========================================");
//     Serial.println("Testing SD Card (Task H script)");
//     Serial.println("=========================================");
//     RUN_TEST(test_Writes_To_Vector);
//     delay(1000);
//     RUN_TEST(test_SD_Card_File_Created_Correctly);
//     delay(1000);
// }

// void loop()
// {
//     runSDCardScript(); // Task H

//     UNITY_END(); // stop unit testing
// }