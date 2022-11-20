/*** 
 * @Author: liubotao
 * @Date: 2022-11-18 00:13:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-18 16:57:09
 * @FilePath: \test51\BSP\bsp_key\bsp_key.h
 * @Description: ���󰴼����
 * @
 */
#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "reg51.h"
#include "bsp.h"

extern int KeyValue;
int matrixKeyScan_1();
int matrixKeyScan_2();
int matrixKeyScan_3();

typedef enum
{
	KEY_NONE = 0,			/* 0 ��ʾ�����¼� */

	KEY_1_DOWN,				/* 1������ */
	KEY_1_UP,				/* 1������ */
	KEY_1_LONG,				/* 1������ */

	KEY_2_DOWN,				/* 2������ */
	KEY_2_UP,				/* 2������ */
	KEY_2_LONG,				/* 2������ */

}KEY_ENUM;
/*
    ÿ��������Ӧ1��ȫ�ֵĽṹ�������
*/
typedef struct
{
	/* ������һ������ָ�룬ָ���жϰ����ַ��µĺ��� */
	unsigned char (*IsKeyDownFunc)(void); /* �������µ��жϺ���,1��ʾ���� */

	unsigned char  Count;			/* �˲��������� */
	unsigned int LongCount;		/* ���������� */
	unsigned int LongTime;		/* �������³���ʱ��, 0��ʾ����ⳤ�� */
	unsigned char  State;			/* ������ǰ״̬�����»��ǵ��� */
	unsigned char  RepeatSpeed;	/* ������������ */
	unsigned char  RepeatCount;	/* �������������� */
}KEY_T;

#define KEY_COUNT    2	   					/* ��������, 8�������� + 2����ϼ� */
#define KEY_FILTER_TIME   5             //�˲�ʱ�� 
#define KEY_LONG_TIME     100			/* ��λ10ms�� ����1�룬��Ϊ�����¼� */

#define KEY_FIFO_SIZE 10

typedef struct
{
    unsigned char Buf[KEY_FIFO_SIZE]; /* ��ֵ������ */
    unsigned char Read;               /* ��������ָ��1 */
    unsigned char Write;              /* ������дָ�� */
    //unsigned char Read2;              /* ��������ָ��2 */
} KEY_FIFO_T;

void bsp_KeyScan(void);
unsigned char bsp_GetKey(void);

#endif
