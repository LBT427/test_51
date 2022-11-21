/*
 * @Author: liubotao
 * @Date: 2022-11-18 00:32:28
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-21 10:09:30
 * @FilePath: \test_51\BSP\bsp.c
 * @Description: 中断和驱动初始化
 *
 */
#include "bsp.h"

static void task10ms();

void bspInit()              //硬件初始化
{
    bsp_InitKeyVar();       //按键初始化
    initLcd1602();          //lcd初始化
    timer0Init();           //中断初始化
}

void timer0Init()           //1ms中断初始化
{
    TMOD |= 0X10;

    TH1 = 0XFC; 
    TL1 = 0X18;
    ET1 = 1;
    EA = 1;
    TR1 = 1;
}

void Timer1() interrupt 3   //中断服务函数
{
    static int time_num;    //中断次数，一次10ms
    TH1 = 0XFC; 
    TL1 = 0X18;
    time_num++;
    if (time_num == 10)     // 10ms
    {
        time_num = 0;
        task10ms();
    }
}

static void task10ms()      //10ms任务
{
    // matrixKeyScan_1();
    // matrixKeyScan_2();
    matrixKeyScan_3();
    bsp_KeyScan();
}

