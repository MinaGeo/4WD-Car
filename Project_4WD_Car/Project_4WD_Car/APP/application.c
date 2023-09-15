/*
 * application.c
 *
 * Created: 8/24/2023 1:51:49 AM
 *  Author: HP
 */
#include "application.h"


/**********************GLOBAL VARIABLES***********************/

// PWM global variables
float32 f32_g_Timer0_time_1;
float32 f32_g_Timer0_speed;
float32 f32_g_Timer0_time_2;

// used in rotate_90degree_calculation





int currentLed = 0;
int currentBlink = CASE1;


uint8_t buttonState = LOW;
uint8_t ledState = LOW;

uint8_t led_pin_tst = LED_0_PIN;
uint8_t btn_pin_tst = BUTTON_START_PIN;
uint8_t timer_mode_tst = timer0_normal_mode;
//static void callback_exti0 (void);
//static void callback_exti1 (void);
//static void callback_exti2 (void);

//
EN_appError_t APP_init(void) {
	
  
  if(LED_init(PWM_LED_PORT , PWM_LED_PIN)!=LED_OK)// pwm
  {
	  return APP_LED_ERROR;
	}
	// timer start
else if(LED_init(TIMER_PORT_CE ,TIMER_PIN_CE)!= LED_OK)
{
	  return APP_LED_ERROR;
}

// timer stops
else if(LED_init(TIMER_PORT_RST ,TIMER_PIN_RST)!= LED_OK)
{
	return APP_LED_ERROR;
}

else if(BUTTON_init(BUTTON_STOP_PORT ,BUTTON_STOP_PIN)!= BTN_OK)
{
	return APP_BTN_ERROR;
}
else if(BUTTON_init(BUTTON_START_PORT ,BUTTON_START_PIN)!= BTN_OK)
{
	return APP_BTN_ERROR;
	
}
else if( LED_init(LED_0_PORT ,LED_0_PIN)!= LED_OK)
{
	return APP_LED_ERROR;
	
}   
else if(LED_init(LED_1_PORT, LED_1_PIN)!= LED_OK)
{
	return APP_LED_ERROR;
	
}
else if(LED_init(LED_2_PORT, LED_2_PIN)!= LED_OK)
{
	return APP_LED_ERROR;
	
}
else if(LED_init(LED_3_PORT, LED_3_PIN)!= LED_OK)
{
	return APP_LED_ERROR;
	
}
else if( motor_init() != MOTOR_OK)
{
	return APP_MOTOR_ERROR;
}
else
{
  INTERRUPTS_enableGlobalInterrupt();
  
  if(INTERRUPTS_enableExternalInterrupts(EXTERNAL_INTERRUPT_0)!=INTERRUPT_OK)
  {
	  return APP_INTERRUPT_ERROR;
  }
  else if(INTERRUPTS_enableExternalInterrupts(EXTERNAL_INTERRUPT_1)!=INTERRUPT_OK)
  {
	  return APP_INTERRUPT_ERROR;
  }
  else if( INTERRUPTS_EXT_SetCallBack(EXTERNAL_INTERRUPT_0,motor_stop)!= INTERRUPT_OK)
  {
	  return APP_INTERRUPT_ERROR;
  }
  else if( INTERRUPTS_extInterruptsEdge(EXTERNAL_INTERRUPT_0,LOW_LEVEL)!= INTERRUPT_OK)
  {
	  return APP_INTERRUPT_ERROR;
  }
  else if( INTERRUPTS_extInterruptsEdge(EXTERNAL_INTERRUPT_1,LOW_LEVEL)!= INTERRUPT_OK)
  {
	  return APP_INTERRUPT_ERROR;
  }
  else if (TIMER_timer2Init()!=TIMER_OK)
  {
	  return APP_TIMER_ERROR;
	  
  }
  

}
  return APP_OK;
  
  }
  


EN_appError_t APP_start(void) {
	
while(1){
  if(u8_g_timerBtn_flag == 1){
	  
	  if(LED_on(TIMER_PORT_CE, TIMER_PIN_CE)!=LED_OK)
	  {
		  return APP_LED_ERROR;
		} 
		else if(LED_off(TIMER_PORT_RST, TIMER_PIN_RST)!= LED_OK)
		{
		  return APP_LED_ERROR;
		  
		}
	  
	  
	  switch(u8_g_currentCarState)
	  {
		  case CASE0:
		  app_car_initial_state();
		  break;
  		  case CASE1:
		  app_move_long_slide();
		  break;
		  case CASE2:
		  app_car_stop();
		  break;
		  case CASE3:
		  app_rotate_car_90Deg();
		  break;
		  case CASE4:
		  app_car_stop();
		  break;
		  case CASE5:
		  app_move_short_slide();
		  break;
		  case CASE6:
		  app_car_stop();
		  break;
		  case CASE7:
		  app_rotate_car_90Deg();
		  break;
		  case CASE8:
		  app_car_stop();
		  break;
		  default:
		  // do nothing
		  break;
	  }
	
	  
	  }
	  else
	  {
	  //rest timer
	  if(LED_off(TIMER_PORT_CE, TIMER_PIN_CE)!=LED_OK)
	  {
		  return APP_LED_ERROR;
	  }
	  else if(LED_on(TIMER_PORT_RST, TIMER_PIN_RST)!= LED_OK)
	  {
		  return APP_LED_ERROR;
		  
	  }
	  
	  }
}
	return APP_OK;
	
}


EN_appError_t app_pwm_mode(float32 pwmValue)
{
	 f32_g_Timer0_speed= pwmValue/PWM_100;
	 f32_g_Timer0_time_1= (f32_g_Timer0_speed * PWM_256);
	 f32_g_Timer0_time_2= PWM_256-f32_g_Timer0_time_1;
	 if(TIMER_timer0PWM_mode(f32_g_Timer0_time_1)!= TIMER_OK)
	 {
		 return APP_TIMER_ERROR;
	 }
	 // this is used to set pin to high

	 if(LED_on(PORT_B,PIN0)!= LED_OK)
	 {
		 return APP_TIMER_ERROR;
	} 
	  if(TIMER_timer0PWM_mode(f32_g_Timer0_time_2)!= TIMER_OK)
	  {
		  return APP_TIMER_ERROR;
	  }
	 // this is used to set pin to low 
	 if(LED_off(PORT_B,PIN0)!= LED_OK)
	 {
		 return APP_TIMER_ERROR;
	 }
	 return APP_OK;
}

EN_appError_t app_move_short_slide(void)
{
	if(LED_off(LED_0_PORT,LED_0_PIN)!= LED_OK)
	{
		return APP_LED_ERROR;
	}
	i32_g_TimeMode_ovf= MOVE_2_SEC; 
	if(motor_move_forward()!=MOTOR_OK)
	{
		return APP_MOTOR_ERROR;
	}
	else if(LED_on(LED_2_PORT,LED_2_PIN)!= LED_OK)
	{
		return APP_LED_ERROR;
	}
	else if(app_pwm_mode(_30_PER_OF_MAX_SPEED)!=APP_OK)
	{
		return APP_ERROR_EXIT;
	}
	
	
	return APP_OK;
	
}

EN_appError_t app_car_stop(void)
{
	
	if(LED_off(LED_1_PORT, LED_1_PIN)!=LED_OK)
	{
		return APP_LED_ERROR;
	}
	else if (LED_off(LED_2_PORT, LED_2_PIN)!= LED_OK)
	{
		return APP_LED_ERROR;
	}
	else if(LED_off(LED_3_PORT, LED_3_PIN)!= LED_OK)
	{
		return APP_LED_ERROR;
	}
	else if(LED_on(LED_0_PORT, LED_0_PIN)!= LED_OK)
	{
		return APP_LED_ERROR;
	}
	else
	{
	i32_g_TimeMode_ovf= STOP_HALF_SEC;  // 5 seconds for simulation test
	motor_stop();
	}
	
	return APP_OK;
	
	
}

// car will move forward to create the longest side of the rectangle for 3 seconds with 50% of its maximum speed
EN_appError_t app_move_long_slide(void)
{
	if(LED_off(LED_0_PORT,LED_0_PIN)!=LED_OK)
	{
		return APP_LED_ERROR;
	}
	i32_g_TimeMode_ovf= MOVE_3_SEC; 
	if(motor_move_forward()!= MOTOR_OK)
	{
		return APP_ERROR_EXIT;
	}
	else if(LED_on(LED_1_PORT,LED_1_PIN)!=LED_OK)
	{
		return APP_LED_ERROR;
		
	}
	else if(app_pwm_mode(_50_PER_OF_MAX_SPEED)!=APP_OK)
	{
		return APP_ERROR_EXIT;
	}
	
	
	
	return APP_OK;
	
}

void app_car_initial_state(void){
	
	i32_g_TimeMode_ovf= MOVE_1_SEC;  // 5 seconds for simulation test
	motor_stop();
}


EN_appError_t app_rotate_car_90Deg(void)
{
	if(LED_off(LED_0_PORT,LED_0_PIN)!= LED_OK)
	{
		return APP_LED_ERROR;
	}
	float32 wheel_rotation, rotation_time, wheel_circumference, wheel_perimeter;
	
	wheel_circumference = MATH_PI*DISTANCE_BETWEEN_WHEELS;
	wheel_perimeter = MATH_PI*DIAMATER_OF_WHEEL;
	
	wheel_rotation = ((wheel_circumference)/(wheel_perimeter));
	rotation_time = ((wheel_rotation*QUARATER_CIRCLE)/(MAXIMUM_SPEED*WHEEL_APPROX))*WHEEL_DEGREE;
	i32_g_TimeMode_ovf = rotation_time/WHEEL_TIME_FREQ;

	if(motor_rotate()!=MOTOR_OK)
	{
		return APP_MOTOR_ERROR;
	}
	else if(LED_on(LED_3_PORT,LED_3_PIN)!= LED_OK)
	{
		return APP_LED_ERROR;
	}
	else if(app_pwm_mode(_10_PER_OF_MAX_SPEED)!=APP_OK)
	{
		return APP_ERROR_EXIT;
		
	}
	
	return APP_OK;
	
}


void test_app(void) {

	/* initializing test cases */
	/* test case 1.. returns APP_LED_ERROR */
	led_pin_tst = testFail;
	APP_init();

	/* test case 2.. returns APP_BTN_ERROR */
	led_pin_tst = LED_0_PIN;
	btn_pin_tst = testFail;
	APP_init();
	//btn_pin_tst = BUTTON_1_PIN;
	
		/* test case 3.. returns APP_ERROR_EXIT */
		led_pin_tst = LED_0_PIN;
		//btn_pin_tst = BUTTON_1_PIN;
		timer_mode_tst = testFail;
		APP_init();
		timer_mode_tst = timer0_normal_mode;

	/* APP_start test cases   */
	/* test case 4.. returns APP_ERROR_EXIT*/
	APP_init();
	led_pin_tst = testFail;
	APP_start();
	led_pin_tst = LED_0_PIN;
	
	
	/*test case 5 [HAPPY Case scenario]*/
		timer_mode_tst = timer0_normal_mode;
	
	led_pin_tst = LED_0_PIN;
	//btn_pin_tst = BUTTON_1_PIN;
	APP_init();
	APP_start();

}
