/*
 * External_INT.c
 *
 *  Created on: Apr 5, 2023
 *      Author: HAZEM-PC
 */

/*============= FILE INCLUSION =============*/
#include "ext_int.h"

/*============= GLOBAL VARAIBLES =============*/
static  void (*g_callBackPtr_0)(void) = NULL_PTR;
static  void (*g_callBackPtr_1)(void) = NULL_PTR;
static  void (*g_callBackPtr_2)(void) = NULL_PTR;


/*============= FUNCTION DEFINITION =============*/
void INT_init(ST_INT_Config* Int_config)
{
	SREG  &= ~(1<<7);				// Disable interrupts by clearing I-bit
	switch (Int_config->source)
	{
	case EN_INT0:
	{
		CLEAR_BIT(DDRD,INT0_pin);
		SET_BIT(GICR,INT0);				// Enable external interrupt pin INT0
		switch (Int_config->trigger)
		{
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;
		case ANY_CHANGE:
			SET_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;
		case FALLING:
			CLEAR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		case RISING:
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		default:
			break;
		}
	}
	break;
	case EN_INT1:
	{
		CLEAR_BIT(DDRD,INT1_pin);	// Configure INT1/PD3/pin17 as input pin
		SET_BIT(GICR,INT1);			// Enable external interrupt pin INT1
		switch (Int_config->trigger)
		{
		case LOW_LEVEL:
			CLEAR_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
			break;
		case ANY_CHANGE:
			SET_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
			break;
		case FALLING:
			CLEAR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
		case RISING:
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
			break;
		default:
			break;
		}
	}
	break;
	case EN_INT2:
	{
		CLEAR_BIT(DDRB,INT2_pin);	// Configure INT2/PB2/pin3 as input pin
		SET_BIT(GICR,INT2);			// Enable external interrupt pin INT2
		switch (Int_config->trigger)
		{
		case FALLING:
			CLEAR_BIT(MCUCSR,ISC2);
			break;
		case RISING:
			SET_BIT(MCUCSR,ISC2);
			break;
		default:
			break;
		}
	}
	break;
	}
	SREG  |= (1<<7);                // Enable interrupts by setting I-bit
}


void INT0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr_0=a_ptr;
}

void INT1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr_1=a_ptr;
}

void INT2_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr_2=a_ptr;
}

void INT_Deinit(ST_INT_Config* Int_config)
{
	CLEAR_BIT(SREG,PIN7);				// Disable interrupts by clearing I-bit
	switch (Int_config->source)
	{
	case EN_INT0:
		CLEAR_BIT(GICR,INT0);			// Disable external interrupt pin INT0
		break;
	case EN_INT1:
		CLEAR_BIT(GICR,INT1);			// Disable external interrupt pin INT1
		break;
	case EN_INT2:
		CLEAR_BIT(GICR,INT2);			// Disable external interrupt pin INT2
		break;
		default:
		{
			//do nothing
		}
		break;
	}
	SET_BIT(SREG,PIN7);       			// Enable interrupts by setting I-bit
}

ISR_HANDLER(EXT_INT0)
{
	if(g_callBackPtr_0 != NULL_PTR)
		{
			g_callBackPtr_0();
		}
}


ISR_HANDLER(EXT_INT1)
{
	if(g_callBackPtr_1 != NULL_PTR)
		{
			g_callBackPtr_1();
		}
}

ISR_HANDLER(EXT_INT2)
{
	if(g_callBackPtr_2 != NULL_PTR)
		{
			g_callBackPtr_2();
		}
}
