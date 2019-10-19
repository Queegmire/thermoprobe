#include <Arduino.h>

#include <WiFi.h>
#include "config.h"

void setup() {
	Serial.begin(115200);

	Serial.print("Connecting to ");
	Serial.println(CONFIG_SSID);

	WiFi.begin(CONFIG_SSID, CONFIG_PASS);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println();
}


void loop() {
	delay(5000);
	// https://www.arduino.cc/en/Reference/WiFiStatus
	if (WiFi.status() == WL_CONNECTED) 
	{
		Serial.println("Status: Connected");
	} else {
		Serial.print("Status: Error ");
		Serial.println(WiFi.status());
	}
}
