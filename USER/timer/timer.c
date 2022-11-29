/*
 * @Author: liubotao
 * @Date: 2022-11-05 16:40:34
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-28 16:09:17
 * @FilePath: \test_51\USER\timer\timer.c
 * @Description: 
 * 
 */
#include "timer.h"

#define BCDTODEC(bcd) ((bcd) = (bcd-(bcd>>4)*6))
#define DECTOBCD(dec) ((dec) = (dec+(dec/10)*6))

//void  setTimer(TIMER_T *time,uint8_t  modes,uint16_t num)
//{
//    time->setMode=modes;
//    time->timeBuffer[modes]=num;
//}
void  modeIncident(TIMER_T *time)
{
    uint8_t  timBuf[7]={0};
    uint8_t  num;
    //time->displayClear();
    time->rANDw= ~(time->rANDw);

    if (time->rANDw == 0)
    {
        for (num = 0; num < 7; num++)
        {
            timBuf[num]=time->timeBuffer[num];     
        }
        time->timerWrite(timBuf);  
    }
    else
    {
        time->timerRead(timBuf);
        for (num = 0; num < 7; num++)
        {
            time->timeBuffer[num]=timBuf[num];
            
        }
    }
}
void  switchIncident(TIMER_T *time)
{
    //time->displayClear();
    if (time->rANDw!=TIMSHOW)
    {
        time->setMode++;
        if (time->setMode==5)time->setMode=6;
        if (time->setMode > 6)
        {
            time->setMode=0;
        }
        
    }
}

void  addIncident(TIMER_T *time)
{
    uint8_t num1;
    if (time->rANDw != TIMSHOW)
    {
        num1 = time->timeBuffer[time->setMode];
        BCDTODEC(num1);
        num1++;
        if (time->setMode == 3)
        {
            if (num1 > 31)
                num1 = 1;
        }
        else if (time->setMode == 4)
        {
            if (num1 > 12)
                num1 = 1;
        }
        else if (time->setMode == 2)
        {
            if (num1 > 24)
                num1 = 0;
        }
        else if (time->setMode == 6)
        {
            if (num1 > 99)
                num1 = 0;
        }
        else if (time->setMode < 2)
        {
            if (num1 > 60)
                num1 = 0;
        }
        DECTOBCD(num1);
        
        
        time->timeBuffer[time->setMode]=num1;
        //time->refreshClock(time);
    }
    //time->displayClear();
}
void  subIncident(TIMER_T *time)
{
    uint8_t  num1;
    if (time->rANDw!=TIMSHOW)
    {
        num1=time->timeBuffer[time->setMode];
        BCDTODEC(num1);
        if(num1>0)num1--;
        DECTOBCD(num1);
        time->timeBuffer[time->setMode]=num1;
        //time->refreshClock(time);
    }
	//time->displayClear();
}

// void  showIncident(TIMER_T *time)
// {
//     if (time->rANDw==TIMSHOW)
//     {
//         time->displayWrite(12, 0, "Show");
//         time->refreshClock(time);
//     }
//     else
//     {
//         //time->displayBlinks(0, 0, 0);
//         time->showClock(time);

//         time->displayWrite(12, 0, "Set");

//         switch (time->setMode)
//         {
//         case second:
//             //time->displayWrite(6, 0, " ");
//             // time->displayBlinks(7, 0, 1);
//             // time->displayBlinks(6, 0, 1);
//             //time->displayWrite(11, 1, "second");
//             time->displayWrite(6, 0, "  ");
//             break;
//         case minute:
//             // time->displayBlinks(4, 0, 1);
//             // time->displayBlinks(3, 0, 1);
//             time->displayWrite(3, 0, "  ");
//             //time->displayWrite(11, 1, "minute");
//             break;
//         case hour:
//             // time->displayBlinks(1, 0, 1);
//             // time->displayWrite(0, 0, "  ");
//             //time->displayWrite(11, 1, "hour");
//             break;
//         case day:
//             // time->displayBlinks(7, 1, 1);
//             // time->displayBlinks(6, 1, 1);
//             time->displayWrite(6, 1, "  ");
//             //time->displayWrite(11, 1, "day");
//             break;
//         case month:
//             // time->displayBlinks(4, 1, 1);
//             // time->displayBlinks(3, 1, 1);
//             time->displayWrite(3, 1, "  ");
//             //time->displayWrite(11, 1, "month");
//             break;
//         case year:
//             // time->displayBlinks(1, 1, 1);
//             // time->displayBlinks(0, 1, 1);
//             time->displayWrite(0, 1, "  ");
//             //time->displayWrite(11, 1, "year");
//             break;
//         default:
//             time->displayWrite(11, 1, "err");
//             break;
            
//         }
//     }
// }








void  showIncident(TIMER_T *time)
{
    time->num+=100;
    if (time->rANDw==TIMSHOW)
    {
        time->refreshClock(time);
    }
    else
    {
        if (time->num > 500)
        {
            //time->num=0;
            switch (time->setMode)
            {
            case second:
                time->displayWrite(6, 0, "  ");
                break;
            case minute:
                time->displayWrite(3, 0, "  ");
                break;
            case hour:
                time->displayWrite(0, 0, "  ");
                break;
            case day:
                time->displayWrite(6, 1, "  ");
                break;
            case month:
                time->displayWrite(3, 1, "  ");
                break;
            case year:

                time->displayWrite(0, 1, "  ");
                break;
            default:
                time->displayWrite(11, 1, "err");
                break;
            }
        }
        if(time->num > 1000)
        {
            time->num=0;
            time->showClock(time);
        }
    }
}