#include "zf_common_headfile.h"
#include "sort_carry.h"
#include "smotor.h"
//Ô¤Èü5·ÖÀà

uint16 pic_werehouse=0;

uint8 mid_werehouse_flag=0;

void pic_sort(uint8 pic_class)
{
	switch(pic_class)
	{
		case firearms: 			  	pic_werehouse=wierehouse_0;break;
		case explosive: 				pic_werehouse=wierehouse_0;break;
		case dagger: 					  pic_werehouse=wierehouse_0;break;
		case spontoon: 			    pic_werehouse=wierehouse_0;break;
		case fire_axe: 				  pic_werehouse=wierehouse_0;break;
		
		case first_aid: 				pic_werehouse=wierehouse_1;break;
		case flashlight: 			  pic_werehouse=wierehouse_1;break;
		case intercom: 				  pic_werehouse=wierehouse_1;break;
		case bulletproof: 	    pic_werehouse=wierehouse_1;break;
		case telescope: 				pic_werehouse=wierehouse_1;break;
		case helmet: 				    pic_werehouse=wierehouse_1;break;
		
		case fire_engine: 			pic_werehouse=wierehouse_2;break;
		case ambulannce: 				pic_werehouse=wierehouse_2;break;
		case armoured: 				  pic_werehouse=wierehouse_2;break;
		case motorcycle: 			  pic_werehouse=wierehouse_2;break;
		default: 						    pic_werehouse=0						;break;

	}
}
void puzzel_sort()
{
	
	switch(pic_class)
	{
		case A1: 				ips114_show_string(100,0,"A1    ");pic_werehouse=wierehouse_3;break;
		case B2: 				ips114_show_string(100,0,"B2   ");pic_werehouse=wierehouse_1;break;
		case C3: 					ips114_show_string(100,0,"C3     ");pic_werehouse=wierehouse_0;break;
		default: 						ips114_show_string(100,0,"         ");pic_werehouse=0						;break;
	}
}
void word_sort()
{
	switch(pic_class)
	{
		case A: 				ips114_show_string(100,0,"A    ");pic_werehouse=wierehouse_3;break;
		case B: 				ips114_show_string(100,0,"B   ");pic_werehouse=wierehouse_1;break;
		case C: 					ips114_show_string(100,0,"C     ");pic_werehouse=wierehouse_0;break;
		case D: 			ips114_show_string(100,0,"D  ");pic_werehouse=wierehouse_0;break;
		case E: 				ips114_show_string(100,0,"E    ");pic_werehouse=wierehouse_3;break;
		case F: 					ips114_show_string(100,0,"F     ");pic_werehouse=wierehouse_4;break;
		case G: 			ips114_show_string(100,0,"G ");pic_werehouse=wierehouse_2;break;
		case H: 				ips114_show_string(100,0,"H   ");pic_werehouse=wierehouse_2;break;
		case I: 			ips114_show_string(100,0,"I ");pic_werehouse=wierehouse_4;break;
		case J: 				ips114_show_string(100,0,"J    ");pic_werehouse=wierehouse_4;break;
		case K: 				ips114_show_string(100,0,"K   ");pic_werehouse=wierehouse_0;break;
		case L: 				ips114_show_string(100,0,"L   ");pic_werehouse=wierehouse_3;break;
		case M: 				ips114_show_string(100,0,"M   ");pic_werehouse=wierehouse_2;break;
		case N: 				ips114_show_string(100,0,"N   ");pic_werehouse=wierehouse_1;break;
		case O: 					ips114_show_string(100,0,"O     ");pic_werehouse=wierehouse_1;break;
		default: 						ips114_show_string(100,0,"         ");pic_werehouse=0						;break;
	}
}
void wieregouse()
{
	smotor3_control(pic_werehouse);
}