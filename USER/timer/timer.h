/*** 
 * @Author: liubotao
 * @Date: 2022-11-05 16:40:34
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-28 16:09:03
 * @FilePath: \test_51\USER\timer\timer.h
 * @Description: 
 * @
 */
#ifndef _TIMER_H
#define _TIMER_H

#include "type.h"
//struct TIMER_T;
#define TIMSHOW 0
//#define TIMSET  1

typedef struct Timer TIMER_T;

struct Timer
{
	uint8_t   rANDw;	    //设置还是显示
    uint8_t   setMode;   //设置模式

    uint16_t   num;    	
    uint8_t   timeBuffer[8]; //储存时间

    void  (*setClock)(TIMER_T * t);     //设置芯片
    void  (*showClock)(TIMER_T * t);    //显示时间
    void  (*refreshClock)(TIMER_T * t);    //显示时间
    void  (*timerRead) (uint8_t  *buf);//读数据
    void  (*timerWrite) (uint8_t  *buf);//写数据
    void  (*displayClear)(void);    //清屏
    void  (*displayWrite) (uint8_t  x,uint8_t  y,uint8_t  *buf);//屏幕写数据
    //void  (*displayBlinks) (uint8_t  x,uint8_t  y,uint8_t mode);//光标闪烁

};


typedef enum
{
    second,
    minute,
    hour,
    day,
    month,
    week,
    year,
}TIMER_ENUM;


//void  setTimer(TIMER_T *time,uint8_t  a,uint16_t b);//设置时间
void  addIncident(TIMER_T *time);           //加 按键事件
void  subIncident(TIMER_T *time);           //减 按键事件
void  showIncident(TIMER_T *time);          //显示事件
void  switchIncident(TIMER_T *time);        //切换设置
void  modeIncident(TIMER_T *time);          //显示模式选择

#endif
