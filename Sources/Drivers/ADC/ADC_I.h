/*
 * ADC_I.h
 *
 *  Created on: Apr 7, 2019
 *      Author: PCO
 */

#ifndef ADC_I_H_
#define ADC_I_H_

#include "derivative.h" /* include peripheral declarations */
#include "ADC_P.h"

#include "../../common.h"


#define LT 0
#define GT 1

unsigned short res, reading, compare;

typedef struct IR {
	unsigned short FrontRight; 
	unsigned short FrontLeft;
	unsigned short BackRight;
	unsigned short BackLeft;
	unsigned short General;
} volatile IR;

IR IR_Data;

void ADC0_IRQHandler() __attribute__((interrupt("ADC0_IRQ")));
void ADC0_init_i(void);
unsigned short ADC0_read_i(unsigned char ch);
void ADC0_compare_i(unsigned char ch, uint16_t cv1, unsigned short type);

#endif /* ADC_I_H_ */


