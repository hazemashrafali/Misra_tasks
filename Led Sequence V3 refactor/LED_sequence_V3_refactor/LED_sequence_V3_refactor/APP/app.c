/*
 * app.c
 *
 * Created: 2023-06-06 8:02:52 AM
 *  Author: HAZEM-PC
 */ 

/*============= FILE INCLUSION =============*/
#include "app.h"

/*============= GLOBAL Variables =============*/
uint8  gl_u8_press_count		=0;
uint16 gl_u16_blink_mode		=100;
uint8  gl_u8_buttonMode_count	=0;

/*============= FUNCTION DEFINITIONS =============*/
void buttonpress(void)
{
		gl_u8_press_count++;
		if(gl_u8_press_count == 8)
		gl_u8_press_count = 0;
}

void Blink_mode(void)
{
	gl_u8_buttonMode_count++;
	switch(gl_u8_buttonMode_count)
	{
		case 1:
		gl_u16_blink_mode=200;
		break;
		case 2:
		gl_u16_blink_mode=300;
		break;
		case 3:
		gl_u16_blink_mode=400;
		break;
		case 4:
		gl_u16_blink_mode=500;
		break;
		case 5:
		gl_u16_blink_mode=800;
		break;
		default:
		gl_u16_blink_mode=100;
		break;
	}
	if(gl_u8_buttonMode_count==6)
	gl_u8_buttonMode_count=0;
}
void app_init(void)
{
	ST_INT_Config blink_button={EN_INT0,RISING};
	ST_INT_Config mode_button={EN_INT1,RISING};
		
	led_init(PORTA_ID , PIN1_ID);
	led_init(PORTA_ID , PIN2_ID);
	led_init(PORTA_ID , PIN3_ID);
	led_init(PORTA_ID , PIN4_ID);
	INT_init(&blink_button);
	INT_init(&mode_button);
	INT0_setCallBack(buttonpress);
	INT1_setCallBack(Blink_mode);
}
void app_start(void)
{
	uint16 u16_off_delay = 0;
	uint16 u16_on_delay	= 0;
	
	while(1)
	{
		switch (gl_u8_press_count)
		{
			case 1:
			led_write(PORTA_ID,PIN1_ID,PIN_HIGH);
			tmr_delay_ms(u16_on_delay);
			led_write(PORTA_ID,PIN1_ID,PIN_LOW);
			tmr_delay_ms(u16_off_delay);
			break;
			case 2:
			led_write(PORTA_ID,PIN1_ID,PIN_HIGH);
			led_write(PORTA_ID,PIN2_ID,PIN_HIGH);
			tmr_delay_ms(u16_on_delay);
			led_write(PORTA_ID,PIN1_ID,PIN_LOW);
			led_write(PORTA_ID,PIN2_ID,PIN_LOW);
			tmr_delay_ms(u16_off_delay);
			break;
			case 3:
			led_write(PORTA_ID,PIN1_ID,PIN_HIGH);
			led_write(PORTA_ID,PIN2_ID,PIN_HIGH);
			led_write(PORTA_ID,PIN3_ID,PIN_HIGH);
			tmr_delay_ms(u16_on_delay);
			led_write(PORTA_ID,PIN1_ID,PIN_LOW);
			led_write(PORTA_ID,PIN2_ID,PIN_LOW);
			led_write(PORTA_ID,PIN3_ID,PIN_LOW);
			tmr_delay_ms(u16_off_delay);
			break;
			case 4:
			led_write(PORTA_ID,PIN1_ID,PIN_HIGH);
			led_write(PORTA_ID,PIN2_ID,PIN_HIGH);
			led_write(PORTA_ID,PIN3_ID,PIN_HIGH);
			led_write(PORTA_ID,PIN4_ID,PIN_HIGH);
			tmr_delay_ms(u16_on_delay);
			led_write(PORTA_ID,PIN1_ID,PIN_LOW);
			led_write(PORTA_ID,PIN2_ID,PIN_LOW);
			led_write(PORTA_ID,PIN3_ID,PIN_LOW);
			led_write(PORTA_ID,PIN4_ID,PIN_LOW);
			tmr_delay_ms(u16_off_delay);
			break;
			case 5:	
			led_write(PORTA_ID,PIN2_ID,PIN_HIGH);
			led_write(PORTA_ID,PIN3_ID,PIN_HIGH);
			led_write(PORTA_ID,PIN4_ID,PIN_HIGH);
			tmr_delay_ms(u16_on_delay);
			led_write(PORTA_ID,PIN2_ID,PIN_LOW);
			led_write(PORTA_ID,PIN3_ID,PIN_LOW);
			led_write(PORTA_ID,PIN4_ID,PIN_LOW);
			tmr_delay_ms(u16_off_delay);
			break;
			case 6:
			led_write(PORTA_ID,PIN3_ID,PIN_HIGH);
			led_write(PORTA_ID,PIN4_ID,PIN_HIGH);
			tmr_delay_ms(u16_on_delay);
			led_write(PORTA_ID,PIN3_ID,PIN_LOW);
			led_write(PORTA_ID,PIN4_ID,PIN_LOW);
			tmr_delay_ms(u16_off_delay);
			break;
			case 7:
			led_write(PORTA_ID,PIN4_ID,PIN_HIGH);
			tmr_delay_ms(u16_on_delay);
			led_write(PORTA_ID,PIN4_ID,PIN_LOW);
			tmr_delay_ms(u16_off_delay);
			break;
			default:
			led_write(PORTA_ID,PIN1_ID,PIN_LOW);
			led_write(PORTA_ID,PIN2_ID,PIN_LOW);
			led_write(PORTA_ID,PIN3_ID,PIN_LOW);
			led_write(PORTA_ID,PIN4_ID,PIN_LOW);
			break;
		}
		u16_on_delay=gl_u16_blink_mode;
		u16_off_delay=1000-gl_u16_blink_mode;
	}
}