/*
 * registers.h
 *
 * Created: 8/23/2023 9:18:44 PM
 *  Author: HP
 */ 
/****************************************************/
/* all micro controller registers */
/****************************************************/


#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "types.h"
#include "bits.h"

/****************************************************/
/* DIO Registers */
/****************************************************/
//PORTA Registers
#define PORTA *((volatile uint8_t*) 0x3B)
#define DDRA *((volatile uint8_t*) 0x3A)
#define PINA *((volatile uint8_t*) 0x39)

//PORTB registers 
#define PORTB *((volatile uint8_t*)0x38)
#define DDRB *((volatile uint8_t*)0x37)
#define PINB *((volatile uint8_t*)0x36)

//PORTC registers

#define PORTC *((volatile uint8_t*)0x35)
#define DDRC *((volatile uint8_t*)0x34)
#define PINC *((volatile uint8_t*)0x33)

//PORTD registers

#define PORTD *((volatile uint8_t*)0x32)
#define DDRD *((volatile uint8_t*)0x31)
#define PIND *((volatile uint8_t*)0x30)


/*************************************/
/* External INTERRUPTS REGISTERS     */
/*************************************/
#define GICR *((volatile uint8_t*)0x5B)
#define GIFR *((volatile uint8_t*)0x5A)
#define MCUCSR *((volatile uint8_t*)0x54)
#define MCUCR *((volatile uint8_t*)0x55)
/* MCUCR */
#define SE      7
#define SM2     6
#define SM1     5
#define SM0     4
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

#define SREG *((volatile uint8_t*)0x5F)

/************************************/
/*   TIMER REGISTERS                */
/************************************/

/***************************** TIMER_0 ******************************/
 
#define TCCR0 *((volatile uint8_t*)0x53)
#define TCNT0 *((volatile uint8_t*)0x52)
#define OCR0  (*((volatile uint8_t*)0x5C))
#define TIFR *((volatile uint8_t*)0x58)
#define TIMSK *((volatile uint8_t*)0x59)
//Timer 0 bits
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0 7


/***************************** TIMER_2 ******************************/
#define TCCR2   (*(volatile uint8_t*)0x45)
#define TCNT2   (*(volatile uint8_t*)0x44)
#define OCR2   (*(volatile uint8_t*)0x43)

/* GICR */
#define INT1    7
#define INT0    6
#define INT2    5
#define IVSEL   1
#define IVCE    0

/**TCCR2**/
#define CS20	0
#define CS21	1
#define CS22	2
#define WGM21	3
#define COM20	4
#define COM21	5
#define WGM20	6
#define FOC2	7

/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0

/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/* MCUCSR */
#define JTD     7
#define ISC2    6
#endif /* REGISTERS_H_ */