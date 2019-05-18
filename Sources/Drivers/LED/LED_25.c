/*
 * LED_25.c
 *
 *  Created on: Apr 28, 2019
 *      Author: Dani
 */

#include "LED_25.h"

void RLED_init(void)
{

}

void GLED_init(void)
{

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

}

void GLED_toggle(void)
{

}

void GLED_off(void)
{

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
