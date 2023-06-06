/*
 * app.c
 *
 * Created: 2023-06-05 11:33:40 PM
 *  Author: HAZEM-PC
 */ 
/*============= FILE INCLUSION =============*/
#include "app.h"

/*============= FUNCTION DEFINITIONS =============*/
void app_init (void)
{	
	//led initialization
	led_init(PORTA_ID , PIN1_ID);
	led_init(PORTA_ID , PIN2_ID);
	led_init(PORTA_ID , PIN3_ID);
	led_init(PORTA_ID , PIN4_ID);
	//button initialization
	button_init(PORTA_ID , PIN0_ID);	

	
}
void app_start (void)
{
	uint8 u8_l_led_count	=0;
	uint8 u8_l_button_flag	=1;
	uint8 u8_l_button_value	=0;
	while(1)
	{
		button_read(PORTA_ID , PIN0_ID, &u8_l_button_value);
		if(u8_l_button_value == LOGIC_HIGH)
		{
			_delay_ms(50);
			button_read(PORTA_ID , PIN0_ID, &u8_l_button_value);
			if(u8_l_button_value == LOGIC_HIGH)
			{
				if(u8_l_button_flag == 0)
				{
					u8_l_led_count++;
					switch (u8_l_led_count)
					{
						case 1:
						led_write(PORTA_ID, PIN1_ID, PIN_HIGH);
						break;
						case 2:
						led_write(PORTA_ID, PIN2_ID, PIN_HIGH);
						break;
						case 3:
						led_write(PORTA_ID, PIN3_ID, PIN_HIGH);
						break;
						case 4:
						led_write(PORTA_ID, PIN4_ID, PIN_HIGH);
						break;
						case 5:
						led_write(PORTA_ID, PIN1_ID, PIN_LOW);
						break;
						case 6:
						led_write(PORTA_ID, PIN2_ID, PIN_LOW);
						break;
						case 7:
						led_write(PORTA_ID, PIN3_ID, PIN_LOW);
						break;
						default:
						led_write(PORTA_ID, PIN1_ID, PIN_LOW);
						led_write(PORTA_ID, PIN2_ID, PIN_LOW);
						led_write(PORTA_ID, PIN3_ID, PIN_LOW);
						led_write(PORTA_ID, PIN4_ID, PIN_LOW);
						u8_l_led_count = 0;
						break;
					}
					u8_l_button_flag = 1;
					if(u8_l_led_count == 9)
					u8_l_led_count = 0;
				}
			}
		}
		else
		{
			u8_l_button_flag = 0;
		}
	}
}