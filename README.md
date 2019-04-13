# thermoprobe
ESP32 based temperature sensor with remote configuration

## Equipment

### Software

* Host running
  * Flask - Python Microframework
  * mysql database - for sensor history
  * hbmqtt - mqtt broker

### Hardware
* ESP32 - DOIT DEVKIT V1
* DHT11 - Temperature and humidity sensor
* LED indicator
* Switch 

## Goals

Basic operation will have the ESP32 board reading temperature and humidity periodically and send the data to the mqtt broker. The board will also accept a signal from the mqtt broker to take an immediate reading or to change the polling interval.

A dashboard built in flask will display current readings and configuration as well as historical charts.
 

