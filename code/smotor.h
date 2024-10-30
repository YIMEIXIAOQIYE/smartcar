#ifndef _SMOTOR_H_
#define _SMOTOR_H_

#include "zf_common_headfile.h"

extern int smotor1_pwm,smotor2_pwm,smotor3_pwm;


void smotor_init(void);
void smotor1_control(int servo_motor_duty);
void smotor2_control(int servo_motor_duty);
void smotor3_control(int servo_motor_duty);
void servo_control(int a,int b,int c);
void electromagup();
void buzzeropen(int time);
void electromagdown();
void pickup();
#endif