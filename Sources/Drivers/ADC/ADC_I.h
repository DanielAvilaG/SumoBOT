/*
 * ADC_I.h
 *
 *  Created on: Apr 7, 2019
 *      Author: PCO
 */

#ifndef ADC_I_H_
#define ADC_I_H_

#include "derivative.h" /* include peripheral declarations */

unsigned short res, reading;

void ADC0_IRQHandler() __attribute__((interrupt("ADC0_IRQ")));
void ADC0_init_i(void);
unsigned short ADC0_read_i(unsigned char ch);

#endif /* ADC_I_H_ */


