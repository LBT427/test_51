/*
 * @Author: liubotao
 * @Date: 2022-08-29 16:37:40
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-29 09:16:24
 * @FilePath: \test_51\USER\main.c
 * @Description: ¾ØÕó°´¼ü¼ì²â
 *
 */
#include "reg51.h"
#include "bsp.h"
//#include "fifo.h"
#include "EventHandler.h"

//extern EVEN_T myevent;
//extern  FIFO f_K;

#define key P1
#define led P2


// uint8_t KEY_1_LongMessage(EVEN_T *pEven)
// {
// 	if (deQueue(&f_K) == KEY_1_LONG)
// 		return eNABLE;
// 	else
// 		return dISABLE;
// }







int main()
{
	bspInit();
	LcdShowStr(0,0,"hello");    			  
	while (1);
}
    