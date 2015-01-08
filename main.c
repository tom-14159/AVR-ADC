#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

void initADC () {
	ADMUX = (1 << ADLAR) | (1 << MUX0) | (1 << MUX1); // ADC3

	ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1);
	ADCSRB = 0;

	sei();

	ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
	static uint8_t val;
	val = ADCH;

	if (val >= 16) {	// ~ 0.3 V
		PORTB = 0x01;
	} else {
		PORTB = 0x00;
	}
}

int main() {
	cli();
	DDRB |= (1 << PB0);
	initADC();
	for (;;) {}
}
