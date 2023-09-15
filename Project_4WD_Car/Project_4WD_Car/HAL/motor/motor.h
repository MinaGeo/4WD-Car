/*
 * motor.h
 *
 * Created: 9/10/2023 9:35:16 PM
 *  Author: HP
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_


#include "../MCAL/dio/dio.h"

typedef enum EN_motorError_t{
	MOTOR_OK,MOTOR_INVALID_INIT, MOTOR_INVALID_MOVEFWD, MOTOR_INVALID_ROTATE, MOTOR_INVALID_STOP
}EN_motorError_t;

#define MOTOR_PORT0 PORT_C
#define MOTOR_PORT1 PORT_C
#define MOTOR_PORT2 PORT_C
#define MOTOR_PORT3 PORT_C

#define MOTOR_PIN0 PIN0
#define MOTOR_PIN1 PIN1
#define MOTOR_PIN2 PIN2
#define MOTOR_PIN3 PIN3



EN_motorError_t motor_init(void);
EN_motorError_t motor_move_forward();
EN_motorError_t motor_rotate(void);
void motor_stop(void);


#endif /* MOTOR_H_ */