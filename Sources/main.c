/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */

#include "Drivers/UART/UART.h"
#include "Drivers/ADC/ADC_I.h"
//#include "Drivers/LED/LED_46.h"
#include "Drivers/LED/LED_25.h"
#include "Drivers/PWM/PWM.h"

#include "UT/IR_Test.h"
#include "UT/HC_Test.h"
#include "UT/PWM_Test.h"

#include "common.h"


int main(void)
{

	ADC0_init_i();
	RLED_init();
	GLED_init();
	BLED_init();
	UART0_init();
	PWM_init();
	HC_init();
	

	
	Test();
	
	for(;;) {     


	}
	return 0;
}

void Test()
{	  
	char c;
	for(;;) {     

		UART0_send_string_ln("Select Test:");
		UART0_send_string_ln("'i': IR \t 'm': MOTORS \t 'u': ULTRASOUND\t 'x': EXIT TESTS");
		
		
		while(!(UART0_S1 & UART0_S1_RDRF_MASK)) { } /* 0x20 wait for receive buffer full */
		c = UART0_D; /* read the char received */
		
		switch (c){
		case 'i':
			RLED_toggle();
			if(IR_test())GLED_toggle();
			delayMs(50);
			GLED_off();
			RLED_toggle();
			break;
			
		case 'm':
			RLED_toggle();
			PWM_test();
			RLED_toggle();
			
			break;
			
		case 'u':
			HC_test();
			break;
			
		case 'x':
			return;
			break;
		
		default:
			UART0_send_ln();
			UART0_send_string("\t\033[37;1;5m");
			UART0_send_char(c);
			UART0_send_string_ln("\033[0m\033[31m IS NOT AN OPTION!\033[0m");
			UART0_send_ln();
			break;
		}
	}
}
