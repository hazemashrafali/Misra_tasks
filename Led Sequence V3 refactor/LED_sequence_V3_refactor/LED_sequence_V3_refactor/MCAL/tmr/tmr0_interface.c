/*
 * TMR0_interface.c
 *
 * Created: 2023-05-16 6:54:02 PM
 *  Author: HAZEM-PC
 */ 

/*============= FILE INCLUSION =============*/
#include "tmr0_interface.h"

/*============= global variables =============*/
static void (*gl_callBackPtr)(void) = NULL_PTR;
static uint8 gl_overflows = 0;
static uint8 gl_tick = 0;
static uint8 gl_initial_value = 0;
volatile BOOLEAN g_timeout_flag = FALSE;

/*============= TYPE DEFINITION =============*/
typedef struct{
	uint8 initial_value;
	uint16 prescaler;
	float32 NO_OF_OV;
}st_tmr_var_t;

/*============= PRIVATE FUNCTIONS =============*/
static uint8 calc_prescaler(float32 delay,uint16* prescale);
static void calc_initialValue(uint16 prescaler,uint8* initial_value,float32 delay);
static void set_prescale(uint16 prescaler);

/*============= FUNCTION DEFINITIONS =============*/
/*
 * Description:used to calculate timer settings
 * calculate pre_scale value
 * calculate number of overflows
 * calculate timer initial value
 */

void tmr_delay_ms(float32 delay)
{
	st_tmr_var_t st_tmr_var;
	uint8 u8_l_realPart;
	uint8 u8_l_reminder;
	uint8 u8_l_count;
	BOOLEAN Bo_l_returnCheck;
	Bo_l_returnCheck = calc_prescaler(delay,&st_tmr_var.prescaler);
	if(Bo_l_returnCheck == TRUE)
	{
		calc_initialValue(st_tmr_var.prescaler, &st_tmr_var.initial_value,delay);
		st_tmr_var.NO_OF_OV = 0;
	}
	else
	{
		st_tmr_var.prescaler		=	P_1024;
		st_tmr_var.NO_OF_OV			=	(delay/MAX_DELAY_MS(P_1024));
		st_tmr_var.initial_value	=	0;
	}
	u8_l_realPart	=	st_tmr_var.NO_OF_OV;
	u8_l_reminder	=	(st_tmr_var.NO_OF_OV-u8_l_realPart)*(MAX_DELAY_MS(P_1024)); //reminder delay to complete required delay period
	u8_l_count		=	u8_l_realPart;
	TCNT0			=	st_tmr_var.initial_value;
	if(u8_l_count == 0)
	{
		set_prescale(st_tmr_var.prescaler);
		while(!(TIFR & (1<<TOV0)));
	}
	else
	{
		TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);			//use clock pre_scale 1024
		while(u8_l_count != 0)								//run delay of real part
		{
			while(!(TIFR & (1<<TOV0)));
			u8_l_count--;
			TIFR |= (1<<TOV0);
		}
		if(u8_l_reminder > 0)											//run remaining delay period
		{
			if(u8_l_reminder <= MAX_DELAY_MS(P_1))						//find best range that contain the required remaining delay
				st_tmr_var.prescaler = P_1;
			else if(u8_l_reminder <= MAX_DELAY_MS(P_8))
				st_tmr_var.prescaler = P_8;
			else if(u8_l_reminder <= MAX_DELAY_MS(P_64))
				st_tmr_var.prescaler = P_64;
			else if(u8_l_reminder <= MAX_DELAY_MS(P_256))
				st_tmr_var.prescaler = P_256;
			else if(u8_l_reminder <= MAX_DELAY_MS(P_1024))
				st_tmr_var.prescaler = P_1024;
			else
				st_tmr_var.prescaler = P_0;
		}
		switch(st_tmr_var.prescaler)												//according to selected pre_scaler value
		{
		case P_1:
			TCNT0 = INIT_VALUE(MAX_DELAY_MS(P_1),u8_l_reminder,MIN_DELAY_MS(P_1));	//set TCNT0 register with the initial value
			TCCR0 = (1<<FOC0) | (1<<CS00);											//set TCCR0 register with clock source
			break;
		case P_8:
			TCNT0 = INIT_VALUE(MAX_DELAY_MS(P_8),u8_l_reminder,MIN_DELAY_MS(P_8));
			TCCR0 = (1<<FOC0) | (1<<CS01);
			break;
		case P_64:
			TCNT0 = INIT_VALUE(MAX_DELAY_MS(P_64),u8_l_reminder,MIN_DELAY_MS(P_64));
			TCCR0 = (1<<FOC0) | (1<<CS01) | (1<<CS00);
			break;
		case P_256:
			TCNT0 = INIT_VALUE(MAX_DELAY_MS(P_256),u8_l_reminder,MIN_DELAY_MS(P_256));
			TCCR0 = (1<<FOC0) | (1<<CS02);
			break;
		case P_1024:
			TCNT0 = INIT_VALUE(MAX_DELAY_MS(P_1024),u8_l_reminder,MIN_DELAY_MS(P_1024));
			TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
			break;
		default:
			TCNT0 = 0;
			TCCR0 = 0;
			break;
		}
		while(!(TIFR & (1<<TOV0)));			//Wait until the Timer0 Overflow occurs (wait until TOV0 = 1)
	}
	TIFR |= (1<<TOV0);						//Clear TOV0 bit by set its value
	TCCR0 = 0;
}

void TMR0_Stop(void)
{
	TIMSK &= ~(1<<TOIE0);
}

void tmr_callEvent(float32 delay,void(*g_ptr)(void))
{	
	TIMSK |= (1<<TOIE0);
	if(delay < MAX_DELAY_MS(P_1024))
	{
		gl_initial_value=(((float32)(MAX_DELAY_MS(P_1024)-delay)/MIN_DELAY_MS(P_1024)));
		gl_overflows=0;
	}
	else
	{
		gl_overflows=delay/MAX_DELAY_MS(P_1024);
		gl_initial_value=0;
	}
	TCNT0 = gl_initial_value;
	
	gl_callBackPtr = g_ptr;
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
}

void tmr_timeout_ms(float32 delay)
{
	/*code to count time in milliseconds*/
	if(delay < MAX_DELAY_MS(P_1024))
	{
		gl_initial_value = delay;
		gl_overflows = 0;
	}
	else
	{
		gl_overflows = ((float32)delay/MAX_DELAY_MS(P_1024));
		gl_initial_value = MAX_COUNT - 1;
	}
	TCNT0 = 0;
	OCR0 = gl_initial_value;
	TIMSK |= (1<<OCIE0);				//enable timer compare match interrupt
	g_timeout_flag = FALSE;				//set flag to default
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
}

ISR_HANDLER(TMR0_CMP)
{
	if(gl_overflows > 0)
	{
		gl_tick++;
		if(gl_tick == gl_overflows)
		{
			g_timeout_flag++;
			gl_tick = 0;			//clear the tick counter again to start new count				
		}
	}
	else
	{
		g_timeout_flag++;
		TCNT0 = 0;
		OCR0 = gl_initial_value;
	}
}

ISR_HANDLER(TMR0_OVF)
{
	if(gl_callBackPtr != NULL_PTR)
	{
		if(gl_overflows > 0)
		{
			gl_tick++;
			if(gl_tick == gl_overflows)
			{
				gl_callBackPtr();
				gl_tick = 0; //clear the tick counter again to start new count
			}
		}
		else
		{
			gl_callBackPtr();
			TCNT0 = gl_initial_value;
		}
	}
}

static uint8 calc_prescaler(float32 delay,uint16* prescale)
{
	if(delay <= MAX_DELAY_MS(P_1024))
	{
		if(delay <= MAX_DELAY_MS(P_1))
			*prescale=P_1;
		else if(delay <= MAX_DELAY_MS(P_8))
			*prescale=P_8;
		else if(delay <= MAX_DELAY_MS(P_64))
			*prescale=P_64;
		else if(delay <= MAX_DELAY_MS(P_256))
			*prescale=P_256;
		else if(delay <= MAX_DELAY_MS(P_1024))
			*prescale=P_1024;
		else
			*prescale = P_0;
		return 1;
	}
	else
		return 0;
}

static void calc_initialValue(uint16 prescaler,uint8* init_value,float32 delay)
{
	switch(prescaler)
	{
	case P_1:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_1),delay,MIN_DELAY_MS(P_1));
		break;
	case P_8:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_8),delay,MIN_DELAY_MS(P_8));
		break;
	case P_64:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_64),delay,MIN_DELAY_MS(P_64));
		break;
	case P_256:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_256),delay,MIN_DELAY_MS(P_256));
		break;
	case P_1024:
		*init_value=INIT_VALUE(MAX_DELAY_MS(P_1024),delay,MIN_DELAY_MS(P_1024));
		break;
	default:
		*init_value=0;
		break;
	}
}

static void set_prescale(uint16 prescaler)
{
	switch(prescaler)
	{
	case P_1:
		TCCR0 = (1<<FOC0) | (1<<CS00);
		break;
	case P_8:
		TCCR0 = (1<<FOC0) | (1<<CS01);
		break;
	case P_64:
		TCCR0 = (1<<FOC0) | (1<<CS01) | (1<<CS00);
		break;
	case P_256:
		TCCR0 = (1<<FOC0) | (1<<CS02);
		break;
	case P_1024:
		TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
		break;
	default:
		TCCR0 = 0;
		break;
	}
}

