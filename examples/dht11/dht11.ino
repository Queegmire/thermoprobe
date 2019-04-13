#include <DHT.h>

#define DHTPIN 22
#define DHTTYPE DHT11
#define FARENHEIT false
#if FARENHEIT
    #define TEMP_UNIT "F"
#else
    #define TEMP_UNIT "C"
#endif

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    Serial.println("Testing DHT11 temperature sensor.");
    Serial.println("");
    dht.begin();
}

void loop()
{
    delay(5000);
    float h = dht.readHumidity();
    float t = dht.readTemperature(false);

    if (isnan(h) || isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    char buffer [42];
    sprintf(buffer, "Humidity: %2.0f%%, Temperature: %2.1f°%s", h, t, TEMP_UNIT);
    Serial.println(buffer);
}
