#ifndef _LOCATION_H
#define _LOCATION_H

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "zf_common_headfile.h"

#define locate_sz 12             //��������������Ŀ�������ȷ����(5-20���п���)

//---------------------�ṹ��---------------------//
//��¼��������λ�õĽṹ��
//struct location_goal{
//    //�ѵ����Ŀ���
//    int8_t Position_Pointer;
//    //��ǰ�ٶ�
//    double Speed_X;
//    double Speed_Y;
//    double Speed_Z;
//    //��ǰλ��
//    float x;
//    float y;
//    //Ŀ��λ��
//    float x1;
//    float y1;
//    //��ǰ��̬
//    float Angel;
//    //Ŀ����̬
//    double Angel_Target;
//    //Ŀ�����
//    float DistanceX;
//    float DistanceY;
//    //���ϴ�ת��֮��ǰ���ľ���(��̣�
//    float MileageX;
//    float MileageY;
//};

//extern struct location_goal Car;

extern uint8 Xt , Xb , Yl , Yr ;
extern int originMap[locate_sz][2];


void carlocation_init(void);

void location_thres_init(void);
void get_route();
void initHashMap(int true_sz);


#endif
