//#include "zf_common_headfile.h"
//#include "PID.h"

////-------------------------------------------------------------------------------------------------------------------
////  @brief      增量式PI算法 电机速度环
////  @param      pid_parameter *pid   PID参数
////  @param      speed_now    	     编码器获取的速度
////  @return     none
////  Sample usage:           
////-------------------------------------------------------------------------------------------------------------------
//void Incremental_PID(struct pid_parameter *pid,int16 speed_now)
//{
//	pid->error_last_last=pid->error_last;
//	pid->error_last=pid->error_now;
//	
//	pid->error_now=pid->expect-speed_now;
//	
//	pid->output+=pid->kp*(pid->error_now-pid->error_last)/10
//				+pid->ki*pid->error_now/10
//				+pid->kd*(pid->error_now-2*pid->error_last+pid->error_last_last)/10.0;
//	
//	if(pid->output>output_max) pid->output=output_max;
//	if(pid->output<-output_max) pid->output=-output_max;

//}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      位置式PD 方向环 
////  @param      pid_parameter *pid PID参数
////  @param           	
////  @return     
////  Sample usage:           
////-------------------------------------------------------------------------------------------------------------------
//void Positional_PD(struct pid_parameter *pid)
//{
//	
//	pid->error_last=pid->error_now;
//	
//	pid->output=pid->kp*pid->error_now*10
//			   +pid->kd*(pid->error_now-pid->error_last);
//	


//}
////-------------------------------------------------------------------------------------------------------------------
////  @brief      位置式PD 角速度环 
////  @param      pid_parameter *pid PID参数
////  @param           	
////  @return     
////  Sample usage:           
////-------------------------------------------------------------------------------------------------------------------
//void Positional_Vel_PD(struct pid_parameter *pid)
//{
//	uint8 error_deadzone=1.0f;
//	uint16 range=25;
//	
//	if(pid->error_now<error_deadzone&&pid->error_now>-error_deadzone) pid->error_now=0;
//	
//	
//	
//	pid->output=pid->kp*pid->error_now/100.0f
//			   +pid->kd*(pid->error_now-pid->error_last);
//	
//	pid->error_last=pid->error_now;
//	//输出限幅
//	if(pid->output>range) pid->output=range;
//	if(pid->output<-range) pid->output=-range;

//}
////-------------------------------------------------------------------------------------------------------------------
////  @brief     位置式PID 角度环 
////  @param     pid_parameter *pid 	PID参数
////  @param     angle                陀螺仪计算角度      	
////  @return     none
////  Sample usage:           
////-------------------------------------------------------------------------------------------------------------------
////void Position_PID(struct pid_parameter *pid,float angle)
////{
////	float error_deadzone=0.1;//设置死区
////	
////	pid->expect=angle;
////	pid->error_last=pid->error_now;
////	pid->error_now=(float)pid->expect-Yaw;
////	
////	if(pid->error_now<error_deadzone&&pid->error_now>-error_deadzone) pid->error_now=0; 
////	
////	pid->error_integral+=pid->error_now;
////	
////	pid->output=(float)pid->kp*pid->error_now/10.0f
////				+(float)pid->ki*pid->error_integral
////				+(float)pid->kd*(pid->error_now-pid->error_last)/10.0f;


////}
////-------------------------------------------------------------------------------------------------------------------
////  @brief     位置式PID 位置控制 
////  @param     pid_parameter *pid 	PID参数    	
////  @return     none
////  Sample usage:           
////-------------------------------------------------------------------------------------------------------------------
//void Position_XY_PID(struct pid_parameter *pid)
//{
//	float error_deadzone=5;//设置死区
//	uint16 range=65;//65
//	
//	
//	
////	if(pid->error_now<error_deadzone&&pid->error_now>-error_deadzone) pid->error_now=0; 
//	
//	pid->error_integral+=pid->error_now;
//	
//	pid->output=(float)pid->kp*pid->error_now/1000.0
//				+(float)pid->ki*pid->error_integral/1000.0
//				+(float)pid->kd*(pid->error_now-pid->error_last)/100.0;
//				
//	pid->error_last=pid->error_now;
//	//输出限幅
//	if(pid->output>range) pid->output=range;
//	if(pid->output<-range) pid->output=-range;
//	
//}


