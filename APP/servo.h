#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f4xx.h"
#include "i2c.h"
#include <math.h>

void PCA9685_write(uint8_t reg,uint8_t data);
uint8_t PCA9685_read(uint8_t reg);
void setPWMFreq(uint8_t freq);
uint16_t calculate_PWM(uint8_t angle);
void setPWM(uint8_t num, uint16_t on, uint16_t off);
void PCA9685_Reset(void);
void reset_reboot(void);



#endif
