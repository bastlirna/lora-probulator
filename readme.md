# LoRa Probulator

<img src="https://raw.githubusercontent.com/bastlirna/lora-probulator/master/photo/front.jpg" height="200" alt="LoRa Probulator photo" align="right">

*Yat Another LoRaWAN Tester*

<img src="https://img.shields.io/badge/HW_status-in%20done-green.svg" alt="status: in progress"> <img src="https://img.shields.io/badge/FW_status-in%20progress-yellow.svg" alt="status: in progress">

<br>

## Motivation

TBD


## Key Features

- Send LoRaWAN message on button press
- Periodic sending
- Configurable message parameters (confirmation, payload, SF, etc.)
- Multiple device (ABP/OTAA, several keys configuration for testing several network providers)  

For more detail about features see [Firmware project](https://github.com/bastlirna/lora-probulator/projects/1) where are list of all ideas, selected requirements and progress of its implementation.

## Build

### Hardware

What do you need:

- [BOM](hw/bom.md)
- [PCB](https://github.com/bastlirna/lora-probulator/blob/master/hw/pcb/lora-tester-top.png)
- [3D printed enclosure ](https://github.com/bastlirna/lora-probulator/blob/master/hw/enclosure/stl/_full_preview.stl) 

For more detail see [schematics](https://github.com/bastlirna/lora-probulator/blob/master/hw/lora-tester.pdf).

### Firmware

FW is written in [Arduino libraries for ESP32](https://github.com/espressif/arduino-esp32) and build with [PlatformIO](http://platformio.org/). 
