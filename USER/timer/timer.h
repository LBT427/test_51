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
	uint8_t   rANDw;	    //���û�����ʾ
    uint8_t   setMode;   //����ģʽ

    uint16_t   num;    	
    uint8_t   timeBuffer[8]; //����ʱ��

    void  (*setClock)(TIMER_T * t);     //����оƬ
    void  (*showClock)(TIMER_T * t);    //��ʾʱ��
    void  (*refreshClock)(TIMER_T * t);    //��ʾʱ��
    void  (*timerRead) (uint8_t  *buf);//������
    void  (*timerWrite) (uint8_t  *buf);//д����
    void  (*displayClear)(void);    //����
    void  (*displayWrite) (uint8_t  x,uint8_t  y,uint8_t  *buf);//��Ļд����
    //void  (*displayBlinks) (uint8_t  x,uint8_t  y,uint8_t mode);//�����˸

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


//void  setTimer(TIMER_T *time,uint8_t  a,uint16_t b);//����ʱ��
void  addIncident(TIMER_T *time);           //�� �����¼�
void  subIncident(TIMER_T *time);           //�� �����¼�
void  showIncident(TIMER_T *time);          //��ʾ�¼�
void  switchIncident(TIMER_T *time);        //�л�����
void  modeIncident(TIMER_T *time);          //��ʾģʽѡ��

#endif
