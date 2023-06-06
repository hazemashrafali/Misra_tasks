/*
 * app.h
 *
 * Created: 2023-06-05 11:33:49 PM
 *  Author: HAZEM-PC
 */ 


#ifndef APP_H_
#define APP_H_

/*============= FILE INCLUSION =============*/
#include "..\HAL\led\led.h"
#include "..\HAL\button\button.h"
#include "util/delay.h"


/*============= TYPE DEFINITION =============*/
#define F_CPU 8000000UL

/*============= FUNCTION PROTOTYPE =============*/
void app_init (void);
void app_start (void);


#endif /* APP_H_ */