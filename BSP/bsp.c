/*
 * @Author: liubotao
 * @Date: 2022-11-18 00:32:28
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-18 02:54:30
 * @FilePath: \test51\BSP\bsp.c
 * @Description: 中断和驱动初始化
 *
 */
#include "bsp.h"

static void task10ms();

void bspInit()
{
    timer0Init();
}

void timer0Init()
{
    TMOD |= 0X10;

    TH1 = 0XFC; //定时1ms
    TL1 = 0X18;
    ET1 = 1;
    EA = 1;
    TR1 = 1;
}

void Timer1() interrupt 3
{
    static int time_num;
    TH1 = 0XFC; //定时1ms
    TL1 = 0X18;
    time_num++;
    if (time_num == 10) // 10ms
    {
        time_num = 0;
        task10ms();
    }
}

static void task10ms()
{
    // matrixKeyScan_1();
    // matrixKeyScan_2();
    matrixKeyScan_3();
}