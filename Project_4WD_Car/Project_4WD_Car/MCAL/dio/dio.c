/*
 * dio.c
 *
 * Created: 8/23/2023 9:48:04 PM
 *  Author: HP
 */
// include .h
// global variables 
// function definitions
#include "dio.h"


void DIO_clearBit(uint8_t u8_a_portNumber, uint8_t u8_a_pinNumber) {
   switch (u8_a_portNumber) {
   case PORT_A: {
      DDRA &= ~(INITIAL_VALUE_1 << u8_a_pinNumber);
      break;
   }

   case PORT_B: {
      DDRB &= ~(INITIAL_VALUE_1 << u8_a_pinNumber);
      break;
   }
   case PORT_C: {
      DDRC &= ~(INITIAL_VALUE_1 << u8_a_pinNumber);
      break;
   }
   case PORT_D: {
      DDRD &= ~(INITIAL_VALUE_1 << u8_a_pinNumber);
      break;
   }
   }
}
void DIO_setBit(uint8_t u8_a_portNumber, uint8_t u8_a_pinNumber) {
   switch (u8_a_portNumber) {
   case PORT_A: {
      DDRA |= (INITIAL_VALUE_1 << u8_a_pinNumber);
      break;
   }

   case PORT_B: {
      DDRB |= (INITIAL_VALUE_1 << u8_a_pinNumber);
      break;
   }
   case PORT_C: {
      DDRC |= (INITIAL_VALUE_1 << u8_a_pinNumber);
      break;
   }
   case PORT_D: {
      DDRD |= (INITIAL_VALUE_1 << u8_a_pinNumber);
      break;
   }
   }
}

EN_dioError_t DIO_init(uint8_t u8_a_portNumber, uint8_t u8_a_pinNumber, uint8_t u8_a_direction) {
   if (u8_a_pinNumber > MAX_PORTS || u8_a_pinNumber < MIN_PORTS) {
      return DIO_INVALID_PIN;
   }

   switch (u8_a_portNumber) {
   case PORT_A: {
      if (u8_a_direction == IN) {
         DIO_clearBit(u8_a_portNumber, u8_a_pinNumber);
         return DIO_OK;
      } else if (u8_a_direction == OUT) {
         CLEAR_BIT(PORTA, u8_a_pinNumber);
         DIO_setBit(u8_a_portNumber, u8_a_pinNumber);
         return DIO_OK;
      } else {
         return DIO_INVALID_INIT;
      }
      break;
   }

   case PORT_B: {
      if (u8_a_direction == IN) {
         DIO_clearBit(u8_a_portNumber, u8_a_pinNumber);
         return DIO_OK;

      } else if (u8_a_direction == OUT) {
         CLEAR_BIT(PORTB, u8_a_pinNumber);
         DIO_setBit(u8_a_portNumber, u8_a_pinNumber);
         return DIO_OK;

      } else {
         return DIO_INVALID_INIT;
      }
      break;
   }

   case PORT_C: {
      if (u8_a_direction == IN) {
         DIO_clearBit(u8_a_portNumber, u8_a_pinNumber);
         return DIO_OK;

      } else if (u8_a_direction == OUT) {
         CLEAR_BIT(PORTC, u8_a_pinNumber);
         DIO_setBit(u8_a_portNumber, u8_a_pinNumber);
         return DIO_OK;

      } else {
         return DIO_INVALID_INIT;
      }
      break;
   }

   case PORT_D: {
      if (u8_a_direction == IN) {
         DIO_clearBit(u8_a_portNumber, u8_a_pinNumber);
         return DIO_OK;
      } else if (u8_a_direction == OUT) {
         CLEAR_BIT(PORTD, u8_a_pinNumber);
         DIO_setBit(u8_a_portNumber, u8_a_pinNumber);
         return DIO_OK;
      } else {
         return DIO_INVALID_INIT;
      }
      break;
   }
   default: {
      return DIO_INVALID_PORT;
   }
   }
   return DIO_INVALID_PORT;

}

EN_dioError_t DIO_write(uint8_t u8_a_portNumber, uint8_t u8_a_pinNumber, uint8_t u8_a_value) {
   if (u8_a_pinNumber > MAX_PORTS || u8_a_pinNumber < MIN_PORTS) {
      return DIO_INVALID_PIN;

   }
   switch (u8_a_portNumber) {
   case PORT_A: {
      if (u8_a_value == LOW) {
         PORTA &= ~(INITIAL_VALUE_1 << u8_a_pinNumber);
         return DIO_OK;
      } else if (u8_a_value == HIGH) {
         PORTA |= (INITIAL_VALUE_1 << u8_a_pinNumber);
         return DIO_OK;

      } else {
         return DIO_INVALID_VALUE;
      }
      break;
   }

   case PORT_B: {
      if (u8_a_value == LOW) {
         PORTB &= ~(INITIAL_VALUE_1 << u8_a_pinNumber);
         return DIO_OK;

      } else if (u8_a_value == HIGH) {
         PORTB |= (INITIAL_VALUE_1 << u8_a_pinNumber);
         return DIO_OK;

      } else {
         return DIO_INVALID_VALUE;

      }
      break;
   }

   case PORT_C: {
      if (u8_a_value == LOW) {
         PORTC &= ~(INITIAL_VALUE_1 << u8_a_pinNumber);
         return DIO_OK;

      } else if (u8_a_value == HIGH) {
         PORTC |= (INITIAL_VALUE_1 << u8_a_pinNumber);
         return DIO_OK;

      } else {
         return DIO_INVALID_VALUE;

      }
      break;
   }

   case PORT_D: {
      if (u8_a_value == LOW) {
         PORTD &= ~(INITIAL_VALUE_1 << u8_a_pinNumber);
         return DIO_OK;

      } else if (u8_a_value == HIGH) {
         PORTD |= (INITIAL_VALUE_1 << u8_a_pinNumber);
         return DIO_OK;
      } else {
         return DIO_INVALID_VALUE;
      }
      break;
   }
   default: {
      return DIO_INVALID_PORT;
   }
   }
}

EN_dioError_t DIO_read(uint8_t u8_a_portNumber, uint8_t u8_a_pinNumber, uint8_t * u8_a_value) {

   if (u8_a_pinNumber > MAX_PORTS || u8_a_pinNumber < MIN_PORTS) {
      return DIO_INVALID_PIN;

   }
   switch (u8_a_portNumber) {
   case PORT_A: {
      * u8_a_value = (PINA & (1 << u8_a_pinNumber)) >> u8_a_pinNumber;
      return DIO_OK;
   }
   case PORT_B: {
      * u8_a_value = (PINB & (1 << u8_a_pinNumber)) >> u8_a_pinNumber;
      return DIO_OK;

   }
   case PORT_C: {
      * u8_a_value = (PINC & (1 << u8_a_pinNumber)) >> u8_a_pinNumber;
      return DIO_OK;

   }
   case PORT_D: {
      * u8_a_value = (PIND & (1 << u8_a_pinNumber)) >> u8_a_pinNumber;
      return DIO_OK;

   }
   default: {
      return DIO_INVALID_PORT;
   }
   }
}

EN_dioError_t DIO_toggle(uint8_t u8_a_portNumber, uint8_t u8_a_pinNumber) {
   if (u8_a_pinNumber > MAX_PORTS || u8_a_pinNumber < MIN_PORTS) {
      return DIO_INVALID_PIN;

   }
   switch (u8_a_portNumber) {
   case PORT_A: {
      TOGGLE_BIT(PORTA, u8_a_pinNumber);
      return DIO_OK;

   }
   case PORT_B: {
      TOGGLE_BIT(PORTB, u8_a_pinNumber);
      return DIO_OK;
   }
   case PORT_C: {
      TOGGLE_BIT(PORTC, u8_a_pinNumber);
      return DIO_OK;
   }
   case PORT_D: {
      TOGGLE_BIT(PORTD, u8_a_pinNumber);
      return DIO_OK;

   }
   default: {
      return DIO_INVALID_PORT;

   }
   }
}

void test_dio(void) {
   /* test case 1.. returns DIO_INVALID_PIN */
   DIO_init(PORT_A, testFailDIO_PIN, OUT);

   /* test case 2.. returns DIO_INVALID_PORT */
   DIO_init(testFailDIO_PORT, PIN1, OUT);

   /* test case 3.. returns DIO_INVALID_INIT*/
   DIO_init(PORT_A, PIN1, testFailDioOp); //not OUT or IN

   /* test case 4.. returns DIO_INVALID_VALUE*/
   DIO_init(PORT_A, PIN1, OUT);
   DIO_write(PORT_A, PIN1, testFailDioOp); // Not HIGH or LOW

   /* test case 5.. returns DIO_OK [HAPPY CASE SCENARIO]*/
   DIO_init(PORT_A, PIN1, OUT);
   DIO_write(PORT_A, PIN1, HIGH);
   uint8_t value;
   DIO_read(PORT_A, PIN1, & value);

}