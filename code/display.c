#include "zf_common_headfile.h"
#include "encoder.h"
#include "attitude_solution.h"
#include "motor.h"
#include "imagine.h"
#include "display.h"
extern float Position_KP ;
extern float Position_KI ;
extern float Position_KD ;
extern float Angel_KP ;
extern float Angel_KD ;
extern float Angel_KI ;
extern float pictureD ;
extern float pictureI ;
extern float pictureP ;
extern int nus;
void basic_information()
{
			ips200_show_int(0, 16 * 1,nus, 4);
//     ips200_show_int(0,16*1,RC_encoder1,4);
//		 ips200_show_int(0,16*2,RC_encoder2,4);
//		 ips200_show_int(0,16*3,RC_encoder3,4);
//		 ips200_show_int(0,16*4,RC_encoder4,4);
		 ips200_show_float(0, 16 * 16,Car.Angel , 3, 6);
	
		 ips200_show_float(0,16*7,pictureP ,4,3);
		 ips200_show_int(0,16*8,Position_KI ,4);
		 ips200_show_float(0,16*9,pictureD ,4,3);
	
     ips200_show_int(0,16*10,Angel_KP ,4);
		 ips200_show_int(0,16*12,Angel_KI ,4);
		 ips200_show_int(0,16*13,Angel_KD ,4);
		 ips200_show_int(0,16*14,eulerAngle.yaw,4);
//			ips200_show_float(0, 16 * 16,offset , 3, 6);
   
}