/*** 
 * @Author: liubotao
 * @Date: 2022-11-18 00:13:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-28 20:59:45
 * @FilePath: \test_51\BSP\bsp_key\bsp_key.h
 * @Description: 按键检测和矩阵按键检测
 * @
 */
#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "type.h"

///////////////////////////////////////////矩阵按键部分///////////////////////////////////////////////

//#define keyboard P1


int8_t matrixKeyScan_1();
int8_t matrixKeyScan_2();
int8_t matrixKeyScan_3();

//extern xdata uint8_t KeyValue;

#define keyUncertainTime 3  //消抖时间 ( x10 ms)

///////////////////////////////////////////独立按键部分///////////////////////////////////////////////

sbit key_1= P3^0;
//sbit key_2 =P3^1;
typedef enum
{
	KEY_NONE = 0,			

	KEY_1_DOWN,				// 1键按下
	KEY_1_UP,				// 1键弹起
	KEY_1_LONG,				// 1键长按

//	KEY_2_DOWN,				// 2键按下 
//	KEY_2_UP,				// 2键弹起 
//	KEY_2_LONG,				// 2键长按 

}KEY_ENUM;


typedef struct
{

	uint8_t     (*IsKeyDownFunc)(void); 	// 指向判断按键手否按下的函数,1表示按下

	uint8_t  	Count;					// 滤波器计数器
	uint16_t 	LongCount;				// 长按计数器
	uint16_t 	LongTime;				// 按键按下持续时间, 0表示不检测长按
	uint8_t  	State;					// 按键当前状态（按下还是弹起）
	
}KEY_T;


#define KEY_FIFO_SIZE 		0			//按键FIFO大小


#define KEY_COUNT    		1	   		// 按键个数,  2个 
#define KEY_FILTER_TIME   	5      		//滤波时间 连续检测到 n ms状态不变 相当于按住 2*n ms
#define KEY_LONG_TIME     	40			// 单位10ms， 持续1秒，认为长按事件 


void bsp_KeyScan(void);
uint8_t bsp_GetKey(void);
void bsp_InitKeyVar(void);


#endif
