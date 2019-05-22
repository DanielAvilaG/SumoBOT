/*
 * common.h
 *
 *  Created on: Apr 29, 2019
 *      Author: PCO
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "MKL25Z4.h"

void delayMs(int);
void WD_touch(int);
void SysTick_Handler(void);

/** TODO
 * Nil necesita una función que se ejecute cada 5 segundos, que vaya con otra que cuando se llame actue como watchdog reiniciando los 5 segundos
 * Y otra función que al llamarla se le pase como argumento un tiempo y 
 * sin bloquear te interrumpa cuando transcurra ese tiempo. Si se llama otra vez antes de la interrupción programada debería reestablecer el contandor anulando la primera llamada.
 */



#endif /* COMMON_H_ */
