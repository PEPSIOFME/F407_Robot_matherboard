#ifndef __KINEMATIC_H
#define __KINEMATIC_H


#include "stm32f4xx.h"
#include <math.h>
#include "uart.h"
#include <stdio.h>
#include "servo.h"

extern double posture0[2];
extern double posture1[2];
extern double posture2[2];
extern double posture3[2];
extern double posture4[2];
extern double posture5[2];

uint8_t *GET_Angle(double *p);
void move(void);

#endif



