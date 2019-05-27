/*
 * common.h
 *
 *  Created on: Apr 29, 2019
 *      Author: PCO
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "MKL25Z4.h"
#include "Drivers/LED/LED_25.h"
#include "Drivers/UART/UART.h"
#include "Drivers/ADC/ADC_I.h"
//#include "Drivers/LED/LED_46.h"
#include "Drivers/LED/LED_25.h"
#include "Drivers/PWM/PWM.h"

#include "UT/IR_Test.h"
#include "UT/HC_Test.h"
#include "UT/PWM_Test.h"

#include "combat.h"
#include "brain.h"
#include "calibrate.h"

#include <stdio.h>

#define HC_TPM0_MOD 60	// ms
#define WD(ms)	((int)(((int)(ms))/HC_TPM0_MOD))
#define WD_5S	5000 	// 5 seg

// NIL
#define DELAY90ESQUERRA 135
#define DELAY120ESQUERRA 180
#define VELOCITAT 0.16 
#define DELAY90DRETA 158
#define DELAY120DRETA 210
#define MOVIMENT 100
#define DELAYDEMESDRETA 1.16666


#define MAXGIR 180
#define GIRINICIAL 1
#define RANGE 30
#define PUSHTHRESHHOLD 10


#define MSINTER 7000

#define IRTHRESHHOLD 30000
#define IRTHRESHHOLDG 25000

#define ROTATION 16000
#define BACKWARD 17000
#define VEL_FORWARD 30 // cm/s
#define VEL_BACKWARD 30 // cm/s
#define VEL_RIGHT 250.00 // grados/s
#define VEL_LEFT 250.00 // grados/s
#define STOP 100



//AQUESTS VAN JUNTS, SI MODIFIQUES UN, MODIFICA ELS ALTRES INVERSAMENT (SI INCREMENTES MS EN *3, DIVIDIR CINCSEC EN 3 Y DELAYCERCLE EN 3)
#define MS 3000 //PER ELS DELAYS DE 90 I 120 TOCAR AQUEST
#define CINCSEC 1500 



#define DELAYCERCLE 23.333
#define MSPERCM 700/9 //gir
#define MSDEMENYS10 111.11111


void delayMs(int);
//void WD_touch(int);
void WD5S_touch(void);
void WD5S(void);
void delayMsinter(int);
void SysTick_delay(int);


volatile int alertstatus;
volatile int alert;
volatile int orientacio;
volatile char state, nextstate;

struct mapa{
	char mapa[77][77];
	int ultimaposicioX;
	int ultimaposicioY;
	int ultimaposicioENEX;
	int ultimaposicioENEY;
};
typedef struct mapa mapa1;
mapa1 mapa2;
/** TODO
 * Nil necesita una función que se ejecute cada 5 segundos, que vaya con otra que cuando se llame actue como watchdog reiniciando los 5 segundos
 * Y otra función que al llamarla se le pase como argumento un tiempo y 
 * sin bloquear te interrumpa cuando transcurra ese tiempo. Si se llama otra vez antes de la interrupción programada debería reestablecer el contandor anulando la primera llamada.
 */



#endif /* COMMON_H_ */
