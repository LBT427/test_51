/*** 
 * @Author: liubotao
 * @Date: 2022-11-20 20:58:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-25 18:40:29
 * @FilePath: \test_51\middleware\FIFO\fifo.h
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
    int8_t head;   //��ʾ���е���ʼλ��
    int8_t tail;   //����λ��
    uint8_t sizes;   //��С

    uint8_t *datas;
}FIFO;


int8_t createQueue(FIFO *f, uint8_t fifoSize,uint8_t *buff);     //��������
int8_t deleteQueue(FIFO *f);     //����
int8_t enQueue(FIFO *f, uint8_t value);            //����
int8_t deQueue(FIFO *f);                       //����
int8_t Front(FIFO *f);                         //���ض�ͷ
int8_t Rear(FIFO *f);                          //���ض�β
int8_t isEmpty(FIFO *f);                       //�Ƿ�Ϊ��
int8_t isFull(FIFO *f);                        //�Ƿ�Ϊ��

//void monitorQueue();

#endif