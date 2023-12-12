#ifndef __KEY_H
#define __KEY_H

#include "main.h"

//按键IO端口定义
#define KEY0() 		PFin(9)   
#define KEY1() 		PFin(8)		
#define KEY2() 		PFin(7)		
#define KEY3() 	    PFin(6)

//按键值定义
#define KEY0_DATA   1
#define KEY1_DATA	2
#define KEY2_DATA	3
#define KEY3_DATA   4

#endif