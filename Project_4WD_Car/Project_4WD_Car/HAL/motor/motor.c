/*
 * motor.c
 *
 * Created: 9/10/2023 9:35:26 PM
 *  Author: HP
 */

#include "motor.h"

uint8_t u8_g_motorTest = MOTOR_PIN0;

EN_motorError_t MOTOR_init(void) {
   if (DIO_init(MOTOR_PORT0, u8_g_motorTest, OUT) != DIO_OK) {
      return MOTOR_INVALID_INIT;

   } else if (DIO_init(MOTOR_PORT1, MOTOR_PIN1, OUT) != DIO_OK) {
      return MOTOR_INVALID_INIT;
   } else if (DIO_init(MOTOR_PORT2, MOTOR_PIN2, OUT) != DIO_OK) {
      return MOTOR_INVALID_INIT;
   } else if (DIO_init(MOTOR_PORT3, MOTOR_PIN3, OUT) != DIO_OK) {
      return MOTOR_INVALID_INIT;

   } else {
      return MOTOR_OK;
   }

}

EN_motorError_t MOTOR_moveForward(void) {

   if (DIO_write(MOTOR_PORT0, u8_g_motorTest, LOW) != DIO_OK) {
      return MOTOR_INVALID_MOVEFWD;

   } else if (DIO_write(MOTOR_PORT1, MOTOR_PIN1, HIGH) != DIO_OK) {
      return MOTOR_INVALID_MOVEFWD;
   } else if (DIO_write(MOTOR_PORT2, MOTOR_PIN2, LOW) != DIO_OK) {
      return MOTOR_INVALID_MOVEFWD;
   } else if (DIO_write(MOTOR_PORT3, MOTOR_PIN3, HIGH) != DIO_OK) {
      return MOTOR_INVALID_MOVEFWD;

   } else {
      return MOTOR_OK;
   }

}

EN_motorError_t MOTOR_rotate(void) {

   if (DIO_write(MOTOR_PORT0, u8_g_motorTest, HIGH) != DIO_OK) {
      return MOTOR_INVALID_ROTATE;

   } else if (DIO_write(MOTOR_PORT1, MOTOR_PIN1, LOW) != DIO_OK) {
      return MOTOR_INVALID_ROTATE;
   } else if (DIO_write(MOTOR_PORT2, MOTOR_PIN2, LOW) != DIO_OK) {
      return MOTOR_INVALID_ROTATE;
   } else if (DIO_write(MOTOR_PORT3, MOTOR_PIN3, HIGH) != DIO_OK) {
      return MOTOR_INVALID_ROTATE;

   } else {
      return MOTOR_OK;
   }

}

void MOTOR_stop(void) {
   DIO_write(MOTOR_PORT0, MOTOR_PIN0, LOW);
   DIO_write(MOTOR_PORT1, MOTOR_PIN1, LOW);
   DIO_write(MOTOR_PORT2, MOTOR_PIN2, LOW);
   DIO_write(MOTOR_PORT3, MOTOR_PIN3, LOW);

}

void test_motor(void) {
   /* test case 1.. returns MOTOR_INVALID_INIT */
   u8_g_motorTest = motorFailTest;
   MOTOR_init();

   /* test case 2.. returns MOTOR_INVALID_MOVEFWD */
   MOTOR_moveForward();

   /* test case 3.. returns MOTOR_INVALID_ROTATE*/
   MOTOR_rotate();

   /* test case 4.. returns MOTOR_OK [example of HAPPY CASE SCENARIO]*/
   u8_g_motorTest = MOTOR_PIN0;
   MOTOR_init();
   MOTOR_moveForward();

}