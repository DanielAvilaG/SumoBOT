/*
 * common.c
 *
 *  Created on: Apr 29, 2019
 *      Author: PCO
 */

#include "common.h"


void delayMsinter(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < MSINTER; j++) {}
}

void delayMs(int n) {
	int i;
	//int j;
	for(i = 0 ; i < n*MS; i++){
		if(alertstatus>0){
			return;
		}
	}
		
		//for (j = 0; j < 7000; j++) {}
}

void delayMS(int n) {
	int i;
	//int j;
	for(i = 0 ; i < n*MS; i++){
		if(alertstatus>0){
			return;
		}
	}
		
		//for (j = 0; j < 7000; j++) {}
}


void SysTick_delay(int ms)
{
	SYST_CSR = 0; // Disable Systick
	SYST_CVR = (1310*ms)-1;
	// Systick 20.97 MHz
	SYST_RVR = (1310*ms)-1; 
	//SYST_CSR = 3; // Enable Systick, Clock Source 20.97/16 = 1310625 Hz, Enable Interrupts
	SYST_CSR = 1; // Enable Systick, Clock Source 20.97/16 = 1310625 Hz, NO Interrupts
	char buffer[30];
	while(!(SYST_CSR & 0x10000)){
		if (ADC0_read_p(13)> IRTHRESHHOLDG){
				IR_Data.FrontRight = ADC0_read_p(8);
				IR_Data.BackRight = ADC0_read_p(9);
				IR_Data.FrontLeft = ADC0_read_p(11);
				IR_Data.BackLeft = ADC0_read_p(12);
				if (IR_Data.FrontRight > IRTHRESHHOLD) {
					PWM_moveBackward(10, 0);
					//PWM_rotateLeft(45);
					//SysTick_delay(50);
					itoa(IR_Data.FrontRight,buffer); 
					UART0_send_char('\t');
					UART0_send_string("IR_Data.FrontRight: "); 
					UART0_send_string_ln(buffer);

				}
				else if (IR_Data.FrontLeft > IRTHRESHHOLD) {
					PWM_moveBackward(10, 0);
					//PWM_rotateRight(45);
					//SysTick_delay(50);
					itoa(IR_Data.FrontLeft,buffer); 
					UART0_send_char('\t');
					UART0_send_string("IR_Data.FrontLeft: "); 
					UART0_send_string_ln(buffer);

				}
				else if (IR_Data.BackRight > IRTHRESHHOLD) {
					PWM_moveForward(10, 0);
					//PWM_rotateLeft(45);
					//SysTick_delay(50);
					itoa(IR_Data.BackRight,buffer); 
					UART0_send_char('\t');
					UART0_send_string("IR_Data.BackRight: "); 
					UART0_send_string_ln(buffer);

				}
				else if (IR_Data.BackLeft > IRTHRESHHOLD) {
					PWM_moveForward(10, 0);
					//PWM_rotateRight(45);
					//SysTick_delay(50);
					itoa(IR_Data.BackLeft,buffer); 
					UART0_send_char('\t');
					UART0_send_string("IR_Data.BackLeft: "); 
					UART0_send_string_ln(buffer);

				}
			}
	}/*wait until the Count flag is set */

	SYST_CSR = 0; /*Stop the timer (Enable = 0) */
}

/*
void SysTick_Handler(void) {
	//BLED_toggle();
	
	BLED_off();
	GLED_on();
	RLED_off();
	if (alertstatus<2){
		alertstatus = 1;
		alert = 1;
		PWM_duty(-20000,20000);//dreta
		delayMsinter(DELAY90DRETA);
		PWM_duty(20000,-20000);//esquerra
		delayMsinter(DELAY90ESQUERRA);
		PWM_duty(100,100);
		alertstatus = 0;
		alert = 0;
		WD_touch(5);
	}
	//RLED_toggle();
	//BLED_toggle();
	 
}*/


volatile int wd = WD(WD_5S); // 5000/60 = 83.3 --> 83*60=4980 ms
void WD5S(void) {
	
	if (!wd) {
		//RLED_toggle();
		
		wd = WD(WD_5S);
		/*
		if (alertstatus!=2){
			alertstatus = 1;
			PWM_duty(-20000,20000);//dreta
			delayMs(105);
			PWM_duty(20000,-20000);//esquerra
			delayMs(90);
			PWM_duty(0,0);
			wd = WD(WD_5S);
			alertstatus = 0;
		}
		*/
	}
	
	--wd;
	TPM0_SC |= TPM_SC_TOF_MASK;
	
}


/**
 * Función wathdog, fija a 4,98 segundos; si la cuenta llega 0 sin que se haya vuelto a llamar se ejecuta la 
 * ISR FTM0_IRQHandler(void) deifina en HC.c
 */
void WD5S_touch()
{
	wd = WD(WD_5S);
}


/*
 alertstatus = 2;
 if ( IR == davant_dreta){
 
 	 PWM_duty(20000,-20000);
 	 while(IR !=davant_esquerra){
 	 } 
 	 PWM_duty(20000,20000);
 	 delayMs(50);
 	 PWM_duty(0,0);
 }else{
 	 if ( IR == davant_esquerra){
 	 	 PWM_duty(-20000,20000);
 	 	 while(IR !=davant_dreta){
 	 	 }
 	 	 PWM_duty(20000,20000);
		 delayMs(50);
		 PWM_duty(0,0); 
 	 }else{
 	 	 if ( IR == darrera_dreta){
 	 	 	 PWM_duty(-20000,20000);
			 while(IR !=darrera_esquerra){
			 }
			 PWM_duty(-20000,-20000);
			 delayMs(50);
			 PWM_duty(0,0); 
 	 	 }else{
 	 	 	 if ( IR == darrera_esquerra){
				 PWM_duty(20000,-20000);
				 while(IR !=darrera_dreta){
				 }
				 PWM_duty(-20000,-20000);
				 delayMs(50);
				 PWM_duty(0,0);
			}
 	 	 }
 	 }
 }
 WD5S_touch();
 alertstatus = 0;
 */
