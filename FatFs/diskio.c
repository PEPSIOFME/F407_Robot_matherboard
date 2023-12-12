/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "flash.h"

#define sFLASH_ID         0xef17
// #include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
// #include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
// #include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module */

/* Definitions of physical drive number for each drive */
// #define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
// #define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
// #define USB		2	/* Example: Map USB MSD to physical drive 2 */
#define SD_CARD 			0 			//SD 卡,卷标为 0
#define SPI_FLASH         	1
#define FLASH_SECTOR_SIZE 	512

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS status = STA_NOINIT;             // 设备状态   

    switch(pdrv)
    {
	case SPI_FLASH:
	    if(SPI_Flash_ReadID() == sFLASH_ID)
	    {
	        status = 0;                  // 设备ID读取成功
	    }
	    else
	    {
		status = STA_NOINIT;         // 设备ID读取失败
	    }
	    break;

	default:
	    status = STA_NOINIT;
    }

    return status;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS status = STA_NOINIT;

	uint16_t i = 500;

	switch(pdrv)
    {
    case SPI_FLASH:
	    Flash_SPI_Init();
	    while(i--);
	    SPI_Flash_WAKEUP();              // 唤醒SPI FLASH
	    status = disk_status(SPI_FLASH);

	    break;

	default: 
	    status = STA_NOINIT;
    }
	return status;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT status = RES_PARERR;

	switch(pdrv)
    {
	case SPI_FLASH:
            sector += 512;                                     // 偏离512个扇区
            SPI_Flash_Read(buff, sector<<12, count<<12); // 左移12位，即乘以2^12
            status = RES_OK;
	    break;

	default:
	    status = RES_PARERR;
	}

	return status;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT status = RES_PARERR;
    uint32_t write_addr;

    switch(pdrv)
    {
	case SPI_FLASH:
        sector += 512;
	    write_addr = sector<<12;
	    SPI_Flash_Erase_Sector(write_addr);                 //写入前先擦除扇区
	    SPI_Flash_Write_NoCheck((u8 *)buff, sector<<12, count<<12);
	    status = RES_OK;
	    break;

	default:
	    status = RES_PARERR;
    }

    return status;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT status = RES_PARERR;

    switch (pdrv) 
    {
	case SPI_FLASH:
	    switch(cmd)
            {
	        /* 扇区数量：14MB*1024*1024/4096=1536 */
		case GET_SECTOR_COUNT:
		    *(DWORD *)buff = 3584;
		    break;

                /* 扇区大小 */
		case GET_SECTOR_SIZE:
		    *(WORD *) buff = 4096;
		    break;

                /* 擦除的扇区个数 */
		case GET_BLOCK_SIZE:
		    *(DWORD *)buff = 1;
		    break;
	    }
	    status = RES_OK;
	    break;

        default:
	    status = RES_PARERR;
    }

    return status;
}
#endif
