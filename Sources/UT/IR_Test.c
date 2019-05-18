/*
 * IR_Test.c
 *
 *  Created on: Apr 29, 2019
 *      Author: PCO
 */
#include "IR_Test.h"

int IR_test(void)
{
	short int result[5]={0};
	int wastedCycles = 0;
	char buffer[10];
	
	UART0_send_string_ln("Start IR test:");
	
	ADC0_read_i(8);
	while(reading){wastedCycles++;};
	result[0] = res;
	itoa(result[0],buffer); 
	UART0_send_char('\t');
	UART0_send_string("Sensor 0 (PTB0): ");
	UART0_send_string_ln(buffer);
	ADC0_read_i(9);
	while(reading){wastedCycles++;};
	result[1] = res;
	itoa(result[1],buffer); 
	UART0_send_char('\t');
	UART0_send_string("Sensor 1 (PTB1): ");
	UART0_send_string_ln(buffer);
	ADC0_read_i(12);
	while(reading){wastedCycles++;};
	result[2] = res;
	itoa(result[2],buffer); 
	UART0_send_char('\t');
	UART0_send_string("Sensor 2 (PTB2): ");
	UART0_send_string_ln(buffer);
	ADC0_read_i(13);
	while(reading){wastedCycles++;};
	result[3] = res;
	itoa(result[3],buffer); 
	UART0_send_char('\t');
	UART0_send_string("Sensor 3 (PTB3): ");
	UART0_send_string_ln(buffer);
	ADC0_read_i(0);
	while(reading){wastedCycles++;};
	result[4] = res;    
	itoa(result[4],buffer); 
	UART0_send_char('\t');
	UART0_send_string("General (PTE20): ");
	UART0_send_string_ln(buffer);
	
	itoa(wastedCycles,buffer);
	UART0_send_string("WastedCycles: ");
	UART0_send_string_ln(buffer);
	UART0_send_ln();
	
	if (result[4] > 150) return 1;
	
	
	
	return 0;
}
