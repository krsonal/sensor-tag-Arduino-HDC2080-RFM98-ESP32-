# sensor-tag
A sensor tag M2M network using atmega328p as a microcontroller and LORA RFM98 as a transmitter module to sense humidity and temperature. 
# ATmega328PB Testing


## Hardware
*  3.3V 8MHz (with ATmega328PB)
* 3.3V RFM98 module
* TI HDC2080 temperature and humidity sensor



## Software

### Installation on Arduino IDE 1.8+

1. Add the following URL to the Arduino Boards Manager (*File->Preferences*).
   ```
   https://github.com/watterott/ATmega328PB-Testing/raw/master/package_m328pb_index.json
   ```

2. Update the **Arduino AVR Boards** to version **1.6.22** or higher via the Boards Manager (*Tools->Boards->Boards Manager*).

3. Install the **ATmega328PB Boards** via the Boards Manager (*Tools->Boards->Boards Manager*).


## Further Infos
* [Arduino AVR-GCC Toolchain with Atmega328PB support](https://github.com/arduino/toolchain-avr/pull/47)
* [Differences between ATmega328/P and ATmega328PB](http://ww1.microchip.com/downloads/en/AppNotes/Atmel-42559-Differences-between-ATmega328P-and-ATmega328PB_ApplicationNote_AT15007.pdf)
* [Another project/guide for the ATmega328PB](https://hackaday.io/project/9313-uino-mini-super-atmega328pb)
* [ATmega328PB Discussion in the Italian Arduino Forum](http://forum.arduino.cc/index.php?topic=374642.0)
* [Optiboot for ATmega328PB](https://github.com/watterott/Wattuino/tree/master/software/Optiboot#optiboot)



### Crystal Oscillator
The ATmega328PB has no full-swing option for the oscillator.


