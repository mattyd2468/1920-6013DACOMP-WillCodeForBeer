#include "SDCard.h"
#include <Arduino.h>
#include <DHTesp.h>
#include <HardwareSerial.h>
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <Vector.h>
#include "enums/PIRStatus.h"

/*
 * CS	PIN 5
 * SCK	PIN 18
 * MOSI	PIN 23
 * MISO	PIN 19
 * VCC	PIN 5V
 * GND	PIN GND
 * PIN 10 needs to be empty
 */

SDCard::SDCard()
{
	// do nothing
}

SDCard::SDCard(int CS_PIN)
{
	Serial.begin(115200);

	Serial.print("Initializing SD card...");
	pinMode(10, OUTPUT); // this needs to be kept as an empty pin in order for the card to work!

	SD.begin(CS_PIN);
	if (!SD.begin(CS_PIN))
	{
		Serial.println("Card Mount Failed");
		return;
	}
	uint8_t cardType = SD.cardType();
	if (cardType == CARD_NONE)
	{
		Serial.println("No SD card attached");
		return;
	}
	if (!SD.begin(CS_PIN))
	{
		Serial.println("initialization failed!");
		return;
	}

	Serial.println("initialization done.");

	this->logging.begin(); // start our vector
}

/**
 * This method stores our DHT11 readings onto our vector for writing to our SD card later
 */
void SDCard::storeDHT11Readings(String temp, String humidity)
{
	logging.push_back("Temperature: " + temp + "°C");
	logging.push_back("Humidity: " + humidity + "%");
}

/**
 * This method stores our PIR readings onto our vector for writing to our SD card later
 */
void SDCard::storePIRReadings(String pirStatus)
{
	logging.push_back("Building Status: " + pirStatus);
}

boolean SDCard::timeDiff(unsigned long start, int specifiedDelay)
{
	return (millis() - start >= specifiedDelay);
}

/**
 * This method will write everything stored in our vector (logging) to the SD card and once done will 
 * clear our logging from local volatile memory (our vetor)
 */
void SDCard::writeToSDCard()
{

	if (timeDiff(this->MILLIS, this->DELAY))
	{
		Serial.println("Writing to SD Card....");
		this->MILLIS = millis();

		// opens the appropriate file
		File myFile = SD.open("/Becky.txt", FILE_APPEND);

		if (myFile)
		{
			// loop through our vector and write each line to the file
			for (const auto &e : this->logging)
			{
				myFile.print("THIS NEEDS TO BE A TIMESTAMP: ");
				myFile.println(e);
			}

			myFile.close(); // closes the file once writing is complete
			Serial.println("Write complete....");
			this->logging.clear(); // empty vector now as we have writting it all to our file
		}
		else
		{
			// if the file didn't open, print an error:
			Serial.println("Error opening file");
		}

	}
}