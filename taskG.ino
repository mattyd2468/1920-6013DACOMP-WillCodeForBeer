#include "Arduino.h"
#include "Thermometer.h"
#include "Humidity.h"
#include "LED.h"
#include <DHTesp.h>

//Pin set up
#define DHTPIN 4 // the pin value for the DHT11 sensor
#define DHTTYPE DHT11
const int BUZZER = 25; //Buzzer pin
const int MOTION_SENSOR = 18;    	// PIR sensor pin
const int MOTION_INDICATOR = 12; // TODO: LED pin, LED is not needed for task D! Change to buzzer maybe?
LED *led = new LED(23, 22, 21); // the LED which shows the status of the sensors, pins 23,22,21

//Variable initialisation
bool firstLoop = true; //Variable to store if it is the first loop or not
int potVal = 0; // Variable to store temperature value
int humVal = 0; // Variable to store the humidity value
long unsigned int lowTime; //Variable for PIR sensor low time
const long unsigned int pauseTime = 5000; //TODO: 600,000 is 10 mins currently 5 secs
boolean isDelayActive = true;	// Prevents duplicate output to console
boolean getLowTime;
const int calibrationTime = 30; // 30 seconds for initialising the PIR Sensor
int freq = 2000; //buzzer set up. Doesnt need to change
int channel = 0; //buzzer set up. Doesnt need to change
int resolution = 8; //buzzer set up. Doesnt need to change
int dutyCycle = 128; //buzzer 128 means noise. Set to 0 for silence
enum LEDColour colour; //Used for current LED colour

//Setting up the objects
Thermometer *thermometer = NULL;
Humidity *humidity = NULL;
DHTesp dht; // object to store the DHT11 sensor
TempAndHumidity tempHum; // the object to store the temperature and humidity values
TemperatureStatus tempStatus; // object to store the temperature status
HumidityStatus humStatus; // object to store the humidity status

void setup() {
	thermometer = new Thermometer(DHTPIN, led);
	humidity = new Humidity(DHTPIN, led);

	Serial.begin(115200); // @suppress("Ambiguous problem")
	dht.setup(DHTPIN, DHTesp::DHT11); // set up the DHT11 sensor

	//taskD setup
	// Setting pins and default values
	pinMode(MOTION_SENSOR, INPUT);
	pinMode(MOTION_INDICATOR, OUTPUT);
	digitalWrite(MOTION_SENSOR, LOW);

	// Waiting for the PIR Sensor to initialise
	Serial.print("Initialising PIR Sensor ");
	for (int i = 0; i < calibrationTime; i++) {
		Serial.print(".");
		delay(1000);
	}
	Serial.println("|");
	Serial.println("SENSOR ACTIVE");
	delay(50);

	//taskG setup
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(BUZZER, channel);
}

void motionSensor() {
	if (digitalRead(MOTION_SENSOR) == HIGH) {
		digitalWrite(MOTION_INDICATOR, HIGH); // TODO: LED is on while motion is sensed

		// Ensures we don't output OCCUPIED until the sensor has since been LOW
		if (isDelayActive) {
			colour = led->currentColour;
			buzz(colour);
			isDelayActive = false;
			Serial.println("---");
			Serial.print("OCCUPIED at ");
			Serial.print(millis() / 1000);
			Serial.println(" sec");
			delay(50);
		}
		getLowTime = true;
	}

	if (digitalRead(MOTION_SENSOR) == LOW) {
		ledcWrite(channel, 0);
		digitalWrite(MOTION_INDICATOR, LOW); // LED is off when motion isn't sensed

		// Getting the time where motion stopped being picked up.
		if (getLowTime) {
			lowTime = millis();
			getLowTime = false; // make sure this is only done at the start of a LOW phase
		}
		// if motion isn't picked up for more than the given pauseTime, the room is assumed to be VACANT.
		if (!isDelayActive && (millis() - lowTime) > pauseTime) {
			// Ensures we don't output VACANT until the sensor has since been HIGH
			isDelayActive = true;
			Serial.print("VACANT at ");
			Serial.print((millis()) / 1000);
			Serial.println(" sec");
			delay(50);
		}
	}
}

void powerOnTest() {
	Serial.println("Power on!");
	tempHum = dht.getTempAndHumidity();
	float temp = tempHum.temperature;
	float hum = tempHum.humidity;

	//DHT11 maximum values. Need to add nan check
	if (temp < 0 || temp > 50) {
		Serial.println("Temperature Error");
	}
	if (hum < 20 || hum > 80) {
		Serial.println("Humidity Error");
	}

	firstLoop = false;
}

void tempAndHumSensor() {
	// get the temperature and humidity readings from the DHT11 sensor
	tempHum = dht.getTempAndHumidity();
	// set LED colours for temp and humidity sensor
	tempStatus = thermometer->calculateStatus(tempHum.temperature, led);
	humStatus = humidity->calculateStatus(tempHum.humidity, led);
	led->setLEDColour(tempStatus, humStatus);
	delay(2000); // delay for 2 seconds - this is needed for the DHT11 sensor as a minimum
}

void buzz(LEDColour colour) {
	//if led red buzz for 3 sec
	if (colour == LEDColour::RED) {
		ledcWrite(channel, dutyCycle);
		delay(3000);
		ledcWrite(channel, 0);
	}
	//else buzz for 1 secs
	else {
		ledcWrite(channel, dutyCycle);
		delay(1000);
		ledcWrite(channel, 0);
	}
}

void loop() {
	//If it is the first loop run power on test
	if (firstLoop) {
		powerOnTest();
	}
	//Else run normal system
	else {
		// get the temperature and humidity readings from the DHT11 sensor
		tempAndHumSensor();
		motionSensor(); //Call taskD code;
	}
}
