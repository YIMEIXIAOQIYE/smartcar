#include "zf_common_headfile.h"
#include "motor.h"
#include "smotor.h"
extern float Position_KP ;
extern float Position_KI ;
extern float Position_KD ;
extern float Angel_KP ;
extern float Angel_KD ;
extern float Angel_KI ;
extern float pictureD ;
extern float pictureI ;
extern float pictureP ;
extern int nus;
#define SWITCH1             (C27)
#define SWITCH2             (C26)
void  mode_change(void)
{
        key_init(5);
        gpio_init(SWITCH1, GPI, GPIO_HIGH, GPI_PULL_UP);
        gpio_init(SWITCH2, GPI, GPIO_HIGH, GPI_PULL_UP);
        key_scanner();
        if(KEY_SHORT_PRESS == key_get_state(KEY_1))
        {
           //pictureP+=0.001;
					nus+=20;
	//				Angel_KP+=1;
            key_clear_state(KEY_1);
        }
         if(KEY_LONG_PRESS == key_get_state(KEY_1))
        {
           // pictureP-=0.001;
					nus-=20;
		//			Angel_KP-=1;
					system_delay_ms(300);
            key_clear_state(KEY_1);
        }
        if(KEY_SHORT_PRESS == key_get_state(KEY_2))                         // ���ⰴ���̰�
        {
             pictureD+=0.001;
            key_clear_state(KEY_2);
            // �̰��İ������ɿ�ʱ ״̬�Żᱻ key_scanner ��λΪ KEY_SHORT_PRESS
            // ���Ե����������״̬  
        }
         if(KEY_LONG_PRESS == key_get_state(KEY_2))
        {
            pictureD-=0.001;
					system_delay_ms(300);
            key_clear_state(KEY_2);
				
        }
         if(KEY_SHORT_PRESS == key_get_state(KEY_3))                         // ���ⰴ���̰�
        {
//             Position_KD+=1;
						Angel_KD+=1;
            key_clear_state(KEY_3);
            // �̰��İ������ɿ�ʱ ״̬�Żᱻ key_scanner ��λΪ KEY_SHORT_PRESS
            // ���Ե����������״̬       
        }
         if(KEY_LONG_PRESS == key_get_state(KEY_3))
        {
//            Position_KD-=1;
					Angel_KD-=1;
					system_delay_ms(300);
            key_clear_state(KEY_3);
        }
}