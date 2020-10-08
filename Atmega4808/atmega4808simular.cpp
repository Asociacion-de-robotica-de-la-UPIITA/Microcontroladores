/*
 * atmega4808simular.cpp
 *
 * Created: 25/08/2020 19:59:03
 * Author : xdzohlx
 */ 
#define F_CPU 20000000 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	PORTMUX_TCAROUTEA |= (1<<PORTMUX_TCA0_PORTA_gc);
	//PORTA_DIR |= (1<<PORTA0);
	PORTA_DIRSET |= (1<<PORTA0);

    while (1){
		PORTA_OUTSET |= (1<<PORTA0);
		_delay_ms(1000);
		PORTA_OUTCLR |= (1<<PORTA0);
		_delay_ms(1000);		
    }
}