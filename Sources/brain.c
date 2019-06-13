/*
 * brain.c
 *
 *  Created on: May 26, 2019
 *      Author: Dani
 */
#include "brain.h"


enum State {INIT = 0, SENSING = 1, PUSHING = 2, APROACHING = 3, SCANNING = 4};
enum State currentState, nextState;

void brain()
{
	currentState = INIT, nextState = INIT;
	while (1) {
		brain_step();
		brain_forward();
	}
}

char IR_gen(){
	char buffer[30];
	if (ADC0_read_p(13)> IRTHRESHHOLDG){
		IR_Data.FrontRight = ADC0_read_p(8);
		IR_Data.BackRight = ADC0_read_p(9);
		IR_Data.FrontLeft = ADC0_read_p(11);
		IR_Data.BackLeft = ADC0_read_p(12);
		if (IR_Data.FrontRight > IRTHRESHHOLD) {
			PWM_moveBackward(10, 1);
			PWM_rotateLeft(45);
			//SysTick_delay(50);
			itoa(IR_Data.FrontRight,buffer); 
			UART0_send_char('\t');
			UART0_send_string("IR_Data.FrontRight: "); 
			UART0_send_string_ln(buffer);

		}
		else if (IR_Data.FrontLeft > IRTHRESHHOLD) {
			PWM_moveBackward(10, 1);
			PWM_rotateRight(45);
			//SysTick_delay(50);
			itoa(IR_Data.FrontLeft,buffer); 
			UART0_send_char('\t');
			UART0_send_string("IR_Data.FrontLeft: "); 
			UART0_send_string_ln(buffer);

		}
		else if (IR_Data.BackRight > IRTHRESHHOLD) {
			PWM_moveForward(10, 1);
			PWM_rotateLeft(45);
			//SysTick_delay(50);
			itoa(IR_Data.BackRight,buffer); 
			UART0_send_char('\t');
			UART0_send_string("IR_Data.BackRight: "); 
			UART0_send_string_ln(buffer);

		}
		else if (IR_Data.BackLeft > IRTHRESHHOLD) {
			PWM_moveForward(10, 1);
			PWM_rotateRight(45);
			//SysTick_delay(50);
			itoa(IR_Data.BackLeft,buffer); 
			UART0_send_char('\t');
			UART0_send_string("IR_Data.BackLeft: "); 
			UART0_send_string_ln(buffer);

		}
		return 1;
	} 
	return 0;
}




void brain_step()
{
	char buffer[20];
	int gir = 0;//GIRINICIAL;
	int cm_Front, cm_Left, cm_Right;
	switch (currentState)
	{
	case INIT:
		UART0_send_string_ln("INIT");
		cm_Front = cm_PTA5;
		cm_Left = cm_PTC8;
		cm_Right = cm_PTC9;
		nextState = SENSING;
		break;
		
	case SENSING:
		UART0_send_string_ln("SENSING");
		cm_Front = cm_PTA5;
		cm_Left = cm_PTC8;
		cm_Right = cm_PTC9;
		if (cm_Front<5 || cm_Left<PUSHTHRESHHOLD || cm_Right<PUSHTHRESHHOLD) // El de alante no va bien..
			nextState = PUSHING;
		else if (cm_Front<(RANGE/2) || cm_Left<RANGE || cm_Right<RANGE) // El de alante no va bien..
			nextState = APROACHING;
		else nextState = SCANNING;
		break;
			
	case PUSHING:
		UART0_send_string_ln("PUSHING");
		BLED_off();
		GLED_off();
		RLED_on();
		if (cm_Front<PUSHTHRESHHOLD)
		{
			PWM_moveForward(5, 1); // El de alante no va bien..
			SysTick_delay(100);
			sprintf(buffer,"HC davanter menor que PUSH: %d", cm_Front);
			UART0_send_string_ln(buffer);
		}
		else if (cm_Left<PUSHTHRESHHOLD)
		{
			PWM_rotateLeft(120);
			SysTick_delay(100);
			PWM_moveForward(RANGE/2, 1);
			sprintf(buffer,"HC esquerra menor que PUSH: %d", cm_Left);
			UART0_send_string_ln(buffer);
		}
		else if (cm_Right<PUSHTHRESHHOLD)
		{
			PWM_rotateRight(120);
			SysTick_delay(100);
			PWM_moveForward(RANGE/2, 1);
			sprintf(buffer,"HC dreta menor que PUSH: %d", cm_Right);
			UART0_send_string_ln(buffer);
		}
		nextState = SENSING;
		break;
			
	case APROACHING:
		UART0_send_string_ln("APROACHING");
		BLED_on();
		GLED_on();
		RLED_off();
		
		
		if (cm_Left<RANGE)
		{
			PWM_rotateLeft(120);
			SysTick_delay(100);
			PWM_moveForward(RANGE/5, 1);
			sprintf(buffer,"HC esquerra menor que RANGE: %d", cm_Left);
			UART0_send_string_ln(buffer);
		}
		else if (cm_Right<RANGE)
		{
			PWM_rotateRight(120);
			SysTick_delay(100);
			PWM_moveForward(RANGE/5, 1);
			sprintf(buffer,"HC dreta menor que RANGE: %d", cm_Right);
			UART0_send_string_ln(buffer);
		}
		else if (cm_Front<RANGE/2) // El de alante no va bien, lo pongo el ultimo y le reduzco distancia
		{
			PWM_moveForward(RANGE/5, 1);
			SysTick_delay(100);
			sprintf(buffer,"HC davanter menor que RANGE: %d", cm_Front);
			UART0_send_string_ln(buffer);
		}
		nextState = SENSING;
		break;
			
	case SCANNING:
		BLED_on();
		GLED_off();
		RLED_off();
		UART0_send_string_ln("SCANNING");
		
		gir = (gir + 1)%8;
		if(gir){  // 15/120 gir max
			PWM_rotateRight(15); //dreta
			SysTick_delay(100);
		}else{
			PWM_moveForward(15, 1);
			SysTick_delay(100);
		}
		
		nextState = SENSING;
		break;
	}

	SysTick_delay(100);
}

void brain_forward()
{
	currentState = nextState;
}
