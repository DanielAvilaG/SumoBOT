#include "derivative.h" /* include peripheral declarations */

#include "../../common.h"

#ifndef PWM_H_
#define PWM_H_
void PWM_init();
void PWM_duty(int motor1, int motor2);

void PWM_moveForward(int);
void PWM_moveBackward(int);
void PWM_rotateLeft(int);
void PWM_rotateRight(int);

#endif /* PWM_H_ */
