#include <Arduino.h>

const double VCC = 3.3;
const double R = 10000; // 10k ohm
const double adc_resolution = 4095; // 12-bit

const double A = 0.001129148;
const double B = 0.000234125;
const double C = 0.0000000876741; 

void setup() {
  Serial.begin(115200);
}

void loop() {
  double Vout, Rth, temperature, adc_value; 

  adc_value = analogRead(GPIO_NUM_34);
  Vout = (adc_value * VCC) / adc_resolution;
  Rth = (VCC * R / Vout) - R;

/*  Steinhart-Hart Thermistor Equation:
 *  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)
 *  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)), 3))));   // Temperature in kelvin

  temperature = temperature - 273.15;  // Temperature in degree celsius
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" degree celsius");
  delay(2000);
}