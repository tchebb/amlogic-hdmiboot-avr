#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/twi.h>

const uint8_t emulated_addr = 0x52;

const uint8_t emulated_data[] = "boot@USB";
//const uint8_t emulated_data[] = "boot@SDC";
const uint8_t emulated_data_start = 0xf8;

ISR(TWI_vect) {
	static uint8_t cur_addr = 0;

	uint8_t offset;

	switch (TWSR) {
	case TW_SR_DATA_ACK:
		// Received address command.
		cur_addr = TWDR;
		break;
	case TW_ST_SLA_ACK:
	case TW_ST_DATA_ACK:
		// Received data read at current address.
		offset = cur_addr - emulated_data_start;
		TWDR = offset < sizeof(emulated_data) ? emulated_data[offset] : 0;
		cur_addr++;
	}

	// Acknowledge interrupt to let hardware continue.
	TWCR |= _BV(TWINT);
}

int main() {
	// Enable internal pull-ups on I2C pins.
	PORTC = _BV(4) | _BV(5);

	// Configure slave address.
	TWAR = emulated_addr << 1;

	// Turn on TWI in slave mode, enable interrupt.
	sei();
	TWCR = _BV(TWEA) | _BV(TWEN) | _BV(TWIE);

	// Sleep the CPU, since we do all our work in interrupts.
	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();
	while (1) {
		sleep_cpu();
	}
}
