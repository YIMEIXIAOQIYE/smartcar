#include "attitude_solution.h"
#include <math.h>
#include "zf_common_headfile.h"

#define sampleFreq	100.f			// sample frequency in Hz
/*�������ڵ�һ�룬���������Ԫ��΢�ַ���ʱ���������
��ȷ���Լ�����̬��������: 5ms,�������sampleFreq: 200Hz*/
#define halfT 0.00445f*2.5/3*0.6*2;
 
//�����Kp,Ki�����ڿ��Ƽ��ٶȼ����������ǻ�����̬���ٶ�
//#define Kp 10.0f  //2.0f
//#define Ki 0.008f  //0.002f
 #define Kp 0.18f  //2.0f
#define Ki 0.003f  //0.002f
 
//��ʼ��̬��Ԫ��(��������ϵ)��q(q0,q1,q2,q3)
static float q0 = 1, q1 = 0, q2 = 0, q3 = 0; //���Ź�����Ԫ��
//������̬�������Ļ���.     
//��ǰ�ӼƲ�õ��������ٶ�������(x,y,z)�ϵķ���,�뵱ǰ��̬��������������������ϵķ��������Ļ���
static float xErrorInt = 0, yErrorInt = 0, zErrorInt = 0;
 
//#define delta_T     0.002f  //2ms����һ��
#define M_PI        3.1415926f

//float I_ex, I_ey, I_ez;  // ������

location_goal Car={0};

quater_param_t Q_info = {1, 0, 0};  // ȫ����Ԫ��
euler_param_t eulerAngle; //ŷ����

icm_param_t icm_data;
gyro_param_t GyroOffset;
bool GyroOffset_init = 0;
//float param_Kp = 0.18;   // ���ٶȼƵ��������ʱ�������
//float param_Ki = 0.003;   //�������������ʵĻ������� 0.004

//float fast_sqrt(float x) {
//    float halfx = 0.5f * x;
//    float y = x;
//    long i = *(long *) &y;
//    i = 0x5f3759df - (i >> 1);
//    y = *(float *) &i;
//    y = y * (1.5f - (halfx * y * y));
//    return y;
//}
void  gyroOffset_init(void)      /////////��������Ʈ��ʼ��
{

    GyroOffset.Xdata = 0;
    GyroOffset.Ydata = 0;
    GyroOffset.Zdata = 0;
    for (uint16_t i = 0; i < 500; ++i) {
        imu660ra_get_gyro();
        imu660ra_get_acc();
        // get_icm20602_gyro_spi();
        // get_icm20602_accdata_spi();
        GyroOffset.Xdata += imu660ra_gyro_x;
        GyroOffset.Ydata += imu660ra_gyro_y;
        GyroOffset.Zdata += imu660ra_gyro_z;
         system_delay_ms(10);
    }

    GyroOffset.Xdata /= 500;
    GyroOffset.Ydata /= 500;
    GyroOffset.Zdata /= 500;

    GyroOffset_init = 1;
}


#define alpha           0.3f

//ת��Ϊʵ������ֵ
void ICM_getValues() {
    /*
        //һ�׵�ͨ�˲�����λg/s
    source_data.acc_x = (((float)imu963ra_acc_x) * alpha) * 8 / 4098 + source_data.acc_x * (1 - alpha);
    source_data.acc_y = (((float)imu963ra_acc_y) * alpha) * 8 / 4098 + source_data.acc_y * (1 - alpha);
    source_data.acc_z = (((float)imu963ra_acc_z) * alpha) * 8 / 4098 + source_data.acc_z * (1 - alpha);

    //�����ǽǶ�ת����
    source_data.gyro_x = ((float)imu963ra_gyro_x - Gyro_Offset.Xdata) * M_PI / 180 / 14.3f;
    source_data.gyro_y = ((float)imu963ra_gyro_y - Gyro_Offset.Ydata) * M_PI / 180 / 14.3f;
    source_data.gyro_z = ((float)imu963ra_gyro_z - Gyro_Offset.Zdata) * M_PI / 180 / 14.3f;
  
    //������ת������
   source_data.mag_x = (float)imu963ra_mag_x / 3000.0f;
   source_data.mag_y = (float)imu963ra_mag_y / 3000.0f;
   source_data.mag_z = (float)imu963ra_mag_z / 3000.0f;
    */

       //һ�׵�ͨ�˲�����λg/s
    icm_data.acc_x = (((float) imu660ra_acc_x) * alpha) * 8 / 4098 + icm_data.acc_x * (1 - alpha);
    icm_data.acc_y = (((float) imu660ra_acc_y) * alpha) * 8 / 4098 + icm_data.acc_y * (1 - alpha);
    icm_data.acc_z = (((float) imu660ra_acc_z) * alpha) * 8 / 4098 + icm_data.acc_z * (1 - alpha);


    //�����ǽǶ�ת����
    icm_data.gyro_x = ((float) imu660ra_gyro_x - GyroOffset.Xdata) * M_PI / 180 / 14.3f;
    icm_data.gyro_y = ((float) imu660ra_gyro_y - GyroOffset.Ydata) * M_PI / 180 / 14.3f;
    icm_data.gyro_z = ((float) imu660ra_gyro_z - GyroOffset.Zdata) * M_PI / 180 / 14.3f;

    // //һ�׵�ͨ�˲�����λg/s
    // icm_data.acc_x = (((float) icm_acc_x) * alpha) * 8 / 4096 + icm_data.acc_x * (1 - alpha);
    // icm_data.acc_y = (((float) icm_acc_y) * alpha) * 8 / 4096 + icm_data.acc_y * (1 - alpha);
    // icm_data.acc_z = (((float) icm_acc_z) * alpha) * 8 / 4096 + icm_data.acc_z * (1 - alpha);


    // //�����ǽǶ�ת����
    // icm_data.gyro_x = ((float) icm_gyro_x - GyroOffset.Xdata) * M_PI / 180 / 16.4f;
    // icm_data.gyro_y = ((float) icm_gyro_y - GyroOffset.Ydata) * M_PI / 180 / 16.4f;
    // icm_data.gyro_z = ((float) icm_gyro_z - GyroOffset.Zdata) * M_PI / 180 / 16.4f;
}

/*
 * 6����������̬�ں��㷨:  Mahony�Ļ����˲��㷨 6���
 * ��λ: m/s^2   rad/s
 * ���ڼ��ٶȵ������ܴ�, �˴�����ʹ���˲��������
 * */
void MahonyImuUpdate(float gx, float gy, float gz, float ax, float ay, float az)//g�������ǣ�a��Ӽ�
{
    float q0temp,q1temp,q2temp,q3temp;//��Ԫ���ݴ���������"΢�ַ���"ʱҪ��
    float norm; //ʸ����ģ����Ԫ���ķ���
    float posture_x, posture_y, posture_z;//��ǰ��̬��������������������ϵķ���
    //��ǰ�ӼƲ�õ��������ٶ��������ϵķ���,���õ�ǰ��̬��������������������ϵķ��������
    float error_x, error_y, error_z;
 
    // �Ȱ���Щ�õõ���ֵ���
    float q0q0 = q0*q0, q0q1 = q0*q1, q0q2 = q0*q2, q0q3 = q0*q3, q1q1 = q1*q1, q1q2 = q1*q2;
    float q1q3 = q1*q3, q2q2 = q2*q2, q2q3 = q2*q3, q3q3 = q3*q3;
 
    //�Ӽƴ�����������״̬ʱ��������̬���㣬��Ϊ�������ĸ���������
    if( (ax == 0.0f) && (ay == 0.0f) && (az == 0.0f) )
       return;
 
    //�����ٶȵ�ԭʼ���ݽ��й�һ��,�õ���λ���ٶ�
    norm = sqrt(ax*ax + ay*ay + az*az);//��λ�����ٶȼƣ�
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;
 
    //�õ�ǰ��̬(�ο�����nϵ)������������������ϵķ���(��������bϵ)��
    /*����Ԫ�������"�������Ҿ���"�еĵ����е�����Ԫ��.�������Ҿ����ŷ���ǵĶ���,��������ϵ����������,ת����������ϵ,������������Ԫ��.*/
    posture_x = 2*(q1q3 - q0q2);
    posture_y = 2*(q0q1 + q2q3);
    posture_z = q0q0 - q1q1 - q2q2 + q3q3;
//		 posture_z = 1-2*q1*q1-2*q2*q2;
    //����: ��������õ������뵱ǰ��̬������������������������Ա�ʾ��һ���
    // Error is sum of cross product between estimated and measured direction of gravity
    error_x = (ay*posture_z - az*posture_y) ;
    error_y = (az*posture_x - ax*posture_z) ;
    error_z = (ax*posture_y - ay*posture_x) ;
 
    //���������������Ĳ�������л���
    xErrorInt = xErrorInt + error_x * Ki;// * (1.0f / sampleFreq);
    yErrorInt = yErrorInt + error_y * Ki;// * (1.0f / sampleFreq);
    zErrorInt = zErrorInt + error_z * Ki;// * (1.0f / sampleFreq);
 
    //���������������Ĳ�����Ļ�����p,i����������ƫ,ͨ������Kp,Ki��������,���Կ��Ƽ��ٶȼ����������ǻ�����̬���ٶ�
    gx = gx + Kp*error_x + xErrorInt;  //�����PI�󲹳��������ǣ����������Ư��
    gy = gy + Kp*error_y + yErrorInt;
    gz = gz + Kp*error_z + zErrorInt; //�����gz����û�й۲��߽��н��������Ư�ƣ����ֳ����ľ��ǻ����������Լ�
 
    // Integrate rate of change of quaternion
    //gx *= (1.0f / sampleFreq);		// pre-multiply common factors
    //gy *= (1.0f / sampleFreq);
    //gz *= (1.0f / sampleFreq);
 
    //���������̬�ĸ��£�Ҳ������Ԫ��΢�ַ��̵����
    q0temp=q0;//�ݴ浱ǰֵ���ڼ���
    q1temp=q1;
    q2temp=q2;
    q3temp=q3;
 
    //��Ԫ��΢�ַ���. ����һ�ױϿ��ⷨ���ںϵ�ǰλ�˺������ǲ���ֵ,��ת��������ο�����ϵN. 
    q0 = q0temp + (-q1temp*gx - q2temp*gy -q3temp*gz)*halfT;
    q1 = q1temp + (q0temp*gx + q2temp*gz -q3temp*gy)*halfT;
    q2 = q2temp + (q0temp*gy - q1temp*gz +q3temp*gx)*halfT;
    q3 = q3temp + (q0temp*gz + q1temp*gy -q2temp*gx)*halfT;
 
    //�Ե�ǰ��̬��Ԫ�����е�λ��,��λ����Ԫ���ڿռ���תʱ�������죬������ת�Ƕ�
    norm = sqrt(q0q0 + q1q1 + q2q2 + q3q3);
//    q0 = q0 / norm;
//    q1 = q1 / norm;
//    q2 = q2 / norm;
//    q3 = q3 / norm;

    Q_info.q0 = q0 /norm;
    Q_info.q1 = q1 / norm;
    Q_info.q2 = q2 / norm;
    Q_info.q3 = q3 / norm;
    //�ٴΰ���Щ�õõ���ֵ���
    q0q1 = q0*q1; q0q2 = q0*q2; q0q3 = q0*q3; q1q1 = q1*q1; q1q2 = q1*q2;
    q1q3 = q1*q3; q2q2 = q2*q2; q2q3 = q2*q3; q3q3 = q3*q3;

// 
//    //��Ԫ����ŷ���ǵ�ת��,����������ǻ���,��Ҫ�Ƕ�ֵ,����ֱ�ӳ���57.3,��һ���ȶ�Ӧ�Ƕ�ֵ
//    eulerAngle.roll  = atan2f(2.f * (q0q1 + q2q3),1 - 2.f * ( q1q1 - q2q2) )*57.3; // roll: X��
//    eulerAngle.pitch  = asinf(2.f * (q0q2 - q1q3) )*57.3; // pitch: Y��
//    //����YAW��������ڼ��ٶȼƶ���û���������ã����ʵ�ʽ������ƫ��,��Ҫ׼ȷ,��Ҫʹ�ô�����
//    eulerAngle.yaw   = atan2f(2.f * (q0q3 + q1q2),1 - 2.f * (q2q2 + q3q3) )*57.3; // yaw: Z��
 
/*
    Note: ����תŷ���ǵĴ���,��ʵ�и�����,���Ǹô�������Է�����������Ƶ�,��ǰ��������Ϊ
��������ϵOxyz��x��,������½�����ֳ�����ǰ��������Ϊ��������ϵOxyz��y��.����Ҫ����, 
ѧϰ�˱��ĺ�,��Ҳ���Զ����޸���.
*/
}

/*����Ԫ��ת����ŷ����*/
void ICM_getEulerianAngles(void) {
    //�ɼ�����������
		imu660ra_get_gyro();
    imu660ra_get_acc();

    // get_icm20602_gyro_spi();
    // get_icm20602_accdata_spi();

    ICM_getValues();
    MahonyImuUpdate(icm_data.gyro_x, icm_data.gyro_y, icm_data.gyro_z, icm_data.acc_x, icm_data.acc_y, icm_data.acc_z);
    float q0 = Q_info.q0;
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;
//	  eulerAngle.roll  = atan2f(2.f * (q0*q1 + q2*q3),1 - 2.f * ( q1*q1 - q2*q2) )*57.3; // roll: X��
//    eulerAngle.pitch  = asinf(2.f * (q0*q2 - q1*q3) )*57.3; // pitch: Y��
//    //����YAW��������ڼ��ٶȼƶ���û���������ã����ʵ�ʽ������ƫ��,��Ҫ׼ȷ,��Ҫʹ�ô�����
//    eulerAngle.yaw   = atan2f(2.f * (q0*q3 + q1*q2),1 - 2.f * (q2*q2 + q3*q3) )*57.3; // yaw: Z��
 //��Ԫ������ŷ����
    eulerAngle.pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 180 / M_PI; // pitch
    eulerAngle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 180 / M_PI; // roll
    eulerAngle.yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 180 / M_PI; // yaw
///*   ��̬����*/
//    if (eulerAngle.roll > 90 || eulerAngle.roll < -90) {
//        if (eulerAngle.pitch > 0) {
//            eulerAngle.pitch = 180 - eulerAngle.pitch;
//        }
//        if (eulerAngle.pitch < 0) {
//            eulerAngle.pitch = -(180 + eulerAngle.pitch);
//        }
//    }
//
//    if (eulerAngle.yaw > 360) {
//        eulerAngle.yaw -= 360;
//    } else if (eulerAngle.yaw < 0) {
//        eulerAngle.yaw += 360;
//    }
}
