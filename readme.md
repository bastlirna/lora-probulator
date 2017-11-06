# LoRa Probulator

*Yat Another LoRaWAN Tester*

<img src="https://img.shields.io/badge/HW_status-in%20done-green.svg" alt="status: in progress"> <img src="https://img.shields.io/badge/FW_status-in%20progress-yellow.svg" alt="status: in progress">

<p align="center">
<img src="https://raw.githubusercontent.com/bastlirna/lora-probulator/master/photo/front.jpg" height="460" alt="LoRa Probulator photo">
</p>

## Motivation

TBD

## BOM

What do you need:

- Wemos LOLIN32 (ESP32 board with USB converter and battery charger)
- RFM95 (LoRa radio module)
- I2C OLED display
- 2 buttons and switch
- SMA pcb edge connector + 868 MHz antenna 
- Few resistors and capacitors
- Li-Pol battery (300 mAh)
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