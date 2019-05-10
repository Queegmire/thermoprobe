#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <time.h>
#include "config.h"

#define DHTPIN 22 
#define DHTTYPE DHT11 
#define LEDPIN 2

// create sensor object
DHT dht(DHTPIN, DHTTYPE);

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

// set up ntp
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -25200;
const int   daylightOffset_sec = 0;

WiFiClient espClient;
PubSubClient PSclient(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int period = 60000;

void setup() {
  Serial.begin(115200);

  // connect to wifi, sensor and mqtt
  setup_wifi();
  dht.begin();
  PSclient.setServer(CONFIG_MQTT, 1883);
  PSclient.setCallback(callback);

  // configure led for PWM
  pinMode(LEDPIN, OUTPUT);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(LEDPIN, ledChannel);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void setup_wifi() {
  Serial.println();
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
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  
  if (String(topic) == "esp32/update") {
    if (messageTemp == "1") {
      update();
      PSclient.publish("esp32/update", "0"); 
    }
  }
  if (String(topic) == "esp32/interval") {
    int pint = messageTemp.toInt(); 
    period = pint * 1000;
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!PSclient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (PSclient.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      PSclient.subscribe("esp32/update");
      PSclient.subscribe("esp32/interval");
    } else {
      Serial.print("failed, rc=");
      Serial.print(PSclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

String getLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "Failed to obtain time";
  }
  char timeStringBuff[50]; //50 chars should be enough
  strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d  %H:%M:%S", &timeinfo);
  return String(timeStringBuff);
}

void update() {
    float temperature = dht.readTemperature();
    char tempString[8];
    dtostrf(temperature, 1, 1, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    PSclient.publish("esp32/temperature", tempString);

    float humidity = dht.readHumidity();
    char humString[8];
    dtostrf(humidity, 1, 0, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);
    PSclient.publish("esp32/humidity", humString);

    Serial.print("Time: ");
    String timeString = getLocalTime();
    Serial.println(timeString);
    const char *timeC = timeString.c_str();
    PSclient.publish("esp32/last", timeC);

    // blink onboard led twice
    for (int blinks = 0; blinks < 2; blinks++) {
        for (int dutyCycle = 0; dutyCycle <= 250; dutyCycle += 2) {
            ledcWrite(ledChannel, dutyCycle);
            delay(1);
        }
     
        for (int dutyCycle = 250; dutyCycle >= 0; dutyCycle -= 2) {
            ledcWrite(ledChannel, dutyCycle);
            delay(1);
        }
    }
}

void loop() {
  if (!PSclient.connected()) {
    reconnect();
    update(); // don't wait interval until first publish
  }

  delay(25);
  PSclient.loop();

  long now = millis();
  if (now - lastMsg > period) {
    lastMsg = now;
    update();
  }
}
