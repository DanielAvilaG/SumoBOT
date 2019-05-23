/*
 * common.h
 *
 *  Created on: Apr 29, 2019
 *      Author: PCO
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "MKL25Z4.h"

#define HC_TPM0_MOD 60	// ms
#define WD(ms)	((int)(((int)(ms))/HC_TPM0_MOD))
#define WD_5S	5000 	// 5 seg

void delayMs(int);
void WD_touch(int);
void WD5S_touch(void);
void SysTick_Handler(void);

/** TODO
 * Nil necesita una función que se ejecute cada 5 segundos, que vaya con otra que cuando se llame actue como watchdog reiniciando los 5 segundos
 * Y otra función que al llamarla se le pase como argumento un tiempo y 
 * sin bloquear te interrumpa cuando transcurra ese tiempo. Si se llama otra vez antes de la interrupción programada debería reestablecer el contandor anulando la primera llamada.
 */



#endif /* COMMON_H_ */
