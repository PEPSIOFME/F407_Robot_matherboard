#ifndef __IIC_H
#define __IIC_H

#include "common.h"
#include "stm32f4xx.h"

#define SDA_High GPIO_SetBits(GPIOE, GPIO_Pin_2)
#define SDA_Low GPIO_ResetBits(GPIOE, GPIO_Pin_2)
#define SCL_High GPIO_SetBits(GPIOE, GPIO_Pin_6)
#define SCL_Low GPIO_ResetBits(GPIOE, GPIO_Pin_6)
#define SDA_Read GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)

extern uint8_t TX_DATA[4];       //显示据缓存区
extern uint8_t BUF[10];          //接收数据缓存区
extern char test;                //IIC用到
extern short T_X, T_Y, T_Z, T_T; //X,Y,Z轴，温度

void IIC_GPIO_Init(void);
void IIC_Begin(void);
void IIC_Stop(void);

bool IIC_WaitAck(void);
void IIC_Ack(void);
void IIC_WriteByte(uint8_t TXD);
uint8_t IIC_ReadByte(uint8_t ack);
bool Single_Write(unsigned char SlaveAddress, unsigned char REG_Address, unsigned char REG_data);
uint8_t Single_Read(uint8_t SlaveAddress, uint8_t REG_Address);
void Init_MPU9250(void);
void READ_MPU9250_ACCEL(void);
void READ_MPU9250_GYRO(void);
void READ_MPU9250_MAG(void);
void Send_data(void);
void USART1_SendData(uint8_t SendData);
void DATA_printf(uint8_t *s, short temp_data);

#endif
