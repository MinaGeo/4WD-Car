/*
 * application.h
 *
 * Created: 8/24/2023 1:51:41 AM
 *  Author: HP
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_
#define PWM_256 256
#define PWM_100 100
#define MATH_PI 3.14159
//CAR MODIFICATIONS
#define DISTANCE_BETWEEN_WHEELS  180
#define DIAMATER_OF_WHEEL            60
#define MAXIMUM_SPEED                120
#define QUARATER_CIRCLE 0.25
#define WHEEL_DEGREE 60
#define WHEEL_APPROX 0.1
#define WHEEL_TIME_FREQ 0.000256

//MOVEMENT SEC
#define MOVE_1_SEC 3907
#define MOVE_2_SEC 7813
#define MOVE_3_SEC 11719
#define STOP_HALF_SEC 1953
//PERCENTAGE OF MAXIMUM SPEED
#define _50_PER_OF_MAX_SPEED 50
#define _30_PER_OF_MAX_SPEED 30
#define _10_PER_OF_MAX_SPEED 10




#include "../HAL/led/led.h"
#include "../HAL/button/button.h"
#include "../HAL/motor/motor.h"


typedef enum EN_appError_t{
	APP_OK, APP_LED_ERROR, APP_BTN_ERROR,APP_INT_ERROR,APP_ERROR_EXIT, APP_MOTOR_ERROR, APP_TIMER_ERROR, APP_INTERRUPT_ERROR
}EN_appError_t;

EN_appError_t APP_init(void);
EN_appError_t APP_start(void);


EN_appError_t app_move_short_slide(void);
EN_appError_t app_move_long_slide(void);
EN_appError_t app_rotate_car_90Deg(void);
EN_appError_t app_car_stop(void);
EN_appError_t app_pwm_mode(float32 pwmValue);
void app_car_initial_state(void);



void test_app(void);
#endif /* APPLICATION_H_ */