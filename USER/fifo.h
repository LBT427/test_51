/*** 
 * @Author: liubotao
 * @Date: 2022-11-20 20:58:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-20 23:53:57
 * @FilePath: \test_51\USER\fifo.h
 * @Description: 
 * @
 */
#ifndef _FIFO_H_
#define _FIFO_H_


#define false 0
#define true  1


typedef struct SeqQueue
{
    int head;   //表示队列的起始位置
    int tail;   //结束位置
    int sizes;   //大小

    int *datas;
}FIFO;


int createQueue(FIFO *f, int fifoSize,int *buff);     //创建队列
int deleteQueue(FIFO *f);     //队列
int enQueue(FIFO *f, int value);            //入列
int deQueue(FIFO *f);                       //出列
int Front(FIFO *f);                         //返回队头
int Rear(FIFO *f);                          //返回队尾
int isEmpty(FIFO *f);                       //是否为空
int isFull(FIFO *f);                        //是否为满

//void monitorQueue();

#endif