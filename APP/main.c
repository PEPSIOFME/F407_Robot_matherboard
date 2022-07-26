#include "main.h"



int main(void)
{
    uint32_t data;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
    MOTOR_Init();
    MOTOR_PWM_Init(999, 83);
    TIM_SetCompare1(TIM2, 500);
    TIM_SetCompare2(TIM2, 500);
    // HALL_Init(0XFFFF, 0);
    // while(1)
    // {
    //     data = N * 65536 + TIM5->CNT;
    // }

    // IIC_GPIO_Init();
    // //printf("xxx0\r\n");
    // usart1_Init();
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



