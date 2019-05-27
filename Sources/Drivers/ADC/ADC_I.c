/*
 * ADC.c
 *
 *  Created on: Apr 7, 2019
 *      Author: PCO
 */

#include "ADC_I.h"

char buffer[20];

void ADC0_IRQHandler1(void) {
	if (compare) {
		alertstatus = 2;
		alert = 2;
		BLED_on();
		RLED_on();
		GLED_on();
		//lineaBlanca = 1;
		compare = 0;
		ADC0_compare_i(13, IRTHRESHHOLDG, GT);
		BLED_off();
		RLED_off();
		GLED_off();
	}
	else {
		res = ADC0_RA;
	}
	reading = 0;
}


void ADC0_IRQHandler(void) {
	if (compare) {
		char buffer[30];
		alertstatus = 2;
		alert = 2;
		BLED_on();
		RLED_on();
		GLED_on();
		IR_Data.General = ADC0_RA;
		IR_Data.FrontRight = 0;
		IR_Data.BackRight = 0;
		IR_Data.FrontLeft = 0;
		IR_Data.BackLeft = 0;
		ADC0_SC2 &= ~ADC_SC2_ACFE_MASK; // Disable Compare
		ADC0_SC3 &= ~ADC_SC3_ADCO_MASK;
		ADC0_SC1A&= ~ADC_SC1_AIEN_MASK;
		//IR_Data.FrontRight = ADC0_read_p(8);
		//IR_Data.BackRight = ADC0_read_p(9);
		//IR_Data.FrontLeft = ADC0_read_p(11);
		//IR_Data.BackLeft = ADC0_read_p(12);
		//PWM_duty(10000, 10000);
		int found = 0, i = 0;
		while (++i<20 && !found)
		{
			IR_Data.FrontRight = ADC0_read_p(8);
			IR_Data.BackRight = ADC0_read_p(9);
			IR_Data.FrontLeft = ADC0_read_p(11);
			IR_Data.BackLeft = ADC0_read_p(12);
			if (IR_Data.FrontRight > IRTHRESHHOLD) {
				PWM_moveBackward(10, 0);
				PWM_rotateLeft(45);
				//SysTick_delay(50);
				itoa(IR_Data.FrontRight,buffer); 
				UART0_send_char('\t');
				UART0_send_string("IR_Data.FrontRight: "); 
				UART0_send_string_ln(buffer);
				found = 1;
			}
			else if (IR_Data.FrontLeft > IRTHRESHHOLD) {
				PWM_moveBackward(10, 0);
				PWM_rotateRight(45);
				//SysTick_delay(50);
				itoa(IR_Data.FrontLeft,buffer); 
				UART0_send_char('\t');
				UART0_send_string("IR_Data.FrontLeft: "); 
				UART0_send_string_ln(buffer);
				found = 1;
			}
			else if (IR_Data.BackRight > IRTHRESHHOLD) {
				PWM_moveForward(10, 0);
				PWM_rotateLeft(45);
				//SysTick_delay(50);
				itoa(IR_Data.BackRight,buffer); 
				UART0_send_char('\t');
				UART0_send_string("IR_Data.BackRight: "); 
				UART0_send_string_ln(buffer);
				found = 1;
			}
			else if (IR_Data.BackLeft > IRTHRESHHOLD) {
				PWM_moveForward(10, 0);
				PWM_rotateRight(45);
				//SysTick_delay(50);
				itoa(IR_Data.BackLeft,buffer); 
				UART0_send_char('\t');
				UART0_send_string("IR_Data.BackLeft: "); 
				UART0_send_string_ln(buffer);
				found = 1;
			}
		}

		//SysTick_delay(100);
		
		//WD5S();
		alertstatus = 0;
		compare = 0;
		ADC0_compare_i(13, IRTHRESHHOLDG, GT);
		BLED_off();
		RLED_off();
		GLED_off();
	}
	else {
		res = ADC0_RA;
	}
	reading = 0;
}


void ADC0_IRQHandler4(void) {
	if (compare) {
		//PWM_duty(10000, 10000);
		alertstatus = 2;
		alert = 2;
		BLED_on();
		RLED_on();
		GLED_on();
		IR_Data.General = ADC0_RA;
		IR_Data.FrontRight = 0;
		IR_Data.BackRight = 0;
		IR_Data.FrontLeft = 0;
		IR_Data.BackLeft = 0;
		ADC0_SC2 &= ~ADC_SC2_ACFE_MASK; // Disable Compare
		ADC0_SC3 &= ~ADC_SC3_ADCO_MASK;
		ADC0_SC1A&= ~ADC_SC1_AIEN_MASK;
		//IR_Data.FrontRight = ADC0_read_p(8);
		//IR_Data.BackRight = ADC0_read_p(9);
		//IR_Data.FrontLeft = ADC0_read_p(11);
		//IR_Data.BackLeft = ADC0_read_p(12);
		int found = 0, i = 0, j=0;
		while (++i<20 && !found)
		{
			if (ADC0_read_p(8) > IRTHRESHHOLD) { // FrontRight
				//sprintf(buffer,"Valor FrontLeft: %d", IR_Data.FrontLeft);
				//UART0_send_string_ln(buffer);
				PWM_duty(-ROTATION, ROTATION); // rotar a la derecha
				j=0;
				while (++j<80 || IR_Data.FrontLeft < IRTHRESHHOLD) {
					IR_Data.FrontLeft = ADC0_read_p(11);
					//sprintf(buffer,"Valor FrontLeft: %d", IR_Data.FrontLeft);
					//UART0_send_string_ln(buffer);
				};
				//delayMsinter(MOVIMENT);
				PWM_duty(BACKWARD, BACKWARD);
				delayMsinter(MOVIMENT);
				PWM_duty(100, 100);
				found=1;
				//orientacio = 210;
				//nextstate = 's';
			}
			else if (ADC0_read_p(11) > IRTHRESHHOLD) { // FrontLeft
				PWM_duty(ROTATION,-ROTATION); // rotar izquierda
				j=0;
				while (++j<80 || IR_Data.FrontRight < IRTHRESHHOLD) {
					IR_Data.FrontRight = ADC0_read_p(9);
					//sprintf(buffer,"Valor FrontRight: %d", IR_Data.FrontRight);
					//UART0_send_string_ln(buffer);
				};
				//delayMsinter(MOVIMENT);
				PWM_duty(BACKWARD, BACKWARD); // Hacia atras
				delayMsinter(MOVIMENT);
				PWM_duty(100, 100);
				found=1;
				//orientacio = 210; 
			}
			else if (ADC0_read_p(9) > IRTHRESHHOLD) { // BackRight
				PWM_duty(ROTATION, -ROTATION); // rotar izquierda
				while (IR_Data.BackLeft < IRTHRESHHOLD) {
					IR_Data.BackLeft = ADC0_read_p(12);
					//sprintf(buffer,"Valor BackLeft: %d", IR_Data.BackLeft);
					//UART0_send_string_ln(buffer);
				};
				//delayMsinter(MOVIMENT);
				PWM_duty(-BACKWARD, -BACKWARD); // Hacia adelante
				delayMsinter(MOVIMENT);
				PWM_duty(100, 100);
				found=1;
				//orientacio = 90;
			}
			else if (ADC0_read_p(12) > IRTHRESHHOLD) { // BackLeft
				PWM_duty(-ROTATION, ROTATION); // rotar a la derecha
				while (IR_Data.BackRight < IRTHRESHHOLD) {
					IR_Data.BackRight = ADC0_read_p(9);
					//sprintf(buffer,"Valor BackRight: %d", IR_Data.BackRight);
					//UART0_send_string_ln(buffer);
				};
				//delayMsinter(MOVIMENT);
				PWM_duty(-BACKWARD, -BACKWARD); // Hacia adelante
				delayMsinter(MOVIMENT);
				PWM_duty(100, 100);
				found=1;
				//orientacio = 90;
			}
		}
		
		
		
		WD5S();
		alertstatus = 0;
		compare = 0;
		ADC0_compare_i(13, IRTHRESHHOLDG, GT);
		BLED_off();
		RLED_off();
		GLED_off();
	}
	else {
		res = ADC0_RA;
	}
	reading = 0;
}



void ADC0_init_i(void){
	
	// Enable clocks
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;	// ADC 0 clock
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;	// PTB clock
	//SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;	// PTB0 clock
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;	// PTC clock
	
	//Set Inputs (not necessary)
	PORTB_PCR0 = 0; // PTB0 analog input */
	PORTB_PCR1 = 0; // PTB1 analog input */
	PORTB_PCR2 = 0; // PTB2 analog input */
	PORTB_PCR3 = 0; // PTB3 analog input */
	//PORTE_PCR20 = 0; // PTB3 analog input */
	PORTC_PCR2 = 0; // PTB3 analog input */

	// Configure ADC
	ADC0_CFG1 = 0; // Reset register
	ADC0_CFG1 |= (ADC_CFG1_MODE(3)  |  	// 10 bits mode
				  ADC_CFG1_ADICLK(0)|	// Input Bus Clock (20-25 MHz out of reset (FEI mode))
				  ADC_CFG1_ADIV(1)) ;	// Clock divide by 1 (10-12.5 MHz)
		
		
	ADC0_SC2 &= ~0x40;  /* software trigger */
	
	//ADC0_SC2 |= ADC_SC2_DMAEN_MASK;    // DMA Enable
	
	NVIC_BASE_PTR -> ICPR |= 1 << (INT_ADC0 - 16); //Borrar peticiones de interrupción anteriores:
	NVIC_BASE_PTR -> ISER |= 1 << (INT_ADC0 - 16); //Habilitar la interrupción (activación global, en el NVIC):
}

unsigned short ADC0_read_i(unsigned char ch)
{
	ADC0_SC2 &= ~ADC_SC2_ACFE_MASK; // Disable Compare
	ADC0_SC3 &= ~ADC_SC3_ADCO_MASK;
	ADC0_SC1A = (ch & ADC_SC1_ADCH_MASK) | 
				ADC_SC1_AIEN_MASK ;     //
	
	//ADC0_SC3 = 0; //Reset continus

	
	
	//while(ADC0_SC2 & ADC_SC2_ADACT_MASK); 	 // Conversion in progress
	//while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // Run until the conversion is complete
	reading = 1;
	compare = 0;
	return 0;//ADC0_RA;
}

void ADC0_compare_i(unsigned char ch, uint16_t cv1, unsigned short type){
	
	ADC0_SC2 |= ADC_SC2_ACFE_MASK;  // Enable compare mode
	//ADC0_SC2 &= ~ADC_SC2_ADTRG_MASK;
	ADC0_SC3 |= ADC_SC3_ADCO_MASK;
	
	
	switch(type){
		case LT:
			ADC0_CV1 = ADC_CV1_CV(cv1);
			break;
		
		case GT: 
			ADC0_SC2 |= ADC_SC2_ACFGT_MASK; // Greater than or equal
			ADC0_CV1 = ADC_CV1_CV(cv1);
			break;
		
		default:
			break;
		
	}
	
	ADC0_SC1A = (ch & ADC_SC1_ADCH_MASK) | ADC_SC1_AIEN_MASK ;
	compare = 1;
	reading = 1;
	
}
