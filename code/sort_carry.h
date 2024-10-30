#ifndef _SORT_CARRY_H_
#define _SORT_CARRY_H_
#include "zf_common_headfile.h"
//#define apple 		0xe0
//#define banana		0xe1
//#define car				0xe2
//#define cat				0xe3
//#define cattle		0xe4
//#define coach			0xe5
//#define dog				0xe6
//#define durian		0xe7
//#define grape			0xe8
//#define horse			0xe9
//#define orange		0xea
//#define pig				0xeb
//#define plane			0xec
//#define steamship	0xed
//#define trains		0xee


#define	firearms 		0x01
#define	explosive  	0x02
#define	dagger			0x03
#define	spontoon 	0x04
#define	fire_axe			0x05
#define	first_aid			0x06
#define	flashlight	0x07
#define	intercom		0x08
#define	bulletproof	0x09
#define	telescope		0x0a
#define	helmet			0x0b
#define	fire_engine		0x0c
#define	ambulannce		0x0d
#define	armoured		0x0e
#define	motorcycle			0x0f


#define	A 		0x11
#define	B  	    0x12
#define	C		0x13
#define	D    	0x14
#define	E		0x15
#define	F		0x16
#define	G    	0x17
#define	H		0x18
#define	I   	0x19
#define	J		0x1a
#define	K		0x1b
#define	L		0x1c
#define	M		0x1d
#define	N		0x1e
#define	O		0x1f



#define	A1		0x21
#define	B2  	0x22
#define	C3		0x23

extern uint8 Grain;
extern uint8 Fruits;
extern uint8 Vegetable;

extern uint8 pic_class;
extern uint8 sort_flag;
extern uint8 carry_flag;
extern uint8 get_sort;


extern uint8 pic_numInwerehouse0;
extern uint8 pic_numInwerehouse1;
extern uint8 pic_numInwerehouse2;
extern uint8 pic_numInwerehouse3;
extern uint8 pic_numInwerehouse4;

extern uint8 change_putModel;


#define wierehouse_0  1			//bean orange cabbage  			//1
#define wierehouse_1  216  	//rice banana radish  			//216
#define wierehouse_2  72  	//potato durian cucumber		//72
#define wierehouse_3  288  	//peanut apple  chili			//288
#define wierehouse_4  144  	//corn eggplant grape			//144
//#define wierehouse5  6  

#define lock_0  B9		//0   b14
#define lock_2	B10		//72  b21
#define lock_4	B15   //144 b23
#define lock_1	B21		//216 b10
#define lock_3	B23		//288 b9

//////////////////////////////////////////////

#define magnet B14   //b15


#define UPanglePerDuty 		13.9    //
#define DownanglePerDuty 	25
#define SpinAngelPerDuty   13.9

#define steer0 PWM4_MODULE2_CHA_C30 //up
#define steer1 PWM1_MODULE3_CHA_D0	//down
#define steer2 PWM1_MODULE3_CHB_D1	//spin

#define upSteer 	1
#define downSteer 2
#define spinSteer 	3

#define upSteer_start 5750
#define downSteer_start 3850
#define spinSteer_start 3050//

#define steer_outMin 950
#define upSteer_outMin 2500

#define upSteer_outMax 6000
#define downSteer_outMax 4850
#define SpinSteer_outMax 7000


extern uint16 sort_angle;
extern uint8 put_in;

void pic_sort(uint8 pic_class);


#endif