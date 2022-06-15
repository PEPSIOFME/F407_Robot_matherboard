#include "servo.h"

#define PCA9685_adrr 0x80
#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE


#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD


void PCA9685_write(uint8_t reg,uint8_t data)
{
    IIC_Begin();
    IIC_WriteByte(PCA9685_adrr);
    IIC_WaitAck();
    IIC_WriteByte(reg);
    IIC_WaitAck();
    IIC_WriteByte(data);
    IIC_WaitAck();
    IIC_Stop();
}

uint8_t PCA9685_read(uint8_t reg)
{
    uint8_t res;
    IIC_Begin();
    IIC_WriteByte(PCA9685_adrr);
    IIC_WaitAck();
    IIC_WriteByte(reg);
    IIC_WaitAck();    
    IIC_Begin();                
    IIC_WriteByte(PCA9685_adrr|0X01);
    IIC_WaitAck();
    res=IIC_ReadByte(0);       
    IIC_Stop();             
    return res;  
}

void setPWMFreq(uint8_t freq)
{
   uint8_t prescale,oldmode,newmode;
   uint32_t prescaleval;
   prescaleval = 25000000.0/(4096*freq*0.915);
   prescale = (uint8_t)floor(prescaleval+0.5)-1;

   oldmode = PCA9685_read(PCA9685_MODE1);
   newmode = (oldmode&0x7F) | 0x10; // sleep
   PCA9685_write(PCA9685_MODE1, newmode); // go to sleep
   PCA9685_write(PCA9685_PRESCALE, prescale); // set the prescaler
   PCA9685_write(PCA9685_MODE1, oldmode);
   delay_ms(5);
   PCA9685_write(PCA9685_MODE1, oldmode | 0xa1); 
}

uint16_t calculate_PWM(uint8_t angle)
{
    return (uint16_t)(204.8*(0.5+angle*1.0/90));
}

void setPWM(uint8_t num, uint16_t on, uint16_t off) 
{
    PCA9685_write(LED0_ON_L+4*num,on);
    PCA9685_write(LED0_ON_H+4*num,on>>8);
    PCA9685_write(LED0_OFF_L+4*num,off);
    PCA9685_write(LED0_OFF_H+4*num,off>>8);
}

void PCA9685_Reset(void)
{
    IIC_GPIO_Init();
    PCA9685_write(PCA9685_MODE1, 0x0);
}

void reset_reboot(void)
{
    uint16_t pwm = calculate_PWM(30);
//    setPWM(0x0,0,pwm);
//    delay_ms(1);
    setPWM(0x1,0,pwm);
    delay_ms(1);
	pwm = calculate_PWM(0);
    setPWM(0x2,0,pwm);
//    delay_ms(1);
//    setPWM(0x3,0,pwm);
//    delay_ms(1);
//    setPWM(0x4,0,pwm);
//    delay_ms(1);
//    setPWM(0x5,0,pwm);
//    delay_ms(1);
//    setPWM(0x6,0,pwm);
//    delay_ms(1);
//    setPWM(0x7,0,pwm);
//    delay_ms(1);
//    setPWM(0x8,0,pwm);
//    delay_ms(1);
//    setPWM(0x9,0,pwm);
//    delay_ms(1);
//    setPWM(0x10,0,pwm);
//    delay_ms(1);
//    setPWM(0x11,0,pwm);
//    delay_ms(1);
//    setPWM(0x12,0,pwm);
//    delay_ms(1);
}
