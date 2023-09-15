/*
 * dio.h
 *
 * Created: 8/23/2023 9:48:13 PM
 *  Author: HP
 */ 


#ifndef DIO_H_
#define DIO_H_
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../MCAL/interrupts/interrupts.h"
#include "../MCAL/timer/timer.h"
#include "../UTIL/registers.h"
#define MIN_PORTS 0
#define MAX_PORTS 7


// all internal driver typedefs
//all driver macros
// all driver function prototypes
typedef enum EN_dioError_t{
	DIO_OK, DIO_INVALID_PORT, DIO_INVALID_PIN, DIO_INVALID_INIT,DIO_INVALID_VALUE
}EN_dioError_t;



EN_dioError_t  DIO_init(uint8_t portNumber, uint8_t pinNumber, uint8_t direction); // initilaize dio direction
EN_dioError_t  DIO_write(uint8_t portNumber,uint8_t pinNumber,uint8_t value); // write data to dio
EN_dioError_t  DIO_toggle(uint8_t portNumber,uint8_t pinNumber); // toggle dio
EN_dioError_t  DIO_read(uint8_t portNumber,uint8_t pinNumber,uint8_t* value);// read dio


void test_dio(void);
#endif /* DIO_H_ */