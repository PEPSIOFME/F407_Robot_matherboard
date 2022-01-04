#include "i2c.h"

// 定义MPU9250内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40

#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42

#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48

		
#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08


#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)


//****************************

#define	GYRO_ADDRESS   0xD0	  //陀螺地址
#define MAG_ADDRESS    0x18   //磁场地址
#define ACCEL_ADDRESS  0xD0 

uint8_t TX_DATA[4];  	    //显示据缓存区
uint8_t BUF[10];            //接收数据缓存区
//char  test=0; 				//IIC用到
short T_X,T_Y,T_Z,T_T;		//X,Y,Z轴，温度



/**
  * @brief  IIC_GPIO初始化
  * @param  None
  * @retval None
  */
void IIC_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);   //使能PORT,PORTG时钟
	GPIO_SetBits(GPIOE, GPIO_Pin_6 | GPIO_Pin_2);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;           //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;          //开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;      //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);                  //初始化
	GPIO_SetBits(GPIOE, GPIO_Pin_6 | GPIO_Pin_2);
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
    //uint8_t ack = 0;

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
  * @retval 是否成功
  */
bool Single_Write(uint8_t SlaveAddress, uint8_t REG_Address, uint8_t REG_data)		     //void
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

/**
  * @brief  单字节读取
  * @param  MPU9250寄存器读取
  * @retval 读取数据
  */
uint8_t Single_Read(uint8_t SlaveAddress,uint8_t REG_Address)
{   
    uint8_t REG_data;     	
	IIC_Begin();
    IIC_WriteByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!IIC_WaitAck())
    {
        IIC_Stop();
        //test=1; 
        return FALSE;
    }
    IIC_WriteByte((uint8_t) REG_Address);   //设置低起始地址      
    IIC_WaitAck();
    IIC_Begin();
    IIC_WriteByte(SlaveAddress+1);
    IIC_WaitAck();

	REG_data= IIC_ReadByte(1);
    IIC_NAck();
    IIC_Stop();
    //return TRUE;
	return REG_data;
}

/**
  * @brief  MPU9250初始化
  * @param  None
  * @retval None
  */
void Init_MPU9250(void)
{
/*
   Single_Write(GYRO_ADDRESS,PWR_M, 0x80);   //
   Single_Write(GYRO_ADDRESS,SMPL, 0x07);    //
   Single_Write(GYRO_ADDRESS,DLPF, 0x1E);    //±2000°
   Single_Write(GYRO_ADDRESS,INT_C, 0x00 );  //
   Single_Write(GYRO_ADDRESS,PWR_M, 0x00);   //
*/
    Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x07);
	Single_Write(GYRO_ADDRESS,CONFIG, 0x06);
	Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);
	Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);
  //----------------
//	Single_Write(GYRO_ADDRESS,0x6A,0x00);//close Master Mode	

}

/**
  * @brief  MPU9250读加速度
  * @param  None
  * @retval None
  */
void READ_MPU9250_ACCEL(void)
{ 

    BUF[0]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_L); 
    BUF[1]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_H);
    T_X=	(BUF[1]<<8)|BUF[0];
    T_X/=164; 						   //读取计算X轴数据

    BUF[2]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_L);
    BUF[3]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_H);
    T_Y=	(BUF[3]<<8)|BUF[2];
    T_Y/=164; 						   //读取计算Y轴数据
    BUF[4]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_L);
    BUF[5]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_H);
    T_Z=	(BUF[5]<<8)|BUF[4];
    T_Z/=164; 					       //读取计算Z轴数据
 
}

/**
  * @brief  MPU9250读陀螺仪
  * @param  None
  * @retval None
  */
void READ_MPU9250_GYRO(void)
{ 

   BUF[0]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_L); 
   BUF[1]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_H);
   T_X=	(BUF[1]<<8)|BUF[0];
   T_X/=16.4; 						   //读取计算X轴数据

   BUF[2]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_L);
   BUF[3]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_H);
   T_Y=	(BUF[3]<<8)|BUF[2];
   T_Y/=16.4; 						   //读取计算Y轴数据
   BUF[4]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_L);
   BUF[5]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_H);
   T_Z=	(BUF[5]<<8)|BUF[4];
   T_Z/=16.4; 					       //读取计算Z轴数据
 
 
  // BUF[6]=Single_Read(GYRO_ADDRESS,TEMP_OUT_L); 
  // BUF[7]=Single_Read(GYRO_ADDRESS,TEMP_OUT_H); 
  // T_T=(BUF[7]<<8)|BUF[6];
  // T_T = 35+ ((double) (T_T + 13200)) / 280;// 读取计算出温度
}

/**
  * @brief  MPU9250读指南针
  * @param  None
  * @retval None
  */
void READ_MPU9250_MAG(void)
{ 
   Single_Write(GYRO_ADDRESS,0x37,0x02);//turn on Bypass Mode 
   delay_ms(10);	
   Single_Write(MAG_ADDRESS,0x0A,0x01);
   delay_ms(10);	
   BUF[0]=Single_Read (MAG_ADDRESS,MAG_XOUT_L);
   BUF[1]=Single_Read (MAG_ADDRESS,MAG_XOUT_H);
   T_X=(BUF[1]<<8)|BUF[0];

   BUF[2]=Single_Read(MAG_ADDRESS,MAG_YOUT_L);
   BUF[3]=Single_Read(MAG_ADDRESS,MAG_YOUT_H);
   T_Y=	(BUF[3]<<8)|BUF[2];
   						   //读取计算Y轴数据
	 
   BUF[4]=Single_Read(MAG_ADDRESS,MAG_ZOUT_L);
   BUF[5]=Single_Read(MAG_ADDRESS,MAG_ZOUT_H);
   T_Z=	(BUF[5]<<8)|BUF[4];
 					       //读取计算Z轴数据
}

//********串口发送数据***************************************
void Send_data(void)
{
    uint8_t i;
    // USART1_SendData(MAG);
    // USART1_SendData(axis);
    // USART1_SendData(':');
    for(i=0;i<4;i++)
    {
        USART1_SendData(TX_DATA[i]);
    }
    // USART1_SendData(',');
    // USART1_SendData(' ');
}

void USART1_SendData(uint8_t SendData)
{
    USART_SendData(USART1, SendData);
    delay_ms(1);
}

void DATA_printf(uint8_t *s,short temp_data)
{
	if(temp_data<0){
	temp_data=-temp_data;
    *s='-';
	}
	else *s=' ';
    *++s =temp_data/100+0x30;
    temp_data=temp_data%100;     //取余运算
    *++s =temp_data/10+0x30;
    temp_data=temp_data%10;      //取余运算
    *++s =temp_data+0x30; 	
}


