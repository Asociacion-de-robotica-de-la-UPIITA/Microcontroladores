/*
 * Botón.c
 *
 * Created: 09/10/2020 23:25:23
 * Author : xDzohlx
 */ 

#include <avr/io.h>

int main(void)
{
    PORTA.DIRSET |= PIN2_bm;//DIRECCION DE SALIDA EN EL PA2
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm;//RESISTENCIA DE PULLUP PARA PA1
	while (1){
		if(PORTA.IN & PIN1_bm){//LECTURA DEL BOTON, EL BOTÓN CONECTA CON TIERRA POR LO QUE EL IF ENTRA CUANDO NO ESTA PRESIONADO
			PORTA.OUTCLR |= PIN2_bm;//APAGA EL LED, PONE EN ALTO EL PIN PA2
			}else{
			PORTA.OUTSET |= PIN2_bm;//PRENDE EL LED, PONE EN BAJO EL PIN PA2
		}
    }
}

