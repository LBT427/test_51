/*
 * @Author: liubotao
 * @Date: 2022-11-24 12:21:37
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-26 20:19:34
 * @FilePath: \test_51\middleware\EventHandler\EventHandler.c
 * @Description: 
 * 
 */
#include "EventHandler.h"


//先模拟一个事件函数

/*按键1 事件  参数1为 事件参数 参数二为 模式，读还是写，
    读就是 处理器判断事件是否产生
    写就是 事件产生后调用这个函数
*/
// event_t key1Message(EVEN_T *pEven,event_t val)
// {

//         pEven->eventBuffer[/*优先级*/] == ENABLE;
   
// }



// event_t lcdEven() //事件
// {


// }
// 扫描器
void evenTrigger(EVEN_T *pEven)
{
    event_t i=0;
    
    
    for ( i = 0; i < (pEven->sizes); i++)
    {
       // if (pEven->pMessageFun[i]()== 0) continue;
        
        if (pEven->pMessageFun[i]()== eNABLE)
        {
            //pEven->eventBuffer[i] = eNABLE;
            pEven->pEventFun[i]();
        }
        // else
        //     pEven->eventBuffer[i] == DISABLE;
        //pEven->hand=i;
    }

//    for ( i = 0; i < (pEven->sizes); i++)
//    {
//        if (pEven->eventBuffer[i] == eNABLE)
//        {
//            pEven->pEventFun[i]();
//        }
//        //pEven->read=i;
//    }
    
}

//连接器 连接消息和事件
event_t evenConnector(EVEN_T *pEven,
                   event_t (*pMessagef)(),
                   event_t (*pEvenf)(void),
                   event_t priority)
{
    if (pEven->pMessageFun[priority] !=0 && priority > pEven->sizes)
    {
       return ERROR;
    }
    
    pEven->pMessageFun[priority]=pMessagef;
    pEven->pEventFun[priority]=pEvenf;
    
}

//初始化

void EnevHancleInit(EVEN_T *pEven)
{
    event_t i;

    pEven->sizes = EVENNUM;
    //pEven->hand = 0;
    //pEven->read = 0;
  
    for (i = 0; i < EVENNUM; i++)
    {
        pEven->pMessageFun[i] = 0;
        pEven->pEventFun[i] = 0;
//        pEven->eventBuffer[i] = 0;
    }

}
