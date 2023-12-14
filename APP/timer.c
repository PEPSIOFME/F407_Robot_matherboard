#include "timer.h"

uint8_t i = 0;
uint8_t flag = 5;

void TIMER2_Init(u16 arr, u16 psc) //TIM2配置，arr为重加载值，psc为预分频系数
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_Period = arr;                     //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             //根据指定的参数初始化TIMx的时间基数单位

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;           //选择TIM2的IRQ通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //IRQ通道优先级=0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能IRQ通道
    NVIC_Init(&NVIC_InitStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update); //清除标志位，以免一启用中断后立即产生中断

    TIM_ARRPreloadConfig(TIM2, DISABLE);       //禁止ARR预装载缓冲器
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //使能TIM2溢出中断
    TIM_Cmd(TIM2, ENABLE);                     //使能TIM2 总中断
}

// void TIM2_IRQHandler(void)
// {
//     if(i <= 5)
//     {
//         GPIO_SetBits(GPIOD, GPIO_Pin_1);
//         i++;
//     }
//     else if(i <= flag)
//     {
//         GPIO_SetBits(GPIOD, GPIO_Pin_1);
//         i++;
//     }
//     else if(i <= 199)
//     {
//         GPIO_ResetBits(GPIOD, GPIO_Pin_1);
//         i++;
//     }
//     else
//     {
//         i = 0;
//     }
    
//     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
// }

//定时器2中断服务函数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{

	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}
