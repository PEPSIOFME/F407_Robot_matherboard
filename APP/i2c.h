#include "stm32f4xx.h"
#include "common.h"

#define SDA_High GPIO_SetBits(GPIOE, GPIO_Pin_0)
#define SDA_Low GPIO_ResetBits(GPIOE, GPIO_Pin_0)
#define SCL_High GPIO_SetBits(GPIOE, GPIO_Pin_1)
#define SCL_Low GPIO_ResetBits(GPIOE, GPIO_Pin_1)
#define SDA_Read GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)

void IIC_GPIO_Init(void);
void IIC_Begin(void);
void IIC_Stop(void);
uint8_t IIC_WaitAck(void);
void IIC_Ack(void);


