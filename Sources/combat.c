/*
 * combat.c
 *
 *  Created on: May 26, 2019
 *      Author: Dani
 */
#include "combat.h"

void ajustarangledreta(){
	PWM_duty(-20000,20000);
	orientacio = orientacio -120;
	delayMs(DELAY120DRETA);
	PWM_duty(-20000,-20000);
}
void ajustarangleesquerra(){
	PWM_duty(20000,-20000); //esquerra
	orientacio = orientacio + 120;
	delayMs(DELAY120ESQUERRA);
	PWM_duty(-20000,-20000);
}
void ajustarcercledreta(int distancia){
	
	PWM_duty(-20000,20000);//dreta
	delayMs(DELAY90DRETA);
	orientacio = orientacio -90;
	PWM_duty(-(((MSPERCM)*(distancia-10))-MSDEMENYS10),-20000);
	posicio(distancia, orientacio);
	orientacio = 170;
	delayMs(DELAYCERCLE*distancia);
	PWM_duty(100,100);
}

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
	int x,y;
	x = (int)(distancia)*sin((3.1415/180)*(orientacio));
	y = (int)(distancia)*cos((3.1415/180)*(orientacio));
	mapa2.ultimaposicioX = x+mapa2.ultimaposicioX;
	mapa2.ultimaposicioY = y+mapa2.ultimaposicioY;
}


void combat(){
	orientacio=90;
	char buffer[20];
	int gir = GIRINICIAL;
	int cm_Front, cm_Left, cm_Right;
	//int random = 1; 
	double distancia = -1;
	crear_mapa();
	state='s', nextstate='s';
	WD5S();
	
	
	ADC0_compare_i(13, IRTHRESHHOLDG, GT);
	
	
	for(;;) {
		if (alertstatus==0){
			switch (state){
				case 's': //Sensing
					cm_Front = cm_PTA5;
					cm_Left = cm_PTC8;
					cm_Right = cm_PTC9;
					//RLED_toggle();
					if (cm_Front>0||cm_Left>0||cm_Right>0){
						if (cm_Front<5){ //Davant
							//sprintf(buffer,"HC davant menor 5: %d", cm_Front);
							//UART0_send_string_ln(buffer);
							PWM_duty(-20000,-20000); //Carga cap endavant
							WD5S();
						}else{
							if (cm_Right<5){ //dreta
								//GLED_toggle();
								sprintf(buffer,"HC dreta menor 5: %d", cm_Right);
								UART0_send_string_ln(buffer);
								PWM_duty(-20000,20000);
								WD5S();
								orientacio = orientacio -120;
								delayMs(DELAY120DRETA);
								PWM_duty(-20000,-20000); //Carga cap endavant
								WD5S();
							}else{
								if (cm_Left<5){ //esquerra
									//GLED_toggle();
									sprintf(buffer,"HC esquerra menor 5: %d", cm_Left);
									UART0_send_string_ln(buffer);
									PWM_duty(20000,-20000); //esquerra
									WD5S();
									orientacio = orientacio + 120;
									delayMs(DELAY120ESQUERRA);
									PWM_duty(-20000,-20000); //Carga cap endavant
									WD5S();
								}else{
									//BLED_toggle();	
									
									if (cm_Front<cm_Left) {
										if (cm_Front<cm_Right) {
											sprintf(buffer,"HC davant: %d", cm_Front);
											UART0_send_string_ln(buffer);
											//random++;
											distancia = cm_Front;
											mapa2.mapa[mapa2.ultimaposicioENEX][mapa2.ultimaposicioENEY]=1;
											int eneX = ((int) (distancia)*sin((3.1415/180)*orientacio))+mapa2.ultimaposicioX;
											int eneY = ((int) (distancia)*cos((3.1415/180)*orientacio))+mapa2.ultimaposicioY;
											if((eneX<77) && (eneY<77))
											{
												if (mapa2.mapa[eneX][eneY]>0){
												//	sprintf(buffer,"HC davant dins mapa: %d", cm_Front);
												//UART0_send_string_ln(buffer);
													mapa2.ultimaposicioENEX = eneX;
													mapa2.ultimaposicioENEY = eneY;
													mapa2.mapa[mapa2.ultimaposicioENEX][mapa2.ultimaposicioENEY]=2;
												}else{
													distancia = -1;
												} 
											}
										}else{
											distancia = cm_Right;
											//sprintf(buffer,"HC dreta: %d", cm_Right);
											//UART0_send_string_ln(buffer);
											//random++;
											mapa2.mapa[mapa2.ultimaposicioENEX][mapa2.ultimaposicioENEY]=1;
											int eneX = ((int) (distancia)*sin((3.1415/180)*orientacio))+mapa2.ultimaposicioX;
											int eneY = ((int) (distancia)*cos((3.1415/180)*orientacio))+mapa2.ultimaposicioY;
											if((eneX<77) && (eneY<77))
												{
												if (mapa2.mapa[eneX][eneY]>0){
													sprintf(buffer,"HC dreta dins mapa: %d", cm_Right);
													UART0_send_string_ln(buffer);
													mapa2.ultimaposicioENEX = eneX;
													mapa2.ultimaposicioENEY = eneY;
													mapa2.mapa[mapa2.ultimaposicioENEX][mapa2.ultimaposicioENEY]=2;
													PWM_duty(-20000,20000);
													WD5S();
													orientacio = orientacio -120;
													delayMs(DELAY120DRETA);
												}else{
													distancia = -1;
												} 
												}
										}
									}else{
										if (cm_Left<cm_Right) {
											distancia = cm_Left;
											sprintf(buffer,"HC esquerra: %d", cm_Left);
											UART0_send_string_ln(buffer);
											//random++;
											mapa2.mapa[mapa2.ultimaposicioENEX][mapa2.ultimaposicioENEY]=1;
											int eneX = ((int) (distancia)*sin((3.1415/180)*orientacio))+mapa2.ultimaposicioX;
											int eneY = ((int) (distancia)*cos((3.1415/180)*orientacio))+mapa2.ultimaposicioY;
											if((eneX<77) && (eneY<77))
												{
												if (mapa2.mapa[eneX][eneY]>0){
													sprintf(buffer,"HC esquerra dins mapa: %d", cm_Left);
													UART0_send_string_ln(buffer);
													mapa2.ultimaposicioENEX = eneX;
													mapa2.ultimaposicioENEY = eneY;
													mapa2.mapa[mapa2.ultimaposicioENEX][mapa2.ultimaposicioENEY]=2;
													PWM_duty(20000,-20000); //esquerra
													WD5S();
													orientacio = orientacio + 120;
													delayMs(DELAY120ESQUERRA);
												}else{
													distancia = -1;
												} 
												}
										}else{
											distancia = cm_Right;
											sprintf(buffer,"HC dreta: %d", cm_Right);
											UART0_send_string_ln(buffer);
											//random++;
											mapa2.mapa[mapa2.ultimaposicioENEX][mapa2.ultimaposicioENEY]=1;
											int eneX = ((int) (distancia)*sin((3.1415/180)*orientacio))+mapa2.ultimaposicioX;
											int eneY = ((int) (distancia)*cos((3.1415/180)*orientacio))+mapa2.ultimaposicioY;
											if((eneX<77) && (eneY<77))
												{
												if (mapa2.mapa[eneX][eneY]>0){
													sprintf(buffer,"HC dreta dins mapa: %d", cm_Right);
													UART0_send_string_ln(buffer);
													mapa2.ultimaposicioENEX = eneX;
													mapa2.ultimaposicioENEY = eneY;
													mapa2.mapa[mapa2.ultimaposicioENEX][mapa2.ultimaposicioENEY]=2;
													PWM_duty(-20000,20000);
													WD5S();
													orientacio = orientacio -120;
													delayMs(DELAY120DRETA);
												}else{
													distancia = -1;
												} 
												}
										}
									}
									if (distancia>5){
										sprintf(buffer,"Distancia fora del mapa: %f", distancia);
										UART0_send_string_ln(buffer);
										nextstate = 'c';
										break;
									}else{
										nextstate = 's';
									//BLED_toggle();	
										break;
									}
							
								}
								
							}
						}
						
						
						//girar per encarar depenen del UC que salti, fer un if de 3
						//distancia = cm_PT que salti
						//orientacio= orientacio +- angle!!! 
						
					}else{
						//RLED_toggle();
						if (gir%2==0){ //dreta
							
							PWM_duty(-20000,20000); //dreta
							WD5S();
							orientacio = orientacio - gir; 
							delayMs(gir/120*DELAY120DRETA);
						}else{
							PWM_duty(20000,-20000); //esquerra
							WD5S();
							orientacio = orientacio + gir;
							delayMs(gir/120*DELAY120ESQUERRA);
						}

						nextstate='s';
						break;
						if (gir <=MAXGIR){
							gir= gir + 1;	
						}else{
							gir= GIRINICIAL+1;
							PWM_duty(-20000,-17500);
							delayMs(MOVIMENT);
							posicio(MOVIMENT*VELOCITAT, orientacio);
						}
						nextstate='s';

							//RLED_toggle();
						break;
						
					}

					nextstate='s';

					//RLED_toggle();
					break;
				case 'c':
					GLED_toggle();
					//random= random%6;
					
					//GLED_toggle();
					PWM_duty(-20000,-17500);//endavant
					WD5S();
					delayMs((distancia-3)/VELOCITAT);
					posicio(distancia-3, orientacio);
					nextstate= 's';
					//random = rand() %6; 
					GLED_toggle();
					break;
				
					/*    
					if (random>2){//endavant
						PWM_duty(-20000,-17500);//endavant
						WD5S();
						delayMs((distancia-3)/VELOCITAT);
						posicio(distancia-3, orientacio);
						nextstate= 's';
						random = 0; 
						GLED_toggle();
						break;
					}else{

						double x = (distancia/2)*sin((3.1415/180)*orientacio);
						double y = (distancia/2)*cos((3.1415/180)*orientacio);
						if (random>4){// gir per la dreta
							
							x = (distancia/2)*sin((3.1415/180)*(orientacio-90));
							y = (distancia/2)*cos((3.1415/180)*(orientacio-90));
							if((x+mapa2.ultimaposicioX<77) && (y+mapa2.ultimaposicioY<77) && (mapa2.mapa[(int)(x+mapa2.ultimaposicioX)][(int)(y+mapa2.ultimaposicioY)]>0))
							{
								PWM_duty(-20000,20000);//dreta
								WD5S();
								delayMs(DELAY90DRETA);
								orientacio = orientacio -90;
								PWM_duty(-(((MSPERCM)*(distancia-10))-MSDEMENYS10),-20000);
								posicio(distancia, orientacio);
								orientacio = 170;
								WD5S();
								delayMs(DELAYCERCLE*distancia);
								WD5S();
								PWM_duty(100,100);
								
								
								nextstate= 's';
								random = 0; 
								GLED_toggle();
								break;
							}else{
								PWM_duty(-20000,-17500);//endavant
								WD5S();
								delayMs((distancia-3)/VELOCITAT);
								posicio(distancia-3, orientacio);
								nextstate= 's';
								random = 0; 
								GLED_toggle();
								break;
							}
						} else{// gir per la esquerra
							x = (distancia/2)*sin((3.1415/180)*(orientacio+90));
							y = (distancia/2)*cos((3.1415/180)*(orientacio+90));
							if((x+mapa2.ultimaposicioX<77) && (y+mapa2.ultimaposicioY<77) && (mapa2.mapa[(int)(x+mapa2.ultimaposicioX)][(int)(y+mapa2.ultimaposicioY)]>0))
							{
								PWM_duty(20000,-20000);//esquerra
								WD5S();
								delayMs(90);
								orientacio = orientacio +90;
								PWM_duty(-20000,-(((MSPERCM)*(distancia-10))-MSDEMENYS10));
								posicio(distancia, orientacio);
								orientacio = 10;
								WD5S();
								delayMs(DELAYCERCLE*distancia);
								WD5S();
								PWM_duty(100,100);
								
								
								nextstate= 's';
								random = 0; 
								GLED_toggle();
								break;
							} else{
								PWM_duty(-20000,-17500);//endavant
								WD5S();
								delayMs((distancia-3)/VELOCITAT);
								posicio(distancia-3, orientacio);
								nextstate= 's';
								random = 0; 
								GLED_toggle();
								break;
							}
						}
						
					}
					*/
					
					 
				default: //per si de cas, torna al estat de sensing si hi ha estat desconegut
					state='s', nextstate='s';
					break;
			}
		state = nextstate;
		}
	}
}
