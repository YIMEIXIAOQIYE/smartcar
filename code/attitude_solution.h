#ifndef __ATTITUDE_SOLUTION_H_
#define __ATTITUDE_SOLUTION_H_

#include "zf_common_headfile.h"
typedef struct {
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float acc_x;
    float acc_y;
    float acc_z;
} icm_param_t;


typedef struct {
    float q0;
    float q1;
    float q2;
    float q3;
} quater_param_t;


typedef struct {
    float pitch;    //������
    float roll;     //ƫ����
    float yaw;       //������
} euler_param_t;


typedef struct {
    float Xdata;
    float Ydata;
    float Zdata;
} gyro_param_t;

typedef struct location_goal{

    double Speed_X;
    double Speed_Y;
    double Speed_Z;

    float Angel;
    //Ŀ����̬
    double Angel_Target;
	    //��ǰλ��
    float x;
    float y;
    //Ŀ��λ��
    float x1;
    float y1;
    //Ŀ�����
    float DistanceX;
    float DistanceY;
    //���ϴ�ת��֮��ǰ���ľ���(��̣�
    float MileageX;
    float MileageY;
	  float mileage;
		float Speed_Z1;
}location_goal;

extern location_goal Car;
extern quater_param_t Q_info ;  // ȫ����Ԫ��
extern euler_param_t eulerAngle;
void gyroOffset_init(void);

float fast_sqrt(float x);

void ICM_AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az);

void ICM_getValues();

void ICM_getEulerianAngles(void);
#endif

