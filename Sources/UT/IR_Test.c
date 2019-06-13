/*
 * IR_Test.c
 *
 *  Created on: Apr 29, 2019
 *      Author: PCO
 */
#include "IR_Test.h"
#include "../common.h"

int IR_test(void)
{
	int wastedCycles = 0;
	char buffer[30];
	
	UART0_send_string_ln("Start IR test:");
	
	UART0_send_string_ln("Continus test 200");
	
	while(reading){wastedCycles++;};
	
	IR_Data.FrontRight = ADC0_read_p(8);
	IR_Data.BackRight = ADC0_read_p(9);
	IR_Data.FrontLeft = ADC0_read_p(11);
	IR_Data.BackLeft = ADC0_read_p(12);
	
	itoa(IR_Data.General,buffer); 
	UART0_send_char('\t');
	UART0_send_string("General 400 <= ");
	UART0_send_string_ln(buffer);
	
	itoa(IR_Data.FrontRight,buffer); 
	UART0_send_char('\t');
	UART0_send_string("Front Right: ");
	UART0_send_string_ln(buffer);
	
	itoa(IR_Data.BackRight,buffer); 
	UART0_send_char('\t');
	UART0_send_string("BackRight: ");
	UART0_send_string_ln(buffer);
		
	itoa(IR_Data.FrontLeft,buffer); 
	UART0_send_char('\t');
	UART0_send_string("FrontLeft: ");
	UART0_send_string_ln(buffer);
		
	itoa(IR_Data.BackLeft,buffer); 
	UART0_send_char('\t');
	UART0_send_string("BackLeft: ");
	UART0_send_string_ln(buffer);

	itoa(wastedCycles,buffer);
	UART0_send_string("WastedCycles: ");
	UART0_send_string_ln(buffer);
	UART0_send_ln();
	
	
	
	return 0;
}
