/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */

#include "common.h"

void Test()
{	  
	char c;
	for(;;) {     

		UART0_send_string_ln("Select Test:");
		UART0_send_string_ln("'i': IR \t 'm': MOTORS \t 'u': ULTRASOUND\t 'p': PLAY\t 'c': CALIBRATE\t 'x': EXIT");
		
		
		while(!(UART0_S1 & UART0_S1_RDRF_MASK)) { } /* 0x20 wait for receive buffer full */
		c = UART0_D; /* read the char received */
		
		switch (c){
		case 'b':
			delayMs(CINCSEC);
			brain();
			break;
		case 'c':
			calibrate();
			break;
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
			//PWM_duty(20000,20000);
			HC_test();
			//PWM_duty(0,0);
			break;
			
		case 'x':
			return;
			break;
			
		case 'w':
			//UART0_send_string_ln("Pulsar de nuevo para tocar al perrito.");
			//WD5S();
			 PWM_rotateLeft(120);
			break;
			
		case 'p':
			RLED_off();
			BLED_on();
			GLED_off();
			SysTick_delay(1000);
			RLED_on();
			BLED_off();
			GLED_off();
			SysTick_delay(1000);
			RLED_on();
			BLED_on();
			GLED_off();
			SysTick_delay(1000);
			RLED_on();
			BLED_on();
			GLED_on();
			SysTick_delay(1000);
			RLED_on();
			BLED_off();
			GLED_off();
			SysTick_delay(1000);
			BLED_on();
			GLED_off();
			RLED_off();
			brain();
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

int main(void)
{
	ADC0_init_i();
	RLED_init();
	GLED_init();
	BLED_init();
	UART0_init();
	PWM_init();
	HC_init();
	
	
	//WD5S(); // Wathdog configurable a 5 s (ejemplo de uso)
	alertstatus = 0;
	RLED_off();
	BLED_off();
	GLED_on();
	//WD5S_touch();
	//PWM_duty(ROTATION, -ROTATION); // Izq
	/*BLED_toggle();
	SysTick_delay(5000);
	BLED_toggle();*/
	//ADC0_compare_i(13, IRTHRESHHOLDG, GT);
	Test();
	//WD5S();
	//delayMs(CINCSEC);
	
	//PWM_duty(20000,20000);
	
	//brain();
	
	//BLED_on();

	//ajustar 5s

	
	//ajustarangledreta();
	//ajustarangleesquerra();	
	//ajustarcercledreta(40);
	
	
	for(;;) {     
		//combat();
	}
	return 0;
}


