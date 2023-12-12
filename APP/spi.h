#include "stm32f4xx.h"

#define Flash_CS_Port       GPIOG
#define Flash_SPI_Port      GPIOB

#define Flash_CS_Pin        GPIO_Pin_8
#define Flash_CLK_Pin       GPIO_Pin_3
#define Flash_MISO_Pin      GPIO_Pin_4
#define Flash_SIMO_Pin      GPIO_Pin_5

#define Flash_CS_High 	GPIO_SetBits(GPIOG, GPIO_Pin_8)
#define Flash_CS_Low    GPIO_ResetBits(GPIOG, GPIO_Pin_8)


void Flash_SPI_Init(void);
void SPI1_Setclock(uint8_t SPI_Prescaler);
uint8_t SPI1_ReadWriteByte(uint8_t TxData);

uint8_t SPI_WriteByte(SPI_TypeDef* SPIx,uint8_t Byte);
void SPI_SetSpeed(SPI_TypeDef* SPIx,uint8_t SpeedSet);

