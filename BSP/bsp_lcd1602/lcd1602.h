/*** 
 * @Author: liubotao
 * @Date: 2022-10-30 15:02:44
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-27 08:07:15
 * @FilePath: \test_51\BSP\bsp_lcd1602\lcd1602.h
 * @Description: 
 * @
 */
#ifndef __LCD1602_H_
#define __LCD1602_H_

#include <reg51.h>
#include "type.h"


#define LCD1602_DB  P0     
sbit LCD1602_RS = P3^2;
sbit LCD1602_RW = P3^3;
sbit LCD1602_EN = P3^4;


void readBusy();                                                  //æ���
void lcd1602WriteCmd(uint8_t cmd);                                //д����
void lcd1602WriteData(uint8_t dat);                               //д����
void lcdSetCursor(uint8_t x,uint8_t y);                    		  //��������
void LcdShowStr(uint8_t x,uint8_t y,uint8_t *str);    			  //��ʾ�ַ���
void initLcd1602();                                               //1602��ʼ��
void currsorBlinks(uint8_t x, uint8_t y, uint8_t mode);           //�����˸					  

#endif
