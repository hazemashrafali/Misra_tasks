/*
 * button.c
 *
 * Created: 2023-06-05 11:21:45 PM
 *  Author: HAZEM-PC
 */ 

/*============= FILE INCLUSION =============*/
#include "button.h"

/*============= FUNCTION DEFINITIONS =============*/

enu_error_state_t button_init(uint8 port,uint8 pin)
{
	enu_error_state_t enu_error_state = VALID_OPERATION;
	enu_error_state = DIO_pinMode(port,pin,PIN_INPUT);
	return enu_error_state;
}


enu_error_state_t button_enable_pullup (uint8 port,uint8 pin)
{
	enu_error_state_t enu_error_state = VALID_OPERATION;
	enu_error_state = DIO_writePin(port,pin,PIN_HIGH);
	return enu_error_state;
}


enu_error_state_t button_read(uint8 port,uint8 pin,uint8* value)
{
	enu_error_state_t enu_error_state = VALID_OPERATION;
	if(value != NULL_PTR)
	{
		enu_error_state = DIO_readPin(port,pin,&value);
	}
	else
	{
		enu_error_state = INVALID_OPERATION;
	}
	return enu_error_state;
}