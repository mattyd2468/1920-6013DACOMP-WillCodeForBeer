#include "main/Connect_WiFi.h"
#include <WiFi.h>
#include <WiFiType.h>
#include <HardwareSerial.h>
#include <IPAddress.h>
#include "HTTPClient.h"
#include "sensors/Thermometer.h"
#include "sensors/Humidity.h"
#include <DHTesp.h>
#include <WString.h>

using namespace std;

Connect_WiFi::Connect_WiFi(TempAndHumidity tempHum)
{
	this->tempHum = tempHum;
}

boolean Connect_WiFi::timeDiff(unsigned long start, int specifiedDelay)
{
	return (millis() - start >= specifiedDelay);
}

void Connect_WiFi::connectToHotspot()
{
	//WiFI
	Serial.print("Connecting to ");
	Serial.println(SSID);
	WiFi.begin(SSID, PASS);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(250);
		Serial.print(".");
	}
	Serial.print("Connected as :");
	Serial.println(WiFi.localIP());
}

/**
 * This will make a noise if last noise was less than 30 seconds ago
 */
void Connect_WiFi::writeToServer()
{
	if (timeDiff(serverMillis, this->WRITE_TO_SERVER_DELAY))
	{
		serverMillis = millis();

		// url parameters
		String url = this->HOST;
		url.concat("?groupname=");
		url.concat(this->GROUPNAME);
		url.concat("&t=");
		url.concat(tempHum.temperature);

		url.concat("&h=");
		url.concat(tempHum.humidity);

		HTTPClient hClient;
		hClient.begin(url);
		const char *headers[] = {"Date"};
		hClient.collectHeaders(headers, 1);
		hClient.setTimeout(TIMEOUT);
		int retCode = hClient.GET();
		if (retCode > 0)
		{
			//a real HTTP code
			Serial.print("HTTP ");
			Serial.println(retCode);
			if (retCode == HTTP_CODE_OK)
			{
				Serial.println("------");
				Serial.println("Date = " + hClient.header("Date"));
				Serial.println("-------");

				date = hClient.header("Date");
			}
		}
		else
		{
			Serial.println("Error... ");
			Serial.println(HTTPClient::errorToString(retCode));
		}
	}
}
