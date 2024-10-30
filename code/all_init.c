#include "zf_common_headfile.h"
#include "motor.h"
#include "encoder.h"
#include "attitude_solution.h"
#include "flash_param.h"
#include "location.h "
#include "timer.h"
#include "smotor.h"
#include "display.h"
void all_init()
{
   	  motor_init();
	  smotor_init();
	  encoder_init();
	  imu660ra_init();
	  gyroOffset_init();
//	flash_param_init();
//	flash_param_load();
    ips200_init(IPS200_TYPE_SPI);


}
