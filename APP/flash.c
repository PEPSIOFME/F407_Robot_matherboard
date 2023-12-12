#include "flash.h"

uint8_t       SPI_FLASH_BUF[4096];

void SPI_FLASH_WriteSR1(uint8_t sr)
{
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_WriteStatusReg1);
    SPI1_ReadWriteByte(sr);
    Flash_CS_High;
}

void SPI_FLASH_WriteSR2(uint8_t sr)
{
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_WriteStatusReg2);
    SPI1_ReadWriteByte(sr);
    Flash_CS_High;
}

void SPI_FLASH_WriteSR3(uint8_t sr)
{
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_WriteStatusReg3);
    SPI1_ReadWriteByte(sr);
    Flash_CS_High;
}

uint8_t SPI_Flash_ReadSR1(void)
{
    uint8_t byte = 0;

    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_ReadStatusReg1);
    byte = SPI1_ReadWriteByte(0Xff);
    Flash_CS_High;

    return byte;
}

uint8_t SPI_Flash_ReadSR2(void)
{
    uint8_t byte = 0;

    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_ReadStatusReg2);
    byte = SPI1_ReadWriteByte(0Xff);
    Flash_CS_High;

    return byte;
}

uint8_t SPI_Flash_ReadSR3(void)
{
    uint8_t byte = 0;

    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_ReadStatusReg3);
    byte = SPI1_ReadWriteByte(0Xff);
    Flash_CS_High;

    return byte;
}

void SPI_Flash_Wait_Busy(void)
{
    while((SPI_Flash_ReadSR1() & 0x01) == 0x01);
}

void SPI_FLASH_Write_Enable(void)
{
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_WriteEnable);
    Flash_CS_High;
}

void SPI_FLASH_Write_Disable(void)
{
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_WriteDisable);
    Flash_CS_High;
}

uint16_t SPI_Flash_ReadID(void)
{
    uint16_t Temp = 0;

    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_ManufactDeviceID);
    SPI1_ReadWriteByte(0x00);
    SPI1_ReadWriteByte(0x00);
    SPI1_ReadWriteByte(0x00);
    Temp |= SPI1_ReadWriteByte(0xFF) << 8;
    Temp |= SPI1_ReadWriteByte(0xFF);
    Flash_CS_High;

    return Temp;
}

void SPI_Flash_WAKEUP(void)
{
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_ReleasePowerDown);
    Flash_CS_High;
    delay_us(3);
}

void SPI_Flash_PowerDown(void)
{
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_PowerDown);
    Flash_CS_High;
    delay_us(3);
}


/*********************************************************************
 * @fn      SPI_Flash_Read
 *
 * @brief   Read data from flash.
 *
 * @param   pBuffer -
 *          ReadAddr -Initial address(24bit).
 *          size - Data length.
 *
 * @return  none
 */
void SPI_Flash_Read(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t size)
{
    uint16_t i;

    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_ReadData);
    SPI1_ReadWriteByte((uint8_t)((ReadAddr) >> 16));
    SPI1_ReadWriteByte((uint8_t)((ReadAddr) >> 8));
    SPI1_ReadWriteByte((uint8_t)ReadAddr);

    for(i = 0; i < size; i++)
    {
        pBuffer[i] = SPI1_ReadWriteByte(0XFF);
    }

    Flash_CS_High;
}

/*********************************************************************
 * @fn      SPI_Flash_Read_FAST
 *
 * @brief   Read data from flash.
 *
 * @param   pBuffer -
 *          ReadAddr -Initial address(24bit).
 *          size - Data length.
 *
 * @return  none
 */
void SPI_Flash_Read_FAST(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t size)
{
    uint16_t i;

    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_FastReadData);
    SPI1_ReadWriteByte((uint8_t)((ReadAddr) >> 16));
    SPI1_ReadWriteByte((uint8_t)((ReadAddr) >> 8));
    SPI1_ReadWriteByte((uint8_t)ReadAddr);

    //Dummy Clocks
    SPI1_ReadWriteByte(0x00);


    for(i = 0; i < size; i++)
    {
        pBuffer[i] = SPI1_ReadWriteByte(0XFF);
    }

    Flash_CS_High;
}

/*********************************************************************
 * @fn      SPI_Flash_Write_Page
 *
 * @brief   Write data by one page.
 *
 * @param   pBuffer -
 *          WriteAddr - Initial address(24bit).
 *          size - Data length.
 *
 * @return  none
 */
void SPI_Flash_Write_Page(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t size)
{
    uint16_t i;

    SPI_FLASH_Write_Enable();
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_PageProgram);
    SPI1_ReadWriteByte((uint8_t)((WriteAddr) >> 16));
    SPI1_ReadWriteByte((uint8_t)((WriteAddr) >> 8));
    SPI1_ReadWriteByte((uint8_t)WriteAddr);

    for(i = 0; i < size; i++)
    {
        SPI1_ReadWriteByte(pBuffer[i]);
    }

    Flash_CS_High;
    SPI_Flash_Wait_Busy();
}

/*********************************************************************
 * @fn      SPI_Flash_Write_NoCheck
 *
 * @brief   Write data to flash.(need Erase)
 *          All data in address rang is 0xFF.
 *
 * @param   pBuffer -
 *          WriteAddr - Initial address(24bit).
 *          size - Data length.
 *
 * @return  none
 */
void SPI_Flash_Write_NoCheck(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t size)
{
    uint16_t pageremain;

    pageremain = 256 - WriteAddr % 256;

    if(size <= pageremain)
        pageremain = size;

    while(1)
    {
        SPI_Flash_Write_Page(pBuffer, WriteAddr, pageremain);

        if(size == pageremain)
        {
            break;
        }
        else
        {
            pBuffer += pageremain;
            WriteAddr += pageremain;
            size -= pageremain;

            if(size > 256)
                pageremain = 256;
            else
                pageremain = size;
        }
    }
}

/*********************************************************************
 * @fn      SPI_Flash_Write
 *
 * @brief   Write data to flash.(no need Erase)
 *
 * @param   pBuffer -
 *          WriteAddr - Initial address(24bit).
 *          size - Data length.
 *
 * @return  none
 */
void SPI_Flash_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t size)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;

    secpos = WriteAddr / 4096;
    secoff = WriteAddr % 4096;
    secremain = 4096 - secoff;

    if(size <= secremain)
        secremain = size;

    while(1)
    {
        SPI_Flash_Read(SPI_FLASH_BUF, secpos * 4096, 4096);

        for(i = 0; i < secremain; i++)
        {
            if(SPI_FLASH_BUF[secoff + i] != 0XFF)
                break;
        }

        if(i < secremain)
        {
            SPI_Flash_Erase_Sector(secpos);

            for(i = 0; i < secremain; i++)
            {
                SPI_FLASH_BUF[i + secoff] = pBuffer[i];
            }

            SPI_Flash_Write_NoCheck(SPI_FLASH_BUF, secpos * 4096, 4096);
        }
        else
        {
            SPI_Flash_Write_NoCheck(pBuffer, WriteAddr, secremain);
        }

        if(size == secremain)
        {
            break;
        }
        else
        {
            secpos++;
            secoff = 0;

            pBuffer += secremain;
            WriteAddr += secremain;
            size -= secremain;

            if(size > 4096)
            {
                secremain = 4096;
            }
            else
            {
                secremain = size;
            }
        }
    }
}

/*********************************************************************
 * @fn      SPI_Flash_Erase_Chip
 *
 * @brief   Erase all FLASH pages.
 *
 * @return  none
 */
void SPI_Flash_Erase_Chip(void)
{
    SPI_FLASH_Write_Enable();
    SPI_Flash_Wait_Busy();
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_ChipErase);
    Flash_CS_High;
    SPI_Flash_Wait_Busy();
}

/*********************************************************************
 * @fn      SPI_Flash_Erase_Sector
 *
 * @brief   Erase one sector(4Kbyte).
 *
 * @param   Dst_Addr - 0 ！！ 2047
 *
 * @return  none
 */
void SPI_Flash_Erase_Sector(uint32_t Dst_Addr)
{
    Dst_Addr *= 4096;
    SPI_FLASH_Write_Enable();
    SPI_Flash_Wait_Busy();
    Flash_CS_Low;
    SPI1_ReadWriteByte(W25Q_SectorErase);
    SPI1_ReadWriteByte((uint8_t)((Dst_Addr) >> 16));
    SPI1_ReadWriteByte((uint8_t)((Dst_Addr) >> 8));
    SPI1_ReadWriteByte((uint8_t)Dst_Addr);
    Flash_CS_High;
    SPI_Flash_Wait_Busy();
}

void SPI_Flash_Erase_Block(uint32_t Dst_Addr, uint8_t Block_xxK)
{
    if(Block_xxK)   Dst_Addr *= (1024*64);
    else            Dst_Addr *= (1024*32);
    SPI_FLASH_Write_Enable();
    SPI_Flash_Wait_Busy();
    Flash_CS_Low;
    if(Block_xxK)   SPI1_ReadWriteByte(W25Q_Block64KErase);
    else            SPI1_ReadWriteByte(W25Q_Block32KErase);
    
    SPI1_ReadWriteByte((uint8_t)((Dst_Addr) >> 16));
    SPI1_ReadWriteByte((uint8_t)((Dst_Addr) >> 8));
    SPI1_ReadWriteByte((uint8_t)Dst_Addr);
    Flash_CS_High;
    SPI_Flash_Wait_Busy();
}
