/*
 * TMR0_interface.h
 *
 * Created: 2023-05-16 6:56:32 PM
 *  Author: HAZEM-PC
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_

/*============= FILE INCLUSION =============*/
#include "..\..\LIBRARY\std_types.h"
#include "..\..\LIBRARY\registers.h"
#include "tmr_private.h"


/*============= extern variables =============*/
extern volatile BOOLEAN g_timeout_flag;


/*============= MACRO DEFINITION =============*/
#define MAX_DELAY_COMP_MODE 40  //evaluate to 40*250ms=10 seconds

/*============= FUNCTION PROTOTYPE =============*/

/**
 * @brief       tmr_delay_ms                :   Function used to apply block delay using overflow mode 
 * 
 * @param[in]   delay						:	time delay in ms
 * 
 * @return      void						:      
   
 */	
void tmr_delay_ms(float32 delay);

/**
 * @brief       tmr_stop					:   Function used to stop timer functionality 
 * 
 * @param[in]   void						:	
 * 
 * @return      void						:      
   
 */	
void tmr_stop(void);

/**
 * @brief       tmr_callEvent               :   Function used to call event after elapse timeout delay using overflow mode
 * 
 * @param[in]   delay						:	time delay in ms
 * @param[in]   g_ptr						:	pointer to call back function 
 * 
 * @return      void						:      
   
 */	
void tmr_callEvent(float32 delay,void(*g_ptr)(void));

/**
 * @brief       tmr_timeout_ms              :   Function used to apply timeout function using compare match mode 
 *												to check that timeout use <g_timeout_flag> which by default is zero
 *												and change to 1 after timeout
 * 
 * @param[in]   delay						:	time delay in ms
 * 
 * @return      void						:      
   
 */	
void tmr_timeout_ms(float32 delay); 

//void TMR0_OVFSetCallBack (void(*g_ptr)(void));
//void TMR0_CMPSetCallBack (void(*g_ptr)(void));

#endif /* TMR0_INTERFACE_H_ */