#include "main.h"


int main(void)
{
//    uint32_t data;
    // FATFS *fs; // TF卡文件系统

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
    usart1_Init();
    printf("ok!\n");
    delay_init();
    LCD_Init();	   //液晶屏初始化
    lv_init();
    lv_port_disp_init();
    lv_demo_widgets();
    // Flash_SPI_Init();
    // SPI_Flash_Erase_Chip();
    // printf("id = %x\n", SPI_Flash_ReadID());
    while(1)
    {
        lv_task_handler();
        delay_ms(1);
    }
    while(1)
    {
        main_test(); 		//测试主界面
		Test_Read();        //读ID和GRAM测试
		Test_Color();  		//简单刷屏填充测试
		Test_FillRec();		//GUI矩形绘图测试
		Test_Circle(); 		//GUI画圆测试
		Test_Triangle();    //GUI三角形绘图测试
		English_Font_test();//英文字体示例测试
		Chinese_Font_test();//中文字体示例测试
		Pic_test();			//图片显示示例测试
		Test_Dynamic_Num(); //动态数字显示
		Rotate_Test();   //旋转显示测试
    }
    // printf("ID = %x\n",SPI_Flash_ReadID());
    // Memory_Init(INSRAM); // 初始化内部内存池
    // fs = (FATFS *)Mem_malloc(INSRAM, sizeof(FATFS)); // 为文件系统分配内存
    // // FATFS fs;                                              // FATFS文件系统结构体对象
    // // FIL fnew;                                              // FIL文件结构体对象
    // FRESULT res_flash;                                     // 文件操作结果结构体对象
    // // UINT fnum;                                             // 文件读写数量
    // // BYTE ReadBuffer[1024] = {0};                           // 读缓冲区
    // // BYTE WriteBuffer[] = "stm32专栏-FatFS测试专用";         // 写缓冲区

    // res_flash = f_mount(fs, "1:", 1);                     // 挂载时会对SPI设备初始化
    // if(res_flash == FR_NO_FILESYSTEM)                      // 判断是否有文件系统，没有则格式化并创建
    // {
    //     printf("FR_NO_FILESYSTEM ...\r\n");
    //     res_flash = f_mkfs("1:", 0, 0);                    // 格式化
    //     // printf("f_mkfs = %d\n", res_flash);
    //     if(res_flash == FR_OK)                             // 格式化成功
    //     {
    //         printf("start system\r\n");
    //         res_flash = f_mount(NULL, "1:", 1);            // 格式化后先取消挂载
    //         res_flash = f_mount(fs, "1:", 1);               // 重新挂载
    //         printf("res_flash = %d\n", res_flash);
    //     }
    //     else
    //     {
    //         printf("system fail\r\n");
    //     while(1);
    //     }
    // }
    // else if(res_flash != FR_OK)
    // {
    //     // printf("FatFS = (%d)\r\n", res_flash);
    //     printf("FatFS = 1\r\n");
    //     while(1);
    // }
    // else
    // {
    //     printf("FatFS = 0\r\n");
    // }

    // while(1);

    // MOTOR_Init();
    // MOTOR_PWM_Init(999, 83);
    // TIM_SetCompare1(TIM2, 500);
    // TIM_SetCompare2(TIM2, 500);
    // HALL_Init(0XFFFF, 0);
    // while(1)
    // {
    //     data = N * 65536 + TIM5->CNT;
    // }

    // IIC_GPIO_Init();
    // //printf("xxx0\r\n");
    
    // delay_init();

    // PCA9685_Reset();
    // setPWMFreq(50);

    // reset_reboot();
    // delay_ms(1000);
    // move();
//     while (1)
//     {
//         printf("ACCEL: ");
//         READ_MPU9250_ACCEL();      //加速度
//         DATA_printf(TX_DATA, T_X); //转换X轴数据到数组
//         Send_data();               //发送X轴数
//         DATA_printf(TX_DATA, T_Y); //转换Y轴数据到数组
//         Send_data();               //发送Y轴数
//         DATA_printf(TX_DATA, T_Z); //转换Z轴数据到数组
//         Send_data();               //发送Z轴数
//         USART1_SendData(0X0D); //换行
//         USART1_SendData(0X0A); //回车

//         printf("GYRO: ");
//         READ_MPU9250_GYRO();       //陀螺
//         DATA_printf(TX_DATA, T_X); //转换X轴数据到数组
//         Send_data();               //发送X轴数
//         DATA_printf(TX_DATA, T_Y); //转换Y轴数据到数组
//         Send_data();               //发送Y轴数
//         DATA_printf(TX_DATA, T_Z); //转换Z轴数据到数组
//         Send_data();               //发送Z轴数
//         USART1_SendData(0X0D); //换行
//         USART1_SendData(0X0A); //回车

//         printf("MAG: ");
//         READ_MPU9250_MAG();	        //磁场
//         DATA_printf(TX_DATA,T_X);   //转换X轴数据到数组
//         Send_data();			//发送X轴数
//         DATA_printf(TX_DATA,T_Y);   //转换Y轴数据到数组
//         Send_data();			//发送Y轴数
//         DATA_printf(TX_DATA,T_Z);   //转换Z轴数据到数组
//         Send_data();			//发送Z轴数

// //        DATA_printf(TX_DATA,T_T);   //转换温度数据到数组
// //        Send_data('T');			    //发送温度数据

//         USART1_SendData(0X0D);	    //换行
//         USART1_SendData(0X0A);	    //回车
//         delay_ms(500); //延时
//     }
}

// void angle(uint8_t a)
// {
//     a /= 9;
//     flag = a;
// }



