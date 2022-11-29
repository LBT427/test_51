/*
 * @Author: liubotao
 * @Date: 2022-08-29 16:37:40
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-29 09:22:45
 * @FilePath: \test_51\USER\main.c
 * @Description: Ê±ÖÓ
 *
 */
#include "reg51.h"
#include "bsp.h"
//#include "fifo.h"
#include "EventHandler.h"

extern EVEN_T  myevent;
extern TIMER_T  timer;
extern uint8_t KeyVal;        


uint8_t KEY_1_DownMessage()
{
	static uint8_t KeyValue_1;
	if (KeyVal == KEY_1_DOWN)
	{
		KeyValue_1=eNABLE;
		KeyVal = KEY_1_UP;
	}

	if (KeyVal == KEY_1_UP&&KeyValue_1==eNABLE)
	{
		KeyValue_1=dISABLE;
		return eNABLE;	
	}	
	else
		return dISABLE;

}
uint8_t KEY_1_LongMessage()
{
	static uint8_t KeyValue_2;
	if (KeyVal == KEY_1_LONG)
	{
		KeyValue_2=eNABLE;
		KeyVal = KEY_1_UP;
	}
	if (KeyVal == KEY_1_UP && KeyValue_2 == eNABLE)
	{
		KeyValue_2 = dISABLE;
		return eNABLE;
	}
	else
		return dISABLE;
}

uint8_t timeadd(void)
{
	addIncident(&timer);
	return 0;
}
uint8_t timeNumber=0;

uint8_t timeSwitch(void)
{
	if (timeNumber > 0)
	{
        switchIncident(&timer);
		
	}
    else modeIncident(&timer);
	timeNumber++;	
	if (timeNumber > 6)
	{
        modeIncident(&timer);
		timeNumber = 0;
	}

}


int main()
{
	EnevHancleInit(&myevent);
    evenConnector(&myevent,
              KEY_1_LongMessage,
              timeSwitch,
              0);
    evenConnector(&myevent,
              KEY_1_DownMessage,
              timeadd,
              1);
	bspInit();
	while (1);
}
    