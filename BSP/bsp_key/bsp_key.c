/*
 * @Author: liubotao
 * @Date: 2022-11-18 00:13:48
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-18 02:49:02
 * @FilePath: \test51\BSP\bsp_key\bsp_key.c
 * @Description: ���󰴼����
 * 
 */
#include "bsp.h"
#define keyboard P1

#define keyUncertainTime 3//����ʱ�� ( x10 ms)

int KeyValue; //ȫ�ֺ�������ֵ

unsigned char code KEY_TABLE[] =
 {
	 0xEE, 0xED, 0xEB, 0xE7,
     0xDE, 0xDD, 0xDB, 0xBB,
     0xBE, 0xBD, 0xBB, 0xB7,
     0x7E, 0x7D, 0x7B, 0x77
 };

int matrixKeyScan_1()//��û������
{
	unsigned char num = 0;
	unsigned int buffer = 0;
	
	for (num = 0; num < 4; num++)
	{
		if (num)
			buffer = buffer << 4;
		keyboard = ~(0x80 >> num);
		buffer |= (keyboard & 0x0f);
	}
	num = 16;
	while (num--)
	{
		if (((buffer >> num) & 0x01) == 0)
		{
			KeyValue = num;
			break;
		}
	}
	return KeyValue;
}
/*
��⵽����������ʱ������ɨ��Ľ��������ʱ�������ٽ�����ɨ�裬�õ��Ľ������ʱ�������л����㡣
ɨ����õ������������飬�ҵ���Ӧ�ı���λ�ò���ʾ����ܱ���
*/
int matrixKeyScan_2()
{
	static unsigned int keyDelayTime;
	unsigned int temp, key, i;
	keyboard = 0xF0;
	if (keyboard != 0xF0)
	{
		keyDelayTime++;
		if (keyDelayTime > 3)
		{
			temp = keyboard;
			keyboard = 0x0F;
			key = temp | keyboard;
			for (i = 0; i < 16; ++i)
			{
				if (key == KEY_TABLE[i])
					break;
			}
			KeyValue = i;
			return KeyValue;
		}
		else return -1;
	}
	else
	{
		keyDelayTime = 0;
		return -1;
	}
}

int matrixKeyScan_3()
{
	static unsigned int  keyDelayTime;
	keyboard=0x0f;
	if(keyboard!=0x0f)
	{
		keyDelayTime++;
		if(keyDelayTime>3)
		{	
			keyboard=0X0F;
			switch(keyboard)
			{
				case(0X0E):	KeyValue=0;break; 
				case(0X0D):	KeyValue=1;break; 
				case(0X0B): KeyValue=2;break; 
				case(0X07):	KeyValue=3;break; 
			}
			keyboard=0XF0;				
			switch(keyboard)
			{
				case(0XE0):	KeyValue=KeyValue;break;  
				case(0XD0):	KeyValue=KeyValue+4;break;
				case(0XB0): KeyValue=KeyValue+8;break;
				case(0X70):	KeyValue=KeyValue+12;break;
			}		
		}
		return KeyValue;
	}
	else
	{
		keyDelayTime = 0;
		return -1;  
	}
	
}
