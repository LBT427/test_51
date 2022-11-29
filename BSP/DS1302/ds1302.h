/*** 
 * @Author: liubotao
 * @Date: 2019-04-10 10:17:14
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-24 10:30:18
 * @FilePath: \test_51\BSP\DS1302\ds1302.h
 * @Description: 
 * @
 */
#ifndef __DS1302_H_
#define __DS1302_H_

#include <reg51.h>
#include <intrins.h>


#include "type.h"


sbit DSIO=P1^0;
sbit RST=P1^2;
sbit SCLK=P1^1;


void Ds1302Write(uint8_t  addr, uint8_t  dat);
uint8_t  Ds1302Read(uint8_t  addr);
void ds1302Init(uint8_t *TIME);
void ds1302ReadTime(uint8_t *TIME);
//extern uint8_t  TIME[7];	//加入全局变量

#endif
