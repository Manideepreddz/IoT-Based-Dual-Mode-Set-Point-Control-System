# IoT-Based-Dual-Mode-Set-Point-Control-System
IoT-Based Dual Mode Set Point Control System.
🌡 IoT-Based Dual Mode Set Point Control System
📌 Project Overview

This project implements an IoT-enabled temperature monitoring and threshold control system using LPC2148 ARM7 microcontroller. The system supports both local and remote set point modification with cloud-based monitoring.

🚀 Features

Real-time temperature monitoring using LM35

Cloud integration using ESP8266 (ESP-01)

ThingSpeak data logging

Dual mode set point control:

Local via keypad

Remote via cloud

EEPROM-based configuration storage

Buzzer alert on threshold exceed

Interrupt-driven local configuration

Optimized cloud polling mechanism

🏗 System Architecture
LM35 → ADC → LPC2148 → ESP01 → ThingSpeak Cloud
                 ↓
              EEPROM
                 ↓
             Keypad (Local)
                 ↓
              Buzzer Alert
