#include "encoder.h"
#include "filter.h"
//#include "location.h"
#include "flash_param.h"
#include "zf_common_headfile.h"
#include "attitude_solution.h"
//float MileageKy=0.01079f;
float MileageKy=0.00866f;
float MileageKx=0.0095f;

//---------------------�ṹ��---------------------//
struct RC_Para Encoder1_Para = {0,0,0.25};
struct RC_Para Encoder2_Para = {0,0,0.25};
struct RC_Para Encoder3_Para = {0,0,0.25};
struct RC_Para Encoder4_Para = {0,0,0.25};

RC_Filter_pt RC_Encoder1 = &Encoder1_Para;
RC_Filter_pt RC_Encoder2 = &Encoder2_Para;
RC_Filter_pt RC_Encoder3 = &Encoder3_Para;
RC_Filter_pt RC_Encoder4 = &Encoder4_Para;

int32 encoder1=0,encoder2=0,encoder3=0,encoder4=0;//��������ֵ
int32 RC_encoder1,RC_encoder2,RC_encoder3,RC_encoder4;//�˲�֮��encoder��ֵ
uint16 speed_l, speed_r;


void encoder_init(void)
{
    //һ��QTIMER���� ����������������
    encoder_quad_init(QTIMER2_ENCODER2,QTIMER2_ENCODER2_CH1_C5,QTIMER2_ENCODER2_CH2_C25);//2
    
    encoder_quad_init( QTIMER2_ENCODER1,QTIMER2_ENCODER1_CH1_C3, QTIMER2_ENCODER1_CH2_C4 );//1
    
    //��ʼ�� QTIMER_1 A��ʹ��QTIMER1_TIMER0_C0 B��ʹ��QTIMER1_TIMER1_C1
    encoder_quad_init(QTIMER1_ENCODER1,QTIMER1_ENCODER1_CH1_C0,QTIMER1_ENCODER1_CH2_C1 );//3
    //��ʼ�� QTIMER_1 A��ʹ��QTIMER2_TIMER0_C3 B��ʹ��QTIMER2_TIMER3_C25

    encoder_quad_init(QTIMER1_ENCODER2,QTIMER1_ENCODER2_CH1_C2,QTIMER1_ENCODER2_CH2_C24);//4
}

void omni_mileage(){
    float detax=0,detay=0;
    detay=(float)(-RC_encoder1 + RC_encoder2 + RC_encoder3 - RC_encoder4)/4;
    detax=(float)(-RC_encoder1 - RC_encoder2 - RC_encoder3 - RC_encoder4)/4;
    Car.MileageY+=(float)(detay*MileageKy);
    Car.MileageX+=(float)(detax*MileageKx);
}

void encoder_get(void)
{
	
    encoder1 = encoder_get_count(QTIMER2_ENCODER2);//������Ҫע��ڶ������������дA������
    encoder2 = encoder_get_count(QTIMER2_ENCODER1);//������Ҫע��ڶ������������дA������
    encoder3 = - encoder_get_count(QTIMER1_ENCODER1);//������Ҫע��ڶ������������дA������
    encoder4 = - encoder_get_count(QTIMER1_ENCODER2);//������Ҫע��ڶ������������дA������
    //����λ��(��λ��m)
    //Car.mileage=(Encoder/1024)*(45/104)*2*PI*0.03;
    omni_mileage();

    RC_encoder1 = (int16_t)RCFilter(encoder1,RC_Encoder1);
    RC_encoder2 = (int16_t)RCFilter(encoder2,RC_Encoder2);
    RC_encoder3 = (int16_t)RCFilter(encoder3,RC_Encoder3);
    RC_encoder4 = (int16_t)RCFilter(encoder4,RC_Encoder4);

    encoder_clear_count (QTIMER2_ENCODER2 );
    encoder_clear_count (QTIMER2_ENCODER1 );
    encoder_clear_count (QTIMER1_ENCODER1 );
    encoder_clear_count (QTIMER1_ENCODER2 );
}

