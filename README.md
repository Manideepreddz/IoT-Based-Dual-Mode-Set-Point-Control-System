IoT-Based Dual Mode Set Point Control System using LPC2148


The IoT-Based Dual Mode Set Point Control System is an embedded system designed to monitor temperature in real time and control threshold values using both local and remote interfaces. The system uses the LPC2148 ARM7 microcontroller as the central processing unit, integrates with the ESP8266 Wi-Fi module for cloud communication, and uses ThingSpeak cloud platform for remote monitoring and configuration.


This project demonstrates the integration of Embedded Systems, IoT, and Real-Time Control Systems.


The system  temperature data from the LM35 temperature sensor, compares it with a configurable set point, and activates a buzzer alert when the threshold is exceeded.


Users can modify the set point using two modes:
Local Mode – via Keypad
Remote Mode – via ThingSpeak Cloud
The configuration is stored in EEPROM to ensure persistence after power loss.

🎯 Objectives

• Monitor temperature in real time

• Allow user-defined temperature set point

• Enable remote monitoring via cloud

• Enable remote configuration via IoT

• Store configuration permanently in EEPROM

• Provide alert mechanism when threshold exceeds

• Implement interrupt-based local configuration



🧠 System Architecture

          LM35 Temperature Sensor
                   ▼
             ADC (LPC2148)
                   ▼
           LPC2148 ARM7 MCU
                     ├── EEPROM (Store Set Point)
                     ├── Keypad (Local Control)
                     ├── Buzzer (Alert)
                     ▼
         ESP8266 WiFi Module
                   ▼
             ThingSpeak Cloud
             
🔧 Hardware Components Used

Component	Description

1)LPC2148	ARM7 Microcontroller.

2)LM35	Temperature Sensor

3)ESP8266 (ESP-01)	WiFi Module

4)4x4 Keypad	Local Set Point Input

5)Buzzer	Alert System

6)EEPROM	Store Set Point

7)Power Supply	3.3V / 5V regulated

8)ADC	Built-in LPC2148 ADC

🖥 Software Requirements

• Keil uVision (ARM Compiler)
• Flash Magic (Program Uploading)
• ThingSpeak Cloud Account
• Embedded C Programming

⚙ Working Principle

The system works in the following sequence:

Step 1: Temperature Acquisition

The LM35 sensor outputs analog voltage proportional to temperature:

Temperature (°C) = Voltage (mV) / 10

Example:
250 mV = 25°C

This analog voltage is converted into digital value using LPC2148 ADC.


Step 2: Temperature Processing

The LPC2148 reads ADC value and converts it into temperature using formula:

Temp = (ADC_value × 3.3 × 100) / 1024

Step 3: Set Point Comparison

The system compares:

if(Current Temperature > Set Point)

   Activate Buzzer

else

   Normal Operation

   

Step 4: Local Set Point Configuration

User enters new set point using keypad.

Interrupt is used to detect keypad input instantly.

Steps:
• User presses keypad
• Interrupt triggered
• Microcontroller enters configuration mode
• New set point stored in EEPROM


Step 5: Remote Monitoring and Control

ESP8266 connects to WiFi and communicates with ThingSpeak using UART.

Functions:
• Upload temperature data to ThingSpeak
• Read set point value from ThingSpeak


Communication protocol used:

AT Commands

UART Serial Communication

Example AT Command:

AT+CIPSTART="TCP","api.thingspeak.com",80


Step 6: EEPROM Storage

EEPROM stores set point value permanently.

Even after power OFF/ON:

Set point remains same


Step 7: Alert Mechanism

If temperature exceeds set point:
• Buzzer turns ON
• Alert triggered

📡 Cloud Integration (ThingSpeak)

ThingSpeak is used for:

• Temperature monitoring
• Remote set point configuration
• Data logging


🧾 Firmware Modules

The firmware consists of following modules:
1. ADC Driver
Responsible for temperature reading.
Functions:
ADC_Init()
ADC_Read()

3. UART Driver
Used for ESP8266 communication.
Functions:
UART_Init()
UART_Send()
UART_Receive()

4. EEPROM Driver
Store and retrieve set point.
Functions:
EEPROM_Write()
EEPROM_Read()

5. Keypad Driver
Handles keypad input using interrupt.
Functions:
Keypad_Init()
Keypad_Read()

6. ESP8266 Driver
Handles IoT communication.
Functions:
ESP_Init()
ESP_SendData()
ESP_GetSetPoint()


🔄 System Flowchart

1.Start

2.Initialize System

3.Read EEPROM Set Point

4.Read Temperature from LM35 Send Data to ThingSpeak

5.Read Set Point from Cloud

6.Compare Temperature with Set Point
  
7.Temperature > Set Point ? Buzzer ON :Buzzer OFF

8.Check Keypad Interrupt
   
9.Update Set Point
   
10.Store in EEPROM
   
11.Repeat

🚀 Key Features 

Dual Mode Control
Mode	Description
Local	User enters set point using keypad
Remote	User updates set point using ThingSpeak
Interrupt Driven System
Interrupt improves performance by avoiding continuous polling.
EEPROM Storage
Ensures permanent storage.
Cloud Monitoring
User can monitor temperature from anywhere.

📊 Advantages

• Real-time monitoring

• Remote access

• Low power consumption

• Reliable system

• Permanent configuration storage

• Scalable design

📍 Applications

• Industrial temperature monitoring
• Smart homes
• Server room monitoring
• Cold storage monitoring
• Laboratory monitoring
• IoT automation systems
