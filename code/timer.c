#include "zf_common_headfile.h"
#include "attitude_solution.h"
#include "encoder.h"
#include "motor.h"
#include "timer.h"
#include "zf_driver_pit.h"
#include "imagine.h"
#include "camera.h"
#include  "motor.h"
#define PIT_CH                         (PIT_CH0 ) 
uint32 getAngel_times=0;
double getAngel_k=0;
double getAngelN=0;
float getAngel_Err=0.000095f;
extern int stop;
extern uint8 fifo_get_data[64];                                                        // fifo �������������
extern int PWM_LIMIT;

extern int go;
extern int u;

extern int x;
extern uint32 fifo_data_count ; 
extern fifo_struct uart_data_fifo;
extern int i;
extern uint8 get_data ;   
extern uint8 get_location;// �������ݱ���
void Find_Edge_1	(void);
//��ǰ��̬
extern int angelTarget;
uint16 msecond=0,time_second=0;
extern uint8 fifo_get_data[64];   
void pit_handler (void)
{
		static uint32 time;
		msecond++;
		time++;
		if(0==(time_second%1000))
		{
				time_second++;
		}

		if( 0==(time%2)){
				//�ɼ����������� 
				//Mahony_computeAngles();
				getAngel_times++;
//			    gyroOffset_init();
				ICM_getEulerianAngles();
		}

		//�ɼ����������� 
		//Mahony_computeAngles();
		//ICM_getEulerianAngles();
		eulerAngle.yaw=eulerAngle.yaw-getAngel_Err*getAngel_times;
   		Car.Angel=eulerAngle.yaw;
		//��ȡ��������ֵ
		encoder_get();
		Car.Speed_Z=angel_pid(eulerAngle.yaw,Car.Angel_Target);
//		fifo_data_count = fifo_used(&uart_data_fifo);                           // �鿴 fifo �Ƿ�������
//        if(fifo_data_count != 0)                                                // ��ȡ��������
//        {
//            fifo_read_buffer(&uart_data_fifo, fifo_get_data, &fifo_data_count, FIFO_READ_AND_CLEAN);    // �� fifo �����ݶ�������� fifo ���صĻ���
//						if(fifo_get_data[0]==122&&fifo_get_data[3]==119)
//						{
//								if(fifo_get_data[1]>0&&fifo_get_data[2]>15)
//							{
//									if(fifo_get_data[1]>22&&fifo_get_data[2]>43)
//							 {	
////								if(i==0)
////								{
////									stop=500;
////											
////								}
//								i++;
////								stop=0;
//								if(i==1)
//								{
//									Car.Angel_Target =90;// Car.Angel + 90;
//								}						
//								
//								PWM_LIMIT=1000;
////								if(Car.Angel_Target>=90)
////								{
////										Car.Speed_X = picture_xerror_pid(fifo_get_data[1],70);
////										Car.Speed_Y = picture_yerror_pid(fifo_get_data[2],40);	

////								}
//							 }	
//							}
//						
//							if(abs(Car.Angel)>Car.Angel_Target)
//             {	
//							Car.Speed_X = picture_xerror_pid(fifo_get_data[1],71);
//              Car.Speed_Y = picture_yerror_pid(fifo_get_data[2],46);
//						}
//						if(fifo_get_data[1]>30&&fifo_get_data[1]<40&&fifo_get_data[2]>33&&fifo_get_data[2]<38)
//						{
//							stop=500;
//							pickup();
//						}
							
						if(go==1000000)
						{
							    stop=0;
								  x=0;
									Car.Speed_Y = 60;
									u=0;
						}
						
		
		if(u==0)
		{
  			car_omni(-offset_2,-Car.Speed_Y,offset);
		}
		if(x==10086)
		{
			car_omni(Car.Speed_X,Car.Speed_Y,Car.Speed_Z);//+Car.Angel);
		}
//		
//	  
//		
//		
		//���Ƶ��ת��
		motor_control(true);
}
void pit_handler1(void)
{
	Camera_All_Deal();
	
}	
void pit_handler2(void)
{
	 fifo_data_count = fifo_used(&uart_data_fifo);
	if(abs(Car.Angel)>Car.Angel_Target)
             {	
							Car.Speed_X = picture_xerror_pid(fifo_get_data[1],90);
              Car.Speed_Y = picture_yerror_pid(fifo_get_data[2],46);
						}
}	
void timerbegin()
{
	pit_ms_init(PIT_CH0, 5);
//	pit_ms_init(PIT_CH1, 10);
	pit_ms_init(PIT_CH2, 5);
	interrupt_global_enable(0);
}


