/*** 
 * @Author: liubotao
 * @Date: 2022-11-18 00:32:49
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-21 10:00:16
 * @FilePath: \test_51\BSP\bsp.h
 * @Description: 中断设置和驱动初始化
 * @
 */
#ifndef _BSP_H_
#define _BSP_H_

#include "reg51.h"
#include "type.h"
#include "bsp_key.h"
#include "lcd1602.h"

void bspInit();
static void timer0Init();



#endif

