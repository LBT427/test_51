/*** 
 * @Author: liubotao
 * @Date: 2022-11-24 12:21:44
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-26 16:43:13
 * @FilePath: \test_51\middleware\EventHandler\EventHandler.h
 * @Description: 
 * @
 */
#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#define READ    0
#define WRITE   1

#define dISABLE 0
#define eNABLE  1

#define ERROR   66


#define EVENNUM 2

typedef unsigned char event_t;

//结构体

typedef struct Event EVEN_T;

struct Event
{
    event_t sizes;             //大小

    //event_t hand;             //写指针
    //event_t read;             //读指针

    event_t (*pMessageFun[EVENNUM])();  //指向消息函数
    //event_t   messageBuffer[EVENNUM];
    event_t (*pEventFun[EVENNUM])();     //指向事件函数
    //event_t   eventBuffer[EVENNUM];

};

void EnevHancleInit(EVEN_T *pEven);//初始化
void evenTrigger(EVEN_T *pEven);// 扫描器
//连接器 连接消息和事件
event_t evenConnector(EVEN_T *pEven,
                   event_t (*pMessagef)(),
                   event_t (*pEvenf)(void),
                   event_t priority);


#endif