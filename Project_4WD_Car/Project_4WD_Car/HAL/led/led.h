/*
 * led.h
 *
 * Created: 8/24/2023 12:40:58 AM
 *  Author: HP
 */

#ifndef LED_H_
#define LED_H_
#include "../MCAL/dio/dio.h"

//defining timer leds pins and ports
#define TIMER_PORT_CE PORT_B
#define TIMER_PORT_RST PORT_B
#define TIMER_PIN_RST PIN4
#define TIMER_PIN_CE PIN3

#define PWM_LED_PORT PORT_B
#define PWM_LED_PIN PIN0
//test fails
#define ledPinFail 10
#define ledPortFail 'E'

typedef enum EN_ledError_t {
   LED_OK,
   LED_INVALID_PORT,
   LED_INVALID_PIN,
   LED_INVALID_INIT,
   LED_INVALID_VALUE
}
EN_ledError_t;

EN_ledError_t LED_init(uint8_t ledPort, uint8_t ledPin); //initialising a LED
EN_ledError_t LED_on(uint8_t u8_a_ledPort, uint8_t u8_a_ledPin); //turning a led on
EN_ledError_t LED_off(uint8_t ledPort, uint8_t ledPin); //turning off a led
EN_ledError_t LED_toggle(uint8_t ledPort, uint8_t ledPin); //switching an on led to off or vice versa
EN_ledError_t LED_read(uint8_t ledPort, uint8_t ledPin, uint8_t * value); //read LED Status

void test_led(void);
#endif /* LED_H_ */