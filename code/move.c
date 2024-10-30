#include "attitude_solution.h"
#include "zf_common_headfile.h"
#include "motor.h"
int count_i=0;
extern int stop;
void reset_mileage(){
    Car.Speed_X=0;
    Car.Speed_Y=0;
    Car.Speed_Z=0;

    Car.MileageX=0;
    Car.MileageY=0;
    Car.DistanceX=0;
    Car.DistanceY=0;
}
void carmove_mileage(float x,float y){
    Car.DistanceX=x;
    Car.DistanceY=y;
    while(abs(Car.MileageX)<abs(Car.DistanceX)) {
        if (x > 0) {
            Car.Speed_X = speed_tar;
        } else if (x == 0) {
            Car.Speed_X = 0;
        } else if (x < 0) {
            Car.Speed_X = -speed_tar;
        }
        system_delay_ms(2);
    }
    Car.Speed_X=0;
    car_stop();
    system_delay_ms(400);
    while(abs(Car.MileageY)< abs(Car.DistanceY)){
        if (y > 0) {
            Car.Speed_Y = speed_tar;
        } else if (y == 0) {
            Car.Speed_Y = 0;
        } else if (y < 0) {
            Car.Speed_Y = -speed_tar;
        }
        system_delay_ms(2);
    }
    reset_mileage();
}
void medistance()
{
		if(abs(Car.MileageY)>60)
				{				
	//			car_stop();
					stop=500;
					system_delay_ms(800);
					if(Car.MileageY<-60)
					{
						Car.Angel_Target+=60;
					}
					system_delay_ms(600);
					motor_init();
					Car.MileageY=0;
					stop=0;	
					if(count_i%2==0)		
					 {
						 Car.Speed_Y = -60;
						 count_i ++;
					 }			
					else 
					 {
						 Car.Speed_Y=60;
						 count_i ++;
					 }	
				}		
}
			