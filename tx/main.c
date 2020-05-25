/*
 * bacon.c
 *
 * Created: 17/05/2020 19:23:26
 * Author : efrenbg1
 */ 
#include <avr/interrupt.h>
#include "macros.h"

void INT1_CONFIG(){
	T1_CLEAR_ON_MATCH();
	T1_PRESCALER_64();
	INTERRUPT_0_5();
	T1_CLEAR();
	T1_INTERRUPT_ON_MATCH();
}

void ADC_CONFIG(){
	ADC_INTERNAL_REFERENCE();
	ADC_ENABLE_ADC3();
	ADC_LEFT_ADJUST();
	ADC_PRESCALER_128();
	ADC_ENABLE();
}

volatile char *msg = "hello";
#define MSG_SIZE 2
volatile int a = 0;
volatile int c = 0;
volatile int b = 8;
volatile int transmitting = 1;

ISR(WDT_vect)
{
	SLEEP_WATCHDOG_CLEAR();
	SLEEP_WATCHDOG_DISABLE();
	PIN0_OUTPUT();
	INT1_CONFIG();
	transmitting = 1;
}

ISR(TIMER1_COMPA_vect){
	if(TXon){
		LOW();
		if(b == 8){
			b--;
			return;
		}
		if(CURRENTbit){
			INTERRUPT_1_END();
		} else {
			INTERRUPT_0_END();
		}
		if(b < 0){
			b = 8;
			c++;
			if(c == MSG_SIZE){ // DONE sending msg
				c = 0;
				transmitting = 0;
				T1_INTERRUPT_DISABLE();
			}
		}
		return;
	}
	HIGH();
	if(b == 8){ // Sync pulse
		INTERRUPT_0_5();
		return;
	}
	if(msg[c] & (0b1 << b)){ // bit is a 1
		INTERRUPT_1();
	} else { // bit is a 0
		INTERRUPT_0();
	}
	b--;
}


int main(void)
{	
	SLEEP_WATCHDOG_CLEAR();
	SLEEP_WATCHDOG_DISABLE();
	
	PIN0_OUTPUT();
	
	INT1_CONFIG();

	//ADC_CONFIG();
	sei();
	
    while (1) 
    {
		while(transmitting){// do nothing
		}
		SLEEP_WATCHDOG_ENABLE();
		SLEEP_ENABLE();
		/*
		ADC_SAMPLE();
		while(ADC_WAIT){
			asm("nop");
		}
		a = ADC_READ;*/
    }
}

