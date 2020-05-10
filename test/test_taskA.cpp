// #include "Arduino.h"
// #include <unity.h>
// #include "../src/main/sensors/PIR.cpp"
// #include "../src/main/SDCard.cpp"
// #include "../src/main/sensors/Thermometer.cpp"
// #include "../src/main/sensors/Humidity.cpp"
// #include "../src/main/sensors/Buzzer.cpp"
// #include "../src/main/sensors/LED.cpp"

// LED *led;
// Thermometer *temperature;
// Humidity *humidity;
// PIR *pir;
// BUZZER *buzzer;
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
//     pir = new PIR(15);
//     buzzer = new BUZZER(pir);
//     temperature = new Thermometer(4, led);
//     humidity = new Humidity(4, led);
//     dht.setup(4, DHTesp::DHT11); // set up the DHT11 sensor
//     String date = "Sun, 12 Apr 2020 23:21:40 GMT";
//     sdcard = new SDCard(5, date);
// }

// /**
//  * SCRIPTS
//  **/

// /**
//  * Test scripts for Task A
//  */
// void test_dht11_pin()
// {
//     TEST_ASSERT_EQUAL(4, temperature->potPin);
//     TEST_ASSERT_EQUAL(4, humidity->potPin);
// }

// void test_led_pin()
// {
//     TEST_ASSERT_EQUAL(26, led->redPin);
//     TEST_ASSERT_EQUAL(33, led->greenPin);
//     TEST_ASSERT_EQUAL(32, led->bluePin);
// }

// void test_pir_pin()
// {
//     TEST_ASSERT_EQUAL(15, pir->MOTION_SENSOR);
// }

// void test_sd_pin()
// {
//     TEST_ASSERT_EQUAL(5, sdcard->CS_PIN);
// }

// void test_Temp_Not_NAN()
// {
//     tempHum = dht.getTempAndHumidity();
//     TEST_ASSERT_NOT_EQUAL(isnan(tempHum.temperature), tempHum.temperature);
// }

// void test_Hum_Not_NAN()
// {
//     tempHum = dht.getTempAndHumidity();
//     TEST_ASSERT_NOT_EQUAL(isnan(tempHum.humidity), tempHum.humidity);
// }

// void test_Hum_Valid()
// {
//     tempHum = dht.getTempAndHumidity();
//     TEST_ASSERT_NOT_EQUAL(100, tempHum.humidity);
// }

// void test_Temp_Valid()
// {
//     tempHum = dht.getTempAndHumidity();
//     TEST_ASSERT_NOT_EQUAL(100, tempHum.temperature);
// }

// void test_Hum_Valid1()
// {
//     tempHum = dht.getTempAndHumidity();
//     TEST_ASSERT_NOT_EQUAL(0, tempHum.humidity);
// }

// void test_Temp_Valid1()
// {
//     tempHum = dht.getTempAndHumidity();
//     TEST_ASSERT_NOT_EQUAL(0, tempHum.temperature);
// }

// /*
// * Run The Tests
// */

// void runPowerOnScript()
// {
//     Serial.println("=========================================");
//     Serial.println("Testing Power on (Task A script)");
//     Serial.println("=========================================");
//     RUN_TEST(test_dht11_pin);
//     delay(1000);
//     RUN_TEST(test_led_pin);
//     delay(1000);
//     RUN_TEST(test_pir_pin);
//     delay(1000);
//     RUN_TEST(test_sd_pin);
//     delay(1000);
//     RUN_TEST(test_Temp_Not_NAN);
//     delay(1000);
//     RUN_TEST(test_Hum_Not_NAN);
//     delay(1000);
//     RUN_TEST(test_Hum_Valid);
//     delay(1000);
//     RUN_TEST(test_Temp_Valid);
//     delay(1000);
//     RUN_TEST(test_Hum_Valid1);
//     delay(1000);
//     RUN_TEST(test_Temp_Valid1);
//     delay(1000);
// }

// void loop()
// {
//     runPowerOnScript(); // Task A

//     UNITY_END(); // stop unit testing
// }