/*
 * interrupts.h
 *
 * Created: 8/27/2023 2:09:12 PM
 *  Author: HP
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../UTIL/registers.h"

#include "../MCAL/dio/dio.h"


typedef enum EN_InterruptError_t {
   INTERRUPT_OK,
   INTERRUPT_INVALID_ENABLE,
   INTERRUPT_INVALID_EDGE,
   INTERRUPT_SETCB_FAIL
}
EN_InterruptError_t;

//defining interrupts MACROS
#define EXTERNAL_INTERRUPT_0 0
#define EXTERNAL_INTERRUPT_1 1
#define EXTERNAL_INTERRUPT_2 2

//Defining edges
#define LOW_LEVEL 0
#define LOGICAL_CHANGE 1
#define FALLING_EDGE 2
#define RISING_EDGE 3

//defining test fails
#define interruptFail 10
#define edgeFail 10

extern uint8_t u8_g_timerBtn_flag;

//defining external interrupts vectors
//external interrupt request 0
#define EXT_INT_0 __vector_1
//external interrupt request 1
#define EXT_INT_1 __vector_2
//external interrupt request 2
#define EXT_INT_2 __vector_3
/* Timer2/Counter2 Overflow */
#define TIMER2_OVF_vect __vector_5
/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect __vector_11

// Setting global interrupts - setting bit 7 in the status register 1
#define sei() __asm__ __volatile__("sei"::: "memory")

// clear global interrupts, set the I-bit in status register 0
#define cli() __asm__ __volatile__("cli"::: "memory")

//ISR FUNCTION
#define ISR(INT_VECT) void INT_VECT(void) __attribute__((signal, used));\
void INT_VECT(void)

//enabling external interrupts
EN_InterruptError_t INTERRUPTS_enableExternalInterrupts(uint8_t Interrupt);

// Enable global interrupts
void INTERRUPTS_enableGlobalInterrupt(void);

// Disable global interrupts
void INTERRUPTS_disableGlobalInterrupt(void);

/* Choose the external interrupt sense - sense on rising edge or negative edge */
EN_InterruptError_t INTERRUPTS_extInterruptsEdge(uint8_t Interrupt, uint8_t edge);

//Set callbacks functions
EN_InterruptError_t INTERRUPTS_EXT_SetCallBack(uint8_t Interrupt, void( * LocalPtr)(void));

//initialize LEDS
void INTERRUPTS_leds_init(void);

//test Function
void test_interrupts(void);
#endif /* INTERRUPTS_H_ */