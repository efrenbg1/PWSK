/*
 * macros.h
 *
 * Created: 18/05/2020 12:10:18
 *  Author: efrenbg1
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define PIN0_OUTPUT() DDRB = 0b1;
#define PINB_INPUT() DDRB = 0;

#define T1_CLEAR_ON_MATCH() TCCR1 |= (1 << CTC1);
#define T1_INTERRUPT_ON_MATCH() TIMSK |= (1 << OCIE1A);
#define T1_INTERRUPT_DISABLE() TIMSK &= ~(1 << OCIE1A);
#define T1_PRESCALER_4() TCCR1 |= 0b11;
#define T1_PRESCALER_64() TCCR1 |= 0b111;
#define T1_CLEAR() TCNT1 = 0;

#define INTERRUPT_1() OCR1C = 205;
#define INTERRUPT_1_END() OCR1C = 51;
#define INTERRUPT_0() OCR1C = 51;
#define INTERRUPT_0_END() OCR1C = 205;
#define INTERRUPT_0_5() OCR1C = 128;
#define CURRENTbit OCR1C > 52

#define HIGH() PORTB |= 0b1;
#define LOW() PORTB &= ~0b1;
#define TXon PORTB & 0b1

#define ADC_INTERNAL_REFERENCE() ADMUX |= (1 << REFS0);
#define ADC_ENABLE_ADC3() ADMUX |= (1 << MUX0) | (1 << MUX1);
#define ADC_LEFT_ADJUST() ADMUX |= (1 << ADLAR); // 8 bit precision of ADC (ADCH contains data)
#define ADC_PRESCALER_8() ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
#define ADC_PRESCALER_128() ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
#define ADC_ENABLE() ADCSRA |= (1 << ADEN);
#define ADC_DISABLE() ADCSRA &= ~(1 << ADEN); 
#define ADC_SAMPLE() ADCSRA |= (1 << ADSC);
#define ADC_WAIT ADCSRA & (1 << ADSC)
#define ADC_READ ADCH;

#define IDLE_MODE() MCUCR &= ~((1 << SM1) | (1 << SM0)); 

#define SLEEP_ENABLE() MCUCR = (1 << SE) | (1 << SM1) | (0 << SM0) | (0 << BODSE); // Config power down sleep without brown out detector
#define SLEEP_SAVING_MODE() PRR = 0b1111; // Turn off all preipherals
#define SLEEP_POWER_UP() PRR = 0; // Turn off all preipherals
#define SLEEP_RESET() MCUSR = 0; // Clear reason for wake up
#define SLEEP_WATCHDOG_ENABLE() WDTCR = (1 << WDIE) | (1 << WDE) | (0 << WDP3) | (0 << WDP2) | (0 << WDP1) | (1 << WDP0);
#define SLEEP_WATCHDOG_CLEAR() WDTCR = (0 << WDIF) | (0 << WDIE) | (1 << WDCE) | (1 << WDE);
#define SLEEP_WATCHDOG_DISABLE() WDTCR &= ~(1 << WDE);

#endif /* MACROS_H_ */