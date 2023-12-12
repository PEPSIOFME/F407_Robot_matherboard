#include "key.h"

void KEY4_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;       // 普通输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100M
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure); // 初始化

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // 使能SYSCFG时钟

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource6); // PF6 连接到中断线6
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource7); // PF7 连接到中断线7
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8); // PF8 连接到中断线8
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource9); // PF9 连接到中断线9

    // 配置外部中断线 EXTI_Line6,7,8,9
    EXTI_InitStructure.EXTI_Line = EXTI_Line6 | EXTI_Line7 | EXTI_Line8 | EXTI_Line9;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     // 中断事件
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;               // 中断线使能
    EXTI_Init(&EXTI_InitStructure);                         // 配置

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;           // 外部中断5-9  刚好 PF6-9 在 EXTI9_5_IRQn 里面
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00; // 抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;        // 子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              // 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);                              // 配置
}

//外部中断线5-9服务程序
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);	//消抖
	
	if(KEY0()==0)	  //当按键按下后就是IO从高电平变为低电平触发外部中断
	{

		EXTI_ClearITPendingBit(EXTI_Line9);  //清除LINE9上的中断标志位  KEY0 对应IO口PF9
	}		

	if(KEY1()==0)	 //当按键按下后就是IO从高电平变为低电平触发外部中断
	{

		EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE8上的中断标志位  KEY1 对应IO口PF8
	}	
	
	if(KEY2()==0)	 //当按键按下后就是IO从高电平变为低电平触发外部中断
	{

		EXTI_ClearITPendingBit(EXTI_Line7);  //清除LINE7上的中断标志位  KEY2 对应IO口PF7
	}	
	
	if(KEY3()==0)	 //当按键按下后就是IO从高电平变为低电平触发外部中断
	{

		EXTI_ClearITPendingBit(EXTI_Line6);  //清除LINE6上的中断标志位  KEY3 对应IO口PF6
	}
	
}	
