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

//�ṹ��

typedef struct Event EVEN_T;

struct Event
{
    event_t sizes;             //��С

    //event_t hand;             //дָ��
    //event_t read;             //��ָ��

    event_t (*pMessageFun[EVENNUM])();  //ָ����Ϣ����
    //event_t   messageBuffer[EVENNUM];
    event_t (*pEventFun[EVENNUM])();     //ָ���¼�����
    //event_t   eventBuffer[EVENNUM];

};

void EnevHancleInit(EVEN_T *pEven);//��ʼ��
void evenTrigger(EVEN_T *pEven);// ɨ����
//������ ������Ϣ���¼�
event_t evenConnector(EVEN_T *pEven,
                   event_t (*pMessagef)(),
                   event_t (*pEvenf)(void),
                   event_t priority);


#endif