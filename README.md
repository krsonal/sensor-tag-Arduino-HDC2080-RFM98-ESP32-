# sensor-tag
A sensor tag M2M network using atmega328p as a microcontroller and LORA RFM98 as a transmitter module to sense humidity and temperature. 
## Main Features
* This module will sense the data and send it to the gateway at aa predefined interval.
* Works on 3.7 li-Ion battery.
* Power efficient sensor node with battery indication.
* When antenna is connected to the module then the node can transmit upto a range of 1 kilometer.


## Hardware
*  3.3V 16MHz (with ATmega328P)
* 3.3V RFM98 module
* TI HDC2080 temperature and humidity sensor

## Materials
* Arduino code with sleep mode and the rfm connections.
* Similar ESP32 code with sleep mode and transmission btu it consumes more power as compared to Arduino328p.
* Reciever code.
* HDC2080 Datasheet.
* Rfm98 datasheet.
* Arduino 328p Datasheet.
* ESP32 Datasheet.
* Li-Ion battery.

## Software

### Installation on Arduino IDE 1.8+

1. Add the following URL to the Arduino Boards Manager (*File->Preferences*).
   ```
   https://github.com/watterott/ATmega328PB-Testing/raw/master/package_m328pb_index.json
   ```

2. Update the **Arduino AVR Boards** to version **1.6.22** or higher via the Boards Manager (*Tools->Boards->Boards Manager*).

3. Install the **ATmega328PB Boards** via the Boards Manager (*Tools->Boards->Boards Manager*).




