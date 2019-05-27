/*
 * calibrate.c
 *
 *  Created on: May 27, 2019
 *      Author: Dani
 */

#include "calibrate.h"

void calibrateForward()
{
	char buffer[30];
	int ticks, tiempo;
	float vel;
	PWM_duty(-BACKWARD,-BACKWARD);
	SYST_CSR = 0; // Disable Systick
	SYST_CVR = 0xFFFFFF; // Current register
	// Systick 20.97 MHz
	SYST_RVR = 0xFFFFFF; // Load register
	//SYST_CSR = 3; // Enable Systick, Clock Source 20.97/16 = 1310625 Hz, Enable Interrupts
	SYST_CSR = 1; // Enable Systick, Clock Source 20.97/16 = 1310625 Hz, NO Interrupts
	//while(!(SYST_CSR & 0x10000)); /*wait until the Count flag is set */
	
	unsigned short res8 = 0, res11 = 0;
	while (res8 < IRTHRESHHOLD && res11 < IRTHRESHHOLD)
	{
		RLED_off();
		BLED_on();
		GLED_on();
		
		ADC0_read_i(8);
		while(reading){};
		res8 = res;
		itoa(res8,buffer); 
		UART0_send_char('\t');
		UART0_send_string("Sensor davant dreta (PTB0): "); //Davant dreta
		UART0_send_string_ln(buffer);
			
		ADC0_read_i(11);
		while(reading){};
		res11 = res;
		itoa(res11,buffer); 
		UART0_send_char('\t');
		UART0_send_string("Sensor Davant esquerra (PTB3): "); //Davant esquerra
		UART0_send_string_ln(buffer);
	}
	SYST_CSR = 0;
	ticks = SYST_CVR;
	ticks = SYST_RVR - ticks;
	sprintf(buffer,"ticks: %d", ticks);
	UART0_send_string_ln(buffer);
	tiempo = (ticks / 1310625);
	sprintf(buffer,"tiempo (ms): %d", (int)tiempo);
	UART0_send_string_ln(buffer);
	vel = (63.00 / tiempo)*0.81;
	sprintf(buffer,"vel: %d", (int)vel);
	UART0_send_string_ln(buffer);
	RLED_on();
	BLED_on();
	GLED_on();
	PWM_duty(STOP,STOP);
	SYST_CSR = 0; /*Stop the timer (Enable = 0) */
}


void calibrateBackward()
{
	char buffer[30];
	int ticks, tiempo;
	float vel;
	PWM_duty(BACKWARD,BACKWARD);
	SYST_CSR = 0; // Disable Systick
	SYST_CVR = 0xFFFFFF; // Current register
	// Systick 20.97 MHz
	SYST_RVR = 0xFFFFFF; // Load register
	//SYST_CSR = 3; // Enable Systick, Clock Source 20.97/16 = 1310625 Hz, Enable Interrupts
	SYST_CSR = 1; // Enable Systick, Clock Source 20.97/16 = 1310625 Hz, NO Interrupts
	//while(!(SYST_CSR & 0x10000)); /*wait until the Count flag is set */
	
	unsigned short res9 = 0, res12 = 0;
	while (res9 < IRTHRESHHOLDG && res12 < IRTHRESHHOLDG)
	{
		RLED_off();
		BLED_on();
		GLED_on();
			
		ADC0_read_i(9);
		while(reading);
		res9 = res;
		itoa(res9,buffer); 
		UART0_send_char('\t');
		UART0_send_string("Sensor Darrera dreta (PTB1): "); //Darrera dreta
		UART0_send_string_ln(buffer);
	
		ADC0_read_i(12);
		while(reading);
		res12 = res;
		delayMs(100);
		itoa(res12,buffer); 
		UART0_send_char('\t');
		UART0_send_string("Sensor Darrera esquerra (PTB2): "); //Darrera esquerra
		UART0_send_string_ln(buffer);
	}
	SYST_CSR = 0;
	ticks = SYST_CVR;
	ticks = SYST_RVR - ticks;
	sprintf(buffer,"ticks: %d", ticks);
	UART0_send_string_ln(buffer);
	tiempo = (ticks / 1310625);
	sprintf(buffer,"tiempo (ms): %d", (int)tiempo);
	UART0_send_string_ln(buffer);
	vel = (63.00 / tiempo);
	sprintf(buffer,"vel: %d", (int)vel);
	UART0_send_string_ln(buffer);
	RLED_on();
	BLED_on();
	GLED_on();
	PWM_duty(STOP,STOP);
	SYST_CSR = 0; /*Stop the timer (Enable = 0) */
}

void calibrateLeft()
{
	PWM_duty(ROTATION,-ROTATION);//esquerra
	SysTick_delay(10000);
	PWM_duty(STOP,STOP);
}

void calibrateRight()
{
	PWM_duty(-ROTATION,ROTATION);//dreta
	SysTick_delay(10000);
	PWM_duty(STOP,STOP);
}

int calibrate(void)
{
	char c;
	for(;;) {     

		UART0_send_string_ln("Select Calibration:");
		UART0_send_string_ln("'f': forward \t 'b': backward \t 'l': left rotation \t  'r': right rotation \t  'x': EXIT TESTS");
		UART0_send_string_ln("'w': forward 30 cm \t 's': backward 30 cm\t 'a': left 90 degrees \t  'd': right 90 degrees \t  'x': EXIT TESTS");
		
		while(!(UART0_S1 & UART0_S1_RDRF_MASK)) { } /* 0x20 wait for receive buffer full */
		c = UART0_D; /* read the char received */
		
		switch (c){
		case 'f':
			calibrateForward();
			break;
			
		case 'b':
			calibrateBackward();
			break;
			
		case 'l':
			calibrateLeft();
			break;
			
		case 'r':
			calibrateRight();
			break;
			
		case 'w':
			PWM_moveForward(30, 1);
			break;
			
		case 's':
			PWM_moveBackward(30, 1);
			break;
			
		case 'a':
			PWM_rotateLeft(90);
			break;
			
		case 'd':
			PWM_rotateRight(90);
			break;
			
		case 'x':
			return 0;
			break;
			
		default:
			UART0_send_ln();
			UART0_send_string("\t\033[37;1;5m");
			UART0_send_char(c);
			UART0_send_string_ln("\033[0m\033[31m IS NOT AN OPTION!\033[0m");
			UART0_send_ln();
			break;
		}
		c = UART0_D;
	}
	return 0;
}
