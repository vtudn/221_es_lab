# esp32_es

**SCENARIO**: The lab work of practices with the NodeMCU ESP32 embedded board and the Espressif IoT Development Framework (ESP-IDF), which is built based on the FreeRTOS platform.

- *ESP32*: a dual-core system with two Xtensa LX6 CPUs, where all embedded memory, external memory and peripherals are located on the data bus and/or the instruction bus of these CPUs. It supports 2.4 GHz Wi-Fi-and-Bluetooth.
- *NodeMCU*: an open source Lua-based firmware for the ESP32 and ESP8266 WiFi SOC from Espressif. It is implemented in C and is layered on the Espressif ESP-IDF. Up to now, the firmware can be run on any ESP module.
- *FreeRTOS*: free and open-source Real-Time Operating System, developed to fit on very small embedded systems with a very minimalist set of functions. This real-time kernel (or real-time scheduler) allows applications to be organized as a collection of independent threads of execution. On a processor that has only one core, only a single thread can be executing at any one time. The kernel decides which thread should be executed by examining the priority assigned to each thread by the application designer.
- *ESP-IDF*: a software development framework which provides basic software and hardware resources for ESP32 series.

**CONTENTS**:
- Read and write with ESP32 GPIO pins.
- Create, schedule, and destroy tasks in FreeRTOS.
- Configure the task scheduling algorithm (pre-emptive and co-operative) in FreeRTOS.
- Use FreeRTOS queues for tasks intercommunication.
- Use FreeRTOS software timer.
- Configure ESP32 Wi-Fi subsystem as an Access Point (AP) and a Station.
- Practice ESP32 Bluetooth Low Energy (BLE) by creating a simple server and scanner.
