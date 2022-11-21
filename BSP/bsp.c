/*
 * @Author: liubotao
 * @Date: 2022-11-18 00:32:28
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-21 12:00:41
 * @FilePath: \test_51\BSP\bsp.c
 * @Description: �жϺ�������ʼ��
 *
 */
#include "bsp.h"
#include "fifo.h"
static void task10ms();
static void task5ms();

extern FIFO f_K;
self_t KeyValue_ind; //ȫ�ֺ�����������ֵ

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


static void task10ms()      //10ms����
{
    // matrixKeyScan_1();
    // matrixKeyScan_2();
    //matrixKeyScan_3();
    bsp_KeyScan();
}

static void task5ms()      //10ms����
{
    // matrixKeyScan_1();
    // matrixKeyScan_2();
     matrixKeyScan_3();
     KeyValue_ind=deQueue(&f_K);
			switch (KeyValue_ind)
		{
		case KEY_1_DOWN:
			LcdShowStr(0, 0, "KEY_1_DOWN");
			break;
		case KEY_1_UP:
			LcdShowStr(0, 0, "KEY_1_UP  ");
			break;
		case KEY_1_LONG:
			LcdShowStr(0, 0, "KEY_1_LONG");
			break;
		case KEY_2_DOWN:
			LcdShowStr(0, 0, "KEY_2_DOWN");
			break;
		case KEY_2_UP:
			LcdShowStr(0, 0, "KEY_2_UP  ");
			break;
		case KEY_2_LONG:
			LcdShowStr(0, 0, "KEY_2_LONG");
			break;
		default:
			break;
		}

}
void Timer1() interrupt 3   //�жϷ�����
{
    static int time_num5;    //�жϴ�����һ��10ms
	  static int time_num10;    //�жϴ�����һ��10ms

    TH1 = 0XFC; 
    TL1 = 0X18;
    time_num5++;
		time_num10++;
    if (time_num5 == 5)     // 10ms
    {
        time_num5 = 0;
        task5ms();
    }
		    if (time_num10 == 10)     // 10ms
    {
        time_num10 = 0;
        
			task10ms();
    }
}
