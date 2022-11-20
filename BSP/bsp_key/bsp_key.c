/*
 * @Author: liubotao
 * @Date: 2022-11-18 00:13:48
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-18 16:59:31
 * @FilePath: \test51\BSP\bsp_key\bsp_key.c
 * @Description: 矩阵按键检测
 * 
 */
#include "bsp.h"
#define keyboard P1

sbit key_1= P3^1;
sbit key_2 =P3^2;

#define keyUncertainTime 3//消抖时间 ( x10 ms)

int KeyValue; //全局函数，键值

unsigned char code KEY_TABLE[] =
 {
	 0xEE, 0xED, 0xEB, 0xE7,
     0xDE, 0xDD, 0xDB, 0xBB,
     0xBE, 0xBD, 0xBB, 0xB7,
     0x7E, 0x7D, 0x7B, 0x77
 };

int matrixKeyScan_1()//还没加消抖
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
检测到按键被按下时，将行扫描的结果存入临时变量，再进行列扫描，得到的结果和临时变量进行或运算。
扫描完得到结果后遍历数组，找到对应的编码位置并显示数码管编码
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
static unsigned char IsKeyDown1(void) {if ((key_1) == 0) return 1;else return 0;}
static unsigned char IsKeyDown2(void) {if ((key_2) == 0) return 1;else return 0;}

static KEY_T s_tBtn[KEY_COUNT] = {0};
static KEY_FIFO_T s_tKey;		/* 按键FIFO变量,结构体 */


void bsp_PutKey(unsigned char _KeyCode)
{
	s_tKey.Buf[s_tKey.Write] = _KeyCode;

	if (++s_tKey.Write  >= KEY_FIFO_SIZE)
	{
		s_tKey.Write = 0;
	}
}

unsigned char bsp_GetKey(void)
{
	unsigned char ret;

	if (s_tKey.Read == s_tKey.Write)
	{
		return KEY_NONE;
	}
	else
	{
		ret = s_tKey.Buf[s_tKey.Read];

		if (++s_tKey.Read >= KEY_FIFO_SIZE)
		{
			s_tKey.Read = 0;
		}
		return ret;
	}
}

void bsp_InitKeyVar(void)
{
	unsigned char i;

	/* 对按键FIFO读写指针清零 */
	s_tKey.Read = 0;
	s_tKey.Write = 0;
//	s_tKey.Read2 = 0;

	/* 给每个按键结构体成员变量赋一组缺省值 */
	for (i = 0; i < KEY_COUNT; i++)
	{
		s_tBtn[i].LongTime = KEY_LONG_TIME;			/* 长按时间 0 表示不检测长按键事件 */
		s_tBtn[i].Count = KEY_FILTER_TIME / 2;		/* 计数器设置为滤波时间的一半 */
		s_tBtn[i].State = 0;							/* 按键缺省状态，0为未按下 */
		s_tBtn[i].RepeatSpeed = 0;						/* 按键连发的速度，0表示不支持连发 */
		s_tBtn[i].RepeatCount = 0;						/* 连发计数器 */
	}
	s_tBtn[0].IsKeyDownFunc = IsKeyDown1;
	s_tBtn[1].IsKeyDownFunc = IsKeyDown2;
}



static void bsp_DetectKey(unsigned char i)
{
	KEY_T *pBtn;

	
		if (s_tBtn[i].IsKeyDownFunc == 0)
		{
			//printf("Fault : DetectButton(), s_tBtn[i].IsKeyDownFunc undefine");
		}
	

	pBtn = &s_tBtn[i];
	if (pBtn->IsKeyDownFunc())
	{
		if (pBtn->Count < KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count < 2 * KEY_FILTER_TIME)
		{
			pBtn->Count++;
		}
		else
		{
			if (pBtn->State == 0)
			{
				pBtn->State = 1;

				/* 发送按钮按下的消息 */
				bsp_PutKey((unsigned char)(3 * i + 1));
			}

			if (pBtn->LongTime > 0)
			{
				if (pBtn->LongCount < pBtn->LongTime)
				{
					/* 发送按钮持续按下的消息 */
					if (++pBtn->LongCount == pBtn->LongTime)
					{
						/* 键值放入按键FIFO */
						bsp_PutKey((unsigned char)(3 * i + 3));
					}
				}
				else
				{
					if (pBtn->RepeatSpeed > 0)
					{
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed)
						{
							pBtn->RepeatCount = 0;
							/* 常按键后，每隔10ms发送1个按键 */
							bsp_PutKey((unsigned char)(3 * i + 1));
						}
					}
				}
			}
		}
	}
	else
	{
		if(pBtn->Count > KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if(pBtn->Count != 0)
		{
			pBtn->Count--;
		}
		else
		{
			if (pBtn->State == 1)
			{
				pBtn->State = 0;

				/* 发送按钮弹起的消息 */
				bsp_PutKey((unsigned char)(3 * i + 2));
			}
		}

		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}

void bsp_KeyScan(void)
{
	unsigned char i;

	for (i = 0; i < KEY_COUNT; i++)
	{
		bsp_DetectKey(i);
	}
}


