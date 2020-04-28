#include "BUZZER.h"
#include "LED.h"

BUZZER::BUZZER() {
	//taskG setup
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(BUZZER_PIN, channel);
}

BUZZER::BUZZER(PIR *pir)
{
	//taskG setup
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(BUZZER_PIN, channel);
	this->pir = pir;
	this->buzzerStatus = BuzzerStatus::NONE;
	this->buzzerSnooze = false;
}

boolean BUZZER::timeDiff(unsigned long start, int specifiedDelay){
    return (millis() - start >= specifiedDelay);
}

void BUZZER::buzz() {
	ledcWrite(channel, dutyCycle);
	delay(1000);
	ledcWrite(channel, 0);
	this->buzzerSnooze = false;
}

/**
 * This will make a noise if last noise was less than 30 seconds ago
 */
void BUZZER::audibleAmberAlert() {
	if (timeDiff(this->alertMillis, AMBER_ALERT_SOUND_DELAY)) {
		this->alertMillis = millis();
		Serial.println("Amber buzz");
		this->buzzerStatus = BuzzerStatus::AMBER;
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
		this->buzzerStatus = BuzzerStatus::RED;
		buzz();
	}
}

/**
 * Check if it should call method to make noise
 */
void BUZZER::whichAlertToMake(TemperatureStatus tempStatus, HumidityStatus humStatus)
{
	if (pir->getPIRStatus() == "OCCUPIED") {
		if (tempStatus == TemperatureStatus::RED || humStatus == HumidityStatus::RED) {
			this->buzzerStatus = BuzzerStatus::RED;
			audibleRedAlert();
		} else if (tempStatus == TemperatureStatus::AMBER || humStatus == HumidityStatus::AMBER) {
			audibleAmberAlert();
			this->buzzerStatus = BuzzerStatus::AMBER;
		} else {
			this->buzzerStatus = BuzzerStatus::NONE;
		}
	} else {
		// building is vacant
		this->buzzerStatus = BuzzerStatus::NONE;
	}
	ledcWrite(channel, 0);
}

String BUZZER::getBuzzerStatus()
{
	if (buzzerStatus == BuzzerStatus::AMBER)
	{
		return "Amber Buzz";
	}
	if (buzzerStatus == BuzzerStatus::RED)
	{
		return "Red Buzz";
	}
	return "No Buzz";
}

String BUZZER::getBuzzerSnooze()
{
	if (buzzerSnooze)
	{
		return "Yes";
	}
	else
	{
		return "No";
	}
}