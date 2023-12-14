#include "key.h"

uint8_t  keydown_data=0x00;    //按键按下后就返回的值
uint8_t  keyup_data=0x00;      //按键抬起返回值
uint16_t  key_time=0x00;       //按键按下之后的时间计数，该值乘以扫描一次按键函数的时间就等于按键按下的时间

uint8_t  key_tem=0x00;         //长按的按键值与按键扫描程序过渡变量
uint8_t  key_bak=0x00;         //按键扫描程序过渡变量

void KEY4_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;


    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;       // 普通输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100M
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure); // 初始化
}

uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0()==0||KEY1()==0||KEY2()==0||KEY3()==0))
	{
		delay_ms(5);//去抖动 
        printf("ok!\n");
		key_up=0;
		if(KEY0()==0)return 1;
		else if(KEY1()==0)return 2;
		else if(KEY2()==0)return 3;
		else if(KEY3()==0)return 4;
	}else if(KEY0()==1&&KEY1()==1&&KEY2()==1&&KEY3()==1)key_up=1; 	    
 	return 0;// 无按键按下
}


