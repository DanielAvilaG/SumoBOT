/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */

#include "Drivers/UART/UART.h"
#include "Drivers/ADC/ADC_I.h"
//#include "Drivers/LED/LED_46.h"
#include "Drivers/LED/LED_25.h"
#include "Drivers/PWM/PWM.h"
#include "Drivers/TPM0/TPM0.h"

#include "UT/IR_Test.h"
#include "UT/HC_Test.h"
#include "UT/PWM_Test.h"

#include "common.h"


//Les necesito per combat, no se si es posible tenirles...
#include <math.h> //arrel cuadrada
#include <time.h> //random
#include <stdlib.h> //random

void crear_mapa(){
	int mapa[77][77];
	int y=0;
	int x=0;
	for (y=-77/2;y <= 77/2;y++)  {
	        for (x=-77/2;x <= 77/2;x++)  {
	 
	            if ((int) sqrt (pow(x,2)+pow(y,2)) >= 77/2){//revisar aixo, ho fa malament, pero no veig cap altre manera
	            	//potser... https://code4run.com/midpoint-circle-algorithm/
	            	mapa[x+77/2][y+77/2] = 0;
	            }else {
	            	mapa[x+77/2][y+77/2] = 1;
	            }
	         }
	     }
	mapa[77/2][(77/2)+5]=2;
	mapa[77/2][(77/2)-5]=3;
}


void combat(){
	int Vx=0, Vy=0, orientacio=90;
	int gir = 1, MAXGIR=120;//Max Gir hauria de ser el que tarda a girar 120º
	int random = rand() %6; 
	int distancia;
	crear_mapa();
	char state='s', nextstate='s';
	srand(time(NULL));
	delayMs(5000);
	for(;;) {
		switch (state){
			case 's': //Sensing
				if (cm_PTA5>0||cm_PTC8>0||cm_PTC9>0){
					//PTA5 davant
					//girar per encarar depenen del UC que salti, fer un if de 3
					//distancia = cm_PT que salti
					//orientacio= orientacio +- angle!!! 
					nextstate = 'c';
				}else{
					if (gir%2==0){
						PWM_duty(10000,10000);
						//orientacio= orientacio +- angle!!!
						delayMs(gir);
					}else{
						PWM_duty(-10000,-10000);
						//orientacio= orientacio +- angle!!!
						delayMs(gir);
					}
					if (gir <=MAXGIR){
						gir++;	
					}else{
						gir=1;
					}
					
					nextstate='s';
				}
				break;
			case 'c':
				if (random>2){//endavant
					PWM_duty(10000,-10000);//espero que sigui endavant XD
					//cada cm update_mapa();
					//es pot fer amb una interrupcio? per anar fent sensing... delayMs(distancia/velocitat)
					//PWM_duty(0,0)
					
					nextstate= 's';
					break;
				}
				if (random>4){//dreta (o esquerra, ni idea de com gira 
					//
					PWM_duty(10000,10000);//espero que sigui dreta
					//delayMs(gir 90º);
					//PWM_duty(10000-angle,-10000);
					//cada cm update_mapa();
					//es pot fer amb una interrupcio? per anar fent sensing... delayMs(distancia/velocitat)
					//PWM_duty(0,0)
					
					nextstate= 's';
					break;
				} 
				if (random>6){//l'altre XD 
					//
					PWM_duty(-10000,-10000);
					//delayMs(gir 90º);
					//PWM_duty(-10000,10000-angle);
					//cada cm update_mapa();
					//es pot fer amb una interrupcio? per anar fent sensing... delayMs(distancia/velocitat)
					//PWM_duty(0,0)
					
					nextstate= 's';
					break;
				} 
			default: //per si de cas, torna al estat de sensing si hi ha estat desconegut
				state='s', nextstate='s';
		}
		state = nextstate;
	}
}

void Test()
{	  
	char c;
	for(;;) {     

		UART0_send_string_ln("Select Test:");
		UART0_send_string_ln("'i': IR \t 'm': MOTORS \t 'u': ULTRASOUND\t 'x': EXIT TESTS");
		
		
		while(!(UART0_S1 & UART0_S1_RDRF_MASK)) { } /* 0x20 wait for receive buffer full */
		c = UART0_D; /* read the char received */
		
		switch (c){
		case 'i':
			RLED_toggle();
			if(IR_test())GLED_toggle();
			delayMs(50);
			GLED_off();
			RLED_toggle();
			break;
			
		case 'm':
			RLED_toggle();
			PWM_test();
			RLED_toggle();
			
			break;
			
		case 'u':
			HC_test();
			break;
			
		case 'x':
			return;
			break;
		
		default:
			UART0_send_ln();
			UART0_send_string("\t\033[37;1;5m");
			UART0_send_char(c);
			UART0_send_string_ln("\033[0m\033[31m IS NOT AN OPTION!\033[0m");
			UART0_send_ln();
			break;
		}
	}
}

int main(void)
{

	ADC0_init_i();
	RLED_init();
	GLED_init();
	BLED_init();
	UART0_init();
	PWM_init();
	TPM0_init();
	HC_init();
	

	BLED_on();
	Test();
	
	for(;;) {     


	}
	return 0;
}


