#include "main.h"

uint8_t a = 0, b = 0;
uint8_t p[2] = {99, 99};
int main(void)
{
    //float t=0;
    delay_init();
    usart1_Init();
    IIC_GPIO_Init();

    delay_ms(10);
    Init_MPU9250();
    // LCD_Init();
    // LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
    while (1)
    {
        // USART1_SendData(p[0]);
        // USART1_SendData(p[1]);

        READ_MPU9250_ACCEL();      //加速度
        DATA_printf(TX_DATA, T_X); //转换X轴数据到数组
        Send_data();               //发送X轴数
        USART1_SendData(0X0D);     //换行
        USART1_SendData(0X0A);     //回车
        DATA_printf(TX_DATA, T_Y); //转换Y轴数据到数组
        Send_data();               //发送Y轴数
        USART1_SendData(0X0D);     //换行
        USART1_SendData(0X0A);     //回车
        DATA_printf(TX_DATA, T_Z); //转换Z轴数据到数组
        Send_data();               //发送Z轴数

        USART1_SendData(0X0D); //换行
        USART1_SendData(0X0A); //回车

        READ_MPU9250_GYRO();       //陀螺
        DATA_printf(TX_DATA, T_X); //转换X轴数据到数组
        Send_data();               //发送X轴数
        USART1_SendData(0X0D);     //换行
        USART1_SendData(0X0A);     //回车
        DATA_printf(TX_DATA, T_Y); //转换Y轴数据到数组
        Send_data();               //发送Y轴数
        USART1_SendData(0X0D);     //换行
        USART1_SendData(0X0A);     //回车
        DATA_printf(TX_DATA, T_Z); //转换Z轴数据到数组
        Send_data();               //发送Z轴数

        USART1_SendData(0X0D); //换行
        USART1_SendData(0X0A); //回车

        // READ_MPU9250_MAG();	        //磁场
        // DATA_printf(TX_DATA,T_X);   //转换X轴数据到数组
        // Send_data();			//发送X轴数
        // DATA_printf(TX_DATA,T_Y);   //转换Y轴数据到数组
        // Send_data();			//发送Y轴数
        // DATA_printf(TX_DATA,T_Z);   //转换Z轴数据到数组
        // Send_data();			//发送Z轴数

        //        DATA_printf(TX_DATA,T_T);   //转换温度数据到数组
        //        Send_data('T');			    //发送温度数据

        // USART1_SendData(0X0D);	    //换行
        // USART1_SendData(0X0A);	    //回车
        delay_ms(500); //延时

        // LCD_ShowChinese(40,0,"中景园电子",RED,WHITE,32,0);
        // LCD_ShowString(10,33,"M, X:",RED,WHITE,32,0);
        // LCD_ShowIntNum(106,33,LCD_W,3,RED,WHITE,32);
        // LCD_ShowString(10,66,"LCD_H:",RED,WHITE,32,0);
        // LCD_ShowIntNum(106,66,LCD_H,3,RED,WHITE,32);
        // LCD_ShowFloatNum1(10,99,t,4,RED,WHITE,32);
        // t+=0.11;
        // LCD_ShowPicture(160,95,40,40,gImage_1);
    }
}
