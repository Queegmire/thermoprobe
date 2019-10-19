#include <Arduino.h>

#define PWM_LED 2
#define BASIC_LED 13

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

const int cycles = 3;

void setup() {
  Serial.begin(115200);

  // configure led for PWM
  pinMode(PWM_LED, OUTPUT);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(PWM_LED, ledChannel);

  // configure led for on/off
  pinMode(BASIC_LED, OUTPUT);
}

void loop() {
	// first pulse with PWM
    for (int blinks = 0; blinks < cycles; blinks++) {
        for (int dutyCycle = 0; dutyCycle <= 250; dutyCycle += 2) {
            ledcWrite(ledChannel, dutyCycle);
            delay(1);
        }
     
        for (int dutyCycle = 250; dutyCycle >= 0; dutyCycle -= 2) {
            ledcWrite(ledChannel, dutyCycle);
            delay(1);
        }
    }        
    delay(1000);
    // next pulse on/off
    for (int blinks = 0; blinks < cycles; blinks++) {
	    digitalWrite(BASIC_LED, HIGH);
	  	delay(125);
	  	digitalWrite(BASIC_LED, LOW);
	  	delay(125);
	}
	delay(1000);
}

