/*
 * timer.h
 *
 * Created: 9/5/2023 6:00:59 PM
 *  Author: HP
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "../UTIL/registers.h"

#include "../MCAL/interrupts/interrupts.h"

#include <math.h>
 //Timers max value
#define TIMR0_MAX_VALUE 256
#define TIMR2_MAX_VALUE 256
#define FAIL_MAX 260
//timer0 modes
#define timer0_normal_mode 0
#define timer0_CTC_mode 1
#define timer0_PWM_mode 2
#define timer0_FastPWM_mode 3
//timer2 modes
#define timer2_normal_mode 0
#define timer2_CTC_mode 1
#define timer2_PWM_mode 2
#define timer2_FastPWM_mode 3
//timer0 prescalar values
#define TIMER0_STOP 0
#define TIMER0_NO_PRESCALLING 1
#define TIMER0_SCALER_8 2
#define TIMER0_SCALER_64 3
#define TIMER0_SCALER_256 4
#define TIMER0_SCALER_1024 5
#define EXTERNAL_FALLING_EDGE 6
#define EXTERNAL_RISING_EDGE 7
//timer2 prescalar values
#define TIMER2_STOP 0
#define TIMER2_NO_PRESCALLING 1
#define TIMER2_SCALER_8 2
#define TIMER2_SCALER_32 3
#define TIMER2_SCALER_64 4
#define TIMER2_SCALER_128 4
#define TIMER2_SCALER_256 5
#define TIMER2_SCALER_1024 6
//define Number and frequency of OVF
#define NUMBER_OF_OVERFLOWS 1000
#define FREQUENCY_OF_OVERFLOWS 0.000256

//timer set bits
#define TIMER_1 1
#define TIMER_0 0

//CAR_MODE
#define CAR_MODES 8

//fail test
#define timerFailTest 10
#define INVALID_NEG_VAL - 100

extern uint8_t u8_g_currentCarState;
extern int32_t i32_g_TimeMode_ovf;

typedef enum EN_TimerError_t {
   TIMER_OK,
   TIMER_INVALID_MODE,
   TIMER_INVALID_PRESCALAR,
   TIMER_INVALID_DELAY,
   TIMER_INVALID_SETINIT,
   TIMER_INVALID_OVF,
   TIMER_INVALID_T0PWM,
   TIMER_INVALID_INIT
}
EN_TimerError_t;

/******************** TIMER0 FUNCTIONS ********************************/

//Set timer0 mode (0 normal, 1 CTC, 2 PWM, 3 FastPWM)
EN_TimerError_t TIMER_timer0InitMode(uint8_t timer1_mode);

/*Timer0 pres calling (TIMER0_STOP 0, TIMER0_NO_PRESCALLING 1, TIMER0_SCALER_8 2, TIMER0_SCALER_64 3,
TIMER0_SCALER_256 4, TIMER0_SCALER_1024 5, EXTERNAL_FALLING_EDGE 6, EXTERNAL_RISING_EDGE 7 */
EN_TimerError_t TIMER_timer0Prescalar(uint8_t u8_a_prescalar);

//this functions is used to set the delay for the timer0
EN_TimerError_t TIMER_timer0Delay(float64 timeDelay);

//timer0 stop
void TIMER_timer0Stop(void);

//overflow flag clear
void TIMER_clrOF_Flag(void);

//Timer0 PWM mode
EN_TimerError_t TIMER_timer0PWM_mode(float32 pwmValue);

//Timer0 number of overflows we want to reach.
EN_TimerError_t TIMER_timer0_OVF_Number(float64 OVFNumber);

// Timer0 set initial value
EN_TimerError_t TIMER_timer0SetInitial(float64 intial_value);

/******************** TIMER2 FUNCTIONS ********************************/

//Set timer2 mode (0 normal, 1 CTC, 2 PWM, 3 FastPWM)
EN_TimerError_t TIMER_timer2InitMode(uint8_t timer2_mode);

/*Timer2 pres calling (TIMER2_STOP 0, TIMER2_NO_PRESCALLING 1, TIMER2_SCALER_8 2, TIMER2_SCALER_32 3,
TIMER2_SCALER_64 4, TIMER2_SCALER_128 5, TIMER2_SCALER_256 6, TIMER2_SCALER_1024 7 */
EN_TimerError_t TIMER_timer2Prescalar(uint8_t time2_prescalar);

// Timer2 stop
void TIMER_timer2Stop(void);

// Timer2 set initial value
EN_TimerError_t TIMER_timer2SetInitial(uint16_t intial_value);

//This function is used to Initialize timer2
EN_TimerError_t TIMER_timer2Init(void);

//test Function
void test_timer(void);
#endif /* TIMER_H_ */