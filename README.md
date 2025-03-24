# Consentium IoT ESP32 OTA Service

## Overview

This project implements an Over-the-Air (OTA) update service using Consentium IoT on an ESP32. The device collects temperature and humidity data from a DHT11 sensor and uploads it to the Consentium IoT cloud. Additionally, the device can receive firmware updates remotely.

## Features
 - Version 0.0: Initial version that uploads only temperature data.
 - Version 0.1: Enhanced to upload both temperature and humidity data.
 - Periodically sends sensor data to the Consentium IoT cloud.
 - Checks for OTA updates every 10 cycles and updates firmware if a new version is available.

## Hardware Requirements
 - ESP32 development board.
 - DHT11 Temperature & Humidity Sensor.
 - WiFi connection.

 ## Software Requirements
  - Consentiumiot Board API. (Setup guide for Consentiumiot: https://docs.consentiumiot.com/readme/consentium-iot-platform-usage)
  - ConsentiumThings library.
  - DHT sensor library.
  - Arduino IDE.

 ## Installation & Setup

 ### Install required libraries in Arduino IDE:
 - ConsentiumThings.
 - DHT Sensor Library

 ### Update WiFi credentials in *main()*
 
 ```cpp

const char *ssid = "YOUR_WIFI_SSID";
const char *pass = "YOUR_WIFI_PASSWORD";
```

 ### Update API keys in *main()*.
 ```cpp:

const char *SendApiKey = "YOUR_SEND_API_KEY";
const char *ReceiveApiKey = "YOUR_RECEIVE_API_KEY";
const char *BoardApiKey = "YOUR_BOARD_API_KEY";
```
 - Upload the code to your ESP32.
 - Monitor the serial output to check data transmission and OTA update status.

 ## Code Explanation
 ### Setup Function
 - Initializes WiFi and Consentium IoT services.
 - Enables OTA update checking.
 - Initializes the DHT11 sensor.

 ### Loop Function
 - Reads temperature and humidity from DHT11.
 - Sends data to Consentium IoT.
 - Checks for OTA updates every 10 cycles.
 - Delays for 5 seconds before the next transmission.
