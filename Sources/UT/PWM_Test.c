/*
 * PWM_Test.c
 *
 *  Created on: Apr 29, 2019
 *      Author: PCO
 */
#include "PWM_Test.h"

int PWM_test(void)
{
	UART0_send_string_ln("\t\033[33mMotors\033[0m");
	PWM_duty(10000,0);
	delayMs(1000);
	PWM_duty(10000,10000);
	delayMs(1000);
	PWM_duty(10000,-10000);
	delayMs(1000);
	PWM_duty(0,0);
	
	return 0;
}
