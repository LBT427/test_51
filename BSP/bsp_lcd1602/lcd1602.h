/*** 
 * @Author: liubotao
 * @Date: 2022-10-30 15:02:44
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-01 15:34:08
 * @FilePath: \ds1302-lcd1602\BSP\LCD\lcd1602.h
 * @Description: 
 * @
 */
#ifndef __LCD1602_H_
#define __LCD1602_H_

#include <reg51.h>

#define uint8_t unsigned char
#define uint16_t unsigned int


#define LCD1602_DB  P0     
sbit LCD1602_RS = P2^0;
sbit LCD1602_RW = P2^1;
sbit LCD1602_EN = P2^2;


void readBusy();                                                  //忙检测
void lcd1602WriteCmd(uint8_t cmd);                                //写命令
void lcd1602WriteData(uint8_t dat);                               //写数据
void lcdSetCursor(uint8_t x,uint8_t y);                    		  //坐标设置
void LcdShowStr(uint8_t x,uint8_t y,uint8_t *str);    			  //显示字符串
void initLcd1602();                                               //1602初始化
					  

#endif
