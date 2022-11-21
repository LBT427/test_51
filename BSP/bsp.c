/*
 * @Author: liubotao
 * @Date: 2022-11-18 00:32:28
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-21 10:09:30
 * @FilePath: \test_51\BSP\bsp.c
 * @Description: �жϺ�������ʼ��
 *
 */
#include "bsp.h"

static void task10ms();

void bspInit()              //Ӳ����ʼ��
{
    bsp_InitKeyVar();       //������ʼ��
    initLcd1602();          //lcd��ʼ��
    timer0Init();           //�жϳ�ʼ��
}

void timer0Init()           //1ms�жϳ�ʼ��
{
    TMOD |= 0X10;

    TH1 = 0XFC; 
    TL1 = 0X18;
    ET1 = 1;
    EA = 1;
    TR1 = 1;
}

void Timer1() interrupt 3   //�жϷ�����
{
    static int time_num;    //�жϴ�����һ��10ms
    TH1 = 0XFC; 
    TL1 = 0X18;
    time_num++;
    if (time_num == 10)     // 10ms
    {
        time_num = 0;
        task10ms();
    }
}

static void task10ms()      //10ms����
{
    // matrixKeyScan_1();
    // matrixKeyScan_2();
    matrixKeyScan_3();
    bsp_KeyScan();
}

