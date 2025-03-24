# Consentium IoT ESP32 OTA Service

## Overview

This project implements an Over-the-Air (OTA) update service using Consentium IoT on an ESP32. The device collects temperature and humidity data from a DHT11 sensor and uploads it to the Consentium IoT cloud. Additionally, the device can receive firmware updates remotely.

## Features
 - Version 0.0: Initial version that uploads only temperature data.
 - Version 0.1: Enhanced to upload both temperature and humidity data.
 - Periodically sends sensor data to the Consentium IoT cloud.
 - Checks for OTA updates every 10 cycles and updates firmware if a new version is available.
