/*
 * LED_25.c
 *
 *  Created on: Apr 28, 2019
 *      Author: Dani
 */

#include "LED_25.h"

void RLED_init(void)
{
	SIM_SCGC5  |= SIM_SCGC5_PORTB_MASK;               	// enable clock to Port B
	PORTB_PCR18 = PORT_PCR_MUX(1);						// make PTB18 pin as GPIO
	GPIOB_PDDR |= (1 << 18);             				// make PTB18 as output pin 
}

void GLED_init(void)
{
		PORTB_PCR19 = PORT_PCR_MUX(1);						// make PTB18 pin as GPIO
		GPIOB_PDDR |= (1 << 19);             				// make PTB18 as output pin 
}

void BLED_init(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;	// enable clock to Port D
	PORTD_PCR1  = PORT_PCR_MUX(1); // PIN 1 DE PORT D (LED) UTILIZAN GPIO KL25Z
	GPIO_PDDR_REG(PTD_BASE_PTR) =  0x00000002; // Declarar puerto de salida pin 1 puerto D (KL25Z) BLUE
	BLED_off();
}

void RLED_toggle(void)
{
	GPIOB_PTOR |= (1 << 18);
}

void RLED_off(void)
{
	GPIOB_PDOR |= (1 << 18);
}

void RLED_on(void)
{
	GPIOB_PCOR |= (1 << 18);
}


void GLED_toggle(void)
{
	GPIOB_PTOR |= (1 << 19);
}

void GLED_off(void)
{
	GPIOB_PDOR |= (1 << 19);
}

void GLED_on(void)
{
	GPIOB_PCOR |= (1 << 19);
}


void BLED_toggle(void)
{
	GPIOD_PTOR |= (1 << 1);
}

void BLED_off(void)
{
	GPIOD_PDOR |= (1 << 1);
}

void BLED_on(void)
{
	GPIOD_PCOR |= (1 << 1);
}
