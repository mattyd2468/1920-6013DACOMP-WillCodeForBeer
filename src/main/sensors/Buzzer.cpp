#include "BUZZER.h"
#include "LED.h"

BUZZER::BUZZER() {
	//taskG setup
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(BUZZER_PIN, channel);
}

BUZZER::BUZZER(PIR *pir, Thermometer *thermometer, Humidity *humidity) {
	//taskG setup
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(BUZZER_PIN, channel);
    this->pir = pir;
    this->thermometer = thermometer;
    this->humidity = humidity;
}

boolean BUZZER::timeDiff(unsigned long start, int specifiedDelay){
    return (millis() - start >= specifiedDelay);
}

void BUZZER::buzz() {
	ledcWrite(channel, dutyCycle);
	delay(1000);
	ledcWrite(channel, 0);
}

/**
 * This will make a noise if last noise was less than 30 seconds ago
 */
void BUZZER::audibleAmberAlert() {
	if (timeDiff(this->alertMillis, AMBER_ALERT_SOUND_DELAY)) {
		this->alertMillis = millis();
		Serial.println("Amber buzz");
		buzz();
	}
}

/**
 * This will make a noise if last noise was less than 5 seconds ago
 */
void BUZZER::audibleRedAlert() {
	if (timeDiff(this->alertMillis, RED_ALERT_SOUND_DELAY)) {
		alertMillis = millis();
		Serial.println("Red buzz");
		buzz();
	}
}

/**
 * Check if it should call method to make noise
 */
void BUZZER::whichAlertToMake(TemperatureStatus tempStatus, HumidityStatus humStatus) {
	if (pir->getPIRStatus() == "OCCUPIED") {
		if (thermometer->getTempStatus(tempStatus) == "RED"
				|| (humidity->getHumStatus(humStatus)) == "RED") {
			audibleRedAlert();
		} else if (thermometer->getTempStatus(tempStatus) == "AMBER"
				|| (humidity->getHumStatus(humStatus)) == "AMBER") {
			audibleAmberAlert();
		}
	}
	ledcWrite(channel, 0);
}