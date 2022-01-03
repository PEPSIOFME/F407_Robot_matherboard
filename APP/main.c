#include "main.h"

uint8_t a=3,b=3;
int main(void)
{
    float t=0;
    delay_init();
    usart1_Init();
//    IIC_GPIO_Init();
//    uint8_t adds = 0x07,data = 0x11;
//    adds <<= 1;
//    IIC_Begin();
//    IIC_WriteByte(adds);
//    if(IIC_WaitAck())
//    {
//        a = 1;
//    }
//    IIC_WriteByte(data);
//    if(IIC_WaitAck())
//    {
//        b = 1;
//    }
//    IIC_Stop();


    // delay_ms(10);
    // Init_MPU9250();
     LCD_Init();
     LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
    while(1)
    {
		// delay_ms(2000);
        // USART1_SendData(a);
        // USART1_SendData(b);

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
       DATA_printf(TX_DATA,T_T);   //转换温度数据到数组
       Send_data('T');			    //发送温度数据
       */
       USART1_SendData(0X0D);	    //换行
       USART1_SendData(0X0A);	    //回车
       delay_ms(10);				//延时
        
        LCD_ShowChinese(40,0,"中景园电子",RED,WHITE,32,0);
		LCD_ShowString(10,33,"M, X:",RED,WHITE,32,0);
		LCD_ShowIntNum(106,33,LCD_W,3,RED,WHITE,32);
		LCD_ShowString(10,66,"LCD_H:",RED,WHITE,32,0);
		LCD_ShowIntNum(106,66,LCD_H,3,RED,WHITE,32);
		LCD_ShowFloatNum1(10,99,t,4,RED,WHITE,32);
		t+=0.11;
		LCD_ShowPicture(160,95,40,40,gImage_1);
    }

}


