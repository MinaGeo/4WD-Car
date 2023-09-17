/*
 * application.c
 *
 * Created: 8/24/2023 1:51:49 AM
 *  Author: HP
 */
#include "application.h"

uint8_t led_pin_tst = TIMER_PIN_CE;
uint8_t btn_pin_tst = BUTTON_START_PIN;
uint8_t ext_tst = EXTERNAL_INTERRUPT_0;

EN_appError_t APP_init(void) {

   if (LED_init(PWM_LED_PORT, PWM_LED_PIN) != LED_OK) {
      return APP_LED_ERROR;
   } else if (LED_init(TIMER_PORT_CE, led_pin_tst) != LED_OK) {
      return APP_LED_ERROR;
   } else if (LED_init(TIMER_PORT_RST, TIMER_PIN_RST) != LED_OK) {
      return APP_LED_ERROR;
   } else if (BUTTON_init(BUTTON_STOP_PORT, BUTTON_STOP_PIN) != BTN_OK) {
      return APP_BTN_ERROR;
   } else if (BUTTON_init(BUTTON_START_PORT, btn_pin_tst) != BTN_OK) {
      return APP_BTN_ERROR;

   } else if (LED_init(LED_0_PORT, LED_0_PIN) != LED_OK) {
      return APP_LED_ERROR;

   } else if (LED_init(LED_1_PORT, LED_1_PIN) != LED_OK) {
      return APP_LED_ERROR;

   } else if (LED_init(LED_2_PORT, LED_2_PIN) != LED_OK) {
      return APP_LED_ERROR;

   } else if (LED_init(LED_3_PORT, LED_3_PIN) != LED_OK) {
      return APP_LED_ERROR;

   } else if (MOTOR_init() != MOTOR_OK) {
      return APP_MOTOR_ERROR;
   } else {
      INTERRUPTS_enableGlobalInterrupt();

      if (INTERRUPTS_enableExternalInterrupts(ext_tst) != INTERRUPT_OK) {
         return APP_INTERRUPT_ERROR;
      } else if (INTERRUPTS_enableExternalInterrupts(EXTERNAL_INTERRUPT_1) != INTERRUPT_OK) {
         return APP_INTERRUPT_ERROR;
      } else if (INTERRUPTS_EXT_SetCallBack(EXTERNAL_INTERRUPT_0, MOTOR_stop) != INTERRUPT_OK) {
         return APP_INTERRUPT_ERROR;
      } else if (INTERRUPTS_extInterruptsEdge(EXTERNAL_INTERRUPT_0, LOW_LEVEL) != INTERRUPT_OK) {
         return APP_INTERRUPT_ERROR;
      } else if (INTERRUPTS_extInterruptsEdge(EXTERNAL_INTERRUPT_1, LOW_LEVEL) != INTERRUPT_OK) {
         return APP_INTERRUPT_ERROR;
      } else if (TIMER_timer2Init() != TIMER_OK) {
         return APP_TIMER_ERROR;

      }

   }
   return APP_OK;

}

EN_appError_t APP_start(void) {

   while (INITIAL_VALUE_1) {
      if (u8_g_timerBtn_flag == CASE1) {

         if (LED_on(TIMER_PORT_CE, led_pin_tst) != LED_OK) {
            return APP_LED_ERROR;
         } else if (LED_off(TIMER_PORT_RST, TIMER_PIN_RST) != LED_OK) {
            return APP_LED_ERROR;
         }

         switch (u8_g_currentCarState) {
         case CASE0:
            APP_carInitialState();
            break;
         case CASE1:
            if (APP_moveLongSlide() != APP_OK) {
               return APP_ERROR_EXIT;
            }
            break;
         case CASE2:
            if (APP_carStop() != APP_OK) {
               return APP_ERROR_EXIT;
            }
            break;
         case CASE3:
            if (APP_rotateCar_90Deg() != APP_OK) {
               return APP_ERROR_EXIT;
            }
            break;
         case CASE4:
            if (APP_carStop() != APP_OK) {
               return APP_ERROR_EXIT;
            }
            break;
         case CASE5:
            if (APP_moveShortSlide() != APP_OK) {
               return APP_ERROR_EXIT;

            }
            break;
         case CASE6:
            if (APP_carStop() != APP_OK) {
               return APP_ERROR_EXIT;
            }
            break;
         case CASE7:
            if (APP_rotateCar_90Deg() != APP_OK) {
               return APP_ERROR_EXIT;
            }
            break;
         case CASE8:
            if (APP_carStop() != APP_OK) {
               return APP_ERROR_EXIT;
            }
            break;
         default:
            // do nothing
            break;
         }
      } else {
         //reset timer
         if (LED_off(TIMER_PORT_CE, TIMER_PIN_CE) != LED_OK) {
            return APP_LED_ERROR;
         } else if (LED_on(TIMER_PORT_RST, TIMER_PIN_RST) != LED_OK) {
            return APP_LED_ERROR;

         }

      }
   }
   return APP_OK;

}

EN_appError_t APP_pwmMode(float32 f32_a_pwmValue) {
   float32 f32_v_Timer0_time_1, f32_v_Timer0_time_2;
   f32_v_Timer0_time_1 = ((f32_a_pwmValue / PWM_100) * PWM_256);
   f32_v_Timer0_time_2 = (PWM_256 - f32_v_Timer0_time_1);
   if (TIMER_timer0PWM_mode(f32_v_Timer0_time_1) != TIMER_OK) {
      return APP_TIMER_ERROR;
   } else if (LED_on(PWM_LED_PORT, PWM_LED_PIN) != LED_OK) {
      return APP_LED_ERROR;
   } else if (TIMER_timer0PWM_mode(f32_v_Timer0_time_2) != TIMER_OK) {
      return APP_TIMER_ERROR;
   } else if (LED_off(PWM_LED_PORT, PWM_LED_PIN) != LED_OK) {
      return APP_LED_ERROR;
   }
   return APP_OK;
}

EN_appError_t APP_moveShortSlide(void) {
   if (LED_off(LED_0_PORT, LED_0_PIN) != LED_OK) {
      return APP_LED_ERROR;
   }
   i32_g_TimeMode_ovf = MOVE_2_SEC;
   if (MOTOR_moveForward() != MOTOR_OK) {
      return APP_MOTOR_ERROR;
   } else if (LED_on(LED_2_PORT, LED_2_PIN) != LED_OK) {
      return APP_LED_ERROR;
   } else if (APP_pwmMode(_30_PER_OF_MAX_SPEED) != APP_OK) {
      return APP_ERROR_EXIT;
   }

   return APP_OK;

}

EN_appError_t APP_carStop(void) {

   if (LED_off(LED_1_PORT, LED_1_PIN) != LED_OK) {
      return APP_LED_ERROR;
   } else if (LED_off(LED_2_PORT, LED_2_PIN) != LED_OK) {
      return APP_LED_ERROR;
   } else if (LED_off(LED_3_PORT, LED_3_PIN) != LED_OK) {
      return APP_LED_ERROR;
   } else if (LED_on(LED_0_PORT, LED_0_PIN) != LED_OK) {
      return APP_LED_ERROR;
   } else {
      i32_g_TimeMode_ovf = STOP_HALF_SEC;
      MOTOR_stop();
   }

   return APP_OK;

}

EN_appError_t APP_moveLongSlide(void) {
   if (LED_off(LED_0_PORT, LED_0_PIN) != LED_OK) {
      return APP_LED_ERROR;
   }
   i32_g_TimeMode_ovf = MOVE_3_SEC;
   if (MOTOR_moveForward() != MOTOR_OK) {
      return APP_MOTOR_ERROR;
   } else if (LED_on(LED_1_PORT, LED_1_PIN) != LED_OK) {
      return APP_LED_ERROR;

   } else if (APP_pwmMode(_50_PER_OF_MAX_SPEED) != APP_OK) {
      return APP_ERROR_EXIT;
   }
   return APP_OK;
}

void APP_carInitialState(void) {
   i32_g_TimeMode_ovf = MOVE_1_SEC;
   MOTOR_stop();
}

EN_appError_t APP_rotateCar_90Deg(void) {
   if (LED_off(LED_0_PORT, LED_0_PIN) != LED_OK) {
      return APP_LED_ERROR;
   }
   float32 wheel_rotation, rotation_time, wheel_circumference, wheel_perimeter;

   wheel_circumference = MATH_PI * DISTANCE_BETWEEN_WHEELS;
   wheel_perimeter = MATH_PI * DIAMATER_OF_WHEEL;

   wheel_rotation = ((wheel_circumference) / (wheel_perimeter));
   rotation_time = ((wheel_rotation * QUARATER_CIRCLE) / (MAXIMUM_SPEED * WHEEL_APPROX)) * WHEEL_DEG;
   i32_g_TimeMode_ovf = rotation_time / WHEEL_TIME_FREQ;

   if (MOTOR_rotate() != MOTOR_OK) {
      return APP_MOTOR_ERROR;
   } else if (LED_on(LED_3_PORT, LED_3_PIN) != LED_OK) {
      return APP_LED_ERROR;
   } else if (APP_pwmMode(_20_PER_OF_MAX_SPEED) != APP_OK) {
      return APP_ERROR_EXIT;
   }
   return APP_OK;
}

void test_app(void) {

   /* initializing test cases (APP_init) */
   /* test case 1.. returns APP_LED_ERROR */
   led_pin_tst = testFail;
   APP_init();

   /* test case 2.. returns APP_BTN_ERROR */
   led_pin_tst = TIMER_PIN_CE;
   btn_pin_tst = testFail;
   APP_init();
   btn_pin_tst = BUTTON_START_PIN;

   /* test case 3.. returns APP_INTERRUPT_ERROR */
   ext_tst = testFail;
   APP_init();
   ext_tst = EXTERNAL_INTERRUPT_0;

   /* APP_start test cases   */
   /* test case 4.. returns APP_ERROR_EXIT*/
   APP_init();
   led_pin_tst = testFail;
   APP_start();
   led_pin_tst = TIMER_PIN_CE;

   /*test case 5 [HAPPY Case scenario]*/
   APP_init();
   APP_start();

}