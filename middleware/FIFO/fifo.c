/*
 * @Author: liubotao
 * @Date: 2022-11-20 20:59:01
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-25 18:41:24
 * @FilePath: \test_51\middleware\FIFO\fifo.c
 * @Description: Ñ­»·¶ÓÁĞ
 * 
 */
#include "fifo.h"

int8_t createQueue(FIFO *f, uint8_t fifoSize,uint8_t *buff)
{
    f -> datas = buff; //(int*)malloc(fifoSize * sizeof(int));
    f -> head = -1;
    f -> tail = -1;
    f -> sizes = fifoSize;
		return 1;
}

int8_t deleteQueue(FIFO *f)
{

    //free(f->datas);
    f -> datas=0;
    f -> head = -1;
    f -> tail = -1;
    f -> sizes = 0;
		return 1;
}


int8_t enQueue(FIFO *f, uint8_t value)
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

int8_t deQueue(FIFO *f)
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

int8_t Front(FIFO *f)
{
    
    if (isEmpty(f))
    {
        return -1;
    }
    return f->datas[f->head];
}
int8_t Rear(FIFO *f)
{
    if (isEmpty(f))
    {
        return -1;
    }
    return f->datas[f->tail];
}

int8_t isEmpty(FIFO *f)
{
    return f->head == -1;
}


int8_t isFull(FIFO *f)
{
    
    return ((f->tail + 1) % f->sizes) == f->head;
}


