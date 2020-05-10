#include "Arduino.h"
#include <unity.h>
#include "../src/main/sensors/Thermometer.cpp"
#include "../src/main/sensors/Humidity.cpp"
#include "../src/main/sensors/LED.cpp"
#include "../src/main/sensors/PIR.cpp"
#include "../src/main/sensors/Buzzer.cpp"
#include "../src/main/SDCard.cpp"

LED *led;
Thermometer *temperature;
Humidity *humidity;
PIR *pir;
SDCard *sdcard;
BUZZER *buzzer;
DHTesp dht; // object to store the DHT11 sensor
TempAndHumidity tempHum;
vector<String> logging;		// Vector to store reading in volatile memory

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    led = new LED(26, 33, 32);
    pir = new PIR(15);
    buzzer = new BUZZER(pir);
    temperature = new Thermometer(4, led);
    humidity = new Humidity(4, led);
    dht.setup(4, DHTesp::DHT11); // set up the DHT11 sensor
    String date = "Fri, 10 Apr 2020 12:48:40 GMT";
    sdcard = new SDCard(5, date);
}

/**
 * SCRIPTS
 **/

/*
* LED Scripts
*/
void test_temp_green_hum_green(void)
{
    led->setLEDColour(TemperatureStatus::GREEN, HumidityStatus::GREEN);

    TEST_ASSERT_EQUAL(LEDColour::GREEN, led->currentColour);
}

void test_temp_amber_hum_green(void)
{
    led->setLEDColour(TemperatureStatus::AMBER, HumidityStatus::GREEN);

    TEST_ASSERT_EQUAL(LEDColour::YELLOW, led->currentColour);
}

void test_temp_amber_hum_amber(void)
{
    led->setLEDColour(TemperatureStatus::AMBER, HumidityStatus::AMBER);

    TEST_ASSERT_EQUAL(LEDColour::YELLOW, led->currentColour);
}

void test_temp_amber_hum_red(void)
{
    led->setLEDColour(TemperatureStatus::AMBER, HumidityStatus::RED);

    TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
}

void test_temp_red_hum_green(void)
{
    led->setLEDColour(TemperatureStatus::RED, HumidityStatus::GREEN);

    TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
}

void test_temp_red_hum_amber(void)
{
    led->setLEDColour(TemperatureStatus::RED, HumidityStatus::GREEN);

    TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
}

void test_temp_red_hum_red(void)
{
    led->setLEDColour(TemperatureStatus::RED, HumidityStatus::RED);

    TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
}

void test_temp_green_hum_amber(void)
{
    led->setLEDColour(TemperatureStatus::GREEN, HumidityStatus::AMBER);

    TEST_ASSERT_EQUAL(LEDColour::YELLOW, led->currentColour);
}

void test_temp_green_hum_red(void)
{
    led->setLEDColour(TemperatureStatus::GREEN, HumidityStatus::RED);

    TEST_ASSERT_EQUAL(LEDColour::RED, led->currentColour);
}

/*
* DHT11 Scripts
*/

void test_temperature_green_status(void)
{
    TEST_ASSERT_EQUAL(TemperatureStatus::GREEN, temperature->calculateStatus(23, led));
}

void test_temperature_green_status2(void)
{
    TEST_ASSERT_EQUAL(TemperatureStatus::GREEN, temperature->calculateStatus(18, led));
}

void test_temperature_green_status3(void)
{
    TEST_ASSERT_EQUAL(TemperatureStatus::GREEN, temperature->calculateStatus(20, led));
}

void test_temperature_amber_status(void)
{
    TEST_ASSERT_EQUAL(TemperatureStatus::AMBER, temperature->calculateStatus(16, led));
}

void test_temperature_amber_status2(void)
{
    TEST_ASSERT_EQUAL(TemperatureStatus::AMBER, temperature->calculateStatus(27, led));
}

void test_temperature_amber_status3(void)
{
    TEST_ASSERT_EQUAL(TemperatureStatus::AMBER, temperature->calculateStatus(24, led));
}

void test_temperature_red_status(void)
{
    TEST_ASSERT_EQUAL(TemperatureStatus::RED, temperature->calculateStatus(15.9, led));
}

void test_temperature_red_status2(void)
{
    TEST_ASSERT_EQUAL(TemperatureStatus::RED, temperature->calculateStatus(27.1, led));
}

void test_temperature_red_status3(void)
{
    TEST_ASSERT_EQUAL(TemperatureStatus::RED, temperature->calculateStatus(30, led));
}

void test_humidity_green_status(void)
{
    TEST_ASSERT_EQUAL(HumidityStatus::GREEN, humidity->calculateStatus(34.00, led));
}

void test_humidity_green_status2(void)
{
    TEST_ASSERT_EQUAL(HumidityStatus::GREEN, humidity->calculateStatus(60.00, led));
}

void test_humidity_green_status3(void)
{
    TEST_ASSERT_EQUAL(HumidityStatus::GREEN, humidity->calculateStatus(50.00, led));
}

void test_humidity_amber_status(void)
{
    TEST_ASSERT_EQUAL(HumidityStatus::AMBER, humidity->calculateStatus(25.00, led));
}

void test_humidity_amber_status2(void)
{
    TEST_ASSERT_EQUAL(HumidityStatus::AMBER, humidity->calculateStatus(75.00, led));
}

void test_humidity_amber_status3(void)
{
    TEST_ASSERT_EQUAL(HumidityStatus::AMBER, humidity->calculateStatus(33.00, led));
}

void test_humidity_red_status(void)
{
    TEST_ASSERT_EQUAL(HumidityStatus::RED, humidity->calculateStatus(24.00, led));
}

void test_humidity_red_status2(void)
{
    TEST_ASSERT_EQUAL(HumidityStatus::RED, humidity->calculateStatus(76.00, led));
}

void test_humidity_red_status3(void)
{
    TEST_ASSERT_EQUAL(HumidityStatus::RED, humidity->calculateStatus(90.00, led));
}

/**
 * Test scripts for Task D
 */

void test_PIR_status()
{
    TEST_ASSERT_EQUAL(PIRStatus::VACANT, pir->motionSensorStatus);
}

void test_PIR_vacant()
{
    pir->lowTime = 5000;
    pir->motionSensor(sdcard, logging);
    TEST_ASSERT_EQUAL(PIRStatus::VACANT, pir->motionSensorStatus);
}

/**
 * Test scripts for Task A
 */
void test_dht11_pin()
{
    TEST_ASSERT_EQUAL(4, temperature->potPin);
    TEST_ASSERT_EQUAL(4, humidity->potPin);
}

void test_led_pin()
{
    TEST_ASSERT_EQUAL(26, led->redPin);
    TEST_ASSERT_EQUAL(33, led->greenPin);
    TEST_ASSERT_EQUAL(32, led->bluePin);
}

void test_pir_pin()
{
    TEST_ASSERT_EQUAL(15, pir->MOTION_SENSOR);
}

void test_sd_pin()
{
    TEST_ASSERT_EQUAL(5, sdcard->CS_PIN);
}

void test_Temp_Not_NAN()
{
    tempHum = dht.getTempAndHumidity();
    TEST_ASSERT_NOT_EQUAL(isnan(tempHum.temperature), tempHum.temperature);
}

void test_Hum_Not_NAN()
{
    tempHum = dht.getTempAndHumidity();
    TEST_ASSERT_NOT_EQUAL(isnan(tempHum.humidity), tempHum.humidity);
}

void test_Hum_Valid()
{
    tempHum = dht.getTempAndHumidity();
    TEST_ASSERT_NOT_EQUAL(100, tempHum.humidity);
}

void test_Temp_Valid()
{
    tempHum = dht.getTempAndHumidity();
    TEST_ASSERT_NOT_EQUAL(100, tempHum.temperature);
}

void test_Hum_Valid1()
{
    tempHum = dht.getTempAndHumidity();
    TEST_ASSERT_NOT_EQUAL(0, tempHum.humidity);
}

void test_Temp_Valid1()
{
    tempHum = dht.getTempAndHumidity();
    TEST_ASSERT_NOT_EQUAL(0, tempHum.temperature);
}

/**
 * Test scripts for Task G
 */

void test_buzzer_red()
{
    pir->motionSensorStatus = PIRStatus::OCCUPIED;
    buzzer->whichAlertToMake(TemperatureStatus::RED, HumidityStatus::GREEN, false);
    TEST_ASSERT_EQUAL(BuzzerStatus::RED, buzzer->buzzerStatus);
}

void test_buzzer_amber()
{
    pir->motionSensorStatus = PIRStatus::OCCUPIED;
    buzzer->whichAlertToMake(TemperatureStatus::AMBER, HumidityStatus::GREEN, false);
    TEST_ASSERT_EQUAL(BuzzerStatus::AMBER, buzzer->buzzerStatus);
}

void test_buzzer_green()
{
    pir->motionSensorStatus = PIRStatus::OCCUPIED;
    buzzer->whichAlertToMake(TemperatureStatus::GREEN, HumidityStatus::GREEN, false);
    TEST_ASSERT_EQUAL(BuzzerStatus::NONE, buzzer->buzzerStatus);
}

void test_buzzer_not_Active_dht11_amber()
{

    pir->motionSensorStatus = PIRStatus::VACANT;
    buzzer->whichAlertToMake(TemperatureStatus::AMBER, HumidityStatus::GREEN, false);
    TEST_ASSERT_EQUAL(BuzzerStatus::NONE, buzzer->buzzerStatus);
}

void test_buzzer_not_Active_dht11_green()
{
    pir->motionSensorStatus = PIRStatus::VACANT;
    buzzer->whichAlertToMake(TemperatureStatus::GREEN, HumidityStatus::GREEN, false);
    TEST_ASSERT_EQUAL(BuzzerStatus::NONE, buzzer->buzzerStatus);
}

void test_buzzer_not_Active_dht11_red()
{
    pir->motionSensorStatus = PIRStatus::VACANT;
    buzzer->whichAlertToMake(TemperatureStatus::RED, HumidityStatus::GREEN, false);
    TEST_ASSERT_EQUAL(BuzzerStatus::NONE, buzzer->buzzerStatus);
}

/**
 * Test scripts for Task H
 */

void test_Writes_To_Vector()
{
    tempHum = dht.getTempAndHumidity();
    // Stores latest recorded DHT11 readings into a vector in volatile memory.

    logging.push_back("Temperature: " + (String)tempHum.temperature + "°C");
    logging.push_back("Humidity: " + (String)tempHum.humidity + "%");
    // Stores latest recorded PIR readings into a vector in volatile memory.
    logging.push_back("Building Status: " + pir->getPIRStatus());
    sdcard->writeToSDCard(logging);

    bool isEmpty = logging.empty();

    TEST_ASSERT_EQUAL(false, isEmpty); // tests that the vector now has elements in it
}

void test_SD_Card_File_Created_Correctly()
{

    // opens the appropriate file
    File myFile = SD.open("/10-04-2020", FILE_APPEND);

    bool fileExist = false;
    if (myFile)
    {
        fileExist = true;
    }

    TEST_ASSERT_EQUAL(true, fileExist); // tests that upon initialisation a file is created with the current date
}

/*
* Run The Tests
*/
void runPowerOnScript()
{
    Serial.println("=========================================");
    Serial.println("Testing Power on (Task A script)");
    Serial.println("=========================================");
    RUN_TEST(test_dht11_pin);
    delay(1000);
    RUN_TEST(test_led_pin);
    delay(1000);
    RUN_TEST(test_pir_pin);
    delay(1000);
    RUN_TEST(test_sd_pin);
    delay(1000);
    RUN_TEST(test_Temp_Not_NAN);
    delay(1000);
    RUN_TEST(test_Hum_Not_NAN);
    delay(1000);
    RUN_TEST(test_Hum_Valid);
    delay(1000);
    RUN_TEST(test_Temp_Valid);
    delay(1000);
    RUN_TEST(test_Hum_Valid1);
    delay(1000);
    RUN_TEST(test_Temp_Valid1);
    delay(1000);
}

void runLEDScript()
{
    Serial.println("=========================================");
    Serial.println("Testing LED (Task B script)");
    Serial.println("=========================================");
    RUN_TEST(test_temp_green_hum_green);
    delay(1000);
    RUN_TEST(test_temp_amber_hum_green);
    delay(1000);
    RUN_TEST(test_temp_amber_hum_amber);
    delay(1000);
    RUN_TEST(test_temp_amber_hum_red);
    delay(1000);
    RUN_TEST(test_temp_red_hum_green);
    delay(1000);
    RUN_TEST(test_temp_red_hum_amber);
    delay(1000);
    RUN_TEST(test_temp_red_hum_red);
    delay(1000);
    RUN_TEST(test_temp_green_hum_amber);
    delay(1000);
    RUN_TEST(test_temp_green_hum_red);
    delay(1000);
}

void runDHT11Script()
{
    Serial.println("=========================================");
    Serial.println("Testing DHT11 Sensor (Task B script)");
    Serial.println("=========================================");
    RUN_TEST(test_temperature_green_status);
    delay(1000);
    RUN_TEST(test_temperature_green_status2);
    delay(1000);
    RUN_TEST(test_temperature_green_status3);
    delay(1000);
    RUN_TEST(test_temperature_amber_status);
    delay(1000);
    RUN_TEST(test_temperature_amber_status2);
    delay(1000);
    RUN_TEST(test_temperature_amber_status3);
    delay(1000);
    RUN_TEST(test_temperature_red_status);
    delay(1000);
    RUN_TEST(test_temperature_red_status2);
    delay(1000);
    RUN_TEST(test_temperature_red_status3);
    delay(1000);

    // Humidity
    RUN_TEST(test_humidity_green_status);
    delay(1000);
    RUN_TEST(test_humidity_green_status2);
    delay(1000);
    RUN_TEST(test_humidity_green_status3);
    delay(1000);
    RUN_TEST(test_humidity_amber_status);
    delay(1000);
    RUN_TEST(test_humidity_amber_status2);
    delay(1000);
    RUN_TEST(test_humidity_amber_status3);
    delay(1000);
    RUN_TEST(test_humidity_red_status);
    delay(1000);
    RUN_TEST(test_humidity_red_status2);
    delay(1000);
    RUN_TEST(test_humidity_red_status3);
    delay(1000);
}

void runPIRScript()
{
    Serial.println("=========================================");
    Serial.println("Testing PIR sensor (Task D script)");
    Serial.println("=========================================");
    RUN_TEST(test_PIR_status);
    delay(1000);
    RUN_TEST(test_PIR_vacant);
    delay(1000);
}

void runBuzzerScript()
{
    Serial.println("=========================================");
    Serial.println("Testing Buzzer (Task G script)");
    Serial.println("=========================================");
    RUN_TEST(test_buzzer_amber);
    delay(1000);
    RUN_TEST(test_buzzer_red);
    delay(1000);
    RUN_TEST(test_buzzer_green);
    delay(1000);
    RUN_TEST(test_buzzer_not_Active_dht11_amber);
    delay(1000);
    RUN_TEST(test_buzzer_not_Active_dht11_green);
    delay(1000);
    RUN_TEST(test_buzzer_not_Active_dht11_red);
}

void runSDCardScript()
{
    Serial.println("=========================================");
    Serial.println("Testing SD Card (Task H script)");
    Serial.println("=========================================");
    RUN_TEST(test_Writes_To_Vector);
    delay(1000);
    RUN_TEST(test_SD_Card_File_Created_Correctly);
    delay(1000);
}

void loop()
{
    runPowerOnScript(); // Task A
    runLEDScript();     // Task B
    runDHT11Script();   // Task B
    runPIRScript();     // Task D
    runBuzzerScript();  // Task G
    runSDCardScript();  // Task H

    UNITY_END(); // stop unit testing
}