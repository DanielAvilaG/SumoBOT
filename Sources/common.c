/*
 * common.c
 *
 *  Created on: Apr 29, 2019
 *      Author: PCO
 */

#include "common.h"

void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}
/**
 * Función wathdog, cada vez que se llama pone un temporizador durante los segundos
 * pasados por parámetro; si la cuenta llega 0 sin que se haya vuelto a llamar se ejecuta la 
 * ISR SysTick_Handler(void)
 */
void WD_touch(int seconds)
{
	SYST_CSR = 0; // Disable Systick
	SYST_CVR = (1310624*seconds)-1;
	// Systick 20.97 MHz
	SYST_RVR = (1310624*seconds)-1; 
	SYST_CSR = 3; // Enable Systick, Clock Source 20.97/16 = 1310625 Hz, Enable Interrupts
}

void SysTick_Handler(void) {
	RLED_toggle();
}

volatile int wd = WD(WD_5S); // 5000/60 = 83.3 --> 83*60=4980 ms
void TPM0_IRQHandler(void) {
	if (!wd) {
		BLED_toggle();
		wd = WD(WD_5S);
	}
	--wd;
	TPM0_SC |= TPM_SC_TOF_MASK;
}

/**
 * Función wathdog, fija a 4,98 segundos; si la cuenta llega 0 sin que se haya vuelto a llamar se ejecuta la 
 * ISR TPM0_IRQHandler(void)
 */
void WD5S_touch()
{
	wd = WD(WD_5S);
}
