#include "smotor.h"
#define SERVO_MOTOR1_PWM             (PWM4_MODULE2_CHA_C30)                          // ���������϶����Ӧ����
#define SERVO_MOTOR2_PWM             (PWM1_MODULE3_CHA_D0)                          // ���������϶����Ӧ����
#define SERVO_MOTOR3_PWM             (PWM1_MODULE3_CHB_D1)                          // ���������϶����Ӧ����
#define SERVO_MOTOR_FREQ            (50 )                                           // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300
#define ELECTROMAG_PIN D4
#define SERVO_MOTOR_L_MAX           (0 )                                           // ���������϶�����Χ �Ƕ�
#define SERVO_MOTOR_R_MAX           (180)                                           // ���������϶�����Χ �Ƕ�

// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
// 
// �����Ӧ�� 0-180 ��Ƕȶ�Ӧ ��������� 0.5ms-2.5ms �ߵ�ƽ
// 
// ��ô��ͬƵ���µ�ռ�ձȼ��㷽ʽ����
// PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) �� 50hz ʱ���� PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
// 
// ��ô 100hz �� 90�ȵĴ�� ���ߵ�ƽʱ��1.5ms ��������Ϊ
// PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
// 
// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))
#define SERVO_MOTOR1_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/180.0))
#if (SERVO_MOTOR_FREQ<50 || SERVO_MOTOR_FREQ>300)
    #error "SERVO_MOTOR_FREQ ERROE!"
#endif 
void smotor_init()
{
    gpio_init(ELECTROMAG_PIN,GPO,GPIO_HIGH,GPO_PUSH_PULL);
    pwm_init(SERVO_MOTOR1_PWM, SERVO_MOTOR_FREQ, 0);
    pwm_init(SERVO_MOTOR2_PWM, SERVO_MOTOR_FREQ, 0); 
    pwm_init(SERVO_MOTOR3_PWM, SERVO_MOTOR_FREQ, 0);
}
// �������״̬
void smotor1_control(int servo_motor_duty)
{
    pwm_set_duty(SERVO_MOTOR1_PWM, (uint32)SERVO_MOTOR_DUTY(servo_motor_duty));
}

void smotor2_control(int servo_motor_duty)
{
   pwm_set_duty(SERVO_MOTOR2_PWM, (uint32)SERVO_MOTOR_DUTY(servo_motor_duty));
}

void smotor3_control(int servo_motor_duty)
{
    pwm_set_duty(SERVO_MOTOR3_PWM, (uint32)SERVO_MOTOR_DUTY(servo_motor_duty));
}    
void electromagup()
{
	 gpio_set_dir(ELECTROMAG_PIN,GPO,1);
}
void electromagdown()
{
	 gpio_set_dir(ELECTROMAG_PIN,GPO,0);
}
void pickup()
{
    electromagup();
	smotor2_control(149);
	system_delay_ms(350);
	smotor3_control(60);
	system_delay_ms(800);
	smotor3_control(160);
	system_delay_ms(300);
	smotor2_control(30);
	electromagdown();
}
void buzzeropen(int time)
{
	gpio_init(B11, GPO, GPIO_HIGH, GPO_PUSH_PULL);
	system_delay_ms(time);
	gpio_init(B11, GPO, GPIO_LOW, GPO_PUSH_PULL);
}
void servo_control(int a,int b,int c){
    smotor1_control(a);
    smotor2_control(b);
    smotor3_control(c);
}
