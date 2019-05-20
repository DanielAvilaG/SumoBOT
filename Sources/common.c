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


