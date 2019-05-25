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

#include "UT/IR_Test.h"
#include "UT/HC_Test.h"
#include "UT/PWM_Test.h"

#include "common.h"


//Les necesito per combat, no se si es posible tenirles...
#include <math.h> //arrel cuadrada
#include <time.h> //random
#include <stdlib.h> //random

struct mapa{
	char mapa[77][77];
	int ultimaposicioX;
	int ultimaposicioY;
	int ultimaposicioENEX;
	int ultimaposicioENEY;
};
typedef struct mapa mapa1;
mapa1 mapa2;
void crear_mapa(){ //Dibuja un circulo de 1's que es el ring. Fuera y el limite son 0's.
	int y=0;
	int x=0;
	for (y=-77/2;y <= 77/2;y++)  {
	        for (x=-77/2;x <= 77/2;x++)  {
	 
	            if ((int) sqrt (pow(x,2)+pow(y,2)) >= 77/2){ 
	            	mapa2.mapa[x+77/2][y+77/2] = 0;
	            }else {
	            	mapa2.mapa[x+77/2][y+77/2] = 1;
	            }
	         }
	     }

	mapa2.ultimaposicioENEX = 77/2;
	mapa2.ultimaposicioENEY = 77/2+5;
	mapa2.mapa[77/2][(77/2)+5]=2;
	mapa2.ultimaposicioX = 77/2;
	mapa2.ultimaposicioY = 77/2-5;
	mapa2.mapa[77/2][(77/2)-5]=3;
}


void posicio(double distancia, int orientacio){
	
	x = (int)(distancia)*sin((3.1415/180)*(orientacio));
	y = (int)(distancia)*cos((3.1415/180)*(orientacio));
	mapa2.ultimaposicioX = x+mapa2.ultimaposicioX;
	mapa2.ultimaposicioY = y+mapa2.ultimaposicioY;
}


void combat(){
	int orientacio=90;
	int gir = 1, MAXGIR=120; //Max Gir es el que tarda a girar 120º
	//srand(time(NULL));
	int random = rand() %6; 
	double distancia;
	crear_mapa();
	char state='s', nextstate='s';
	delayMs(5000);
	for(;;) {
		if (alertstatus==0){
			switch (state){
				case 's': //Sensing
					if (cm_PTA5>0||cm_PTC8>0||cm_PTC9>0){
						if (cm_PTA5<3){ //Davant
							PWM_duty(-20000,-20000); //Carga cap endavant
							WD_touch(5);
						}else{
							if (cm_PTC9<3){ //dreta
								PWM_duty(-20000,20000);
								WD_touch(5);
								orientacio = orientacio -120;
								delayMs(140);
								PWM_duty(-20000,-20000);
								WD_touch(5);

							}else{
								if (cm_PTC8<3){ //esquerra
									PWM_duty(20000,-20000); //esquerra
									WD_touch(5);
									orientacio = orientacio + 120;
									delayMs(120);
									PWM_duty(-20000,-20000);
									WD_touch(5);
								}else{
									if (cm_PTA5<cm_PTC8) {
										if (cm_PTA5<cm_PTC9) {
											distancia = cm_PTA5;
											mapa2.mapa[ultimaposicioENEX][ultimaposicioENEY]=1;
											int eneX = ((int) (distancia)*sin((3.1415/180)*orientacio))+mapa2.ultimaposicioX;
											int eneY = ((int) (distancia)*cos((3.1415/180)*orientacio))+mapa2.ultimaposicioY;
											if((eneX<77) && (eneY<77) && (mapa2.mapa[eneX][eneY]>0))
												{
													mapa2.ultimaposicioENEX = eneX;
													mapa2.ultimaposicioENEY = eneY;
													mapa2.mapa[ultimaposicioENEX][ultimaposicioENEY]=2;
												}
										}else{
											distancia = cm_PTC9;
											mapa2.mapa[ultimaposicioENEX][ultimaposicioENEY]=1;
											int eneX = ((int) (distancia)*sin((3.1415/180)*orientacio))+mapa2.ultimaposicioX;
											int eneY = ((int) (distancia)*cos((3.1415/180)*orientacio))+mapa2.ultimaposicioY;
											if((eneX<77) && (eneY<77) && (mapa2.mapa[eneX][eneY]>0))
												{
													mapa2.ultimaposicioENEX = eneX;
													mapa2.ultimaposicioENEY = eneY;
													mapa2.mapa[ultimaposicioENEX][ultimaposicioENEY]=2;
												}
										}
									}else{
										if (cm_PTC8<cm_PTC9) {
											distancia = cm_PTC8;
											mapa2.mapa[ultimaposicioENEX][ultimaposicioENEY]=1;
											int eneX = ((int) (distancia)*sin((3.1415/180)*orientacio))+mapa2.ultimaposicioX;
											int eneY = ((int) (distancia)*cos((3.1415/180)*orientacio))+mapa2.ultimaposicioY;
											if((eneX<77) && (eneY<77) && (mapa2.mapa[eneX][eneY]>0))
												{
													mapa2.ultimaposicioENEX = eneX;
													mapa2.ultimaposicioENEY = eneY;
													mapa2.mapa[ultimaposicioENEX][ultimaposicioENEY]=2;
												}
										}else{
											distancia = cm_PTC9;
											mapa2.mapa[ultimaposicioENEX][ultimaposicioENEY]=1;
											int eneX = ((int) (distancia)*sin((3.1415/180)*orientacio))+mapa2.ultimaposicioX;
											int eneY = ((int) (distancia)*cos((3.1415/180)*orientacio))+mapa2.ultimaposicioY;
											if((eneX<77) && (eneY<77) && (mapa2.mapa[eneX][eneY]>0))
												{
													mapa2.ultimaposicioENEX = eneX;
													mapa2.ultimaposicioENEY = eneY;
													mapa2.mapa[ultimaposicioENEX][ultimaposicioENEY]=2;
												}
										}
									}
									nextstate = 'c';
								}
							}
						}
						
						//girar per encarar depenen del UC que salti, fer un if de 3
						//distancia = cm_PT que salti
						//orientacio= orientacio +- angle!!! 
						
					}else{
						if (gir%2==0){ //dreta
							
							PWM_duty(-20000,20000); //dreta
							WD_touch(5);
							orientacio = orientacio - gir; 
							delayMs(gir*1.1666);
							PWM_duty(0,0);
						}else{
							PWM_duty(20000,-20000); //esquerra
							WD_touch(5);
							orientacio = orientacio + gir;
							delayMs(gir);
							PWM_duty(0,0);
						}
						if (gir <=MAXGIR){
							gir++;	
						}else{
							gir=1;
							PWM_duty(-20000,-17500);
							delayMs(50);
							posicio(50*0.16, orientacio);
						}
						
						nextstate='s';
					}
					break;
				case 'c':
					if (random>2){//endavant
						PWM_duty(-20000,-17500);//endavant
						WD_touch(5);
						delayMs((distancia-3)/0.16);
						posicio(distancia-3, orientacio);
						nextstate= 's';
						random = rand() %6; 
						break;
					}else{

						double x = (distancia/2)*sin((3.1415/180)*orientacio);
						double y = (distancia/2)*cos((3.1415/180)*orientacio);
						if (random>4){//dreta
							
							x = (distancia/2)*sin((3.1415/180)*(orientacio-90));
							y = (distancia/2)*cos((3.1415/180)*(orientacio-90));
							if((x+mapa2.ultimaposicioX<77) && (y+mapa2.ultimaposicioY<77) && (mapa2.mapa[(int)(x+mapa2.ultimaposicioX)][(int)(y+mapa2.ultimaposicioY)]>0))
							{
								PWM_duty(-20000,20000);//dreta
								WD_touch(5);
								delayMs(105);
								PWM_duty(0,0);
								orientacio = orientacio -90;
								PWM_duty(-(((500/9)*(distancia-10))-111.11111),-20000);
								posicio(distancia, orientacio);
								WD_touch(5);
								delayMs(2500);
								WD_touch(5);
								PWM_duty(0,0);
								
								
								nextstate= 's';
								random = rand() %6; 
								break;
							}else{
								PWM_duty(-20000,-17500);//endavant
								WD_touch(5);
								delayMs((distancia-3)/16);
								posicio(distancia-3, orientacio);
								nextstate= 's';
								random = rand() %6; 
								break;
							}
						} else{//esquerra
							x = (distancia/2)*sin((3.1415/180)*(orientacio+90));
							y = (distancia/2)*cos((3.1415/180)*(orientacio+90));
							if((x+mapa2.ultimaposicioX<77) && (y+mapa2.ultimaposicioY<77) && (mapa2.mapa[(int)(x+mapa2.ultimaposicioX)][(int)(y+mapa2.ultimaposicioY)]>0))
							{
								PWM_duty(20000,-20000);//esquerra
								WD_touch(5);
								delayMs(90);
								PWM_duty(0,0);
								orientacio = orientacio +90;
								PWM_duty(-20000,-(((500/9)*(distancia-10))-111.11111));
								posicio(distancia, orientacio);
								WD_touch(5);
								delayMs(2500);
								WD_touch(5);
								PWM_duty(0,0);
								
								
								nextstate= 's';
								random = rand() %6; 
								break;
							} else{
								PWM_duty(-20000,-17500);//endavant
								WD_touch(5);
								delayMs((distancia-3)/16);
								posicio(distancia-3, orientacio);
								nextstate= 's';
								random = rand() %6; 
								break;
							}
						}
					}
					
					 
				default: //per si de cas, torna al estat de sensing si hi ha estat desconegut
					state='s', nextstate='s';
					break;
			}
		state = nextstate;
		}
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
			
		case 'w':
			UART0_send_string_ln("Pulsar de nuevo para tocar al perrito.");
			WD_touch(5);
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
	HC_init();
	WD_touch(5); // Wathdog configurable a 10 s (ejemplo de uso)
	alertstatus = 0;
	//RLED_toggle();
			
	//WD5S_touch();
	Test();
	
	//BLED_on();
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
	//combat();
	
	
	
	
	for(;;) {     


	}
	return 0;
}


