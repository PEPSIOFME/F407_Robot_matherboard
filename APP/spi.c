#include "spi.h"

void Flash_SPI_Init(void)
{	 
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    SPI_InitTypeDef  SPI_InitStructure = {0};
        
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);           //使能GPIOB时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);           //使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);            //使能SPI1时钟
    
    //GPIOFB3,4,5IO口初始化设置
    GPIO_InitStructure.GPIO_Pin = Flash_CLK_Pin|Flash_MISO_Pin|Flash_SIMO_Pin; //PB3~5复用功能输出	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                    //复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;              //100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                    //上拉
    GPIO_Init(Flash_SPI_Port, &GPIO_InitStructure);                          //初始化IO口

    GPIO_InitStructure.GPIO_Pin = Flash_CS_Pin; //PG8
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                   //输出功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;              //100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                    //上拉
    GPIO_Init(Flash_CS_Port, &GPIO_InitStructure);                          //初始化IO口
        
    GPIO_PinAFConfig(Flash_SPI_Port,GPIO_PinSource3,GPIO_AF_SPI1);           //PB3复用为 SPI1
    GPIO_PinAFConfig(Flash_SPI_Port,GPIO_PinSource4,GPIO_AF_SPI1);           //PB4复用为 SPI1
    GPIO_PinAFConfig(Flash_SPI_Port,GPIO_PinSource5,GPIO_AF_SPI1);           //PB5复用为 SPI1

    //SPI口初始化
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);             //复位SPI1
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);            //停止复位SPI1

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;          //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                        //设置SPI工作模式:设置为主SPI
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                    //设置SPI的数据大小:SPI发送接收8位帧结构
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		                            //串行同步时钟的空闲状态为高电平
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	                            //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                            //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;        //定义波特率预分频的值:波特率预分频值为256
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                        //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI_InitStructure.SPI_CRCPolynomial = 7;	                                //CRC值计算的多项式
    SPI_Init(SPI1, &SPI_InitStructure);                                         //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

    SPI_Cmd(SPI1, ENABLE);    //使能SPI外设
}

void SPI1_Setclock(u8 SPI_Prescaler)
{
	SPI1->CR1&=0XFFC7;                              //先将bit3-5清零 
	SPI1->CR1|=SPI_Prescaler;	                    //设置SPI1速度 
	SPI_Cmd(SPI1,ENABLE);                           //使能SPI1
}

uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{
	uint8_t i;

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
    {
        i++;
        if(i > 200)
            return 0;
    }

    SPI_I2S_SendData(SPI1, TxData);
    i = 0;

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
    {
        i++;
        if(i > 200)
            return 0;
    }

    return SPI_I2S_ReceiveData(SPI1);
}

/*****************************************************************************
 * @name       :u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
 * @date       :2018-08-09 
 * @function   :Write a byte of data using STM32's hardware SPI
 * @parameters :SPIx: SPI type,x for 1,2,3
                Byte:Data to be written
 * @retvalue   :Data received by the bus
******************************************************************************/
uint8_t SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte)
{
	while((SPIx->SR&SPI_I2S_FLAG_TXE)==RESET);		//等待发送区空	  
	SPIx->DR=Byte;	 	//发送一个byte   
	while((SPIx->SR&SPI_I2S_FLAG_RXNE)==RESET);//等待接收完一个byte  
	return SPIx->DR;          	     //返回收到的数据			
} 

/*****************************************************************************
 * @name       :void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
 * @date       :2018-08-09 
 * @function   :Set hardware SPI Speed
 * @parameters :SPIx: SPI type,x for 1,2,3
                SpeedSet:0-high speed
												 1-low speed
 * @retvalue   :None
******************************************************************************/
void SPI_SetSpeed(SPI_TypeDef* SPIx,u8 SpeedSet)
{
	SPIx->CR1&=0XFFC7;
	if(SpeedSet==1)//高速
	{
		SPIx->CR1|=SPI_BaudRatePrescaler_2;//Fsck=Fpclk/2	
	}
	else//低速
	{
		SPIx->CR1|=SPI_BaudRatePrescaler_16; //Fsck=Fpclk/32
	}
	SPIx->CR1|=1<<6; //SPI设备使能
} 

