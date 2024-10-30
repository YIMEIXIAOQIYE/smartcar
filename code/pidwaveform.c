#include "pidwaveform.h"
#include "encoder.h"
#include "zf_common_headfile.h"
void piddisplayinit()
   {
        wireless_uart_init();
        seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
        // ��ʼ���������ʾ�����Ľṹ��
        seekfree_assistant_oscilloscope_struct oscilloscope_data;
        oscilloscope_data.data[0] = RC_encoder1;
        oscilloscope_data.data[1] = RC_encoder2;
        oscilloscope_data.data[2] = RC_encoder3;
        oscilloscope_data.data[3] = RC_encoder4;
        // ����Ϊ4��ͨ����ͨ���������Ϊ8��
        oscilloscope_data.channel_num = 4;
/////////����д��������ѭ������
			  seekfree_assistant_oscilloscope_send(&oscilloscope_data);
		oscilloscope_data.data[0] =RC_encoder1;
		oscilloscope_data.data[1] =RC_encoder2;
		oscilloscope_data.data[2] =RC_encoder3;
		oscilloscope_data.data[3] =RC_encoder4;
	
		

   }
void pidloop()
{

}
//#include "zf_common_headfile.h"
//#include "motor.h"
//#include "encoder.h"
//#include "attitude_solution.h"
//#include "flash_param.h"
//#include "location.h "
//#include "timer.h"
//#include "smotor.h"
//#include "display.h"
//#include "all_init.h"
//#include "menu.h"
//#define LED1 (B9)
//extern int angelTarget;
//// float Angel_KP = 0.35f;
//// float Angel_KD = 1.5f;
////float Angel_KI = 0;
//uint8 data_buffer[10];
//int main(void)
//{
//	clock_init(SYSTEM_CLOCK_600M); // ����ɾ��
//	debug_init();				   // ���Զ˿ڳ�ʼ��
//	DisableGlobalIRQ();
//	gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);
////	buzzeropen(300);
//	all_init();
//	wireless_uart_init();
//	// �����������ʹ��DEBUG���ڽ����շ�
//    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
//    // ��ʼ���������ʾ�����Ľṹ��
//    seekfree_assistant_oscilloscope_struct oscilloscope_data;
////    oscilloscope_data.data[0] = RC_encoder1;
////    oscilloscope_data.data[1] = RC_encoder2;
////    oscilloscope_data.data[2] = RC_encoder3;
////    oscilloscope_data.data[3] = RC_encoder4;
//    // ����Ϊ4��ͨ����ͨ���������Ϊ8��
//    oscilloscope_data.channel_num = 4;
//	system_delay_ms(300);
//	EnableGlobalIRQ(0);
//	while (1)
//	{
//		if (imu660ra_init())
//		{
//			ips200_show_string(0, 16 * 11, "error");
//		}
//		else
//		{
//			ips200_show_string(0, 16 * 11, "finish");
//			break;
//		}
//		gpio_toggle_level(LED1); // ��ת LED ���������ƽ ���� LED ���� ��ʼ����������ƻ����ĺ���
//	}
//	while (1)
//	{
//		basic_information();
//		mode_change();
//		if(KEY_SHORT_PRESS == key_get_state(KEY_4))	
//		{
//			key_clear_state(KEY_4);
//			break;
//		}
//	}
//	while(1)
//    {
//        if(mt9v03x_init())
//            ips200_show_string(0, 18, "mt9v03x reinit.");
//        else
//            break;
//        system_delay_ms(500);                                                   // ����ʱ�������Ʊ�ʾ�쳣
//    }
//	
//		timerbegin();
////		pickup();
////		system_delay_ms(1000);
//  	Car.Angel_Target=0;
//	Car.Speed_X = 0, Car.Speed_Y = 35;
////	Car.Speed_Z=0;
//	
//	while (1)
//	{
//		if(mt9v03x_finish_flag)
//        {
//            ips200_displayimage03x((const uint8 *)mt9v03x_image, 240, 180);
//            mt9v03x_finish_flag = 0;
//        }
//		seekfree_assistant_oscilloscope_send(&oscilloscope_data);
//		oscilloscope_data.data[0] =RC_encoder1;
//		oscilloscope_data.data[1] =RC_encoder2;
//		oscilloscope_data.data[2] =RC_encoder3;
//		oscilloscope_data.data[3] =RC_encoder4;
//		system_delay_ms(100);
//		// angelTarget=90;
//		basic_information();
//		gpio_toggle_level(LED1);
//		system_delay_ms(10);
//		// �˴���д��Ҫѭ��ִ�еĴ���
//	}
//}
