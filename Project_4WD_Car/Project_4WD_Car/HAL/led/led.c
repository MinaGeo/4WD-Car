/*
 * led.c
 *
 * Created: 8/24/2023 12:41:04 AM
 *  Author: HP
 */ 

#include "led.h"

EN_ledError_t LED_init(uint8_t ledPort,uint8_t ledPin){
	return(DIO_init(ledPort,ledPin,OUT));
}
EN_ledError_t LED_on(uint8_t ledPort,uint8_t ledPin){
	return(DIO_write(ledPort,ledPin,HIGH));
}
EN_ledError_t LED_off(uint8_t ledPort,uint8_t ledPin){
	return(DIO_write(ledPort,ledPin,LOW));
}
EN_ledError_t LED_toggle(uint8_t ledPort,uint8_t ledPin){
	return(DIO_toggle(ledPort,ledPin));
}
EN_ledError_t LED_read(uint8_t ledPort,uint8_t ledPin,uint8_t* value){
	return(DIO_read(ledPort,ledPin,value));
}







