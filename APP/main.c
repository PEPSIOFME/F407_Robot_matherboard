#include "main.h"

int main(void)
{
    delay_init();
    IIC_GPIO_Init();
    IIC_Begin();
    // IIC_Stop();
}


