/*
 * Decodificador ppm.c
 *
 * Created: 02/12/2020 21:44:54
 * Author : Usuario
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile static uint16_t canal[6];
int cont = 0;

void setup(void){
	DDRA |= (1<<PORTA0)|(1<<PORTA1)|(1<<PORTA2)|(1<<PORTA3)|(1<<PORTA7);//pines de salida del decodificador
	PCICR |= (1<<PCIE2);//Habilita las interrupciones por cambio de estado en este caso la 2
	PCMSK2 |= (1<<PCINT18);//Habilita el pin 0 de la interrupcion que es el PORTC2
	//Configuracion de timer de 16 bits para lectura de ppm con microsegundos
	TCCR1B = (1<<WGM12)|(1<<CS11);//Seleccion de reloj y forma de donda en este caso sirve para captura
	
	OCR1A = 0xFA0;//valor de sincronizacion
	//Interrupciones
	TIMSK1 = (1<<OCIE1A);//Habilita interrupciones del timer
	
	TCNT1 = 0x0000;//Reinicia el contador
	sei();//Activa interrupciones globales
}
//Interrupcion por cambio de estado para lectura
ISR(PCINT2_vect){
	PORTA ^= (1<<PORTA7);
	if (!(PINC & 0x04)){//checa el cambio en el pin si es bajo
		if (cont == 0){//flanco de subida canal 1
			PORTA |= (1<<PORTA0);
		}
		if (cont > 0){// lectura del canal no es necesario para decodificador
			canal[cont -1]=TCNT1;//lectura del canal no necesario para salida decodificada
			PORTA = (PORTA<<1);
		}
		TCNT1 = 0x00;//reinicio del timer del canal
		cont++;//siguiente canal
	}
}
ISR(TIMER1_COMPA_vect){//Segundo vector de interrupcion, sincronizacion
	cont = 0;//reinicia la posicion de los canales
	PORTA &= ~(1<<PORTA7);//se apaga en la sincronicación si el led esta apagago es que no hay coneccción

}
int main(void){
	setup();//inizializacion
	while(1){
	}
}

