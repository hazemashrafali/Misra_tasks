/*
 * app.h
 *
 * Created: 2023-06-06 8:03:04 AM
 *  Author: HAZEM-PC
 */ 


#ifndef APP_H_
#define APP_H_
/*============= FILE INCLUSION =============*/
#include "..\HAL\led\led.h"
#include "..\HAL\button\button.h"
#include "..\MCAL\ext_interrupt\ext_int.h"
#include "..\MCAL\tmr\tmr0_interface.h"


/*============= TYPE DEFINITION =============*/


/*============= FUNCTION PROTOTYPE =============*/
void buttonpress	(void);
void Blink_mode		(void);
void app_init		(void);
void app_start		(void);



#endif /* APP_H_ */