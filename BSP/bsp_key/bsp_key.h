/*** 
 * @Author: liubotao
 * @Date: 2022-11-18 00:13:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-18 16:57:09
 * @FilePath: \test51\BSP\bsp_key\bsp_key.h
 * @Description: 矩阵按键检测
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
	KEY_NONE = 0,			/* 0 表示按键事件 */

	KEY_1_DOWN,				/* 1键按下 */
	KEY_1_UP,				/* 1键弹起 */
	KEY_1_LONG,				/* 1键长按 */

	KEY_2_DOWN,				/* 2键按下 */
	KEY_2_UP,				/* 2键弹起 */
	KEY_2_LONG,				/* 2键长按 */

}KEY_ENUM;
/*
    每个按键对应1个全局的结构体变量。
*/
typedef struct
{
	/* 下面是一个函数指针，指向判断按键手否按下的函数 */
	unsigned char (*IsKeyDownFunc)(void); /* 按键按下的判断函数,1表示按下 */

	unsigned char  Count;			/* 滤波器计数器 */
	unsigned int LongCount;		/* 长按计数器 */
	unsigned int LongTime;		/* 按键按下持续时间, 0表示不检测长按 */
	unsigned char  State;			/* 按键当前状态（按下还是弹起） */
	unsigned char  RepeatSpeed;	/* 连续按键周期 */
	unsigned char  RepeatCount;	/* 连续按键计数器 */
}KEY_T;

#define KEY_COUNT    2	   					/* 按键个数, 8个独立建 + 2个组合键 */
#define KEY_FILTER_TIME   5             //滤波时间 
#define KEY_LONG_TIME     100			/* 单位10ms， 持续1秒，认为长按事件 */

#define KEY_FIFO_SIZE 10

typedef struct
{
    unsigned char Buf[KEY_FIFO_SIZE]; /* 键值缓冲区 */
    unsigned char Read;               /* 缓冲区读指针1 */
    unsigned char Write;              /* 缓冲区写指针 */
    //unsigned char Read2;              /* 缓冲区读指针2 */
} KEY_FIFO_T;

void bsp_KeyScan(void);
unsigned char bsp_GetKey(void);

#endif
