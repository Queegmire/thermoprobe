

DROK Temperature Sensor Probe, 10k Ohm - [Source](https://www.amazon.com/DROK-Waterproof-Temperature-Thermistor-Transimitter/dp/B01MR37GOQ/)

- Type : NTC 10K/B3950 1%

Note: ADC2 pins and wifi can have conflicts on ESP32 Devkit v1 DOIT. Use ADC1 pin.

Use [Steinhart–Hart equation](https://en.wikipedia.org/wiki/Steinhart–Hart_equation)

Readings with current settings seem good at room temperature, but are too low as the temperature rises.
How to recalculate?

Code base on [Thermistor Interfacing with NodeMCU](https://www.electronicwings.com/nodemcu/thermistor-interfacing-with-nodemcu)

