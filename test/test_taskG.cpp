// #include "Arduino.h"
// #include <unity.h>
// #include "../src/main/sensors/PIR.cpp"
// #include "../src/main/sensors/Thermometer.cpp"
// #include "../src/main/sensors/Humidity.cpp"
// #include "../src/main/sensors/Buzzer.cpp"
// #include "../src/main/sensors/LED.cpp"
// #include "../src/main/SDCard.cpp"

// PIR *pir;
// SDCard *sdcard;
// BUZZER *buzzer;
// Thermometer *temp;
// Humidity *hum;
// LED *led;

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
//  * Test scripts for Task G
//  */

// void test_buzzer_red()
// {
//     pir->motionSensorStatus = PIRStatus::OCCUPIED;
//     buzzer->whichAlertToMake(TemperatureStatus::RED, HumidityStatus::GREEN);
//     TEST_ASSERT_EQUAL(BuzzerStatus::RED, buzzer->buzzerStatus);
// }

// void test_buzzer_amber()
// {
//     pir->motionSensorStatus = PIRStatus::OCCUPIED;
//     buzzer->whichAlertToMake(TemperatureStatus::AMBER, HumidityStatus::GREEN);
//     TEST_ASSERT_EQUAL(BuzzerStatus::AMBER, buzzer->buzzerStatus);
// }

// void test_buzzer_green()
// {
//     pir->motionSensorStatus = PIRStatus::OCCUPIED;
//     buzzer->whichAlertToMake(TemperatureStatus::GREEN, HumidityStatus::GREEN);
//     TEST_ASSERT_EQUAL(BuzzerStatus::NONE, buzzer->buzzerStatus);
// }

// void test_buzzer_not_Active_dht11_amber()
// {

//     pir->motionSensorStatus = PIRStatus::VACANT;
//     buzzer->whichAlertToMake(TemperatureStatus::AMBER, HumidityStatus::GREEN);
//     TEST_ASSERT_EQUAL(BuzzerStatus::NONE, buzzer->buzzerStatus);
// }

// void test_buzzer_not_Active_dht11_green()
// {
//     pir->motionSensorStatus = PIRStatus::VACANT;
//     buzzer->whichAlertToMake(TemperatureStatus::GREEN, HumidityStatus::GREEN);
//     TEST_ASSERT_EQUAL(BuzzerStatus::NONE, buzzer->buzzerStatus);
// }

// void test_buzzer_not_Active_dht11_red()
// {
//     pir->motionSensorStatus = PIRStatus::VACANT;
//     buzzer->whichAlertToMake(TemperatureStatus::RED, HumidityStatus::GREEN);
//     TEST_ASSERT_EQUAL(BuzzerStatus::NONE, buzzer->buzzerStatus);
// }

// /*
// * Run The Tests
// */

// void runBuzzerScript()
// {
//     Serial.println("=========================================");
//     Serial.println("Testing Buzzer (Task G script)");
//     Serial.println("=========================================");
//     RUN_TEST(test_buzzer_amber);
//     delay(1000);
//     RUN_TEST(test_buzzer_red);
//     delay(1000);
//     RUN_TEST(test_buzzer_green);
//     delay(1000);
//     RUN_TEST(test_buzzer_not_Active_dht11_amber);
//     delay(1000);
//     RUN_TEST(test_buzzer_not_Active_dht11_green);
//     delay(1000);
//     RUN_TEST(test_buzzer_not_Active_dht11_red);
// }

// void loop()
// {
//     runBuzzerScript(); // Task G

//     UNITY_END(); // stop unit testing
// }