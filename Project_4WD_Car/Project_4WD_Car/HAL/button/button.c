/*
 * button.c
 *
 * Created: 8/24/2023 2:49:47 AM
 *  Author: HP
 */

#include "button.h"

EN_btnError_t BUTTON_init(uint8_t u8_a_buttonPort, uint8_t u8_a_buttonPin) {
   return (DIO_init(u8_a_buttonPort, u8_a_buttonPin, IN));

}

EN_btnError_t BUTTON_read(uint8_t u8_a_buttonPort, uint8_t u8_a_buttonPin, uint8_t * u8_a_value) {
   return (DIO_read(u8_a_buttonPort, u8_a_buttonPin, u8_a_value));
}

void test_button(void) {
   /* test case 1.. returns BTN_INVALID_PIN */
   BUTTON_init(PORT_A, btnPinFail);

   /* test case 2.. returns BTN_INVALID_PORT */
   BUTTON_init(btnPortFail, PIN1);

   /* test case 3.. returns DIO_OK [HAPPY CASE SCENARIO]*/
   BUTTON_init(PORT_A, PIN1);
   uint8_t value;
   BUTTON_read(PORT_A, PIN1, & value);

}