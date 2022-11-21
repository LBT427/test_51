/*** 
 * @Author: liubotao
 * @Date: 2022-11-20 20:58:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-21 11:53:06
 * @FilePath: \test_51\USER\fifo.h
 * @Description: ѭ������
 * @
 */
#ifndef _FIFO_H_
#define _FIFO_H_

#include "type.h"

#define false 0
#define true  1


typedef struct SeqQueue
{
    int head;   //��ʾ���е���ʼλ��
    int tail;   //����λ��
    unsigned char sizes;   //��С

    unsigned char *datas;
}FIFO;


int createQueue(FIFO *f, unsigned char fifoSize,unsigned char *buff);     //��������
int deleteQueue(FIFO *f);     //����
int enQueue(FIFO *f, unsigned char value);            //����
int deQueue(FIFO *f);                       //����
int Front(FIFO *f);                         //���ض�ͷ
int Rear(FIFO *f);                          //���ض�β
int isEmpty(FIFO *f);                       //�Ƿ�Ϊ��
int isFull(FIFO *f);                        //�Ƿ�Ϊ��

//void monitorQueue();

#endif