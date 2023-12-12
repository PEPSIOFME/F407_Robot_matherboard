#include "stm32f4xx.h"
#include "spi.h"
#include "common.h"

/* Winbond SPIFalsh Instruction List */
#define W25Q_WriteEnable         0x06
#define W25Q_WriteDisable        0x04
#define W25Q_ReadStatusReg1      0x05
#define W25Q_WriteStatusReg1     0x01
#define W25Q_ReadStatusReg2      0x35
#define W25Q_WriteStatusReg2     0x31
#define W25Q_ReadStatusReg3      0x15
#define W25Q_WriteStatusReg3     0x11
#define W25Q_ReadData            0x03
#define W25Q_FastReadData        0x0B
#define W25Q_FastReadDual        0x3B
#define W25Q_PageProgram         0x02
#define W25Q_Block64KErase       0xD8
#define W25Q_Block32KErase       0x52
#define W25Q_SectorErase         0x20
#define W25Q_ChipErase           0xC7
#define W25Q_PowerDown           0xB9
#define W25Q_ReleasePowerDown    0xAB
#define W25Q_DeviceID            0xAB
#define W25Q_ManufactDeviceID    0x90
#define W25Q_JedecDeviceID       0x9F


void SPI_FLASH_WriteSR1(uint8_t sr);
void SPI_FLASH_WriteSR2(uint8_t sr);
void SPI_FLASH_WriteSR3(uint8_t sr);
uint8_t SPI_Flash_ReadSR1(void);
uint8_t SPI_Flash_ReadSR2(void);
uint8_t SPI_Flash_ReadSR3(void);

void SPI_FLASH_Write_Enable(void);
void SPI_FLASH_Write_Disable(void);
uint16_t SPI_Flash_ReadID(void);

void SPI_Flash_WAKEUP(void);
void SPI_Flash_PowerDown(void);

void SPI_Flash_Read(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t size);
void SPI_Flash_Read_FAST(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t size);
void SPI_Flash_Write_Page(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t size);
void SPI_Flash_Write_NoCheck(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t size);
void SPI_Flash_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t size);
void SPI_Flash_Erase_Chip(void);

void SPI_Flash_Erase_Sector(uint32_t Dst_Addr);
void SPI_Flash_Erase_Block(uint32_t Dst_Addr, uint8_t Block_xxK);


