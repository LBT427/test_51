/*** 
 * @Author: liubotao
 * @Date: 2022-11-18 00:13:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-28 20:59:45
 * @FilePath: \test_51\BSP\bsp_key\bsp_key.h
 * @Description: �������;��󰴼����
 * @
 */
#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "type.h"

///////////////////////////////////////////���󰴼�����///////////////////////////////////////////////

//#define keyboard P1


int8_t matrixKeyScan_1();
int8_t matrixKeyScan_2();
int8_t matrixKeyScan_3();

//extern xdata uint8_t KeyValue;

#define keyUncertainTime 3  //����ʱ�� ( x10 ms)

///////////////////////////////////////////������������///////////////////////////////////////////////

sbit key_1= P3^0;
//sbit key_2 =P3^1;
typedef enum
{
	KEY_NONE = 0,			

	KEY_1_DOWN,				// 1������
	KEY_1_UP,				// 1������
	KEY_1_LONG,				// 1������

//	KEY_2_DOWN,				// 2������ 
//	KEY_2_UP,				// 2������ 
//	KEY_2_LONG,				// 2������ 

}KEY_ENUM;


typedef struct
{

	uint8_t     (*IsKeyDownFunc)(void); 	// ָ���жϰ����ַ��µĺ���,1��ʾ����

	uint8_t  	Count;					// �˲���������
	uint16_t 	LongCount;				// ����������
	uint16_t 	LongTime;				// �������³���ʱ��, 0��ʾ����ⳤ��
	uint8_t  	State;					// ������ǰ״̬�����»��ǵ���
	
}KEY_T;


#define KEY_FIFO_SIZE 		0			//����FIFO��С


#define KEY_COUNT    		1	   		// ��������,  2�� 
#define KEY_FILTER_TIME   	5      		//�˲�ʱ�� ������⵽ n ms״̬���� �൱�ڰ�ס 2*n ms
#define KEY_LONG_TIME     	40			// ��λ10ms�� ����1�룬��Ϊ�����¼� 


void bsp_KeyScan(void);
uint8_t bsp_GetKey(void);
void bsp_InitKeyVar(void);


#endif
