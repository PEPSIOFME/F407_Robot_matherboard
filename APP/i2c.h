#ifndef __IIC_H
#define __IIC_H

#include "delay.h"
#include "stm32f4xx.h"

#define SDA_High GPIO_SetBits(GPIOE, GPIO_Pin_1)
#define SDA_Low GPIO_ResetBits(GPIOE, GPIO_Pin_1)
#define SCL_High GPIO_SetBits(GPIOE, GPIO_Pin_0)
#define SCL_Low GPIO_ResetBits(GPIOE, GPIO_Pin_0)
#define SDA_Read GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)

void IIC_GPIO_Init(void);
void IIC_Begin(void);
void IIC_Stop(void);

bool IIC_WaitAck(void);
void IIC_Ack(void);
void IIC_WriteByte(uint8_t TXD);
uint8_t IIC_ReadByte(uint8_t ack);
bool Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
uint8_t Single_Read(uint8_t SlaveAddress,uint8_t REG_Address);
void Init_MPU9250(void);
void READ_MPU9250_ACCEL(void);


#endif


