/*
 * @Author: liubotao
 * @Date: 2022-08-29 16:37:40
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-20 10:26:35
 * @FilePath: \test_51\USER\main.c
 * @Description: ¾ØÕó°´¼ü¼ì²â
 *
 */
#include "reg51.h"
#include "bsp.h"
#define uint8_t unsigned char
#define uint16_t unsigned short int
#define key P1
#define led P2

uint8_t code disBuffer[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
							0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

int main()
{
	bspInit();
	while (1)
	{
		if (KeyValue >=0 && KeyValue < 16)
		{
			led = disBuffer[KeyValue];
		}
	}
}
//Ò»´Î²âÊÔ