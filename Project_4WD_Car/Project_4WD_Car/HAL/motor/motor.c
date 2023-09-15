/*
 * motor.c
 *
 * Created: 9/10/2023 9:35:26 PM
 *  Author: HP
 */ 

#include "motor.h"

EN_motorError_t motor_init(void)
{
		if(DIO_init(MOTOR_PORT0,MOTOR_PIN0,OUT)!=DIO_OK)
		{
			return MOTOR_INVALID_INIT;
			
		}
		else if(DIO_init(MOTOR_PORT1,MOTOR_PIN1,OUT)!=DIO_OK)
		{
			return MOTOR_INVALID_INIT;
		}
		else if(DIO_init(MOTOR_PORT2,MOTOR_PIN2,OUT)!=DIO_OK)
		{
			return MOTOR_INVALID_INIT;
		}
		else if(DIO_init(MOTOR_PORT3,MOTOR_PIN3,OUT)!= DIO_OK)
		{
			return MOTOR_INVALID_INIT;
			
		}
		else
		{
			return MOTOR_OK;
		}
		
}

EN_motorError_t motor_move_forward()
{
	
		if(DIO_write(MOTOR_PORT0,MOTOR_PIN0,LOW)!=DIO_OK) 
		{
			return MOTOR_INVALID_MOVEFWD;
			
		}
		else if(DIO_write(MOTOR_PORT1,MOTOR_PIN1,HIGH)!=DIO_OK)
		{
			return MOTOR_INVALID_MOVEFWD;
		}
		else if(DIO_write(MOTOR_PORT2,MOTOR_PIN2,LOW)!=DIO_OK)
		{
			return MOTOR_INVALID_MOVEFWD;
		}
		else if(DIO_write(MOTOR_PORT3,MOTOR_PIN3,HIGH)!= DIO_OK)
		{
			return MOTOR_INVALID_MOVEFWD;
			
		}
		else
		{
				return MOTOR_OK;
		}

	
	
}

EN_motorError_t motor_rotate(void)
{
	
	
	if(DIO_write(MOTOR_PORT0,MOTOR_PIN0,HIGH)!=DIO_OK) 
	{
		return MOTOR_INVALID_ROTATE;
		
	}
	else if(DIO_write(MOTOR_PORT1,MOTOR_PIN1,LOW)!=DIO_OK)
	{
		return MOTOR_INVALID_ROTATE;
	}
	else if(DIO_write(MOTOR_PORT2,MOTOR_PIN2,LOW)!=DIO_OK)
	{
		return MOTOR_INVALID_ROTATE;
	}
	else if(DIO_write(MOTOR_PORT3,MOTOR_PIN3,HIGH)!= DIO_OK)
	{
		return MOTOR_INVALID_ROTATE;
		
	}
	else
	{
		return MOTOR_OK;
	}
	
	
}


void motor_stop(void)
{
	DIO_write(MOTOR_PORT0,MOTOR_PIN0,LOW);
	DIO_write(MOTOR_PORT1,MOTOR_PIN1,LOW);
	DIO_write(MOTOR_PORT2,MOTOR_PIN2,LOW);
	DIO_write(MOTOR_PORT3,MOTOR_PIN3,LOW);
	
	 //if(DIO_write(MOTOR_PORT0,MOTOR_PIN0,LOW)!=DIO_OK) // +VE pin of the motor
	 //{
		 //return MOTOR_INVALID_STOP;
		 //
	 //}
	 //else if(DIO_write(MOTOR_PORT1,MOTOR_PIN1,LOW)!=DIO_OK)// -VE pin of the motor
	 //{
		 //return MOTOR_INVALID_STOP;
	 //}
	 //else if(DIO_write(MOTOR_PORT2,MOTOR_PIN2,LOW)!=DIO_OK)//+VE pin of the motor
	 //{
		 //return MOTOR_INVALID_STOP;
	 //}
	 //else if(DIO_write(MOTOR_PORT3,MOTOR_PIN3,LOW)!= DIO_OK)//-VE pin of the motor
	 //{
		 //return MOTOR_INVALID_STOP;
		 //
	 //}
	 //else
	 //{
		 ////timer_PWM_Timer2_Stop();
		 //return MOTOR_OK;
	 //}

}