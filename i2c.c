#include "i2c.h"

/**
  * @brief  IIC_GPIO初始化
  * @param  None
  * @retval None
  */
void IIC_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);   //使能PORT,PORTG时钟
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;           //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;          //开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;      //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);                  //初始化
	GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1);
}

/**
  * @brief  IIC开始信号
  * @param  None
  * @retval None
  */
void IIC_Begin(void)
{
    SCL_High;
    SDA_High;
    delay_us(5);
    SDA_Low;
    delay_us(5);
    SCL_Low;
}

/**
  * @brief  IIC停止信号
  * @param  None
  * @retval None
  */
void IIC_Stop(void)
{
    SCL_High;
    SDA_Low;
    delay_us(5);
    SDA_High;
    delay_us(5);
}

/**
  * @brief  IIC等待响应
  * @param  None
  * @retval None
  */
bool IIC_WaitAck(void)
{
    uint8_t count = 0;

    SDA_High;
    delay_us(4);
    while(SDA_Read)
    {
        count++;
        if(count > 250)
        {
            return FALSE;
        }
    }
    SCL_High;
    delay_us(4);
    SCL_Low;
    
    return TRUE;
}

/**
  * @brief  IIC应答
  * @param  None
  * @retval None
  */
void IIC_Ack(void)
{
    SDA_Low;
    delay_us(4);
    SCL_High;
    delay_us(4);
    SCL_Low;
    delay_us(4);
    SDA_High;
}

/**
  * @brief  IIC非应答
  * @param  None
  * @retval None
  */
void IIC_NAck(void)
{
    SDA_High;
    delay_us(4);
    SCL_High;
    delay_us(4);
    SCL_Low;
    delay_us(4);
}

/**
  * @brief  IIC发送一个字节
  * @param  预发送的字节
  * @retval None
  */
void IIC_WriteByte(uint8_t TXD)
{
    uint8_t i;
    SCL_Low;

    for(i = 0; i < 8; i++)
    {
        if(TXD & 0x80)
        {
            SDA_High;
        }
        else
        {
            SDA_Low;
        }
        TXD <<= 1;
        delay_us(2);
        SCL_High;
        delay_us(2);
        SCL_Low;
        delay_us(2);
    }
}

/**
  * @brief  IIC读一个字节
  * @param  预发送的字节
  * @retval None
  */
uint8_t IIC_ReadByte(uint8_t ack)
{
    uint8_t i, rcv = 0;
    for(i = 0; i < 8; i++)
    {
        SCL_High;
        delay_us(4);
        rcv <<= 1;
        if(SDA_Read)
        {
            rcv++;
        }
        SCL_Low;
        delay_us(4);
    }
    if(ack)
    {
        IIC_Ack();
    }
    else
    {
        IIC_NAck();
    }
	return rcv;
}

/**
  * @brief  单字节写入
  * @param  MPU9250寄存器写入
  * @retval None
  */
bool Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	IIC_Begin();
    IIC_WriteByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!IIC_WaitAck())
    {
        IIC_Stop(); 
        return FALSE;
    }
    IIC_WriteByte(REG_Address);   //设置低起始地址      
    IIC_WaitAck();	
    IIC_WriteByte(REG_data);
    IIC_WaitAck();   
    IIC_Stop();
    delay_ms(5);
    return TRUE;
}

