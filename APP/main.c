#include "main.h"

int main(void)
{
    delay_init();
    usart1_Init();
    IIC_GPIO_Init();
    delay_ms(10);
    Init_MPU9250();
    while(1)
    {
        READ_MPU9250_ACCEL();       //加速度
        DATA_printf(TX_DATA,T_X);   //转换X轴数据到数组
        Send_data('A','X');			//发送X轴数
        DATA_printf(TX_DATA,T_Y);   //转换Y轴数据到数组
        Send_data('A','Y');			//发送Y轴数
        DATA_printf(TX_DATA,T_Z);   //转换Z轴数据到数组
        Send_data('A','Z');			//发送Z轴数
        
        READ_MPU9250_GYRO();        //陀螺
        DATA_printf(TX_DATA,T_X);   //转换X轴数据到数组
        Send_data('G','X');			//发送X轴数
        DATA_printf(TX_DATA,T_Y);   //转换Y轴数据到数组
        Send_data('G','Y');			//发送Y轴数
        DATA_printf(TX_DATA,T_Z);   //转换Z轴数据到数组
        Send_data('G','Z');			//发送Z轴数
        
        READ_MPU9250_MAG();	        //磁场
        DATA_printf(TX_DATA,T_X);   //转换X轴数据到数组
        Send_data('M','X');			//发送X轴数
        DATA_printf(TX_DATA,T_Y);   //转换Y轴数据到数组
        Send_data('M','Y');			//发送Y轴数
        DATA_printf(TX_DATA,T_Z);   //转换Z轴数据到数组
        Send_data('M','Z');			//发送Z轴数
        /*
        DATA_printf(TX_DATA,T_T);//转换温度数据到数组
        Send_data('T');			 //发送温度数据
        */
        USART1_SendData(0X0D);	 //换行
        USART1_SendData(0X0A);	 //回车
        delay_ms(10);				 //延时
    }

}


