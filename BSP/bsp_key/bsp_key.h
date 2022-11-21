/*** 
 * @Author: liubotao
 * @Date: 2022-11-18 00:13:57
 * @LastEditors: liubotao
 * @LastEditTime: 2022-11-21 11:21:50
 * @FilePath: \test_51\BSP\bsp_key\bsp_key.h
 * @Description: �������;��󰴼����
 * @
 */
#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "type.h"


int matrixKeyScan_1();
int matrixKeyScan_2();
int matrixKeyScan_3();

extern self_t KeyValue;

typedef enum
{
	KEY_NONE = 0,			

	KEY_1_DOWN,				// 1������
	KEY_1_UP,				// 1������
	KEY_1_LONG,				// 1������

	KEY_2_DOWN,				// 2������ 
	KEY_2_UP,				// 2������ 
	KEY_2_LONG,				// 2������ 

}KEY_ENUM;


typedef struct
{

	unsigned char (*IsKeyDownFunc)(void); 	// ָ���жϰ����ַ��µĺ���,1��ʾ����

	unsigned char  	Count;					// �˲���������
	unsigned int 	LongCount;				// ����������
	unsigned int 	LongTime;				// �������³���ʱ��, 0��ʾ����ⳤ��
	unsigned char  	State;					// ������ǰ״̬�����»��ǵ���
	unsigned char  	RepeatSpeed;			// ������������
	unsigned char  	RepeatCount;			// ��������������
	
}KEY_T;


#define KEY_FIFO_SIZE 		10			//����FIFO��С


#define KEY_COUNT    		2	   		// ��������,  2�� 
#define KEY_FILTER_TIME   	5      	//�˲�ʱ�� ������⵽ n ms״̬���� �൱�ڰ�ס 2*n ms
#define KEY_LONG_TIME     	100			// ��λ10ms�� ����1�룬��Ϊ�����¼� 


void bsp_KeyScan(void);
unsigned char bsp_GetKey(void);
void bsp_InitKeyVar(void);


#endif
