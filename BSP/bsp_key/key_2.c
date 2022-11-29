#include "bsp.h"
unsigned char KeyVal = 0;
unsigned char Count = 0;
unsigned char State = 0;
unsigned char LongTime = KEY_LONG_TIME;
unsigned char LongCount = 0;
unsigned char Double = 0;
unsigned char loose = 0;
void bsp_DetectKey(uint8_t i)
{
    //	KEY_T *pBtn;

    /*
        如果没有初始化按键函数，则报错
        if (s_tBtn[i].IsKeyDownFunc == 0)
        {
            printf("Fault : DetectButton(), s_tBtn[i].IsKeyDownFunc undefine");
        }
    */
    // Double++;
    // if (Double > 255)
    // {
    //     Double = 255;
    // }
    if (State == 1 && (++Double) == KEY_DOUBLE_TIME && loose != 0)
    {
        // State = 1;
        KeyVal = KEY_1_DOWN;
        State = 0;
        loose = 0;
    }
    // pBtn = &s_tBtn[i];
    if (GPIO_PIN_K1==0)
    {
        if (Count < KEY_FILTER_TIME)
        {
            Count = KEY_FILTER_TIME;
        }
        else if (Count < 2 * KEY_FILTER_TIME)
        {
            Count++;
        }
        else //按下
        {
           // Double = 0;

            // if (State == 1 && loose != 0)
            // {

            //     KeyVal = KEY_1_Double;
            //     loose = 0;
            //     State = 3;
            //     // break;
            // }

            if (State == 0)
            {
                State = 1;

                /* 发送按钮按下的消息 */
                //
                // bsp_PutKey((uint8_t)(3 * i + 1));
            }
            // else if (Double > KEY_DOUBLE_TIME)
            // {
            // 	State = 1;
            // 	bsp_PutKey((uint8_t)(3 * i + 1));
            // }

            else if (LongCount < KEY_LONG_TIME)
            {
                /* 发送按钮持续按下的消息 */
                if (++LongCount == KEY_LONG_TIME)
                {
                    /* 键值放入按键FIFO */
                    KeyVal = KEY_1_LONG;
                    State = 3;
                    loose = 0;
                    // bsp_PutKey((uint8_t)(3 * i + 3));
                }
            }
        }
    }
    else
    {
        if (Count > KEY_FILTER_TIME)
        {
            Count = KEY_FILTER_TIME;
        }
        else if (Count != 0)
        {
            Count--;
        }
        else
        {
            if (State == 3)
            {
                State = 0;
            }
            if (State == 1)
            {

                loose = 1;
                /* 发送按钮弹起的消息 */
                KeyVal = KEY_1_UP;
                LongCount = 0;
                // bsp_PutKey((uint8_t)(3 * i + 2));
            }
        }

        // RepeatCount = 0;
    }
}
