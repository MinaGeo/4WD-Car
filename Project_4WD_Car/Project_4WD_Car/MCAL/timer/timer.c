/*
 * timer.c
 *
 * Created: 9/5/2023 6:01:10 PM
 *  Author: HP
 */ 

#include "timer.h"
//GLOBAL VARIABLES
static float64 f64_gs_Timer0_OVFNumber;
static float64 f64_gs_Timer0_OVFtime;

 uint8_t u8_g_currentCarState = INITIAL_VALUE_0;
 int32_t i32_g_TimeMode_ovf = INITIAL_VALUE_0;
 static int32_t i32_gs_TimeDec_ovf = INITIAL_VALUE_0;

/************************************************************/
/*************************** TIMER0 *************************/
/************************************************************/


EN_TimerError_t TIMER_timer0InitMode(uint8_t u8_a_timer1Mode)
{
	
	if(u8_a_timer1Mode == timer0_normal_mode) //Normal mode
	{
		 TCCR0 &= ~(TIMER_1<<WGM00);
		 TCCR0 &= ~(TIMER_1<<WGM01);
		 return TIMER_OK;
	}
	else if(u8_a_timer1Mode ==timer0_CTC_mode) //CTC mode
	{
		 TCCR0 &= ~(TIMER_1<<WGM00);
		 TCCR0 |=(TIMER_1<<WGM01);
		 return TIMER_OK;
		 
	}
	else if(u8_a_timer1Mode ==timer0_PWM_mode) //PWM mode
	{
		 TCCR0  |=(TIMER_1<<WGM00);
		 TCCR0 &= ~(TIMER_1<<WGM01);
		 return TIMER_OK;
		 
	}
	else if(u8_a_timer1Mode ==timer0_FastPWM_mode) //FAST PWM mode
	{
		TCCR0 |=(TIMER_1<<WGM00);
		TCCR0 |=(TIMER_1<<WGM01);
		 return TIMER_OK;
		 
	}
	else
	{
		//do nothing 
				 return TIMER_INVALID_MODE;

	}
	
	
}

EN_TimerError_t TIMER_timer0Prescalar(uint8_t u8_a_prescalar)
{
		if(u8_a_prescalar == TIMER0_STOP) //Timer stop
		{
			TCCR0 &= ~(TIMER_1 << CS00);  // clear bit CS00 to 0
			TCCR0 &= ~(TIMER_1 << CS01); // Clear bit CS01 to 0
			TCCR0 &= ~(TIMER_1 << CS02); // Clear bit CS02 to 0
		  return TIMER_OK;

		}
		else if(u8_a_prescalar ==TIMER0_NO_PRESCALLING) // No prescalling
		{
			TCCR0 |= (TIMER_1 << CS00);  // Set bit CS00 to 1
			TCCR0 &= ~(TIMER_1 << CS01); // Clear bit CS01 to 0
			TCCR0 &= ~(TIMER_1 << CS02); // Clear bit CS02 to 0
		  return TIMER_OK;
		}
		else if(u8_a_prescalar ==TIMER0_SCALER_8) //Prescalar of 8 
		{
				TCCR0 &= ~(TIMER_1 << CS00);  // Clear bit CS00 to 0
				TCCR0 |= (TIMER_1 << CS01); // Set bit CS01 to 1
				TCCR0 &= ~(TIMER_1 << CS02); // Clear bit CS02 to 0
		  return TIMER_OK;
		}
		else if(u8_a_prescalar ==TIMER0_SCALER_64) //Prescalar of 64
		{
			TCCR0 |= (TIMER_1 << CS00);  // Set bit CS00 to 1
			TCCR0 |= (TIMER_1 << CS01); // Set bit CS01 to 1
			TCCR0 &= ~(TIMER_1 << CS02); // Clear bit CS02 to 0
		  return TIMER_OK;
		}
		else if(u8_a_prescalar ==TIMER0_SCALER_256) //Prescalar of 256
		{
			TCCR0 &= ~(TIMER_1 << CS00);  // Clear bit CS00 to 0
			TCCR0 &= ~(TIMER_1 << CS01); // Clear bit CS01 to 0
			TCCR0 |= (TIMER_1 << CS02); // Clear bit CS02 to 1
		  return TIMER_OK;
		}
		else if(u8_a_prescalar ==TIMER0_SCALER_1024) //Prescalar of 1024
		{
			TCCR0 |= (TIMER_1 << CS00);  // Set bit CS00 to 1
			TCCR0 &= ~(TIMER_1 << CS01); // Clear bit CS01 to 0
			TCCR0 |= (TIMER_1 << CS02); // Set bit CS02 to 1
		  return TIMER_OK;
		}
		else if(u8_a_prescalar ==EXTERNAL_FALLING_EDGE) //External clock source on T0 pin. Clock on falling edge
		{
			TCCR0 &= ~(TIMER_1 << CS00);  // clear bit CS00 to 0
			TCCR0 |= (TIMER_1 << CS01); // Set bit CS01 to 1
			TCCR0 |= (TIMER_1 << CS02); // Set bit CS02 to 1
		  return TIMER_OK;
		}
		else if(u8_a_prescalar ==EXTERNAL_RISING_EDGE) //External clock source on T0 pin. Clock on rising edge.
		{
			TCCR0 |= (TIMER_1 << CS00);  // Set bit CS00 to 1
			TCCR0 |= (TIMER_1 << CS01); // Set bit CS01 to 1
			TCCR0 |= (TIMER_1 << CS02); // Set bit CS02 to 1
		  return TIMER_OK;
		}	
		else
		{
			//do nothing
			return TIMER_INVALID_PRESCALAR;
		}
}

EN_TimerError_t TIMER_timer0SetInitial(float64 u8_a_intialValue)
{
	
	if(u8_a_intialValue < TIMR0_MAX_VALUE && u8_a_intialValue >= INITIAL_VALUE_0)
	{
		
		TCNT0 = ceil(u8_a_intialValue);
		return TIMER_OK;
	}
	else
	{
		return TIMER_INVALID_SETINIT;
	}
}

EN_TimerError_t TIMER_timer0Delay(float64 f64_a_timeDelay)
{
	f64_gs_Timer0_OVFtime = f64_a_timeDelay/NUMBER_OF_OVERFLOWS ;
	f64_gs_Timer0_OVFNumber = ceil (f64_gs_Timer0_OVFtime / FREQUENCY_OF_OVERFLOWS) ;
	if(TIMER_timer0InitMode(timer0_normal_mode)!= TIMER_OK)
	{
		return TIMER_INVALID_DELAY;
	}
	if(TIMER_timer0SetInitial(INITIAL_VALUE_0)!= TIMER_OK)
	{
		return TIMER_INVALID_DELAY;
	}
	if(TIMER_timer0Prescalar(TIMER0_NO_PRESCALLING)!=TIMER_OK)
	{
		return TIMER_INVALID_DELAY;
	}
	if(TIMER_timer0_OVF_Number(f64_gs_Timer0_OVFNumber)!= TIMER_OK){
		return TIMER_INVALID_DELAY;
	}
	return TIMER_OK;
}

EN_TimerError_t TIMER_timer0_OVF_Number(float64 f64_a_OVFNumber)
{
	float64 f64_v_numberOfOverflows = INITIAL_VALUE_0;
	if (f64_a_OVFNumber > INITIAL_VALUE_0)
	{
		while(f64_v_numberOfOverflows<f64_a_OVFNumber)
		{
			
			while(READ_BIT(TIFR,TOV0)==INITIAL_VALUE_0);
			SET_BIT(TIFR,TOV0);
			f64_v_numberOfOverflows++;
		}
		f64_v_numberOfOverflows = INITIAL_VALUE_0;
	}
	else if (f64_a_OVFNumber <= INITIAL_VALUE_0)
	{
		f64_a_OVFNumber = INITIAL_VALUE_1;
		while(f64_v_numberOfOverflows<f64_a_OVFNumber){
			
			while(READ_BIT(TIFR,TOV0)==INITIAL_VALUE_0);
			SET_BIT(TIFR,TOV0);
			f64_v_numberOfOverflows++;
		}
		f64_v_numberOfOverflows = INITIAL_VALUE_0;
	}

	else{
		return TIMER_INVALID_OVF;
	}

	return TIMER_OK;
}

void TIMER_timer0Stop(void)
{
	CLEAR_BIT(TCCR0,CS00);
	CLEAR_BIT(TCCR0,CS01);
	CLEAR_BIT(TCCR0,CS02);
	
	
}

EN_TimerError_t TIMER_timer0PWM_mode(float32 f32_a_pwmValue)
{
	
	uint8_t u8_v_timer = ceil(f32_a_pwmValue);
	if(TIMER_timer0InitMode(timer0_normal_mode)!= TIMER_OK)
	{
		return TIMER_INVALID_T0PWM;
	}
	TCNT0 =   u8_v_timer;
	if(TIMER_timer0Prescalar(TIMER0_SCALER_1024)!= TIMER_OK)
	{
		return TIMER_INVALID_T0PWM;
	}
	if(TIMER_timer0_OVF_Number(INITIAL_VALUE_1)!= TIMER_OK)
	{
		return TIMER_INVALID_T0PWM;
	}
	TCCR0 = INITIAL_VALUE_0;
	TCNT0 = INITIAL_VALUE_0;
	SET_BIT(TIFR,TOV0);
	return TIMER_OK;
}



/************************************************************/
/*************************** TIMER2 *************************/
/************************************************************/

EN_TimerError_t TIMER_timer2InitMode(uint8_t u8_a_timer2Mode)
{
	
	if(u8_a_timer2Mode == timer2_normal_mode) //Normal mode
	{
		CLEAR_BIT(TCCR2,WGM20);
		CLEAR_BIT(TCCR2,WGM21);
		return TIMER_OK;
	}
	else if(u8_a_timer2Mode ==timer2_CTC_mode) //CTC mode
	{
		CLEAR_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		return TIMER_OK;
		
	}
	else if(u8_a_timer2Mode ==timer2_PWM_mode) //PWM mode
	{
		SET_BIT(TCCR2,WGM20);
		CLEAR_BIT(TCCR2,WGM21);
		return TIMER_OK;
		
	}
	else if(u8_a_timer2Mode ==timer2_FastPWM_mode) //FAST PWM mode
	{
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
		return TIMER_OK;
		
	}
	else
	{
		//do nothing
		return TIMER_INVALID_MODE;

	}
}

EN_TimerError_t TIMER_timer2Prescalar(uint8_t u8_a_timer2Prescalar)
{
if(u8_a_timer2Prescalar == TIMER2_STOP) //Timer stop
{
	CLEAR_BIT(TCCR2,CS20);
	CLEAR_BIT(TCCR2,CS21);
	CLEAR_BIT(TCCR2,CS22);
	return TIMER_OK;
	

}
else if(u8_a_timer2Prescalar ==TIMER2_NO_PRESCALLING) // No prescalling
{
	SET_BIT(TCCR2,CS20);
	CLEAR_BIT(TCCR2,CS21);
	CLEAR_BIT(TCCR2,CS22);
	return TIMER_OK;
	

}
else if(u8_a_timer2Prescalar ==TIMER2_SCALER_8) //Prescalar of 8
{
	CLEAR_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	CLEAR_BIT(TCCR2,CS22);
	return TIMER_OK;
	

}
else if(u8_a_timer2Prescalar ==TIMER2_SCALER_32) //Prescalar of 32
{
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	CLEAR_BIT(TCCR2,CS22);
	return TIMER_OK;
	

}
else if(u8_a_timer2Prescalar ==TIMER2_SCALER_64) //Prescalar of 64
{
	CLEAR_BIT(TCCR2,CS20);
	CLEAR_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	return TIMER_OK;
	
}
else if(u8_a_timer2Prescalar ==TIMER2_SCALER_128) //Prescalar of 128
{
	SET_BIT(TCCR2,CS20);
	CLEAR_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	return TIMER_OK;
	
}
else if(u8_a_timer2Prescalar ==TIMER2_SCALER_256) //Prescalar of 256
{
	CLEAR_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	return TIMER_OK;
	
}
else if(u8_a_timer2Prescalar ==TIMER2_SCALER_1024) //Prescalar of 1024
{
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	return TIMER_OK;
	
}
else
{
	//do nothing
	return TIMER_INVALID_PRESCALAR;
}
	
}

EN_TimerError_t TIMER_timer2SetInitial(uint8_t u8_a_timer2IntialValue)
{
	if(u8_a_timer2IntialValue < TIMR2_MAX_VALUE && u8_a_timer2IntialValue >= INITIAL_VALUE_0)
	{
		
		TCNT2 = u8_a_timer2IntialValue;
		return TIMER_OK;
	}
	else
	{
		return TIMER_INVALID_SETINIT;
	}
}



EN_TimerError_t TIMER_timer2Init(void){
	SET_BIT(TIMSK,TOIE2);
	if(TIMER_timer2InitMode(timer2_normal_mode)!=TIMER_OK)
	{
		return TIMER_INVALID_INIT;
	}
	else if (TIMER_timer2SetInitial(INITIAL_VALUE_0)!= TIMER_OK)
	{
		return TIMER_INVALID_INIT;
		
	}
	else if(TIMER_timer2Prescalar(TIMER2_NO_PRESCALLING)!=TIMER_OK)
	{
		return TIMER_INVALID_INIT;
	}
	else{
		u8_g_timerBtn_flag = INITIAL_VALUE_0;
	}
	return TIMER_OK;
	
}

void TIMER_timer2Stop(void)
{
	CLEAR_BIT(TCCR2,CS20);
	CLEAR_BIT(TCCR2,CS21);
	CLEAR_BIT(TCCR2,CS22);
}


/********************** TIMERS FUNCTIONS *******************/
void TIMER_clrOF_Flag(void)
{
	TIFR |= (TIMER_1<<TIMER_0);
}


ISR(TIMER2_OVF_vect){
	
	if(u8_g_timerBtn_flag == INITIAL_VALUE_1)
	{
		
		if (i32_gs_TimeDec_ovf < i32_g_TimeMode_ovf )
		{
			i32_gs_TimeDec_ovf++;
		}
		else if ( i32_gs_TimeDec_ovf == i32_g_TimeMode_ovf && i32_g_TimeMode_ovf!=INITIAL_VALUE_0)
		{
			i32_gs_TimeDec_ovf = INITIAL_VALUE_0;
			
			if (u8_g_currentCarState < CAR_MODES)
			{
				u8_g_currentCarState++;
				
			}
			else
			{
				u8_g_currentCarState = INITIAL_VALUE_1;
			}
			
		}
		
	}
	
}