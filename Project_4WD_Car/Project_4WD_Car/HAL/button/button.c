/*
 * button.c
 *
 * Created: 8/24/2023 2:49:47 AM
 *  Author: HP
 */ 

#include "button.h"
EN_btnError_t BUTTON_init(uint8_t buttonPort,uint8_t buttonPin)
{
	return(DIO_init(buttonPort,buttonPin,IN));
	
}
EN_btnError_t BUTTON_read(uint8_t buttonPort,uint8_t buttonPin,uint8_t* value)
{
	return(DIO_read(buttonPort,buttonPin,value));
}


