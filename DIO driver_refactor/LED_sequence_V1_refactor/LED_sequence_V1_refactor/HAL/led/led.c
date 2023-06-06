/*
 * led.c
 *
 * Created: 2023-06-05 7:17:22 PM
 *  Author: HAZEM-PC
 */ 
/*============= FILE INCLUSION =============*/
#include "led.h"

/*============= FUNCTION DEFINITIONS =============*/

enu_error_state_t led_init(uint8 u8_port,uint8 u8_pin)
{
	enu_error_state_t enu_error_state = VALID_OPERATION;
	enu_error_state = DIO_pinMode(u8_port,u8_pin,PIN_OUTPUT);
	if(enu_error_state == VALID_OPERATION)
	{
		enu_error_state = DIO_writePin(u8_port,u8_pin,PIN_LOW);	
	}
	return enu_error_state;
}

enu_error_state_t led_write(uint8 u8_port,uint8 u8_pin,enu_pin_value_t enu_led_state)
{
	enu_error_state_t enu_error_state = VALID_OPERATION;
	
	enu_error_state = DIO_writePin(u8_port,u8_pin,enu_led_state);

	return enu_error_state;
}

enu_error_state_t led_toggle(uint8 u8_port,uint8 u8_pin)
{
	enu_error_state_t enu_error_state = VALID_OPERATION;
	
	enu_error_state = DIO_togglePin(u8_port,u8_pin);
	
	return enu_error_state;
}