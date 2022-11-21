/*** 
 * @Author: liubotao
 * @Date: 2022-11-18 00:13:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-21 11:21:50
 * @FilePath: \test_51\BSP\bsp_key\bsp_key.h
 * @Description: 按键检测和矩阵按键检测
 * @
 */
#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "type.h"


int matrixKeyScan_1();
int matrixKeyScan_2();
int matrixKeyScan_3();

extern self_t KeyValue;

typedef enum
{
	KEY_NONE = 0,			

	KEY_1_DOWN,				// 1键按下
	KEY_1_UP,				// 1键弹起
	KEY_1_LONG,				// 1键长按

	KEY_2_DOWN,				// 2键按下 
	KEY_2_UP,				// 2键弹起 
	KEY_2_LONG,				// 2键长按 

}KEY_ENUM;


typedef struct
{

	unsigned char (*IsKeyDownFunc)(void); 	// 指向判断按键手否按下的函数,1表示按下

	unsigned char  	Count;					// 滤波器计数器
	unsigned int 	LongCount;				// 长按计数器
	unsigned int 	LongTime;				// 按键按下持续时间, 0表示不检测长按
	unsigned char  	State;					// 按键当前状态（按下还是弹起）
	unsigned char  	RepeatSpeed;			// 连续按键周期
	unsigned char  	RepeatCount;			// 连续按键计数器
	
}KEY_T;


#define KEY_FIFO_SIZE 		10			//按键FIFO大小


#define KEY_COUNT    		2	   		// 按键个数,  2个 
#define KEY_FILTER_TIME   	5      	//滤波时间 连续检测到 n ms状态不变 相当于按住 2*n ms
#define KEY_LONG_TIME     	100			// 单位10ms， 持续1秒，认为长按事件 


void bsp_KeyScan(void);
unsigned char bsp_GetKey(void);
void bsp_InitKeyVar(void);


#endif
