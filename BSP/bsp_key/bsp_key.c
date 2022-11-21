/*
 * @Author: liubotao
 * @Date: 2022-11-18 00:13:48
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-21 11:21:55
 * @FilePath: \test_51\BSP\bsp_key\bsp_key.c
 * @Description: �������;��󰴼����
 * 
 */

#include "bsp.h"
#include "fifo.h"


#define keyboard P1

sbit key_1= P3^0;
sbit key_2 =P3^1;

#define keyUncertainTime 3//����ʱ�� ( x10 ms)

self_t KeyValue; //ȫ�ֺ�������ֵ

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

///////////////////////////////
//��������ɨ�躯��
static unsigned char IsKeyDown1(void) {if ((key_1) == 0) return 1;else return 0;}

static unsigned char IsKeyDown2(void) {if ((key_2) == 0) return 1;else return 0;}
//....
//���ఴ�����ں���
//////////////////////////////

FIFO f_K;											//��������FIFO
self_t keyFIFOBuffer[KEY_FIFO_SIZE]={0};   
KEY_T s_tBtn[KEY_COUNT] = {0};						//�����ṹ��		
void bsp_InitKeyVar(void)
{
	unsigned char i;

	createQueue(&f_K,KEY_FIFO_SIZE,keyFIFOBuffer);	//���г�ʼ��
	//��ÿ�������ṹ���Ա������һ��ȱʡֵ
	for (i = 0; i < KEY_COUNT; i++)
	{
		s_tBtn[i].LongTime = KEY_LONG_TIME;				// ����ʱ�� 0 ��ʾ����ⳤ�����¼� 
		s_tBtn[i].Count = KEY_FILTER_TIME / 2;			// ����������Ϊ�˲�ʱ���һ�� 
		s_tBtn[i].State = 0;							// ����ȱʡ״̬��0Ϊδ���� 
		s_tBtn[i].RepeatSpeed = 0;						// �����������ٶȣ�0��ʾ��֧������ 
		s_tBtn[i].RepeatCount = 0;						// ���������� 
	} 

	////////////////////////
	s_tBtn[0].IsKeyDownFunc = IsKeyDown1;				
	s_tBtn[1].IsKeyDownFunc = IsKeyDown2;
	//....
	//���ఴ�����ں���
	///////////////////////
}

static void bsp_DetectKey(unsigned char i)			//����ɨ��
{
	KEY_T *pBtn;

	if (s_tBtn[i].IsKeyDownFunc == NULL)
	{
		return;
		//printf("Fault : DetectButton(), s_tBtn[i].IsKeyDownFunc undefine");
	}

	pBtn = &s_tBtn[i];								//����ɨ�谴��
	if (pBtn->IsKeyDownFunc())
	{
		if (pBtn->Count < KEY_FILTER_TIME)
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if (pBtn->Count < 2 * KEY_FILTER_TIME)	//С������������
		{
			pBtn->Count++;
		}
		else										//��������
		{
			if (pBtn->State == 0)
			{
				pBtn->State = 1;
				// ���Ͱ�ť���µ���Ϣ
				enQueue(&f_K, 3 * i + 1); //push
			}

			if (pBtn->LongTime > 0)							//�����ж�
			{
				if (pBtn->LongCount < pBtn->LongTime)		//����������С���趨��ʱ��
				{
					/* ���Ͱ�ť�������µ���Ϣ */
					if (++pBtn->LongCount == pBtn->LongTime)
					{
						enQueue(&f_K, 3 * i + 3); //push
					}
				}
				else
				{
					if (pBtn->RepeatSpeed > 0)
					{
						if (++pBtn->RepeatCount >= pBtn->RepeatSpeed)
						{
							pBtn->RepeatCount = 0;
							//����������ÿ�� x10 ms����1������ 
							enQueue(&f_K, 3 * i + 1); //����
						}
					}
				}
			}
		}
	}
	else										//�ɿ�
	{
		if (pBtn->Count > KEY_FILTER_TIME)      //�����������趨ʱ����Ƕ���
		{
			pBtn->Count = KEY_FILTER_TIME;
		}
		else if (pBtn->Count != 0)
		{
			pBtn->Count--;
		}
		else									//����ɿ���
		{
			if (pBtn->State == 1)
			{
				pBtn->State = 0;
				// ���Ͱ�ť�������Ϣ
				enQueue(&f_K, 3 * i + 2); //push
			}
		}

		pBtn->LongCount = 0;
		pBtn->RepeatCount = 0;
	}
}

void bsp_KeyScan(void)	//ɨ��ȫ������
{
	unsigned char i;

	for (i = 0; i < KEY_COUNT; i++)
	{
		bsp_DetectKey(i);
	}
}


