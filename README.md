# QR Based Automated Food Dispenser System using ESP32

## Overview
An IoT based automated food dispensing system that uses ESP32 and Firebase Firestore for smart food order verification and dispensing.

The system verifies user orders through QR code authentication and automatically dispenses the required quantity of food using sensors and motor control mechanisms.

## Features
- QR Code based order verification
- Firebase Firestore integration for real-time data access
- Automatic food dispensing system
- Weight measurement using HX711 Load Cell
- Container detection using Ultrasonic Sensor
- DC Motor based dispensing control
- Servo motor gate mechanism
- LCD display for system status
- WiFi based IoT connectivity


## Hardware Components

- ESP32 Development Board
- HX711 Load Cell Module
- HC-SR04 Ultrasonic Sensor
- DC Motors
- SG90 Servo Motors
- L298N Motor Driver
- 16x2 I2C LCD Display
- QR Code Scanner
- Power Supply


## Software & Tools Used

- Arduino IDE
- Embedded C
- Firebase Firestore
- Arduino Libraries


## Working Principle

1. User scans QR code generated after food booking.
2. ESP32 receives QR data and verifies order details from Firebase.
3. Ultrasonic sensor detects container placement.
4. Motor and servo mechanism starts dispensing food.
5. Load cell continuously measures food quantity.
6. System automatically stops when required weight is reached.


## Applications

- Smart Canteens
- Colleges
- Offices
- Automated Food Distribution Systems


## Developed By

Hariharan K S
Electronics and Communication Engineering
