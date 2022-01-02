#include "main.h"

int main(void)
{
    uint8_t i[2]={0x05,0x05},a,adds = 0x12;

    delay_init(168);
    IIC_GPIO_Init();
    //delay_ms(10);
    adds <<= 1;
    IIC_Begin();

    IIC_WriteByte(adds);
    for(a = 0; a < 2; a++)
    {
        IIC_WriteByte(i[a]);
    }
    IIC_Stop();

    
}


