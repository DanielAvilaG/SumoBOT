/*
 * combat.h
 *
 *  Created on: May 26, 2019
 *      Author: Dani
 */

#ifndef COMBAT_H_
#define COMBAT_H_

#include "common.h"
#include <math.h> //arrel cuadrada

void combat(void);
void crear_mapa(void);
void posicio(double, int);
void ajustarangledreta(void);
void ajustarangleesquerra(void);
void ajustarcercledreta(int);

/*
		//PWM   = distancia(cm)	= temps (s)
		//-3000 = 66 maxim.		= 4.97
		//-2500 = 57			= 2.64
		//-2000 = 48			= 2.88
		//-1500 = 39            = 2.57
		//-1000 = 30			= 2.51
		//-500  = 19			= 2.50
		//0		= 10 minim.
		PWM_duty(20000,-20000);//esquerra
		WD5S_touch();
		delayMs(90);
		PWM_duty(-20000,-1000);
		delayMs(1200);
		PWM_duty(0,0);*/

#endif /* COMBAT_H_ */
