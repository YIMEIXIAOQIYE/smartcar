#ifndef _IMAGINE_H_
#define _IMAGINE_H_
#include "zf_common_headfile.h"
extern float offset; 
extern float offset_2;
uint8 GetOSTU();
void Get_Pixle(void);
void Horizontal_line(void);
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row);
uint8 Threshold_Deal(uint8* image, uint16 x, uint16 y );
void Get01change_Dajin();
void Search_Line();
void Calculate_Offset();
void Blacking();
void Camera_All_Deal(void);
#endif