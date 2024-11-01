#include "attitude_solution.h"
#include <math.h>
#include "zf_common_headfile.h"

#define sampleFreq	100.f			// sample frequency in Hz
/*采样周期的一半，用于求解四元数微分方程时计算角增量
请确定自己的姿态调用周期: 5ms,即上面的sampleFreq: 200Hz*/
#define halfT 0.00445f*2.5/3*0.6*2;
 
//这里的Kp,Ki是用于控制加速度计修正陀螺仪积分姿态的速度
//#define Kp 10.0f  //2.0f
//#define Ki 0.008f  //0.002f
 #define Kp 0.18f  //2.0f
#define Ki 0.003f  //0.002f
 
//初始姿态四元数(地理坐标系)，q(q0,q1,q2,q3)
static float q0 = 1, q1 = 0, q2 = 0, q3 = 0; //最优估计四元数
//定义姿态解算误差的积分.     
//当前加计测得的重力加速度在三轴(x,y,z)上的分量,与当前姿态计算得来的重力在三轴上的分量的误差的积分
static float xErrorInt = 0, yErrorInt = 0, zErrorInt = 0;
 
//#define delta_T     0.002f  //2ms计算一次
#define M_PI        3.1415926f

//float I_ex, I_ey, I_ez;  // 误差积分

location_goal Car={0};

quater_param_t Q_info = {1, 0, 0};  // 全局四元数
euler_param_t eulerAngle; //欧拉角

icm_param_t icm_data;
gyro_param_t GyroOffset;
bool GyroOffset_init = 0;
//float param_Kp = 0.18;   // 加速度计的收敛速率比例增益
//float param_Ki = 0.003;   //陀螺仪收敛速率的积分增益 0.004

//float fast_sqrt(float x) {
//    float halfx = 0.5f * x;
//    float y = x;
//    long i = *(long *) &y;
//    i = 0x5f3759df - (i >> 1);
//    y = *(float *) &i;
//    y = y * (1.5f - (halfx * y * y));
//    return y;
//}
void  gyroOffset_init(void)      /////////陀螺仪零飘初始化
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

//转化为实际物理值
void ICM_getValues() {
    /*
        //一阶低通滤波，单位g/s
    source_data.acc_x = (((float)imu963ra_acc_x) * alpha) * 8 / 4098 + source_data.acc_x * (1 - alpha);
    source_data.acc_y = (((float)imu963ra_acc_y) * alpha) * 8 / 4098 + source_data.acc_y * (1 - alpha);
    source_data.acc_z = (((float)imu963ra_acc_z) * alpha) * 8 / 4098 + source_data.acc_z * (1 - alpha);

    //陀螺仪角度转弧度
    source_data.gyro_x = ((float)imu963ra_gyro_x - Gyro_Offset.Xdata) * M_PI / 180 / 14.3f;
    source_data.gyro_y = ((float)imu963ra_gyro_y - Gyro_Offset.Ydata) * M_PI / 180 / 14.3f;
    source_data.gyro_z = ((float)imu963ra_gyro_z - Gyro_Offset.Zdata) * M_PI / 180 / 14.3f;
  
    //磁力计转换量程
   source_data.mag_x = (float)imu963ra_mag_x / 3000.0f;
   source_data.mag_y = (float)imu963ra_mag_y / 3000.0f;
   source_data.mag_z = (float)imu963ra_mag_z / 3000.0f;
    */

       //一阶低通滤波，单位g/s
    icm_data.acc_x = (((float) imu660ra_acc_x) * alpha) * 8 / 4098 + icm_data.acc_x * (1 - alpha);
    icm_data.acc_y = (((float) imu660ra_acc_y) * alpha) * 8 / 4098 + icm_data.acc_y * (1 - alpha);
    icm_data.acc_z = (((float) imu660ra_acc_z) * alpha) * 8 / 4098 + icm_data.acc_z * (1 - alpha);


    //陀螺仪角度转弧度
    icm_data.gyro_x = ((float) imu660ra_gyro_x - GyroOffset.Xdata) * M_PI / 180 / 14.3f;
    icm_data.gyro_y = ((float) imu660ra_gyro_y - GyroOffset.Ydata) * M_PI / 180 / 14.3f;
    icm_data.gyro_z = ((float) imu660ra_gyro_z - GyroOffset.Zdata) * M_PI / 180 / 14.3f;

    // //一阶低通滤波，单位g/s
    // icm_data.acc_x = (((float) icm_acc_x) * alpha) * 8 / 4096 + icm_data.acc_x * (1 - alpha);
    // icm_data.acc_y = (((float) icm_acc_y) * alpha) * 8 / 4096 + icm_data.acc_y * (1 - alpha);
    // icm_data.acc_z = (((float) icm_acc_z) * alpha) * 8 / 4096 + icm_data.acc_z * (1 - alpha);


    // //陀螺仪角度转弧度
    // icm_data.gyro_x = ((float) icm_gyro_x - GyroOffset.Xdata) * M_PI / 180 / 16.4f;
    // icm_data.gyro_y = ((float) icm_gyro_y - GyroOffset.Ydata) * M_PI / 180 / 16.4f;
    // icm_data.gyro_z = ((float) icm_gyro_z - GyroOffset.Zdata) * M_PI / 180 / 16.4f;
}

/*
 * 6轴陀螺仪姿态融合算法:  Mahony的互补滤波算法 6轴版
 * 单位: m/s^2   rad/s
 * 由于加速度的噪音很大, 此处建议使用滤波后的数据
 * */
void MahonyImuUpdate(float gx, float gy, float gz, float ax, float ay, float az)//g表陀螺仪，a表加计
{
    float q0temp,q1temp,q2temp,q3temp;//四元数暂存变量，求解"微分方程"时要用
    float norm; //矢量的模或四元数的范数
    float posture_x, posture_y, posture_z;//当前姿态计算得来的重力在三轴上的分量
    //当前加计测得的重力加速度在三轴上的分量,与用当前姿态计算得来的重力在三轴上的分量的误差
    float error_x, error_y, error_z;
 
    // 先把这些用得到的值算好
    float q0q0 = q0*q0, q0q1 = q0*q1, q0q2 = q0*q2, q0q3 = q0*q3, q1q1 = q1*q1, q1q2 = q1*q2;
    float q1q3 = q1*q3, q2q2 = q2*q2, q2q3 = q2*q3, q3q3 = q3*q3;
 
    //加计处于自由落体状态时不进行姿态解算，因为会产生分母无穷大的情况
    if( (ax == 0.0f) && (ay == 0.0f) && (az == 0.0f) )
       return;
 
    //将加速度的原始数据进行归一化,得到单位加速度
    norm = sqrt(ax*ax + ay*ay + az*az);//单位化加速度计，
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;
 
    //用当前姿态(参考坐标n系)计算出重力在三个轴上的分量(载体坐标b系)，
    /*把四元数换算成"方向余弦矩阵"中的第三列的三个元素.根据余弦矩阵和欧拉角的定义,地理坐标系的重力向量,转到载体坐标系,正好是这三个元素.*/
    posture_x = 2*(q1q3 - q0q2);
    posture_y = 2*(q0q1 + q2q3);
    posture_z = q0q0 - q1q1 - q2q2 + q3q3;
//		 posture_z = 1-2*q1*q1-2*q2*q2;
    //计算: 传感器测得的重力与当前姿态计算的重力间的误差，向量外积可以表示这一误差
    // Error is sum of cross product between estimated and measured direction of gravity
    error_x = (ay*posture_z - az*posture_y) ;
    error_y = (az*posture_x - ax*posture_z) ;
    error_z = (ax*posture_y - ay*posture_x) ;
 
    //对两种重力分量的叉积误差进行积分
    xErrorInt = xErrorInt + error_x * Ki;// * (1.0f / sampleFreq);
    yErrorInt = yErrorInt + error_y * Ki;// * (1.0f / sampleFreq);
    zErrorInt = zErrorInt + error_z * Ki;// * (1.0f / sampleFreq);
 
    //对两种重力分量的叉积误差的积分做p,i修正陀螺零偏,通过调节Kp,Ki两个参数,可以控制加速度计修正陀螺仪积分姿态的速度
    gx = gx + Kp*error_x + xErrorInt;  //将误差PI后补偿到陀螺仪，即补偿零点漂移
    gy = gy + Kp*error_y + yErrorInt;
    gz = gz + Kp*error_z + zErrorInt; //这里的gz由于没有观测者进行矫正会产生漂移，表现出来的就是积分自增或自减
 
    // Integrate rate of change of quaternion
    //gx *= (1.0f / sampleFreq);		// pre-multiply common factors
    //gy *= (1.0f / sampleFreq);
    //gz *= (1.0f / sampleFreq);
 
    //下面进行姿态的更新，也就是四元数微分方程的求解
    q0temp=q0;//暂存当前值用于计算
    q1temp=q1;
    q2temp=q2;
    q3temp=q3;
 
    //四元数微分方程. 采用一阶毕卡解法，融合当前位姿和陀螺仪测量值,并转换到世界参考坐标系N. 
    q0 = q0temp + (-q1temp*gx - q2temp*gy -q3temp*gz)*halfT;
    q1 = q1temp + (q0temp*gx + q2temp*gz -q3temp*gy)*halfT;
    q2 = q2temp + (q0temp*gy - q1temp*gz +q3temp*gx)*halfT;
    q3 = q3temp + (q0temp*gz + q1temp*gy -q2temp*gx)*halfT;
 
    //对当前姿态四元数进行单位化,单位化四元数在空间旋转时不会拉伸，仅有旋转角度
    norm = sqrt(q0q0 + q1q1 + q2q2 + q3q3);
//    q0 = q0 / norm;
//    q1 = q1 / norm;
//    q2 = q2 / norm;
//    q3 = q3 / norm;

    Q_info.q0 = q0 /norm;
    Q_info.q1 = q1 / norm;
    Q_info.q2 = q2 / norm;
    Q_info.q3 = q3 / norm;
    //再次把这些用得到的值算好
    q0q1 = q0*q1; q0q2 = q0*q2; q0q3 = q0*q3; q1q1 = q1*q1; q1q2 = q1*q2;
    q1q3 = q1*q3; q2q2 = q2*q2; q2q3 = q2*q3; q3q3 = q3*q3;

// 
//    //四元数到欧拉角的转换,这里输出的是弧度,想要角度值,可以直接乘以57.3,即一弧度对应角度值
//    eulerAngle.roll  = atan2f(2.f * (q0q1 + q2q3),1 - 2.f * ( q1q1 - q2q2) )*57.3; // roll: X轴
//    eulerAngle.pitch  = asinf(2.f * (q0q2 - q1q3) )*57.3; // pitch: Y轴
//    //其中YAW航向角由于加速度计对其没有修正作用，因此实际结果会逐渐偏移,想要准确,需要使用磁力计
//    eulerAngle.yaw   = atan2f(2.f * (q0q3 + q1q2),1 - 2.f * (q2q2 + q3q3) )*57.3; // yaw: Z轴
 
/*
    Note: 上面转欧拉角的代码,其实有个问题,就是该代码是针对飞行器导航设计的,其前后纵向轴为
载体坐标系Oxyz的x轴,而不是陆地四轮车那样前后纵向轴为载体坐标系Oxyz的y轴.但不要担心, 
学习了本文后,你也可以动手修改它.
*/
}

/*把四元数转换成欧拉角*/
void ICM_getEulerianAngles(void) {
    //采集陀螺仪数据
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
//	  eulerAngle.roll  = atan2f(2.f * (q0*q1 + q2*q3),1 - 2.f * ( q1*q1 - q2*q2) )*57.3; // roll: X轴
//    eulerAngle.pitch  = asinf(2.f * (q0*q2 - q1*q3) )*57.3; // pitch: Y轴
//    //其中YAW航向角由于加速度计对其没有修正作用，因此实际结果会逐渐偏移,想要准确,需要使用磁力计
//    eulerAngle.yaw   = atan2f(2.f * (q0*q3 + q1*q2),1 - 2.f * (q2*q2 + q3*q3) )*57.3; // yaw: Z轴
 //四元数计算欧拉角
    eulerAngle.pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 180 / M_PI; // pitch
    eulerAngle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 180 / M_PI; // roll
    eulerAngle.yaw = atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 180 / M_PI; // yaw
///*   姿态限制*/
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
