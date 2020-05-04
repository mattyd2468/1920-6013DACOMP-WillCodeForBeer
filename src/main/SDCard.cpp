#include "SDCard.h"
#include <Arduino.h>
#include <DHTesp.h>
#include <HardwareSerial.h>
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <Vector.h>
#include "enums/PIRStatus.h"

using namespace std;

String dateTime[6];
String localDate;
String wifiTime;
String logname; // the name of the file being written to

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

/**
 * This method will get the month as a string (e.g. JAN, FEB, MAR) and convert it to the corresponding number
 */
String SDCard::formatMonth(String month)
{

	if (month.equalsIgnoreCase("Jan"))
	{
		return "01";
	}
	else if (month.equalsIgnoreCase("Feb"))
	{
		return "02";
	}
	else if (month.equalsIgnoreCase("Mar"))
	{
		return "03";
	}
	else if (month.equalsIgnoreCase("Apr"))
	{
		return "04";
	}
	else if (month.equalsIgnoreCase("May"))
	{
		return "05";
	}
	else if (month.equalsIgnoreCase("Jun"))
	{
		return "06";
	}
	else if (month.equalsIgnoreCase("Jul"))
	{
		return "07";
	}
	else if (month.equalsIgnoreCase("Aug"))
	{
		return "08";
	}
	else if (month.equalsIgnoreCase("Sep"))
	{
		return "09";
	}
	else if (month.equalsIgnoreCase("Oct"))
	{
		return "10";
	}
	else if (month.equalsIgnoreCase("Nov"))
	{
		return "11";
	}
	else if (month.equalsIgnoreCase("Dec"))
	{
		return "12";
	}
	return "01";
}

/**
 * This method will break the full date/time string into date and time variables
 */
void SDCard::formatDate(String date)
{
	String array[7];
	int i = 0;
	String word;
	for (char &c : date)
	{
		if (c == ' ' || c == ',')
		{
			array[i] = word;
			word = "";
			i++;
		}
		else
		{
			word.concat(c);
		}
	}

	// format the date and time
	String year = array[4];
	String month = array[3];
	month = formatMonth(month);
	String day = array[2];
	String localtime = array[5];

	// set the date
	localDate = (day + "-" + month + "-" + year);

	// set the time
	wifiTime = localtime;
	
	Serial.print("The date and time is: ");
	Serial.println(localDate + " " + wifiTime);

	// create file name for sd card
	logname = ("/" + localDate + ".txt");
	Serial.println("The file name for the SD card is: " + logname);
}


SDCard::SDCard(int CS_PIN, String date)
{
	Serial.begin(115200);

	Serial.println("Initializing SD card...");
	pinMode(10, OUTPUT); // this needs to be kept as an empty pin in order for the card to work!
	this->date = date;

	this->CS_PIN = CS_PIN;
	
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

	formatDate(date);

	File myFile = SD.open(logname, FILE_WRITE);
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
		File myFile;

		// opens the appropriate file
		myFile = SD.open(logname, FILE_APPEND);

		if (myFile)
		{
			// loop through our vector and write each line to the file
			for (const auto &e : this->logging)
			{
				myFile.print(localDate + " " + wifiTime + "		");
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
