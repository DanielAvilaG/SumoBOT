#include "MKL25Z4.h"
#include "HC.h"


volatile int then_PTA5 = 0, then_PTC8 = 0, then_PTC9 = 0;
volatile int now_PTA5 = 0, now_PTC8= 0, now_PTC9 = 0;
volatile int cm_PTA5 = 0 , cm_PTC8 = 0 , cm_PTC9 = 0 ;

void HC_init()
{
	// PTA4 salida a trigger conectado con TPM0_CH1
	TPM0_C1SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; // SELECT CHANNEL MODE
	TPM0_C1V = 11;  // * especificar duty cycle 11 us
	PORTA_PCR4 = PORT_PCR_MUX(3);  // * especificar multiplexacio del TPM0_CH1 Alternativa 3
	
	// Configuracion de la recepcion de echo
	// PTA5 TPM0 CHANNEL 2
	TPM0_C2SC =  TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK; // Capture on both edges
	TPM0_C2SC &= ~(TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK);// Capture on both edges
	PORTA_PCR5 = PORT_PCR_MUX(3);  // * especificar multiplexacio del TPM0_CH2 Alternativa 3
	TPM0_C2SC |= TPM_CnSC_CHIE_MASK; // Enable int on channel
	
	// PTC8 TPM0 CHANNEL 4
	TPM0_C4SC =  TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK; // Capture on both edges
	TPM0_C4SC &= ~(TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK);// Capture on both edges
	PORTC_PCR8 = PORT_PCR_MUX(3);  // * especificar multiplexacio del TPM0_CH4 Alternativa 3
	TPM0_C4SC |= TPM_CnSC_CHIE_MASK; // Enable int on channel
	
	// PTC9 TPM0 CHANNEL 5
	TPM0_C5SC =  TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK; // Capture on both edges
	TPM0_C5SC &= ~(TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK);// Capture on both edges
	PORTC_PCR9 = PORT_PCR_MUX(3);  // * especificar multiplexacio del TPM0_CH5 Alternativa 3
	TPM0_C5SC |= TPM_CnSC_CHIE_MASK; // Enable int on channel

	NVIC_BASE_PTR -> ICPR |= 1 << (INT_TPM0 - 16); //Borrar peticiones de interrupción anteriores:
	NVIC_BASE_PTR -> ISER |= 1 << (INT_TPM0 - 16); //Habilitar la interrupción (activación global, en el NVIC)
	TPM0_BASE_PTR->SC |= 0x08;
}


void FTM0_IRQHandler(void) {
	if (TPM0_STATUS & (1<<2))
	{ // INT PTA5 TPM0 CHANNEL 2
		then_PTA5 = now_PTA5;
		now_PTA5 = TPM0_C2V;
		cm_PTA5 = (now_PTA5 - then_PTA5) / 58;
		TPM0_C2SC |= 0x80; // clear CHF
	}
	else if (TPM0_STATUS & (1<<4))
	{ // INT PTC8 TPM0 CHANNEL 4
		then_PTC8 = now_PTC8;
		now_PTC8 = TPM0_C4V;
		cm_PTC8 = (now_PTC8 - then_PTC8) / 58;
		TPM0_C4SC |= 0x80; // clear CHF
	}
	else if (TPM0_STATUS & (1<<5))
	{ // INT PTC9 TPM0 CHANNEL 5
		then_PTC9 = now_PTC9;
		now_PTC9 = TPM0_C5V;
		cm_PTC9 = (now_PTC9 - then_PTC9) / 58;
		TPM0_C5SC |= 0x80; // clear CHF
	}
}

int HC1_getCM()
{
	int then = 0, now = 0, diff;
	int i;
	for (i = 0; i<2; i++)
	{
		while(!(TPM0_C2SC & 0x80)) { } // wait until the CHF is set 
		TPM0_C2SC |= 0x80; // clear CHF 
		then = TPM0_C2V;
		while(!(TPM0_C2SC & 0x80)) { } // wait until the CHF is set 
		TPM0_C2SC |= 0x80; // clear CHF
		now = TPM0_C2V;
		//diff = ((now - then) + diff) / 2; // you may put a breakpoint here and examine the values
		diff = now - then; // you may put a breakpoint here and examine the values
		TPM0_C2V = 0;
	}
	return (diff /58);
}

int HC2_getCM()
{
	int then = 0, now = 0, diff;
	int i;
	for (i = 0; i<2; i++)
	{
		while(!(TPM0_C4SC & 0x80)) { } // wait until the CHF is set 
		TPM0_C4SC |= 0x80; // clear CHF 
		then = TPM0_C4V;
		while(!(TPM0_C4SC & 0x80)) { } // wait until the CHF is set 
		TPM0_C4SC |= 0x80; // clear CHF
		now = TPM0_C4V;
		diff = ((now - then) + diff) / 2; // you may put a breakpoint here and examine the values
		TPM0_C4V = 0;
	}
	return (diff /58);
}

int HC3_getCM()
{
	int then = 0, now = 0, diff;
	int i;
	for (i = 0; i<2; i++)
	{
		while(!(TPM0_C5SC & 0x80)) { } // wait until the CHF is set 
		TPM0_C5SC |= 0x80; // clear CHF 
		then = TPM0_C5V;
		while(!(TPM0_C5SC & 0x80)) { } // wait until the CHF is set 
		TPM0_C5SC |= 0x80; // clear CHF
		now = TPM0_C5V;
		//diff = ((now - then) + diff) / 2; // you may put a breakpoint here and examine the values
		diff = now - then; // you may put a breakpoint here and examine the values
		TPM0_C5V = 0;
	}
	return (diff /58);
}
