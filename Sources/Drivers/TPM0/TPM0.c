/*
 * TPM0.c
 *
 *  Created on: May 20, 2019
 *      Author: Dani
 */
#include "MKL25Z4.h"
#include "TPM0.h"

void TPM0_init()
{
	// Configurar reloj interno desde 2 MHz a 25 Hz -> 60 ms con un duty de 11 us para el trigger
	MCG_BASE_PTR->C1 = MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK; //  INTERNAL CLOCK|MCGIRCLK ACTIVE(SET)
	MCG_BASE_PTR->C2 = MCG_C2_IRCS_MASK;   // SELECT FAST INTERNAL REFERENCE CLOCK (1)
	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM0_MASK;  // ENABLE TPM0 CLOCK GATE
	SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(3);  // MCGIRCLK IS SELECTED FOR TPM CLOCK
	TPM0_BASE_PTR->SC = 0;
	TPM0_BASE_PTR->SC |= TPM_SC_PS(1);  // * especificar frequencia
	TPM0_BASE_PTR->SC |= TPM_SC_CMOD(1);  // COUNTER INC. ON EVERY CLOCK
	TPM0_BASE_PTR->MOD = 60000;  // * especificar periodo 60 ms
	
	// Clock to PortA and PortC
	SIM_BASE_PTR->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTC_MASK;
}


/** TODO
 * Nil necesita una función que se ejecute cada 5 segundos, que vaya con otra que cuando se llame actue como watchdog reiniciando los 5 segundos
 * Y otra función que al llamarla se le pase como argumento un tiempo y 
 * sin bloquear te interrumpa cuando transcurra ese tiempo. Si se llama otra vez antes de la interrupción programada debería reestablecer el contandor anulando la primera llamada.
 */

void setDelay(int ms)
{
	
}
