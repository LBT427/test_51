/*
 * @Author: liubotao
 * @Date: 2022-08-29 16:37:40
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-21 10:13:50
 * @FilePath: \test_51\USER\main.c
 * @Description: ¾ØÕó°´¼ü¼ì²â
 *
 */
#include "reg51.h"
#include "bsp.h"
#include "fifo.h"

#define key P1
#define led P2

uint8_t code disBuffer[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
							0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

int main()
{
	extern FIFO f_K;
	self_t KeyValue_ind; //È«¾Öº¯Êý£¬¶ÀÁ¢¼üÖµ

	bspInit();
	while (1)
	{
 		KeyValue_1=deQueue(&f_K);
		//LcdShowStr(0,0,"okk");    			  //ÏÔÊ¾×Ö·û´®

		if (KeyValue >=0 && KeyValue < 16)
		{
			led = disBuffer[KeyValue];
		}
		switch (KeyValue_1)
		{
		case KEY_1_DOWN:
			LcdShowStr(0, 0, "KEY_1_DOWN");
			break;
		case KEY_1_UP:
			LcdShowStr(0, 0, "KEY_1_UP");
			break;
		case KEY_1_LONG:
			LcdShowStr(0, 0, "KEY_1_LONG");
			break;
		case KEY_2_DOWN:
			LcdShowStr(0, 0, "KEY_2_DOWN");
			break;
		case KEY_2_UP:
			LcdShowStr(0, 0, "KEY_2_UP");
			break;
		case KEY_2_LONG:
			LcdShowStr(0, 0, "KEY_2_LONG");
			break;
		default:
			break;
		}
	}
}
    