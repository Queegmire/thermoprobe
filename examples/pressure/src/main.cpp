#include <Arduino.h>

const double VCC = 3.3;
const double adc_resolution = 4095; // 12-bit


void setup() {
  Serial.begin(115200);
}

void loop() {
  double Vout, adc_value; 

  adc_value = analogRead(GPIO_NUM_34);
  Serial.print("adc_value = ");
  Serial.println(adc_value);
  Vout = (adc_value * VCC) / adc_resolution;
  Serial.print("Vout = ");
  Serial.println(Vout);
  // need calibration to convert Vout to PSI
  delay(2500);
}
