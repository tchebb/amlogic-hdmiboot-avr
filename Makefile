MCU := atmega328p
PROGPORT := /dev/ttyUSB0

CC := avr-gcc
CFLAGS := -mmcu=$(MCU) -Wall -Wextra -O2
LDFLAGS := -mmcu=$(MCU)

i2c-flash: i2c-flash.o

.PHONY: program
program: i2c-flash
	avrdude -c arduino -p $(MCU) -b 57600 -P $(PROGPORT) -D -U flash:w:$<
