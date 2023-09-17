/*
 * interrupts.c
 *
 * Created: 8/30/2023 2:38:13 PM
 *  Author: HP
 */
#include "interrupts.h"

static void( * INT0_CallBack_ptr)(void) = NULLPTR;
static void( * INT1_CallBack_ptr)(void) = NULLPTR;
static void( * INT2_CallBack_ptr)(void) = NULLPTR;

uint8_t u8_g_timerBtn_flag = INITIAL_VALUE_0;

EN_InterruptError_t INTERRUPTS_enableExternalInterrupts(uint8_t u8_a_interrupt) {

   switch (u8_a_interrupt) {
   case EXTERNAL_INTERRUPT_0:
      SET_BIT(GICR, INT0);
      return INTERRUPT_OK;
   case EXTERNAL_INTERRUPT_1:
      SET_BIT(GICR, INT1);
      return INTERRUPT_OK;
   case EXTERNAL_INTERRUPT_2:
      SET_BIT(GICR, INT2);
      return INTERRUPT_OK;
   default:
      //do nothing
      return INTERRUPT_INVALID_ENABLE;
   }

}

// Enable global interrupts
void INTERRUPTS_enableGlobalInterrupt(void) {
   sei();

}
// Disable global interrupts
void INTERRUPTS_disableGlobalInterrupt(void) {

   cli();
}

EN_InterruptError_t INTERRUPTS_extInterruptsEdge(uint8_t u8_a_interrupt, uint8_t u8_a_edge) {

   switch (u8_a_interrupt) {
   case EXTERNAL_INTERRUPT_0:
      switch (u8_a_edge) {
      case LOW_LEVEL:
         CLEAR_BIT(MCUCR, ISC00);
         CLEAR_BIT(MCUCR, ISC01);
         return INTERRUPT_OK;

      case LOGICAL_CHANGE:
         SET_BIT(MCUCR, ISC00);
         CLEAR_BIT(MCUCR, ISC01);
         return INTERRUPT_OK;

      case FALLING_EDGE:
         CLEAR_BIT(MCUCR, ISC00);
         SET_BIT(MCUCR, ISC01);
         return INTERRUPT_OK;

      case RISING_EDGE:
         SET_BIT(MCUCR, ISC00);
         SET_BIT(MCUCR, ISC01);
         return INTERRUPT_OK;

      default:
         //do nothing
         return INTERRUPT_INVALID_EDGE;

      }
   case EXTERNAL_INTERRUPT_1:
      switch (u8_a_edge) {
      case LOW_LEVEL:
         CLEAR_BIT(MCUCR, ISC10);
         CLEAR_BIT(MCUCR, ISC11);
         return INTERRUPT_OK;

      case LOGICAL_CHANGE:
         SET_BIT(MCUCR, ISC10);
         CLEAR_BIT(MCUCR, ISC11);
         return INTERRUPT_OK;

      case FALLING_EDGE:
         CLEAR_BIT(MCUCR, ISC10);
         SET_BIT(MCUCR, ISC11);
         return INTERRUPT_OK;

      case RISING_EDGE:
         SET_BIT(MCUCR, ISC10);
         SET_BIT(MCUCR, ISC11);
         return INTERRUPT_OK;

      default:
         //do nothing
         return INTERRUPT_INVALID_EDGE;

      }
      return INTERRUPT_OK;

   case EXTERNAL_INTERRUPT_2:
      switch (u8_a_edge) {

      case FALLING_EDGE:
         CLEAR_BIT(MCUCSR, ISC2);
         return INTERRUPT_OK;

      case RISING_EDGE:
         SET_BIT(MCUCSR, ISC2);
         return INTERRUPT_OK;

      default:
         //do nothing
         return INTERRUPT_INVALID_EDGE;

      }
      return INTERRUPT_OK;

   default:
      //do nothing
      return INTERRUPT_INVALID_ENABLE;
   }

}

/************************************Call back functions*********************************************/

EN_InterruptError_t INTERRUPTS_EXT_SetCallBack(uint8_t u8_a_interrupt, void(*LocalPtr)(void)) {
   switch (u8_a_interrupt) {
   case EXTERNAL_INTERRUPT_0:
      INT0_CallBack_ptr = LocalPtr;
      return INTERRUPT_OK;

   case EXTERNAL_INTERRUPT_1:
      INT1_CallBack_ptr = LocalPtr;
      return INTERRUPT_OK;

   case EXTERNAL_INTERRUPT_2:
      INT2_CallBack_ptr = LocalPtr;
      return INTERRUPT_OK;

   default:
      //do nothing
      return INTERRUPT_SETCB_FAIL;
   }

}

void INTERRUPTS_leds_init(void) {
   DIO_write(LED_0_PORT, LED_0_PIN, HIGH);
   DIO_write(LED_1_PORT, LED_1_PIN, LOW);
   DIO_write(LED_2_PORT, LED_2_PIN, LOW);
   DIO_write(LED_3_PORT, LED_3_PIN, LOW);
}

void test_interrupts(void) {
   /* test case 1.. returns INTERRUPT_INVALID_ENABLE */
   INTERRUPTS_enableExternalInterrupts(interruptFail);

   /* test case 2.. returns INTERRUPT_INVALID_ENABLE */
   INTERRUPTS_extInterruptsEdge(interruptFail, RISING_EDGE);

   /* test case 3.. returns INTERRUPT_INVALID_EDGE*/
   INTERRUPTS_extInterruptsEdge(EXTERNAL_INTERRUPT_0, edgeFail);

   /* test case 4.. returns INTERRUPT_OK [example of HAPPY CASE SCENARIO]*/
   INTERRUPTS_extInterruptsEdge(EXTERNAL_INTERRUPT_0, RISING_EDGE);

}

//ISR functions for EXI0, EXI1 and EXI2

ISR(EXT_INT_0) {
   u8_g_timerBtn_flag = INITIAL_VALUE_0;
   if (INT0_CallBack_ptr != NULLPTR) {
      INT0_CallBack_ptr();
      INTERRUPTS_leds_init();
   }
}

ISR(EXT_INT_1) {
   if (INT1_CallBack_ptr != NULLPTR) {
      INT1_CallBack_ptr();
   }
   u8_g_timerBtn_flag = INITIAL_VALUE_1;
}
ISR(EXT_INT_2) {
   if (INT2_CallBack_ptr != NULLPTR) {
      INT2_CallBack_ptr();
   }
}