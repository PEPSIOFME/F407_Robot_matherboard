#include "test.h"

void CH446_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOB, ENABLE);       //使能PORT,PORTG时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4; //P1:X0, P2:DAT, P3:CS, P4:STB
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                                    //普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                                   //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;                               //100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                                     //上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);                                           //初始化
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                                        //P0:Y0 IN
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                                     //普通输入模式
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                           //初始化
    GPIO_ResetBits(GPIOD, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
}

void SerSet446(uint8_t addr, bool swon)
{
    uint8_t i;
    for (i = 0; i < 7; i++)
    {
        if (addr & 0x40)
        {
            GPIO_SetBits(GPIOD, GPIO_Pin_2); //R32_PD_OUT |= PD_CH446_DAT;
        }
        else
        {
            GPIO_ResetBits(GPIOD, GPIO_Pin_2); //R32_PD_OUT &= ~PD_CH446_DAT;
        }

        delay_us(40);
        GPIO_ResetBits(GPIOD, GPIO_Pin_3); //R32_PA_CLR = PA_CH446_CS;
        delay_us(60);
        addr <<= 1;
        delay_us(20);
        GPIO_SetBits(GPIOD, GPIO_Pin_3); //R32_PA_OUT |= PA_CH446_CS;
        delay_us(20);
    }
    if (swon)
        GPIO_SetBits(GPIOD, GPIO_Pin_2); //R32_PD_OUT |= PD_CH446_DAT;
    else
        GPIO_ResetBits(GPIOD, GPIO_Pin_2); //R32_PD_OUT &= ~PD_CH446_DAT;
    delay_us(20);
    GPIO_SetBits(GPIOD, GPIO_Pin_3);   //R32_PA_OUT |= PA_CH446_CS;
    GPIO_ResetBits(GPIOD, GPIO_Pin_4); //R32_PA_CLR = PA_CH446_STB;
    GPIO_SetBits(GPIOD, GPIO_Pin_4);   //R32_PA_OUT |= PA_CH446_STB;
    delay_us(20);
    GPIO_ResetBits(GPIOD, GPIO_Pin_4); //R32_PA_CLR = PA_CH446_STB;
    GPIO_ResetBits(GPIOD, GPIO_Pin_3); //R32_PA_CLR = PA_CH446_CS;
}



