/*
 * External_INT.h
 *
 *  Created on: Apr 5, 2023
 *      Author: HAZEM-PC
 */

#ifndef MCAL_EXTERNAL_INT_EXTERNAL_INT_H_
#define MCAL_EXTERNAL_INT_EXTERNAL_INT_H_

/*============= FILE INCLUSION =============*/
#include "..\..\LIBRARY\std_types.h"
#include "..\..\LIBRARY\registers.h"
#include "..\..\LIBRARY\common_macros.h"

/*============= TYPE DEFINITION =============*/
typedef enum{
	EN_INT0,EN_INT1,EN_INT2
}EN_INT_source;

typedef enum{
	LOW_LEVEL,ANY_CHANGE,FALLING,RISING
}EN_INT_TRIGGER;

typedef struct{
	EN_INT_source source;
	EN_INT_TRIGGER trigger;
}ST_INT_Config;


#define INT0_pin 2 //PD2
#define INT1_pin 3 //PD3
#define INT2_pin 3 //PB2

/*============= FUNCTION PROTOTYPE =============*/
void INT_init(ST_INT_Config* Int_config);
void INT0_setCallBack(void(*a_ptr)(void));
void INT1_setCallBack(void(*a_ptr)(void));
void INT2_setCallBack(void(*a_ptr)(void));
void INT_Deinit(ST_INT_Config* Int_config);


#endif /* MCAL_EXTERNAL_INT_EXTERNAL_INT_H_ */
