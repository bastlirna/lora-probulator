# LoRa Probulator

<img src="https://raw.githubusercontent.com/bastlirna/lora-probulator/master/photo/front.jpg" height="200" alt="LoRa Probulator photo" align="right">

*Yat Another LoRaWAN Tester*

<img src="https://img.shields.io/badge/HW_status-in%20done-green.svg" alt="status: in progress"> <img src="https://img.shields.io/badge/FW_status-in%20progress-yellow.svg" alt="status: in progress">

<br>

## Motivation

TBD

## Build

What do you need:

- [BOM](hw/bom.md)
- [PCB](https://github.com/bastlirna/lora-probulator/blob/master/hw/pcb/lora-tester-top.png)
- [3D printed enclosure ](https://github.com/bastlirna/lora-probulator/blob/master/hw/enclosure/stl/_full_preview.stl) 

For more detail see [schematics](https://github.com/bastlirna/lora-probulator/blob/master/hw/lora-tester.pdf).

## Key Features

- Send LoRaWAN message and button press [done]
- Periodic sending
- Change message parameters
	- Confirmation [done]
	- Payload format
	- SF
- Contain multiple device (ABP/OTAA, several keys configuration for testing several network providers)  