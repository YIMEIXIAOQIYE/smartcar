//#include "zf_common_headfile.h"
//#include "math.h"
//int16 Y_KP = 35;//30
//int16 DIR_KP = 61;//40
//int16 DIR_KD = -31; //-16
//int8 ForesightMax = 14; //13
//int16 SPEED_init = 220;
//float DIR_DT  = 0.9;
//int16 Z_gyro=0;
//int16 Z_gyro_old=0;
//int16 Y_gyro;
//int8 TJP = 0;  //�����ܱ�־

//int8 HD_ERR = 0 ;  //�Ҷ�ƫ��

//#define Q_KP 0.0
//#define DJ_INIT 740  //740
//#define DJ_L 650
//#define DJ_R 830

//#define X 0
//#define Y 1

//#define IMG_H MT9V03X_H/2
//#define IMG_W MT9V03X_W/2
//#define GrayScale 256
//uint8 image_threshold;  //ͼ����ֵ

//uint8* p;
//uint8 img[IMG_H][IMG_W];
//uint8 end_img[IMG_H][IMG_W];
//uint8 see_img[IMG_H][IMG_W];

//uint8 YS[8] = {0};   // =1 R  =2 Y  =3 B  =4 P
//uint8 YS_N =0;  //Ԫ�ؼ���

////
//int8 CAR_MODE = 0;    //=0�ȴ����� =1����   =2 ������  =3 ���
//int8 GO_DIR = 1;  //��������
//uint16 FC_L=0;   //����·�̻���
//float FC_ANG=0.0; //�����ǶȻ���
////UI����
//uint8 GB_H = 0;
//uint8 GB_MODE = 0;
//uint32 TIME = 0;

//int16 MAX_Y_GYRO=0;
//int16 MIN_Y_GYRO=0;

////�ؼ������
//int8 point[20][2];
////�µ�����
//int8 PO_STEP=0;
//uint16 PO_L=0;
////P������
////�����߲���
//int8 BMX_STEP=0;
//int8 BMX_DIR=0;
//uint16 BMX_L=0;
//uint8 BMX_T=0;
//uint8 BMX_N=2;
////P������
//int8 P_STEP=0;
//int8 P_DIR=0;
//uint16 P_L=0;
//int8 P_N=0;
//float P_ANG=0.0;
////Բ������
//int8 YH_STEP=0;
//int8 YH_DIR=0;
//float YH_ANG=0.0;
//uint16 YH_L=0;
//int8 YH_N=0;
////����·�ڲ���
//int8 SC_STEP=0;
//int8 SC_DIR=0;
//uint16 SC_L=0;
//float SC_ANG=0.0;
//int8 SC_N=0;
////ʮ��·�ڲ���
//int8 SZLK_STEP = -1;
//uint16 SZLK_L =0;

//uint16 POWER_V;  //��ص�ѹ
////Ѱ������
//int midline[IMG_H] = {0};
//int nextLine[IMG_H] = {0};
//int liftLine[IMG_H] = {0};
//int rightLine[IMG_H] = {0};

//float err = 0.0;
//float A_x, A_y, B_x, B_y, C_x, C_y;     //����A,B,C�������xy����

//int min_W = 71;  //������������ؿ��
//int max_W = 22;  //������Զ�����ؿ��
//uint16 W_K[IMG_H]={1000}; //����ÿ�п�ȱ���*1000
//float MAX_W_K = 0;  //��������ȱ���

//float dir_out=0.0,dir_out_old=0.0; //���PWM���


////void PID();
//void findMidline();
//void direction_PID();
////void uart_to_pc();

//void img_vary(void);  //ͼ������
//extern void dis_oled(void); //ˢ��ͼ��
//extern void dis_num(uint8 x,uint8 y,int16 A,int16 B);
//void img_change(int8 X1,int8 Y1,int8 X2,int8 Y2,int8 H0,int8 H1);
//void point_find(void); //�ҹؼ���
//void Binarization(void);  //ȡͼ����ֵ��
//extern void UART_GO(void);


//int16 farthestEffective;     //����������Զ��Ч��
//int16 a_x, a_y, b_x, b_y, c_x, c_y, //�����µ���������
//      d_x, d_y, e_x, e_y, f_x, f_y; //�Ҳ���µ���������

//int rightWidth[64] = {0};       //���������ֱ��ͼ����
//int liftWidth[64] = {0};        //���������ֱ��ͼ����

//uint8 width;   //������ɫ���
//int widthArray[32];     //������ɫ�������

//int m, n;

//uint8 TU_N=0,TU_F=0;  //ͼ��֡��


//uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
//{
//    uint16 width = col;
//    uint16 height = row;
//    int pixelCount[GrayScale];
//    float pixelPro[GrayScale];
//    int i, j, pixelSum = width * height;
//    uint8 threshold = 0;
//    uint8* data = image;  //ָ���������ݵ�ָ��
//    for (i = 0; i < GrayScale; i++)
//    {
//        pixelCount[i] = 0;
//        pixelPro[i] = 0;
//    }

//    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
//    for (i = 0; i < height; i++)
//    {
//        for (j = 0; j < width; j++)
//        {
//            pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
//        }
//    }

//    //����ÿ������������ͼ���еı���
//    float maxPro = 0.0;
//    for (i = 0; i < GrayScale; i++)
//    {
//        pixelPro[i] = (float)pixelCount[i] / pixelSum;
//        if (pixelPro[i] > maxPro)
//        {
//            maxPro = pixelPro[i];
//        }
//    }

//    //�����Ҷȼ�[0,255]
//    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
//    for (i = 0; i < GrayScale; i++)     // i��Ϊ��ֵ
//    {
//        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
//        for (j = 0; j < GrayScale; j++)
//        {
//            if (j <= i)   //��������
//            {
//                w0 += pixelPro[j];
//                u0tmp += j * pixelPro[j];
//            }
//            else   //ǰ������
//            {
//                w1 += pixelPro[j];
//                u1tmp += j * pixelPro[j];
//            }
//        }
//        u0 = u0tmp / w0;
//        u1 = u1tmp / w1;
//        u = u0tmp + u1tmp;
//        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
//        if (deltaTmp > deltaMax)
//        {
//            deltaMax = deltaTmp;
//            threshold = (uint8)i;
//        }
//    }

//    return threshold;
//}

//void point_find(void)
//{
//    uint8 i,j,x,y,r,l;
//    float k,n;


//    //////////////////////////////////////////////////////////׼���ҵ㹤��///////////////////////////////////////////////////////

//    //��ؼ���0-4
//    l=0;
//    r = IMG_W - 1;

//    for(int i=0;i<IMG_W-1;i++)
//    {
//        if(img[IMG_H - 1][i] == 0xff) //�׵�
//        {
//            l = i;
//            break;
//        }
//    }
//    for(int i=IMG_W-1;i>1;i--)
//    {
//        if(img[IMG_H - 1][i] == 0xff) //�׵�
//        {
//            r = i;
//            break;
//        }
//    }
//    point[2][X] =  (l+r)/2;  //2������X
//    point[2][Y] =  IMG_H - 1;  //2������Y

//    point[1][X] =  l;  //1������X
//    point[1][Y] =  IMG_H - 1;  //1������Y

//    point[3][X] =  r;  //3������X
//    point[3][Y] =  IMG_H - 1;  //3������Y

//    point[0][X] =  0;  //0������X
//    point[0][Y] =  IMG_H - 1;  //0������Y

//    point[4][X] =  IMG_W - 1;  //4������X
//    point[4][Y] =  IMG_H - 1;  //4������Y

//    //�ҹؼ��� 5��9
//    l=2;
//    for(i=IMG_H-1;i>=2;i--)  //�����
//    {
//        if(img[i-1][1] - img[i][1] ==0XFF || i==2)  //�ҵ��ڱ��
//        {
//            l = i;
//            break;
//        }
//    }
//    r=2;
//    for(i=IMG_H-1;i>=2;i--)  //�ұ���
//    {
//        if(img[i-1][IMG_W-1] - img[i][IMG_W-1] == 0XFF || i==2)  //�ҵ��ڱ��
//        {
//            r = i;
//            break;
//        }
//    }

//    point[5][X]=1;  //5�㸳ֵ
//    point[5][Y]=l;
//    point[9][X]=IMG_W-1;  //9�㸳ֵ
//    point[9][Y]=r;

//    //�ҹؼ���10.13
//    l=1;
//    for(i=point[5][Y]-1;i>=1;i--)
//    {
//        if(img[i-1][1]!=img[i][1] || i==1)  //�ҵ��ڱ��
//        {
//            l = i;
//            break;
//        }
//    }
//    r=1;
//   for(i=point[9][Y]-1;i>=1;i--)  //�ұ���
//   {
//       if(img[i-1][IMG_W-1]!= img[i][IMG_W-1] || i==1)  //�ҵ��ڱ��
//       {
//           r = i;
//           break;
//       }
//   }

//   point[10][X]=1;  //10�㸳ֵ
//   point[10][Y]=l;
//   point[13][X]=IMG_W-1;  //13�㸳ֵ
//   point[13][Y]=r;


//    //��ؼ���6.7.8

//    x = IMG_H - 1;  //��־λ��0
//    l = 0;

//    if(point[1][X] == 0)  //�����޺�
//    {
//        for(i=IMG_H-1;i>0;i--)
//       {
//           if(img[i][0] == 0x00 || i==1)
//           {
//               break;
//           }
//       }
//      // i= point[9][Y];
//       j = 0;

//    }
//    else  //�����к�
//    {
//        i= IMG_H -2;
//        j=point[1][X];
//    }


//    for(;i>1 ; i--)  //����������
//    {
//        for(;j<IMG_W - 1;j++)
//        {
//            if(img[i][j]==0xff)  //���������ҵ���
//            {
//                if(img[i-1][j-1]==0x00) //�����к�,�����������
//                {
//                    j-=1;
//                }
//                else  //�����޺ڣ�˵���ҵ����
//                {
//                    x=i;
//                    l = j-1;
//                }
//                break;
//            }
//        }
//        if(x != IMG_H - 1) break;
//    }
//    point[6][X]=j-1;  //6�㸳ֵ
//    point[6][Y]=i;

//    y = IMG_H - 1;  //��־λ��0
//    r = IMG_W - 1;

//    if(point[3][X] == IMG_W-1)  //�����޺�
//    {
//        for(i=IMG_H-1;i>0;i--)
//        {
//            if(img[i][IMG_W-1] == 0x00 || i==1)
//            {
//                break;
//            }
//        }
//       // i= point[9][Y];
//        j= IMG_W-1;
//    }
//    else  //�����к�
//    {
//        i= IMG_H -2;
//        j =point[3][X];
//    }


//    for(;i>1 ; i--)  //����������
//    {
//        for(; j >1; j--)
//        {
//            if(img[i][j]==0xff)  //���������ҵ���
//            {
//                if(img[i-1][j+1]==0x00) //�����к�,�����������
//                {
//                    j+=1;

//                }
//                else  //�����޺ڣ�˵���ҵ����
//                {
//                    y=i;
//                    r = j+1;
//                }
//                break;
//            }
//        }
//        if(y != IMG_H - 1) break;
//    }
//    point[8][X]=j+1;  //8�㸳ֵ
//    point[8][Y]=i;


//    if(point[6][X] < point[8][X]) //�������
//    {
//        if( point[6][Y] <  point[8][Y])  //����ҵ�
//        {
//            point[7][Y] = point[8][Y];
//            l = IMG_W/2 + (IMG_W/2 - point[8][X]);  //Ĭ��λ��
//            for(i=point[8][X]-3 ; i>1 ; i--)
//            {
//                if(img[point[7][Y]][i]==0x00)  //�����Һ�
//                {
//                    l = (i+point[8][X])/2;
//                    break;
//                }
//            }
//        }
//        else       //����Ҹ�
//        {
//            point[7][Y] = point[6][Y];
//            l = IMG_W/2 + (IMG_W/2 - point[6][X]);  //Ĭ��λ��
//            for(i=point[6][X]+3 ; i<IMG_W-1 ; i++)
//            {
//                if(img[point[7][Y]][i]==0x00)  //�����Һ�
//                {
//                    l = (i+point[6][X])/2;
//                    break;
//                }
//            }
//        }
//        point[7][X]=l;  //7�㸳ֵ
//    }
//    else
//    {
//        point[7][X] = (point[6][X] +point[8][X])/2;  //���������7��ȡ6���8���е�
//        point[7][Y] = (point[6][Y] +point[8][Y])/2;
//    }



//   //�ҹؼ���11.12
//    l=1;
//    for(i=point[6][Y];i>1;i--)  //�����
//    {
//      if(img[i][point[6][X]] - img[i-1][point[6][X]] == 0xff)  //�ҵ��ױ��
//      {
//          l = i;
//          break;
//      }
//    }
//    r=1;
//    for(i=point[8][Y];i>1;i--)  //�ұ���
//    {
//     if(img[i][point[8][X]] - img[i-1][point[8][X]] == 0xff)  //�ҵ��ױ��
//     {
//         r = i;
//         break;
//     }
//    }

//    point[11][X]=point[6][X];  //11�㸳ֵ
//    point[11][Y]=l;
//    point[12][X]=point[8][X];  //12�㸳ֵ
//    point[12][Y]=r;

//    //�ҹؼ���14

//    if(point[7][X] == point[2][X])  //һ��ֱ��
//    {
//        l= IMG_H-1;
//        r = point[2][X];

//        for(i=IMG_H-1;i>0;i--)
//        {
//            j=r;
//            if(img[i][j] == 0x00 || i==1) //�Һ�
//            {
//                l = i;
//                r = j;
//                break;
//            }
//        }
//    }
//    else
//    {
//        k = (float)(point[7][Y] - point[2][Y])/(point[7][X] - point[2][X]);   //�� 7.2б��
//        n = (float)(point[2][Y] -( k * point[2][X]));

//        l= IMG_H-1;
//        r = point[2][X];

//        for(i=IMG_H-1;i>0;i--)
//        {
//            j=(i-n)/k;
//            if(img[i][j] == 0x00 || i==1) //�Һ�
//            {
//                l = i;
//                r = j;
//                break;
//            }
//        }
//    }

//    point[14][X]=r;  //14�㸳ֵ
//    point[14][Y]=l;

////////////////////////////////////////////////////////////׼����������///////////////////////////////////////////////////////
//}


//void Binarization(void)  //ȡͼ����ֵ��
//{
//    uint8 i,j;

//    for(i = 0; i < IMG_H; i++)
//    {
//        for(j = 0; j < IMG_W; j++)
//        {
//            img[i][j] = mt9v03x_image[i*2][j*2];
//        }
//    }
//    p = img[0];
//    //����ֵ
//    image_threshold = otsuThreshold(p, IMG_H, IMG_W) + HD_ERR;

//   // if(CAR_MODE==0) //��ͼ��ֵ��
//    //{
//        //��ֵ��
//        for(i = 0; i < IMG_H;i++)
//        {
//            for(j=0; j< IMG_W; j++)
//            {
//                if(img[i][j]>image_threshold)
//                {
//                    img[i][j]=0xff;
//                    see_img[i][j]=0xff;
//                    end_img[i][j]=0xff;
//                }
//                else
//                {
//                    img[i][j]=0x00;
//                    see_img[i][j]=0x00;
//                    end_img[i][j]=0x00;
//                }
//            }
//        }/*
//    }
//    else //�����ܶ�ֵ��
//    {
//        //��ֵ��
//        for(i = 0; i < IMG_H;i++)
//        {
//            for(j=0; j< IMG_W; j++)
//            {
//                if(img[i][j]>image_threshold)
//                {
//                    img[i][j]=0xff;
//                    end_img[i][j]=0xff;
//                }
//                else
//                {
//                    img[i][j]=0x00;
//                    end_img[i][j]=0x00;
//                }
//            }
//        }
//    }*/
//}


//void img_vary(void)
//{

//    uint8 i,j,x,y,r,l;
//    float k,n;

//    //////////////////////////////////////////////////////////׼���ҵ㹤��///////////////////////////////////////////////////////
//    point_find();
////////////////////////////////////////////////////////////׼����������///////////////////////////////////////////////////////
///////////////////////////////////////////////////////�µ�ʶ��///////////////////////////////////////////////////////////////
//    switch(PO_STEP)
//    {
//        case 0:
//        {
//            for(i=IMG_H-1;i>0;i--)
//            {
//                if(img[i][IMG_W/2] == 0X00)
//                {
//                    break;
//                }
//            }
//            if(CAR_MODE ==3 && YH_STEP <=0 && BMX_STEP <= 0 && P_STEP <= 0&& SC_STEP <=0 && SZLK_STEP <=0  &&  Y_gyro<-2000.0 && PO_L>10000 && i<IMG_H/2)  //�ж��µ���ֵ
//            {
//                PO_STEP=1;
//                PO_L=0;
//                gpio_set_level( B11, 1);
//            }
//        }break;
//        case 1:
//        {
//            if((PO_L > 4000 &&  Y_gyro <-2000.0) || PO_L > 12000)  //�ж��µ���ֵ
//            {
//                PO_STEP=2;
//                PO_L=0;
//            }
//        }break;
//        case 2:
//        {
//            if(PO_L > 5000)  //�ж��µ���ֵ
//            {
//                PO_STEP=-1;
//                PO_L=0;
//                BMX_STEP=0;
//                YH_STEP=0;
//                SC_STEP=0;
//                gpio_set_level( B11, 0);
//            }
//        }break;
//    }

//    ////////////////////////////////////////////////////�жϰ����߿�ʼ//////////////////////////////////////////////////////////
//    switch(BMX_STEP)
//    {
//        case 0:
//        {
//            BMX_T=0;
//            for(i=IMG_H-2*ForesightMax+3;i>IMG_H-2*ForesightMax-2;i--)  //ͳ�ư����������
//            {
//                for(j=IMG_W/4;j<IMG_W*3/4;j++)
//                {
//                    if(img[i][j] != img[i][j+1])
//                    {
//                        BMX_T+=1;
//                    }
//                }
//            }
//            if( CAR_MODE ==3 && YH_STEP <=3 &&   PO_STEP <=0 && SZLK_STEP <= 0  && P_STEP<=0  && BMX_T>25)
//            {
//                SC_STEP =0;
//                YH_STEP = 0;
//                if(point[6][Y]<point[8][Y])  //�жϳ��ⷽ��
//                {
//                    BMX_DIR = 1;  //�Ҳ೵��
//                }
//                else
//                {
//                    BMX_DIR = 0;  //��೵��
//                }

//                if(CAR_MODE==3) BMX_N--;  //�����ܽ׶�



//                if(BMX_N) //����������
//                {
//                    gpio_set_level( B11, 1);
//                    BMX_STEP = 1;
//                    BMX_L =0;
//                }
//                else //������
//                {
//                    gpio_set_level( B11, 1);
//                    FC_ANG = 0.0;  //�ǶȻ���
//                    FC_L = 0;
//                    CAR_MODE = 4;   //�������׶�
//                }
//            }
//        }break;
//        case 1:  //����
//        {

//            if(BMX_L>4000)
//            {
//                BMX_STEP = 0;
//                gpio_set_level( B11, 0);
//                break;
//            }

//            for(i=IMG_H-ForesightMax*2-1;i<IMG_H;i++)  //������Ϳ��
//            {
//                for(j=IMG_W/2-i*3/4;j<IMG_W/2+i*3/4;j++)
//                {
//                    end_img[i][j] = 0xff;
//                    see_img[i][j] = 0xff;
//                }
//            }

//            //������
//            img_change(point[1][X],point[1][Y],point[8][X]-max_W,point[8][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//            //������
//            img_change(point[3][X]-1,point[3][Y],point[6][X]+max_W,point[6][Y],IMG_H-ForesightMax*2-1,IMG_H-1);

//           /* if(BMX_N) //����������
//            {
//                if(BMX_DIR == 0) //�������
//                {
//                    //������
//                    img_change(point[1][X],point[1][Y],point[8][X]-max_W,point[8][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//                }
//                else //���Ҳ���
//                {
//                    //������
//                    img_change(point[3][X]-1,point[3][Y],point[6][X]+max_W,point[6][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//                }
//            }
//            else  //��ǰ���������
//            {

//            }*/
//        }break;

//    }

//////////////////////////////////////////////////////�жϰ����߽���//////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////ʶ��ʮ��·�ڲ�����///////////////////////////////////////////////////
//    switch(SZLK_STEP)
//    {
//        case 0:
//        {      //6.8��߶Ȳ�С��10              6.8�߶ȶ���ǰհ��Χ��                                                   ��Զ��߶�С��5      �����Ҳ�5.6��7.8���ֵС��7                                    ��������ȴ���200%
//            if( CAR_MODE ==3 &&  PO_STEP <=0 && BMX_STEP <= 0 && YH_STEP <= 0 && P_STEP<=0 && SC_STEP<=0 && abs(point[6][Y]-point[8][Y])<10 && point[6][Y]>IMG_H-2*ForesightMax && point[8][Y]>IMG_H-2*ForesightMax && point[14][Y] < 5 && (abs(point[5][Y]-point[6][Y])<7 || abs(point[8][Y]-point[9][Y])<7 ) && MAX_W_K>2000)
//            {
//              SZLK_STEP =1;
//              SZLK_L = 0;
//              gpio_set_level( B11, 1);
//            }
//        }break;
//        case 1:  //����·�ڵ�һ�׶�
//        {
//            if((SZLK_L>5000) || (point[1][X] == 0 || point[3][X] == IMG_W-1))  //�ж��ǵ�һ�׶ν���
//            {
//                SZLK_STEP = 2;
//                SZLK_L = 0;
//                break;
//            }
//            //������
//            img_change(point[1][X],point[1][Y],point[6][X],point[6][Y],IMG_H-ForesightMax*2-1,IMG_H-1);

//            //������
//            img_change(point[3][X],point[3][Y],point[8][X],point[8][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//        }break;
//        case 2:
//        {
//            if(SZLK_L>5000)  //�ж��ǵ�2�׶ν���
//            {
//                SZLK_STEP = 0;
//                SZLK_L = 0;
//                gpio_set_level(B11, 0);
//                break;
//            }
//            //������
//            img_change(1,IMG_H-1,IMG_W/2-11,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//            //������
//            img_change(IMG_W-2,IMG_H-1,IMG_W/2+11,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//        }break;
//    }
///////////////////////////////////////////////////////////ʶ��ʮ��·�ڽ���///////////////////////////////////////////////////

///////////////////////////////////////////////////////////ʶ������·�ڿ�ʼ///////////////////////////////////////////////////
//    switch(SC_STEP)
//    {
//        case 0:  //ʶ������·��
//        {
//            if( CAR_MODE ==3 &&  PO_STEP <=0 && BMX_STEP <= 0 && YH_STEP<=0 && P_STEP<=0 && SZLK_STEP <=0 && abs(point[6][Y]-point[8][Y]) < 15 &&  point[6][Y]>IMG_H-ForesightMax*2 &&point[8][Y]>IMG_H-ForesightMax*2 && (point[5][Y]<10 || point[9][Y]<10)&&point[14][Y]>5 && point[14][Y]<15 && SC_L>12000)
//            {
//               // SC_DIR = SC_N/2%2;
//                SC_ANG=0.0;
//                SC_STEP =1;
//                SC_L=0;
//                gpio_set_level( B11, 1);
//            }
//        }break;
//        case 1:
//        {
//            //����
//            if(SC_DIR == 0)  //������
//            {
//                if(point[8][Y]<10 || SC_L>6000 || fabs(SC_ANG) >100.0) //�ж���ֹ����
//                {
//                    SC_STEP =2;
//                    SC_L=0;
//                    break;
//                }
//                //������
//                img_change(IMG_W-2,IMG_H-1,point[14][X],point[14][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//            else //������
//            {
//                if(point[6][Y]<10 || SC_L>6000 || fabs(SC_ANG) >100.0) //�ж���ֹ����
//                {
//                    SC_STEP =2;
//                    SC_L=0;
//                    break;
//                }
//                //������
//                img_change(1,IMG_H-1,point[14][X],point[14][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//        }break;
//        case 2:
//        {
//            if(SC_DIR==0) ////������
//            {
//                if(point[3][X]<IMG_W-2 || SC_L>6000 || fabs(SC_ANG) >120.0)  //�ж���ֹ����
//                {
//                    SC_STEP =3;
//                    SC_L=0;
//                    break;
//                }
//                //������
//                img_change(IMG_W-2,IMG_H-1,10,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//            else //������
//            {
//                if(point[1][X]>1 || SC_L>6000 || fabs(SC_ANG) >120.0) //�ж���ֹ����
//               {
//                   SC_STEP =3;
//                   SC_L=0;
//                   break;
//               }
//                //������
//                img_change(1,IMG_H-1,IMG_W-10,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//        }break;
//        case 3:
//        {
//            if(SC_L>2000 || fabs(SC_ANG) >120.0)
//            {
//                gpio_set_level( B11, 0);
//                SC_N++;
//                YH_L=0;
//                SC_STEP =0;
//            }
//        }break;
//    }
//    /////////////////////////////////////////////////////////ʶ������·�ڽ���///////////////////////////////////////////////////

//    /////////////////////////////////////////////////////////ʶ��Բ����ʼ///////////////////////////////////////////////////////

//    switch(YH_STEP)
//    {
//        case 0:  //�ȴ�ʶ��Բ��
//        {
//            if( YH_L > 10000 && CAR_MODE ==3 &&  PO_STEP <=0 && BMX_STEP <= 0 && P_STEP <= 0&& SC_STEP <=0 && SZLK_STEP <=0  &&(point[6][Y]<5 || point[8][Y]<5)&& abs(point[6][Y]-point[8][Y]) > IMG_H-2*ForesightMax &&  point[14][Y] < 5 && point[6][X]<point[8][X])
//            {
//                if(point[6][Y]<point[8][Y]) //�һ�
//                {
//                    if(abs(point[12][Y]-point[8][Y])>10 && abs(point[9][Y]-point[8][Y])<5 && abs(point[9][Y]-point[13][Y])>15)
//                    {
//                        YH_STEP = 1;
//                        YH_DIR = 1;
//                        YH_L=0;
//                        YH_ANG =0.0;
//                        gpio_set_level( B11, 1);
//                    }
//                }
//                else //��
//                {
//                    if(abs(point[11][Y]-point[6][Y])>10 && abs(point[5][Y]-point[6][Y])<5 && abs(point[5][Y]-point[10][Y])>15)
//                   {
//                       YH_STEP = 1;
//                       YH_DIR = 0;
//                       YH_L=0;
//                       YH_ANG =0.0;
//                       gpio_set_level( B11, 1);
//                   }
//                }
//            }
//        }break;
//        case 1:  //��ʼԲ����һ�׶β���
//        {
//            if(YH_DIR == 0)  //��
//            {
//                if(point[6][Y]<IMG_H-2*ForesightMax && YH_L > 2500) //�ж���ֹ����
//                {
//                    YH_STEP =2;
//                    YH_L=0;
//                   // gpio_set_level( B11, 0);
//                    break;
//                }
//                //����
//                i = point[11][Y]-2;
//                j = point[11][X];
//                y = i;
//                for(;i>1 ; i--)  //����������
//                    {
//                        for(;j<IMG_W - 1;j++)
//                        {
//                            if(img[i][j]==0xff)  //���������ҵ���
//                            {
//                                if(img[i-1][j-2]==0x00) //�����к�,�����������
//                                {
//                                    j-=2;
//                                }
//                                else  //�����޺ڣ�˵���ҵ����
//                                {
//                                    y=i;
//                                    l = j-1;
//                                }
//                                break;
//                            }
//                        }
//                        if(y != i) break;
//                    }
//                x=j-1; //�õ��е�����
//                y=i;
//                img_change(x,y,point[6][X],point[6][Y],y,point[6][Y]);
//            }
//            else //�һ�
//            {
//               if(point[8][Y]<IMG_H-2*ForesightMax && YH_L > 2500) //�ж���ֹ����
//               {
//                   YH_STEP =2;
//                   YH_L=0;
//                  // gpio_set_level( B11, 0);
//                   break;
//               }
//                //����
//                i = point[12][Y]-2;
//                j = point[12][X];
//                y = i;
//                for(;i>1 ; i--)  //����������
//                {
//                    for(; j >1; j--)
//                    {
//                        if(img[i][j]==0xff)  //���������ҵ���
//                        {
//                            if(img[i-1][j+2]==0x00) //�����к�,�����������
//                            {
//                                j+=2;
//                            }
//                            else  //�����޺ڣ�˵���ҵ����
//                            {
//                                y=i;
//                                r = j+1;
//                            }
//                            break;
//                        }
//                    }
//                    if(y != i ) break;
//                }
//                x=j+1; //�õ��е�����
//                y=i;
//                img_change(x,y,point[8][X],point[8][Y],y,point[8][Y]);
//            }
//        }break;
//        case 2: //�������׶β���
//            {
//                if(YH_DIR == 0)  //��
//                {
//                    if(point[1][X]>5 && YH_L > 1500)
//                    {
//                       YH_STEP =3;
//                       YH_L=0;
//                       gpio_set_level( B11, 0);
//                       break;
//                    }
//                    //����
//                    img_change(5,IMG_H-1,IMG_W/2-max_W/2,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//                }
//                else //�һ�
//                {
//                    if(point[3][X]<IMG_W-5 && YH_L > 1500)
//                    {
//                       YH_STEP =3;
//                       YH_L=0;
//                       gpio_set_level( B11, 0);
//                       break;
//                    }
//                    //����
//                    img_change(IMG_W-5,IMG_H-1,IMG_W/2+max_W/2,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//                }
//            }break;
//        case 3:
//        {
//            if(point[8][X] < point[6][X] && point[14][Y] > 2) //˵����P·��
//            {
//               P_STEP = 1;
//               P_DIR = YH_DIR;
//               P_ANG=0.0;
//               YH_STEP =0;

//            }
//            else
//           {
//               YH_STEP =4;
//               YH_L = 0;
//           }

//        }break;
//        case 4: //���������׶β���
//        {
//            if(YH_L > 25000 && fabs(YH_ANG)>180.0)
//            {
//                YH_STEP = 5;
//                YH_L=0;
//            }
//            if(YH_DIR==0) //��
//            {
//                //����
//                img_change(IMG_W-2,IMG_H-1,IMG_W/2-max_W,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//            }
//            else //�һ�
//            {
//                //����
//                img_change(1,IMG_H-1,IMG_W/2+max_W,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//        }break;
//        case 5:  //����������
//        {
//            if(YH_DIR==0) //��
//            {
//                if((point[8][X]>IMG_W/2 || fabs(YH_ANG)>200.0) && YH_L>3000)
//                {
//                    YH_STEP = 6;
//                    YH_L =0;
//                }
//                //����
//                img_change(IMG_W-1,IMG_H-1,IMG_W/2-max_W,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//            }
//            else //�һ�
//            {
//                if((point[6][X]<IMG_W/2 ||  fabs(YH_ANG)>200.0) && YH_L>3000)
//                {
//                    YH_STEP = 6;
//                    YH_L =0;
//                }
//                //����
//                img_change(1,IMG_H-1,IMG_W/2+max_W,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//        }break;
//        case 6:  //����һ�׶β���
//        {
//          if(YH_DIR==0) //��
//          {
//              if((point[8][X]<10 || fabs(YH_ANG)>220.0) && YH_L>2000)
//              {
//                  gpio_set_level( B11, 1);
//                  YH_STEP = 7;
//                  YH_L =0;
//              }
//              //����
//              img_change(IMG_W-10,IMG_H-1,1,10,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//          else //�һ�
//          {
//               if((point[6][X]>IMG_W-10  || fabs(YH_ANG)>220.0) && YH_L>2000)
//                {
//                   gpio_set_level( B11, 1);
//                    YH_STEP = 7;
//                    YH_L =0;
//                }
//              //����
//              img_change(10,IMG_H-1,IMG_W-2,10,IMG_H-ForesightMax*2-1,IMG_H-1);
//          }
//        }break;
//        case 7: //�������׶β���
//        {
//          if(YH_DIR==0) //��
//          {
//              if(((point[9][Y]>IMG_H-8 || point[9][Y]<5 ) && YH_L>5000)  || fabs(YH_ANG)>330.0)
//              {
//                  YH_STEP = 8;
//                  YH_L =0;
//              }
//              //����
//              img_change(IMG_W-10,IMG_H-1,1,10,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//          else //�һ�
//          {
//              if(((point[5][Y]>IMG_H-8 || point[5][Y]<5) && YH_L>5000)  || fabs(YH_ANG)>330.0)
//             {
//                YH_STEP = 8;
//                YH_L =0;
//             }
//              //����
//              img_change(10,IMG_H-1,IMG_W-2,10,IMG_H-ForesightMax*2-1,IMG_H-1);
//          }
//        }break;
//        case 8://���������׶β���
//        {
//          if(YH_DIR==0) //��
//          {
//              for(i=IMG_H-1;i>1;i--)
//                {
//                    if(img[i][0] != img[i-1][0] || i==1)
//                    {
//                        break;
//                    }
//                }
//              if(i>IMG_H-ForesightMax*2 && i<IMG_H-ForesightMax && YH_L>2000)
//               {
//                  gpio_set_level( B11, 0);
//                  YH_STEP = 9;
//                  YH_L =0;
//               }
//              //����
//              img_change(1,IMG_H-1,point[8][X]-max_W/2,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//          else //�һ�
//          {
//              for(i=IMG_H-1;i>1;i--)
//              {
//                  if(img[i][IMG_W-1] != img[i-1][IMG_W-1] || i==1)
//                  {

//                      break;
//                  }
//              }
//              if(i>IMG_H-ForesightMax*2 && i<IMG_H-ForesightMax && YH_L>2000)
//             {
//                  gpio_set_level( B11, 0);
//                YH_STEP = 9;
//                YH_L =0;
//             }
//              //����
//              img_change(IMG_W-2,IMG_H-1,point[6][X]+max_W/2,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//        }break;
//        case 9:
//        {
//              if(YH_DIR==0) //��
//              {
//                  if(point[1][X]>0 && YH_L>2000  || fabs(YH_ANG)>330.0)
//                   {

//                      YH_STEP = 0;
//                      SC_L=0;
//                      YH_L =10000;
//                   }
//                  //����
//                  img_change(1,IMG_H-1,point[6][X]+max_W/2,point[6][Y],IMG_H-ForesightMax*2-1,IMG_H-1);

//              }
//              else //�һ�
//              {
//                  if(point[3][X]<IMG_W-1 && YH_L>2000  || fabs(YH_ANG)>330.0)
//                 {
//                    YH_STEP = 0;
//                    SC_L=0;
//                    YH_L =10000;
//                 }
//                  //����
//                  img_change(IMG_W-2,IMG_H-1,point[8][X]-max_W/2,point[8][Y],IMG_H-ForesightMax*2-1,IMG_H-1);

//              }
//        }break;

//    }

//    /////////////////////////////////////Բ���������//////////////////////////////////////////////////

//    ///////////////////////////////////P·�ڴ��� /////////////////////////////////////////////////////////////////////////////////////////////////
//    switch(P_STEP)
//    {
//        case 0:break; //�ȴ���P
//        case 1:  //�ȴ�ʶ���P
//        {
//          if(P_DIR==0) //��P
//          {
//              if(point[8][X]>IMG_W/2+8 && P_L > 20000 && fabs(P_ANG)>230.0)
//              {
//                  gpio_set_level( B11, 1);
//                  P_STEP = 2;
//                  P_L=0;
//              }
//          }
//          else //��P
//          {
//              if(point[6][X]<IMG_W/2-8 && P_L > 20000 && fabs(P_ANG)>230.0)
//              {
//                  gpio_set_level( B11, 1);
//                  P_STEP = 2;
//                  P_L=0;
//              }
//          }
//        }break;
//        case 2: //��P����
//        {
//           if(P_L > 10000)  //�ж���ֹ����
//           {
//              if(P_DIR==0)  //,�ж��Ƿ�P��Բ������P������8��Y
//              {
//                  for(i=IMG_H-1;i>1;i--)
//                  {
//                      if(img[i][IMG_W-1] - img[i-1][IMG_W-1]== 0xFF || i==2) break;
//                  }

//                  if(point[6][Y]<15 && i>5 && TJP==0)  //��P������Բ��
//                  {
//                      YH_STEP = 2;
//                        YH_DIR = 1;
//                        YH_L=0;
//                        P_STEP =0;
//                        P_L=0;
//                        SC_L=0;

//                  }
//                  else  //��P����
//                  {
//                        gpio_set_level( B11, 0);
//                        P_STEP =0;
//                        YH_L=0;
//                        SC_L=0;
//                        P_L=0;
//                        SC_L=0;
//                  }

//              }
//              else //��P�������Y
//              {
//                for(i=IMG_H-1;i>1;i--)
//                {
//                    if(img[i][0] - img[i-1][0]== 0xFF || i==2) break;
//                }
//                if((point[8][Y]<15 && i>5) || TJP==1)  //��P��������Բ��
//                {
//                    YH_STEP = 2;
//                    YH_DIR = 0;
//                    YH_L=0;
//                    P_STEP =0;
//                    P_L=0;
//                    SC_L=0;
//                }
//                else  //��P����
//                {
//                    gpio_set_level( B11, 0);
//                    P_STEP =0;
//                    P_L=0;
//                    SC_L=0;
//                }
//              }

//           }

//          if(P_DIR==0) //��P
//          {
//              //�Ҳ��߹ؼ���
//              if(point[8][X] == point[3][X])  //һ��ֱ��
//              {
//                  l= point[8][Y]-1;
//                  r = point[3][X];

//                  for(i=point[8][Y]-1;i>0;i--)
//                  {
//                      j=r;
//                      if(img[i][j] == 0x00 || i==1) //�Һ�
//                      {
//                          l = i;
//                          r = j;
//                          break;
//                      }
//                  }
//              }
//              else
//              {
//                  k = (float)(point[8][Y] - point[3][Y])/(point[8][X] - point[3][X]);   //�� 7.2б��
//                  n = (float)(point[3][Y] -( k * point[3][X]));

//                  l= point[8][Y]-1;
//                  r = point[3][X];

//                  for(i=point[8][Y]-1;i>0;i--)
//                  {
//                      j=(i-n)/k;
//                      if(img[i][j] == 0x00 || i==1) //�Һ�
//                      {
//                          l = i;
//                          r = j;
//                          break;
//                      }
//                  }
//              }

//              x=r;  //14�㸳ֵ
//              y=l;

//              img_change(1,IMG_H-1,IMG_W-2,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//          else //��P
//          {
//              //�Ҳ��߹ؼ���
//            if(point[6][X] == point[1][X])  //һ��ֱ��
//            {
//                l= point[6][Y]-1;
//                r = point[1][X];

//                for(i=point[6][Y]-1;i>0;i--)
//                {
//                    j=r;
//                    if(img[i][j] == 0x00 || i==1) //�Һ�
//                    {
//                        l = i;
//                        r = j;
//                        break;
//                    }
//                }
//            }
//            else
//            {
//                k = (float)(point[6][Y] - point[1][Y])/(point[6][X] - point[1][X]);   //�� 7.2б��
//                n = (float)(point[1][Y] -( k * point[1][X]));

//                l= point[6][Y]+1;
//                r = point[1][X];

//                for(i=point[6][Y]-1;i>0;i--)
//                {
//                    j=(i-n)/k;
//                    if(img[i][j] == 0x00 || i==1) //�Һ�
//                    {
//                        l = i;
//                        r = j;
//                        break;
//                    }
//                }
//            }

//            x=r;  //14�㸳ֵ
//            y=l;

//            img_change(IMG_W-2,IMG_H-1,1,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//          }
//        }break;
//    }
//    ////////////////////////////////////////P·�ڽ���///////////////////////////////////////////////////////////////////////////////////////////////

//}





//void img_change(int8 X1,int8 Y1,int8 X2,int8 Y2,int8 H0,int8 H1)  //�����㣬�ڷ�Χ�ڲ���
//{
//    uint8 i,j;
//    float k,n;

//    if(H0>H1) //ȷ���иߵ�
//    {
//        i=H0;
//        H0=H1;
//        H1=i;
//    }

//    if(X1<1)    X1=1; //�����޷�
//    if(X2<1)    X2=1;
//    if(Y1<1)    Y1=1;
//    if(Y2<1)    Y2=1;
//    if(X1>IMG_W-2)    X1=IMG_W-2;
//    if(X2>IMG_W-2)    X2=IMG_W-2;
//    if(Y1>IMG_H-1)    Y1=IMG_H-1;
//    if(Y1>IMG_H-1)    Y2=IMG_H-1;

//    if(X1 == X2)  //��һ����ֱֱ��
//    {
//        for(i=H0;i<=H1;i++)
//        {
//            j=X1;
//            end_img[i][j] = 0X00;
//            end_img[i][j+1] = 0X00;

//            see_img[i][j] = 0X00;
//            see_img[i][j+1] = 0X00;

//        }
//    }
//    else  //��б��
//    {
//        k = (float)(Y2 - Y1)/(X2 - X1);   //�� 6.1б��
//        n = (float)(Y1 -( k * X1));

//        for(i=H0;i<=H1;i++)
//        {
//            j=(i-n)/k;
//            end_img[i][j] = 0X00;
//            end_img[i][j+1] = 0X00;

//            see_img[i][j] = 0X00;
//            see_img[i][j+1] = 0X00;
//        }
//    }
//}


////Ѱ������
//void findMidline()
//{
//    int8 l = 0 ,r = IMG_W - 1;

//    //�������鸳��ֵ
//    for(int i = 0; i < IMG_H; i++)
//    {
//        midline[i] = IMG_W / 2;
//        liftLine[i] = 0;
//        rightLine[i] = IMG_W - 1;
//        nextLine[i] = IMG_W / 2;
//    }

//    midline[IMG_H - 1] = point[2][X];       //��ȡ����¼�е�
//    nextLine[IMG_H - 2] = point[2][X];       //����

//    W_K[IMG_H - 1] = abs(point[3][X] - point[1][X])*1000/((IMG_H - 1)*(min_W-max_W)/(IMG_H - 1)+max_W);
//    MAX_W_K = W_K[IMG_H - 1];  //��ʼ����������ȱ���ϵ��

//    for(int i = IMG_H - 2; i > 0; i--)
//    {
//        liftLine[i] = 0;
//        rightLine[i] = IMG_W - 1;
//        //�����޷�
//        if(nextLine[i] < 1)
//        {
//            nextLine[i] = 1;
//        }
//        if(nextLine[i] > IMG_W-2)
//        {
//            nextLine[i] = IMG_W-2;
//        }


//        for(int j = nextLine[i]; j > 1; j -= 1)
//        {
//            if(end_img[i][j] != end_img[i][j - 1])
//            {
//                liftLine[i] = j;
//                break;
//            }
//        }

//        for(int k = nextLine[i]; k < IMG_W - 2; k += 1)
//        {
//            if(end_img[i][k] != end_img[i][k + 1])
//            {
//                rightLine[i] = k;
//                break;
//            }
//        }


//        nextLine[i - 1] = (liftLine[i] + rightLine[i]) / 2; //��������
//        midline[i] = (liftLine[i] + rightLine[i]) / 2;

//        W_K[i] = abs(liftLine[i] - rightLine[i])*1000/((i)*(min_W-max_W)/(IMG_H-1)+max_W);  //����������ȱ���

//        if(W_K[i] > MAX_W_K)    MAX_W_K = W_K[i];  //��¼��������ȱ���

//     }
//    for (int i = 0; i < IMG_H - 1; i++)
//    {
//       see_img[i][midline[i]] = 0x00;
//    }
//    //oled_dis_bmp(IMG_H, IMG_W, see_img, image_threshold);

//}

////���㷽��PID
//void direction_PID()
//{
//    float curvature;    //����

//    float L_AB, L_BC, L_AC, K_AB, K_BC, COS_A, A;

//    A_y = IMG_H - 1;
//    A_x = midline[IMG_H - 2];
//    //A_y = IMG_H - 1 - A_y;

//    B_y = IMG_H - ForesightMax+1;
//    B_x = midline[(int)B_y];
//    //B_y = IMG_H - 1- B_y;

//    C_y = IMG_H - 2 * ForesightMax-1;
//    C_x = midline[(int)C_y];
//   // C_y = IMG_H - 1- C_y;

//    for(uint8 i=0;i<IMG_W;i++) //ͼ����ʾǰհ
//    {
//        see_img[(int)(B_y)][i] = 0x00;
//        see_img[(int)(C_y)][i] = 0x00;
//    }

//    K_AB = (B_y - A_y) / (B_x - A_x);       //����AB����
//    K_BC = (C_y - B_y) / (C_x - B_x);       //����BC����

//    //AB �� BC��������ȣ����㹲�ߣ����� = 0
//    if(K_AB == K_BC)
//    {
//        curvature = 0;
//    }
//    else
//    {
//        L_AB = sqrt((A_x - B_x) * (A_x - B_x) + (A_y - B_y) * (A_y - B_y));   // �����߱߳�
//        L_AC = sqrt((A_x - C_x) * (A_x - C_x) + (A_y - C_y) * (A_y - C_y));
//        L_BC = sqrt((B_x - C_x) * (B_x - C_x) + (B_y - C_y) * (B_y - C_y));

//        A = L_AC * L_AC + L_BC * L_BC - L_AB * L_AB;          //���Ҷ���
//        COS_A = A / (2 * L_AC * L_BC);
//        COS_A = sqrt(1 - COS_A * COS_A);      //������
//        curvature = COS_A / (0.5 * L_AB);


//        if (C_x > B_x && B_x > A_x)            //�ж����ʼ���
//        {
//            curvature *= 100;
//        }
//        else if (C_x < B_x && B_x < A_x)
//        {
//            curvature *= -100;
//        }
//        else if (C_x > B_x && A_x > B_x)
//        {
//            curvature *= 100;
//        }
//        else {
//            curvature *= -100;
//        }
//    }

//    if((C_x < B_x && B_x < A_x) || (C_x > B_x && B_x > A_x))
//    {
//        err = 100 * (C_x - A_x) / (2 * ForesightMax);
//    }
//    else
//    {
//        err = 150 * (B_x - A_x) / ((1 * ForesightMax));
//    }

//    dir_out = (float)(0.95 * (((A_x - IMG_W/2) * Y_KP * -0.1) - curvature * Q_KP + Z_gyro * DIR_KD * 0.01 - err * DIR_KP * 0.01))*DIR_DT + dir_out_old*(1.0-DIR_DT);
//   // if(DIS_MODE) dir_out*=0.6;///����ģʽ�·���ϵ����С
//    dir_out_old  = dir_out;

//    if(dir_out<-90)dir_out=-90;
//    if(dir_out>90)dir_out=90;

////    pwm_set_duty(ATOM2_CH1_P33_5,dir_out + DJ_INIT);
//}

//#pragma section all restore
