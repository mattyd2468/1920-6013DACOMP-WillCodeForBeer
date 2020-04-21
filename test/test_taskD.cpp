// #include "Arduino.h"
// #include <unity.h>
// #include "../src/main/sensors/PIR.cpp"
// #include "../src/main/SDCard.cpp"

// PIR *pir;
// SDCard* sdcard;

// void setup()
// {
//     // NOTE!!! Wait for >2 secs
//     // if board doesn't support software reset via Serial.DTR/RTS
//     delay(2000);

//     UNITY_BEGIN(); // IMPORTANT LINE!
//     pir = new PIR(15);

//     pinMode(15, INPUT);
// }

// /**
//  * SCRIPTS
//  **/

// /**
//  * Test scripts for Task D
//  */

// void test_PIR_status()
// {
//     TEST_ASSERT_EQUAL(PIRStatus::VACANT, pir->motionSensorStatus);
// }

// void test_PIR_vacant()
// {
//     pir->lowTime = 5000;
//     pir->motionSensor(sdcard);
//     TEST_ASSERT_EQUAL(PIRStatus::VACANT, pir->motionSensorStatus);
// }

// void test_PIR_occupied()
// {
//     pir->isDelayActive = true;
//     digitalWrite(15, HIGH);
//     pir->motionSensor(sdcard);
//     TEST_ASSERT_EQUAL(PIRStatus::OCCUPIED, pir->motionSensorStatus);
// }

// /*
// * Run The Tests
// */

// void runPIRScript()
// {
//     RUN_TEST(test_PIR_status);
//     delay(1000);
//     RUN_TEST(test_PIR_vacant);
//     delay(1000);
//     RUN_TEST(test_PIR_occupied);
//     delay(1000);
// }

// void loop()
// {
//     runPIRScript(); // Task D

//     UNITY_END(); // stop unit testing
// }