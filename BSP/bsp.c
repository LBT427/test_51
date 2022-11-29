/*
 * @Author: liubotao
 * @Date: 2022-11-18 00:32:28
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-29 09:15:19
 * @FilePath: \test_51\BSP\bsp.c
 * @Description: 中断和驱动初始化
 *
 */
#include "bsp.h"
//#include "fifo.h"
#include "EventHandler.h"
static void task10ms();
static void task5ms();
void mainSetClock(TIMER_T * t);
void mainShowClock(TIMER_T * t);//显示正在设置的时间
void mainRefreshClock(TIMER_T * t);//显示时钟芯片的时间

void dataPros(uint8_t *buf_s,uint8_t *buf_d);
//extern  FIFO f_K;
extern uint8_t KeyVal;        //全局函数，独立键值
EVEN_T  myevent;
TIMER_T  timer=
{
	0,
	0,
	0,
	{0, 0x30, 0x16, 0x31, 0x10, 0x06, 0x22},
	mainSetClock,
	mainShowClock,
	mainRefreshClock,
	ds1302ReadTime,
	ds1302Init,
	initLcd1602,
	LcdShowStr,
};

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



// uint8_t KEY_1_DownMessage()
// {
// 	static uint8_t KeyValue_1;
// 	if (KeyVal == KEY_1_DOWN)
// 	{
// 		return eNABLE;	
// 	}

// 	else
// 		return dISABLE;

// }
// uint8_t KEY_1_LongMessage()
// {
// 	static uint8_t KeyValue_2;
// 	if (KeyVal == KEY_1_LONG)
// 	{
// 		return eNABLE;	
// 	}
// 	else
// 		return dISABLE;
// }




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

void bspInit()              //硬件初始化
{
    timer.setClock(&timer);

    bsp_InitKeyVar();       //按键初始化
    initLcd1602();          //lcd初始化
    EnevHancleInit(&myevent);
    evenConnector(&myevent,
              KEY_1_LongMessage,
              timeSwitch,
              0);
    evenConnector(&myevent,
              KEY_1_DownMessage,
              timeadd,
              1);
	Timer1Init();
   // timer0Init();           //中断初始化
}
void timer1Init()           //1ms中断初始化
{
    TMOD |= 0X10;

    TH1 = 0XD8; 
    TL1 = 0XF0;
    ET1 = 1;
    EA = 1;
    TR1 = 1;
}
//void Timer0Init(void)		//50毫秒@12.000MHz
//{
//	TMOD |= 0X01;
//	TL0 = 0xB0;		//设置定时初值
//	TH0 = 0x3C;		//设置定时初值
//	TF0 = 0;		//清除TF1标志
//	TR0 = 1;		//定时器1开始计时
//}


static void task10ms()      //10ms任务
{
    bsp_KeyScan();
    //bsp_DetectKey(0);
    evenTrigger(&myevent);
}

static void task5ms() // 5ms任务
{
	showIncident(&timer);
}


//void Timer0() interrupt 1   //中断服务函数
//{
//    
//	static char time_num100;    //中断次数，一次10ms

//    TL0 = 0xB0;
//	TH0 = 0x3C;
//	time_num100++;
//     if (time_num100 == 2)     // 10ms
//     {
//        time_num100 = 0;
//         
//		showIncident(&timer);


//     }

//}


void Timer1() interrupt 3   //中断服务函数
{
	static char time_num20; //中断次数，一次10ms
	static char time_num10; //中断次数，一次10ms

	TH1 = 0XD8;
	TL1 = 0XF0;
	time_num20++;
	time_num10++;
	if (time_num20 == 10) // 10ms
	{
		time_num20 = 0;
		task5ms();
	}
	if (time_num10 == 1) // 10ms
	{
		time_num10 = 0;
		task10ms();
	}
}


void mainSetClock(TIMER_T * t)
{

	ds1302Init(t->timeBuffer);
}

void mainShowClock(TIMER_T * t)//显示正在设置的时间
{

	 unsigned  char buf_s[10]={0};
	 unsigned  char buf_d[10]={0};

	buf_s[0] = (t->timeBuffer[2]/16)+0x30;				
	buf_s[1] = (t->timeBuffer[2]&0x0f)+0x30;				 
	buf_s[2] = '-';
	buf_s[3] = (t->timeBuffer[1]/16)+0x30;				
	buf_s[4] = (t->timeBuffer[1]&0x0f)+0x30;	
	buf_s[5] = '-';
	buf_s[6] = (t->timeBuffer[0]/16)+0x30;				
	buf_s[7] = (t->timeBuffer[0]&0x0f)+0x30;

	buf_d[0] = (t->timeBuffer[6] / 16) + 0x30; 
	buf_d[1] = (t->timeBuffer[6] & 0x0f) + 0x30;
	buf_d[2] = '-';
	buf_d[3] = (t->timeBuffer[4] / 16) + 0x30; 
	buf_d[4] = (t->timeBuffer[4] & 0x0f) + 0x30;
	buf_d[5] = '-';
	buf_d[6] = (t->timeBuffer[3] / 16) + 0x30; 
	buf_d[7] = (t->timeBuffer[3] & 0x0f) + 0x30;
	LcdShowStr(0,0,buf_s); 
	LcdShowStr(0,1,buf_d); 
	
}

void mainRefreshClock(TIMER_T * t)//显示时钟芯片的时间
{
	 unsigned  char buffer_1[9]={0};
	 unsigned  char buffer_2[13]={0};
	
	dataPros(buffer_1,buffer_2);

	LcdShowStr(0,0,buffer_1); 
	LcdShowStr(0,1,buffer_2);   

}

void dataPros(uint8_t *buf_s,uint8_t *buf_d)//读取时间并且转换为10进制
{
	uint8_t datas[8];
   	ds1302ReadTime(datas);
	buf_s[0] = (datas[2]/16)+0x30;				//时
	buf_s[1] = (datas[2]&0x0f)+0x30;				 
	buf_s[2] = '-';
	buf_s[3] = (datas[1]/16)+0x30;				//分
	buf_s[4] = (datas[1]&0x0f)+0x30;	
	buf_s[5] = '-';
	buf_s[6] = (datas[0]/16)+0x30;				//秒
	buf_s[7] = (datas[0]&0x0f)+0x30;

	buf_d[0] = (datas[6] / 16) + 0x30; //日
	buf_d[1] = (datas[6] & 0x0f) + 0x30;
	buf_d[2] = '-';
	buf_d[3] = (datas[4] / 16) + 0x30; //月
	buf_d[4] = (datas[4] & 0x0f) + 0x30;
	buf_d[5] = '-';
	buf_d[6] = (datas[3] / 16) + 0x30; //年
	buf_d[7] = (datas[3] & 0x0f) + 0x30;
}