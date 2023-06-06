/*
 * registers.h
 *
 * Created: 2023-06-05 7:15:38 PM
 *  Author: HAZEM-PC
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "std_types.h"

#define PORTA	(*((volatile uint8*)0x3B))
#define DDRA	(*((volatile uint8*)0x3A))
#define PINA	(*((volatile uint8*)0x39))

#define PORTB	(*((volatile uint8*)0x38))
#define DDRB	(*((volatile uint8*)0x37))
#define PINB	(*((volatile uint8*)0x36))

#define PORTC	(*((volatile uint8*)0x35))
#define DDRC	(*((volatile uint8*)0x34))
#define PINC	(*((volatile uint8*)0x33))

#define PORTD	(*((volatile uint8*)0x32))
#define DDRD	(*((volatile uint8*)0x31))
#define PIND	(*((volatile uint8*)0x30))


#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7
#define MAX_PIN 8


#endif /* REGISTERS_H_ */