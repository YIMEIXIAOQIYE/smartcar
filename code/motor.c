#include "motor.h"
#include "zf_common_headfile.h"
#include "flash_param.h"
#include "encoder.h"

#define DIR_1 D2
#define PWM_1 PWM2_MODULE2_CHB_C11/////1

#define DIR_2 C10
#define PWM_2 PWM2_MODULE3_CHB_D3//////2

#define DIR_3 C7
#define PWM_3 PWM2_MODULE0_CHA_C6//////3

#define DIR_4 C9
#define PWM_4 PWM2_MODULE1_CHA_C8//////4

int PWM_LIMIT=900;

int duty1=0,duty2=0,duty3=0,duty4=0;//电机PWM值
float Position_KP =200;
float Position_KI =0;
float Position_KD =30; 
float  Angel_KP = 30;
float  Angel_KD = 30;
float  Angel_KI = 0;
float pictureD = 0.005;
float pictureI = 0;
float pictureP = 0.76;
//积分法计算位移参数
int stop;
//电机目标速度
int speed_tar_1 = 0;
int speed_tar_2 = 0;
int speed_tar_3 = 0;
int speed_tar_4 = 0;

double speed_tar = 0;//目标速度

void motor_init(void)
{
    gpio_init(DIR_1, GPO, 0, GPI_PULL_UP); 		//单片机端口D0 初始化DIR_1			GPIO
    gpio_init(DIR_2, GPO, 0, GPI_PULL_UP); 		//单片机端口D1 初始化DIR_2			GPIO
    pwm_init(PWM_1, 17000, 0);      					//单片机端口D2 初始化PWM_1周期10K 占空比0
    pwm_init(PWM_2, 17000, 0);     						//单片机端口D3 初始化PWM_2周期10K 占空比0
    gpio_init(DIR_3, GPO, 0, GPI_PULL_UP);       //单片机端口D0 初始化DIR_1          GPIO
    gpio_init(DIR_4, GPO, 0, GPI_PULL_UP);       //单片机端口D1 初始化DIR_2          GPIO
    pwm_init(PWM_3, 17000, 0);                          //单片机端口D2 初始化PWM_1周期10K 占空比0
    pwm_init(PWM_4, 17000, 0);                          //单片机端口D3 初始化PWM_2周期10K 占空比0											// PWM 通道4 初始化频率10KHz 占空比初始为0
}
//麦轮编号
//4  3


//2  1
void car_omni(float x, float y, float z){
    speed_tar_1= y + x + z;
    speed_tar_2= y - x - z;
    speed_tar_3= y + x - z;
    speed_tar_4= y - x + z;
}



void car_ahead(){
    speed_tar_1 = speed_tar;
    speed_tar_2 = speed_tar;
    speed_tar_3 = speed_tar;
    speed_tar_4 = speed_tar;
}

void car_back(){
    speed_tar_1 = -speed_tar;
    speed_tar_2 = -speed_tar;
    speed_tar_3 = -speed_tar;
    speed_tar_4 = -speed_tar;
}

void car_sideWay(){
    speed_tar_1 = speed_tar;
    speed_tar_2 = -speed_tar;
    speed_tar_3 = speed_tar;
    speed_tar_4 = -speed_tar;
}

void car_rsideWay(){
    speed_tar_1 = -speed_tar;
    speed_tar_2 = speed_tar;
    speed_tar_3 = -speed_tar;
    speed_tar_4 = speed_tar;
}

void car_diagonal(){
    speed_tar_1 = speed_tar;
    speed_tar_2 = 0;
    speed_tar_3 = speed_tar;
    speed_tar_4 = 0;
}

void car_turnround(){
    speed_tar_1 = speed_tar;
    speed_tar_2 = speed_tar;
    speed_tar_3 = -speed_tar;
    speed_tar_4 = -speed_tar;
}

void car_anticlockwise() {
    speed_tar_1 = -speed_tar;
    speed_tar_2 = -speed_tar;
    speed_tar_3 = speed_tar;
    speed_tar_4 = speed_tar;
}

void car_concerning(){
    speed_tar_1 = speed_tar;
    speed_tar_2 = speed_tar;
    speed_tar_3 = 0;
    speed_tar_4 = 0;
}

void car_stop(){
    speed_tar_1 = 0;
    speed_tar_2 = 0;
    speed_tar_3 = 0;
    speed_tar_4 = 0;
}


/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
****************************************************************************/

//struct {
//    float set_speed;//设定速度 
//    float actual_speed;//实际速度
//    float error;//偏差  
//    float error_next;//上一个偏差  
//    float error_last;//上上一个偏差 
//    float kp,ki,kd;//定义比例，积分，微分参数  
//     
//}pid;
//void pid_init()
//{
//    pid.set_speed = 0.0;
//    pid.error = 0.0;
//    pid.error_next = 0.0;
//    pid.error_last = 0.0;
//    //可调节PID 参数。使跟踪曲线慢慢接近阶跃函数200.0 // 
//    pid.kp = 900;
//    pid.ki = 100;
//    pid.kd = 0;
//}


//float pid_realise1(float speed)//实现pid  
//{
//		pid.actual_speed = RC_encoder1;
//    pid.set_speed = speed;//设置目标速度  
//    pid.error = pid.set_speed - pid.actual_speed;
//    float increment_speed;//增量
//     
//    increment_speed = pid.kp*(pid.error-pid.error_next)+pid.ki*pid.error+\
//    pid.kd*(pid.error-2*pid.error_next+pid.error_last);//增量计算公式  
//    
//    pid.actual_speed+= increment_speed;
//    pid.error_last = pid.error_next;//下一次迭代  
//    pid.error_next = pid.error;
//    return pid.actual_speed; 
//    
//}

//float pid_realise2(float speed)//实现pid  
//{
//	  pid.actual_speed = RC_encoder2;
//    pid.set_speed = speed;//设置目标速度  
//    pid.error = pid.set_speed - pid.actual_speed;
//    float increment_speed;//增量
//     
//    increment_speed = pid.kp*(pid.error-pid.error_next)+pid.ki*pid.error+\
//    pid.kd*(pid.error-2*pid.error_next+pid.error_last);//增量计算公式  
//    
//    pid.actual_speed+= increment_speed;
//    pid.error_last = pid.error_next;//下一次迭代  
//    pid.error_next = pid.error;
//    return pid.actual_speed; 
//    
//}
//float pid_realise3(float speed)//实现pid  
//{
//	  pid.actual_speed = RC_encoder3;
//    pid.set_speed = speed;//设置目标速度  
//    pid.error = pid.set_speed - pid.actual_speed;
//    float increment_speed;//增量
//     
//    increment_speed = pid.kp*(pid.error-pid.error_next)+pid.ki*pid.error+\
//    pid.kd*(pid.error-2*pid.error_next+pid.error_last);//增量计算公式  
//    
//    pid.actual_speed+= increment_speed;
//    pid.error_last = pid.error_next;//下一次迭代  
//    pid.error_next = pid.error;
//    return pid.actual_speed; 
//    
//}

//float pid_realise4(float speed)//实现pid  
//{
//		pid.actual_speed = RC_encoder4;
//    pid.set_speed = speed;//设置目标速度  
//    pid.error = pid.set_speed - pid.actual_speed;
//    float increment_speed;//增量
//     
//    increment_speed = pid.kp*(pid.error-pid.error_next)+pid.ki*pid.error+\
//    pid.kd*(pid.error-2*pid.error_next+pid.error_last);//增量计算公式  
//    
//    pid.actual_speed+= increment_speed;
//    pid.error_last = pid.error_next;//下一次迭代  
//    pid.error_next = pid.error;
//    return pid.actual_speed; 
//    
//}

/**
 * @name: position_pid
 * @msg: 位置式pid
 * @param {int Encoder,int Target}
 * @return {int pwm}
 */
int position_pid1(int Encoder,int Target){
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=(float)(Target - Encoder);//当前误差
    Integral_bias+=Bias;//误差的积累
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);//当前误差-上次误差
    Last_Bias=Bias;
    return (int)Pwm;
}

int position_pid2(int Encoder,int Target){
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=(float)(Target - Encoder);
    Integral_bias+=Bias;
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);
    Last_Bias=Bias;
    return (int)Pwm;
}

int position_pid3(int Encoder,int Target){
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=(float)(Target - Encoder);
    Integral_bias+=Bias;
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);
    Last_Bias=Bias;
    return (int)Pwm;
}


int position_pid4(int Encoder,int Target){
    static float Bias,Pwm,Integral_bias,Last_Bias;
    Bias=(float)(Target - Encoder);
    Integral_bias+=Bias;
    Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);
    Last_Bias=Bias;
    return (int)Pwm;
}

int angel_pid(int NowAngel,int TargetAngel){
    if (NowAngel<=0){
        if(NowAngel-TargetAngel<=-180){
            NowAngel+=180;
            TargetAngel-=180;
        }
    }else if(NowAngel>0){
        if(NowAngel-TargetAngel>=180){
            NowAngel-=180;
            TargetAngel+=180;
        }
    }
    static float Bias,Speed_Z,Integral_bias,Last_Bias;
    Bias=(float)(TargetAngel - NowAngel);
    Integral_bias+=Bias;
    Speed_Z=Angel_KP*Bias+Angel_KI*Integral_bias+Angel_KD*(Bias-Last_Bias);
    Last_Bias=Bias;
    if(Speed_Z>=3000)
        Speed_Z=3000;
    if(Speed_Z<=-3000)
        Speed_Z=-3000;
    return (int)Speed_Z;
}

int picture_xerror_pid(int16 now_x,int16 target_x){
    static float Bias,Speed_X,Integral_bias,Last_Bias;
    Bias=(float)(target_x - now_x);
    Integral_bias+=Bias;
    Speed_X=pictureP*Bias+pictureI*Integral_bias+pictureD*(Bias-Last_Bias);
    Last_Bias=Bias;
    if(Speed_X>=3000)
        Speed_X=3000;
    if(Speed_X<=-3000)
        Speed_X=-3000;
    return (int)Speed_X;
}

int picture_yerror_pid(int16 now_y,int16 target_y){
    static float Bias,Speed_Y,Integral_bias,Last_Bias;
    Bias=(float)(target_y - now_y);
    Integral_bias+=Bias;
    Speed_Y=pictureP*Bias+pictureI*Integral_bias+pictureD*(Bias-Last_Bias);
    Last_Bias=Bias;
    if(Speed_Y>=3000)
        Speed_Y=3000;
    if(Speed_Y<=-3000)
        Speed_Y=-3000;
    return (int)Speed_Y;
}

/**
 * @name: limit_pwm
 * @msg: pwm限幅
 * @param {int pwm}
 * @return {int pwm}
 */

int limit_pwm(int pwm){
    if (pwm>=0)
    {
        if (pwm>=PWM_LIMIT)
        {
            pwm = PWM_LIMIT;
        }

    }
    else if (pwm<=0)
    {
        if (pwm<-PWM_LIMIT)
        {
            pwm = -PWM_LIMIT;
        }

    }
    return pwm;
}


/**
 * @name: PID_Calculate
 * @msg: 调用各个轮子的pid函数，得出运算后的PWM值
 * @param {void}
 * @return {void}
 */
void pid_calculate(void){
    duty1 = position_pid1(RC_encoder1,speed_tar_1);
    duty2 = position_pid2(RC_encoder2,speed_tar_2);
    duty3 = position_pid3(RC_encoder3,speed_tar_3);
    duty4 = position_pid4(RC_encoder4,speed_tar_4);
		if(stop==500)
		{
			duty1 = 0;
			duty2 = 0;
			duty3 = 0;
			duty4 = 0;
		} 
    duty1 = limit_pwm(duty1);
    duty2 = limit_pwm(duty2);
    duty3 = limit_pwm(duty3);
    duty4 = limit_pwm(duty4);
		
}
void motor_control(bool run)
{
    if(run) {
        pid_calculate();
    }else{
        duty1 = 0;
        duty2 = 0;
        duty3 = 0;
        duty4 = 0;
    }

    if(duty1>=0){
        gpio_set_level(DIR_1,1);
        pwm_set_duty (PWM_1,duty1);
    } else {
				gpio_set_level(DIR_1,0);
        pwm_set_duty (PWM_1,-duty1);
    }
    if(duty2>=0){
        gpio_set_level(DIR_2,1);
        pwm_set_duty (PWM_2,duty2);
    } else {
        gpio_set_level(DIR_2,0);
        pwm_set_duty (PWM_2,-duty2);
    }

    if(duty3>=0){
        gpio_set_level(DIR_3,0);
        pwm_set_duty (PWM_3,duty3);
    } else {
        gpio_set_level(DIR_3,1);
        pwm_set_duty (PWM_3,-duty3);
    }

    if(duty4>=0){
        gpio_set_level(DIR_4,0);
        pwm_set_duty (PWM_4,duty4);
    } else {
        gpio_set_level(DIR_4,1);
        pwm_set_duty (PWM_4,-duty4);
    }
}

void motor_test(){
    uint8 dir=0;
    int32 duty=1000;
    while (1)
    {
		if(dir)
        {
            duty += 10;
            if(2000<=duty)   dir = 0;
        }
        else
        {
            duty -= 10;
            if(-2000>=duty)   dir = 1;
        } 
		
        system_delay_ms(1);
       
        if(duty>=0) //正转
        {
            gpio_set_level(DIR_1,1);
             pwm_set_duty(PWM_1,duty);
			
           gpio_set_level(DIR_2,1);
             pwm_set_duty(PWM_2,duty);

            gpio_set_level(DIR_3,0);
            pwm_set_duty(PWM_3,duty);
            
            gpio_set_level(DIR_4,0);
             pwm_set_duty(PWM_4,duty);
        }
        else        //反转
        {
            gpio_set_level(DIR_1,0);
             pwm_set_duty(PWM_1,-duty);
			
						gpio_set_level(DIR_2,0);
             pwm_set_duty(PWM_2,-duty);

            gpio_set_level(DIR_3,1);
            pwm_set_duty(PWM_3,-duty);
            
            gpio_set_level(DIR_4,1);
             pwm_set_duty(PWM_4,-duty);
        }
    }
}
