/*
 * @Author: liubotao
 * @Date: 2022-11-20 20:59:01
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-20 23:54:17
 * @FilePath: \test_51\USER\fifo.c
 * @Description: 
 * 
 */
#include "fifo.h"

int createQueue(FIFO *f, int fifoSize,int *buff)
{
    f -> datas = buff;//(int*)malloc(fifoSize * sizeof(int));
    f -> head = -1;
    f -> tail = -1;
    f -> sizes = fifoSize;
}

int deleteQueue(FIFO *f)
{

    //free(f->datas);
    f -> datas=0;
    f -> head = -1;
    f -> tail = -1;
    f -> sizes = 0;
}


int enQueue(FIFO *f, int value)
{
    if (isFull(f))
    {
        return 0;
    }
    if (isEmpty(f))
    {
        f->head = 0;
    }
    f->tail = (f->tail + 1) % f->sizes;
    f->datas[f->tail] = value;
    return 1;
}

int deQueue(FIFO *f)
{
	int temp =Front(f);
    if (isEmpty(f))
    {
        return false;
    }
    
    if (f->head == f->tail)
    {
        f->head = -1;
        f->tail = -1;
        return temp;
    }
    f->head = (f->head + 1) % f->sizes;
    return temp;
}

int Front(FIFO *f)
{
    
    if (isEmpty(f))
    {
        return -1;
    }
    return f->datas[f->head];
}
int Rear(FIFO *f)
{
    if (isEmpty(f))
    {
        return -1;
    }
    return f->datas[f->tail];
}

int isEmpty(FIFO *f)
{
    return f->head == -1;
}


int isFull(FIFO *f)
{
    return ((f->tail + 1) % f->sizes) == f->head;
}


