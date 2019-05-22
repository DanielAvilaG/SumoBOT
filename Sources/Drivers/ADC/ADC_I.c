/*
 * ADC.c
 *
 *  Created on: Apr 7, 2019
 *      Author: PCO
 */

#include "ADC_I.h"



void ADC0_IRQHandler(void){
	if(compare){
		IR_Data.General = ADC0_RA;
		IR_Data.FrontRight = ADC0_read_p(8);
		IR_Data.BackRight = ADC0_read_p(9);
		IR_Data.FrontLeft = ADC0_read_p(11);
		IR_Data.BackLeft = ADC0_read_p(12);
		compare = 0;
	}else{
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
	ADC0_CFG1 |= (ADC_CFG1_MODE(2)  |  	// 10 bits mode
				  ADC_CFG1_ADICLK(0)|	// Input Bus Clock (20-25 MHz out of reset (FEI mode))
				  ADC_CFG1_ADIV(1)) ;	// Clock divide by 1 (10-12.5 MHz)
		
		
	ADC0_SC2 &= ~0x40;  /* software trigger */
	
	//ADC0_SC2 |= ADC_SC2_DMAEN_MASK;    // DMA Enable
	
	NVIC_BASE_PTR -> ICPR |= 1 << (INT_ADC0 - 16); //Borrar peticiones de interrupción anteriores:
	NVIC_BASE_PTR -> ISER |= 1 << (INT_ADC0 - 16); //Habilitar la interrupción (activación global, en el NVIC):
}

unsigned short ADC0_read_i(unsigned char ch)
{
	ADC0_SC1A = (ch & ADC_SC1_ADCH_MASK) | 
				ADC_SC1_AIEN_MASK ;     // 

	
	
	//while(ADC0_SC2 & ADC_SC2_ADACT_MASK); 	 // Conversion in progress
	//while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // Run until the conversion is complete
	reading = 1;
	compare = 0;
	return 0;//ADC0_RA;
}

void ADC0_compare_i(unsigned char ch, uint16_t cv1, unsigned short type){
	ADC0_SC1A = (ch & ADC_SC1_ADCH_MASK) | ADC_SC1_AIEN_MASK ;
	ADC0_SC2 |= ADC_SC2_ACFE_MASK;  // Enable compare mode
	
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
	
	
	compare = 1;
	reading = 1;
	
}
