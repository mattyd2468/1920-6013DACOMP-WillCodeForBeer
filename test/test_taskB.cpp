// #include "Arduino.h"
// #include <unity.h>
// #include "../src/main/sensors/Thermometer.cpp"
// #include "../src/main/sensors/Humidity.cpp"
// #include "../src/main/sensors/LED.cpp"

// /**
//  * 
//  * THIS IS THE TEST SCRIPT FOR TASK B
//  * 
//  */

// LED *led;
// Thermometer *temperature;
// Humidity *humidity;

// void setup()
// {
//     // NOTE!!! Wait for >2 secs
//     // if board doesn't support software reset via Serial.DTR/RTS
//     delay(2000);

//     UNITY_BEGIN(); // IMPORTANT LINE!
//     led = new LED(27, 33, 32);
//     temperature = new Thermometer(4, led);
//     humidity = new Humidity(4, led);

//     pinMode(4, INPUT);
//     pinMode(26, OUTPUT);
//     pinMode(33, OUTPUT);
//     pinMode(32, OUTPUT);
// }

// /*
// * LED Scripts
// */
// void test_temp_green_hum_green(void)
// {
//     led->setLEDColour(TemperatureStatus::GREEN, HumidityStatus::GREEN);

//     TEST_ASSERT_EQUAL(LEDColour::GREEN, led->currentColour);
// }

// void test_temp_amber_hum_green(void)
// {
//     led->setLEDColour(TemperatureStatus::AMBER, HumidityStatus::GREEN);

//     TEST_ASSERT_EQUAL(LEDColour::YELLOW, led->currentColour);
// }

// void test_temp_amber_hum_amber(void)
// {
//     led->setLEDColour(TemperatureStatus::AMBER, HumidityStatus::AMBER);

//     TEST_ASSERT_EQUAL(LEDColour::YELLOW, led->currentColour);
// }

// void test_temp_amber_hum_red(void)
// {
//     led->setLEDColour(TemperatureStatus::AMBER, HumidityStatus::RED);

//     TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
// }

// void test_temp_red_hum_green(void)
// {
//     led->setLEDColour(TemperatureStatus::RED, HumidityStatus::GREEN);

//     TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
// }

// void test_temp_red_hum_amber(void)
// {
//     led->setLEDColour(TemperatureStatus::RED, HumidityStatus::GREEN);

//     TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
// }

// void test_temp_red_hum_red(void)
// {
//     led->setLEDColour(TemperatureStatus::RED, HumidityStatus::RED);

//     TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
// }

// void test_temp_green_hum_amber(void)
// {
//     led->setLEDColour(TemperatureStatus::GREEN, HumidityStatus::AMBER);

//     TEST_ASSERT_EQUAL(LEDColour::YELLOW, led->currentColour);
// }

// void test_temp_green_hum_red(void)
// {
//     led->setLEDColour(TemperatureStatus::GREEN, HumidityStatus::RED);

//     TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
// }

// /*
// * DHT11 Scripts
// */

// void test_temperature_green_status(void)
// {
//     TEST_ASSERT_EQUAL(TemperatureStatus::GREEN, temperature->calculateStatus(23, led));
// }

// void test_temperature_green_status2(void)
// {
//     TEST_ASSERT_EQUAL(TemperatureStatus::GREEN, temperature->calculateStatus(18, led));
// }

// void test_temperature_green_status3(void)
// {
//     TEST_ASSERT_EQUAL(TemperatureStatus::GREEN, temperature->calculateStatus(20, led));
// }

// void test_temperature_amber_status(void)
// {
//     TEST_ASSERT_EQUAL(TemperatureStatus::AMBER, temperature->calculateStatus(16, led));
// }

// void test_temperature_amber_status2(void)
// {
//     TEST_ASSERT_EQUAL(TemperatureStatus::AMBER, temperature->calculateStatus(27, led));
// }

// void test_temperature_amber_status3(void)
// {
//     TEST_ASSERT_EQUAL(TemperatureStatus::AMBER, temperature->calculateStatus(24, led));
// }

// void test_temperature_red_status(void)
// {
//     TEST_ASSERT_EQUAL(TemperatureStatus::RED, temperature->calculateStatus(15.9, led));
// }

// void test_temperature_red_status2(void)
// {
//     TEST_ASSERT_EQUAL(TemperatureStatus::RED, temperature->calculateStatus(27.1, led));
// }

// void test_temperature_red_status3(void)
// {
//     TEST_ASSERT_EQUAL(TemperatureStatus::RED, temperature->calculateStatus(30, led));
// }

// void test_humidity_green_status(void)
// {
//     TEST_ASSERT_EQUAL(HumidityStatus::GREEN, humidity->calculateStatus(34.00, led));
// }

// void test_humidity_green_status2(void)
// {
//     TEST_ASSERT_EQUAL(HumidityStatus::GREEN, humidity->calculateStatus(60.00, led));
// }

// void test_humidity_green_status3(void)
// {
//     TEST_ASSERT_EQUAL(HumidityStatus::GREEN, humidity->calculateStatus(50.00, led));
// }

// void test_humidity_amber_status(void)
// {
//     TEST_ASSERT_EQUAL(HumidityStatus::AMBER, humidity->calculateStatus(25.00, led));
// }

// void test_humidity_amber_status2(void)
// {
//     TEST_ASSERT_EQUAL(HumidityStatus::AMBER, humidity->calculateStatus(75.00, led));
// }

// void test_humidity_amber_status3(void)
// {
//     TEST_ASSERT_EQUAL(HumidityStatus::AMBER, humidity->calculateStatus(33.00, led));
// }

// void test_humidity_red_status(void)
// {
//     TEST_ASSERT_EQUAL(HumidityStatus::RED, humidity->calculateStatus(24.00, led));
// }

// void test_humidity_red_status2(void)
// {
//     TEST_ASSERT_EQUAL(HumidityStatus::RED, humidity->calculateStatus(76.00, led));
// }

// void test_humidity_red_status3(void)
// {
//     TEST_ASSERT_EQUAL(HumidityStatus::RED, humidity->calculateStatus(90.00, led));
// }

// /*
// * Run The Tests
// */
// void runLEDScript()
// {
//     Serial.println("=========================================");
//     Serial.println("Testing LED (Task B script)");
//     Serial.println("=========================================");
//     RUN_TEST(test_temp_green_hum_green);
//     delay(1000);
//     RUN_TEST(test_temp_amber_hum_green);
//     delay(1000);
//     RUN_TEST(test_temp_amber_hum_amber);
//     delay(1000);
//     RUN_TEST(test_temp_green_hum_amber);
//     delay(1000);
//     RUN_TEST(test_temp_amber_hum_red);
//     delay(1000);
//     RUN_TEST(test_temp_red_hum_green);
//     delay(1000);
//     RUN_TEST(test_temp_red_hum_amber);
//     delay(1000);
//     RUN_TEST(test_temp_red_hum_red);
//     delay(1000);
//     RUN_TEST(test_temp_green_hum_red);
//     delay(1000);

// }

// void runDHT11Script()
// {
//     Serial.println("=========================================");
//     Serial.println("Testing DHT11 Sensor (Task B script)");
//     Serial.println("=========================================");
//     RUN_TEST(test_temperature_green_status);
//     delay(1000);
//     RUN_TEST(test_temperature_green_status2);
//     delay(1000);
//     RUN_TEST(test_temperature_green_status3);
//     delay(1000);
//     RUN_TEST(test_temperature_amber_status);
//     delay(1000);
//     RUN_TEST(test_temperature_amber_status2);
//     delay(1000);
//     RUN_TEST(test_temperature_amber_status3);
//     delay(1000);
//     RUN_TEST(test_temperature_red_status);
//     delay(1000);
//     RUN_TEST(test_temperature_red_status2);
//     delay(1000);
//     RUN_TEST(test_temperature_red_status3);
//     delay(1000);

//     // Humidity
//     RUN_TEST(test_humidity_green_status);
//     delay(1000);
//     RUN_TEST(test_humidity_green_status2);
//     delay(1000);
//     RUN_TEST(test_humidity_green_status3);
//     delay(1000);
//     RUN_TEST(test_humidity_amber_status);
//     delay(1000);
//     RUN_TEST(test_humidity_amber_status2);
//     delay(1000);
//     RUN_TEST(test_humidity_amber_status3);
//     delay(1000);
//     RUN_TEST(test_humidity_red_status);
//     delay(1000);
//     RUN_TEST(test_humidity_red_status2);
//     delay(1000);
//     RUN_TEST(test_humidity_red_status3);
//     delay(1000);
// }

// void loop()
// {
//     runDHT11Script();
//     runLEDScript();

//     UNITY_END(); // stop unit testing
// }