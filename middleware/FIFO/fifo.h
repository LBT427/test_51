/*** 
 * @Author: liubotao
 * @Date: 2022-11-20 20:58:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-25 18:40:29
 * @FilePath: \test_51\middleware\FIFO\fifo.h
 * @Description: 循环队列
 * @
 */
#ifndef _FIFO_H_
#define _FIFO_H_

#include "type.h"

#define false 0
#define true  1


typedef struct SeqQueue
{
    int8_t head;   //表示队列的起始位置
    int8_t tail;   //结束位置
    uint8_t sizes;   //大小

    uint8_t *datas;
}FIFO;


int8_t createQueue(FIFO *f, uint8_t fifoSize,uint8_t *buff);     //创建队列
int8_t deleteQueue(FIFO *f);     //队列
int8_t enQueue(FIFO *f, uint8_t value);            //入列
int8_t deQueue(FIFO *f);                       //出列
int8_t Front(FIFO *f);                         //返回队头
int8_t Rear(FIFO *f);                          //返回队尾
int8_t isEmpty(FIFO *f);                       //是否为空
int8_t isFull(FIFO *f);                        //是否为满

//void monitorQueue();

#endif