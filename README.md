This project is a very simple emulator of an I2C flash for AVR microcontrollers,
designed to trigger BootROM recovery mode on Amlogic SoCs like the S905Y2.
See [here][1] and [here][2] for prior work. Unlike the Arduino sketch in the
Exploitee.rs release, which was designed for the ARM core on an Arduino Due,
this implementation is fast enough to avoid clock stretching on an AVR core,
which is critical since Amlogic's BootROM I2C master does not support clock
stretching.

I've tested this on an Arduino Duemilanove, but it will definitely work on any
board with an ATmega48/88/168/328, and possibly others. Just set `MCU`
appropriately in the Makefile.

To use, attach the SCL and SDA DDC lines (pins 15 and 16, respectively) of an
HDMI breakout to the I2C lines on your AVR (which are PC5 and PC4, respectively,
on the ATmega48/88/168/328), attach HDMI pin 17 to GND, and shunt HDMI pins 18
and 19 together, then connect that to your target device and apply power to it.
The SoC should enter BootROM USB DFU mode with no additional interaction needed.

[1]: https://www.exploitee.rs/index.php/FireFU_Exploit
[2]: https://github.com/superna9999/linux/wiki/Amlogic-HDMI-Boot-Dongle
