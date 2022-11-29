/*** 
 * @Author: liubotao
 * @Date: 2022-11-28 17:30:34
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-28 17:46:32
 * @FilePath: \test_51\BSP\bsp_key\key_2.h
 * @Description: 
 * @
 */
#ifndef _KEY_2_H
#define _KEY_2_H


#include "type.h"


void bsp_DetectKey(uint8_t i);



#define KEY_FILTER_TIME   4
#define KEY_LONG_TIME     30			/* 单位10ms， 持续1秒，认为长按事件 */

#define KEY_DOUBLE_TIME   150


typedef enum
{
	KEY_NONE = 0,			/* 0 表示按键事件 */

	KEY_1_DOWN,				/* 1键按下 */
	KEY_1_UP,				/* 1键弹起 */
	KEY_1_LONG,				/* 1键长按 */
	KEY_1_Double,
}KEY_ENUM;

#endif