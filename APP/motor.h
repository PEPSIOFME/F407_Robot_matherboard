#include "stm32f4xx.h"

extern int16_t N;

#define STBY_ENBLE      GPIO_SetBits(GPIOE, GPIO_Pin_6);
#define STBY_DISABLE    GPIO_ResetBits(GPIOE, GPIO_Pin_6);

#define M1_FORWARD      {GPIO_ResetBits(GPIOE, GPIO_Pin_2); GPIO_SetBits(GPIOE, GPIO_Pin_3);}
#define M1_REVERSE      {GPIO_SetBits(GPIOE, GPIO_Pin_2); GPIO_ResetBits(GPIOE, GPIO_Pin_3);}
#define M1_STOP         {GPIO_SetBits(GPIOE, GPIO_Pin_2); GPIO_SetBits(GPIOE, GPIO_Pin_3);}

#define M2_FORWARD      {GPIO_ResetBits(GPIOE, GPIO_Pin_4); GPIO_SetBits(GPIOE, GPIO_Pin_5);}
#define M2_REVERSE      {GPIO_SetBits(GPIOE, GPIO_Pin_4); GPIO_ResetBits(GPIOE, GPIO_Pin_5);}
#define M2_STOP         {GPIO_SetBits(GPIOE, GPIO_Pin_4); GPIO_SetBits(GPIOE, GPIO_Pin_5);}

#define FORWARD_RT      {M1_FORWARD M2_FORWARD}
#define REVERSE_RT      {M1_REVERSE M2_REVERSE}
#define STOP_RT         {M1_STOP M2_STOP}

void MOTOR_Init(void);
void MOTOR_PWM_Init(uint32_t auto_data, uint32_t fractional);
void HALL_Init(u32 arr,u32 psc);

