/*
 * led.c
 *
 * Created: 8/24/2023 12:41:04 AM
 *  Author: HP
 */

#include "led.h"

EN_ledError_t LED_init(uint8_t u8_a_ledPort, uint8_t u8_a_ledPin) {
   return (DIO_init(u8_a_ledPort, u8_a_ledPin, OUT));
}

EN_ledError_t LED_on(uint8_t u8_a_ledPort, uint8_t u8_a_ledPin) {
   return (DIO_write(u8_a_ledPort, u8_a_ledPin, HIGH));
}

EN_ledError_t LED_off(uint8_t u8_a_ledPort, uint8_t u8_a_ledPin) {
   return (DIO_write(u8_a_ledPort, u8_a_ledPin, LOW));
}

EN_ledError_t LED_toggle(uint8_t u8_a_ledPort, uint8_t u8_a_ledPin) {
   return (DIO_toggle(u8_a_ledPort, u8_a_ledPin));
}

EN_ledError_t LED_read(uint8_t u8_a_ledPort, uint8_t u8_a_ledPin, uint8_t * u8_a_value) {
   return (DIO_read(u8_a_ledPort, u8_a_ledPin, u8_a_value));
}

void test_led(void) {
   /* test case 1.. returns LED_INVALID_PIN */
   LED_init(PORT_A, ledPinFail);

   /* test case 2.. returns LED_INVALID_PORT */
   LED_on(ledPortFail, PIN1);

   /* test case 3.. returns LED_INVALID_PORT*/
   LED_off(ledPortFail, PIN1);

   /* test case 4.. returns LED_INVALID_PIN*/
   LED_toggle(PORT_A, ledPinFail);

   /* test case 5.. returns LED_OK [HAPPY CASE SCENARIO]*/
   LED_init(PORT_A, PIN1);
   LED_on(PORT_A, PIN1);
   uint8_t value;
   LED_read(PORT_A, PIN1, & value);
}