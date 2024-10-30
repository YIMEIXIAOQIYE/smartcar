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
//int8 TJP = 0;  //条件跑标志

//int8 HD_ERR = 0 ;  //灰度偏差

//#define Q_KP 0.0
//#define DJ_INIT 740  //740
//#define DJ_L 650
//#define DJ_R 830

//#define X 0
//#define Y 1

//#define IMG_H MT9V03X_H/2
//#define IMG_W MT9V03X_W/2
//#define GrayScale 256
//uint8 image_threshold;  //图像阈值

//uint8* p;
//uint8 img[IMG_H][IMG_W];
//uint8 end_img[IMG_H][IMG_W];
//uint8 see_img[IMG_H][IMG_W];

//uint8 YS[8] = {0};   // =1 R  =2 Y  =3 B  =4 P
//uint8 YS_N =0;  //元素计数

////
//int8 CAR_MODE = 0;    //=0等待发车 =1出库   =2 正常跑  =3 入库
//int8 GO_DIR = 1;  //发车方向
//uint16 FC_L=0;   //发车路程积分
//float FC_ANG=0.0; //发车角度积分
////UI参数
//uint8 GB_H = 0;
//uint8 GB_MODE = 0;
//uint32 TIME = 0;

//int16 MAX_Y_GYRO=0;
//int16 MIN_Y_GYRO=0;

////关键点参数
//int8 point[20][2];
////坡道参数
//int8 PO_STEP=0;
//uint16 PO_L=0;
////P环参数
////斑马线参数
//int8 BMX_STEP=0;
//int8 BMX_DIR=0;
//uint16 BMX_L=0;
//uint8 BMX_T=0;
//uint8 BMX_N=2;
////P环参数
//int8 P_STEP=0;
//int8 P_DIR=0;
//uint16 P_L=0;
//int8 P_N=0;
//float P_ANG=0.0;
////圆环参数
//int8 YH_STEP=0;
//int8 YH_DIR=0;
//float YH_ANG=0.0;
//uint16 YH_L=0;
//int8 YH_N=0;
////三岔路口参数
//int8 SC_STEP=0;
//int8 SC_DIR=0;
//uint16 SC_L=0;
//float SC_ANG=0.0;
//int8 SC_N=0;
////十字路口参数
//int8 SZLK_STEP = -1;
//uint16 SZLK_L =0;

//uint16 POWER_V;  //电池电压
////寻找中线
//int midline[IMG_H] = {0};
//int nextLine[IMG_H] = {0};
//int liftLine[IMG_H] = {0};
//int rightLine[IMG_H] = {0};

//float err = 0.0;
//float A_x, A_y, B_x, B_y, C_x, C_y;     //定义A,B,C三个点的xy坐标

//int min_W = 71;  //赛道最近点像素宽度
//int max_W = 22;  //赛道最远点像素宽度
//uint16 W_K[IMG_H]={1000}; //赛道每行宽度比例*1000
//float MAX_W_K = 0;  //赛道最大宽度比例

//float dir_out=0.0,dir_out_old=0.0; //舵机PWM输出


////void PID();
//void findMidline();
//void direction_PID();
////void uart_to_pc();

//void img_vary(void);  //图像处理函数
//extern void dis_oled(void); //刷新图像
//extern void dis_num(uint8 x,uint8 y,int16 A,int16 B);
//void img_change(int8 X1,int8 Y1,int8 X2,int8 Y2,int8 H0,int8 H1);
//void point_find(void); //找关键点
//void Binarization(void);  //取图并二值化
//extern void UART_GO(void);


//int16 farthestEffective;     //左右赛道最远有效行
//int16 a_x, a_y, b_x, b_y, c_x, c_y, //左侧从下到上三个点
//      d_x, d_y, e_x, e_y, f_x, f_y; //右侧从下到上三个点

//int rightWidth[64] = {0};       //右赛道宽度直方图数组
//int liftWidth[64] = {0};        //左赛道宽度直方图数组

//uint8 width;   //赛道白色宽度
//int widthArray[32];     //赛道白色宽度数组

//int m, n;

//uint8 TU_N=0,TU_F=0;  //图像帧率


//uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
//{
//    uint16 width = col;
//    uint16 height = row;
//    int pixelCount[GrayScale];
//    float pixelPro[GrayScale];
//    int i, j, pixelSum = width * height;
//    uint8 threshold = 0;
//    uint8* data = image;  //指向像素数据的指针
//    for (i = 0; i < GrayScale; i++)
//    {
//        pixelCount[i] = 0;
//        pixelPro[i] = 0;
//    }

//    //统计灰度级中每个像素在整幅图像中的个数
//    for (i = 0; i < height; i++)
//    {
//        for (j = 0; j < width; j++)
//        {
//            pixelCount[(int)data[i * width + j]]++;  //将像素值作为计数数组的下标
//        }
//    }

//    //计算每个像素在整幅图像中的比例
//    float maxPro = 0.0;
//    for (i = 0; i < GrayScale; i++)
//    {
//        pixelPro[i] = (float)pixelCount[i] / pixelSum;
//        if (pixelPro[i] > maxPro)
//        {
//            maxPro = pixelPro[i];
//        }
//    }

//    //遍历灰度级[0,255]
//    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
//    for (i = 0; i < GrayScale; i++)     // i作为阈值
//    {
//        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
//        for (j = 0; j < GrayScale; j++)
//        {
//            if (j <= i)   //背景部分
//            {
//                w0 += pixelPro[j];
//                u0tmp += j * pixelPro[j];
//            }
//            else   //前景部分
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


//    //////////////////////////////////////////////////////////准备找点工作///////////////////////////////////////////////////////

//    //求关键点0-4
//    l=0;
//    r = IMG_W - 1;

//    for(int i=0;i<IMG_W-1;i++)
//    {
//        if(img[IMG_H - 1][i] == 0xff) //白点
//        {
//            l = i;
//            break;
//        }
//    }
//    for(int i=IMG_W-1;i>1;i--)
//    {
//        if(img[IMG_H - 1][i] == 0xff) //白点
//        {
//            r = i;
//            break;
//        }
//    }
//    point[2][X] =  (l+r)/2;  //2点坐标X
//    point[2][Y] =  IMG_H - 1;  //2点坐标Y

//    point[1][X] =  l;  //1点坐标X
//    point[1][Y] =  IMG_H - 1;  //1点坐标Y

//    point[3][X] =  r;  //3点坐标X
//    point[3][Y] =  IMG_H - 1;  //3点坐标Y

//    point[0][X] =  0;  //0点坐标X
//    point[0][Y] =  IMG_H - 1;  //0点坐标Y

//    point[4][X] =  IMG_W - 1;  //4点坐标X
//    point[4][Y] =  IMG_H - 1;  //4点坐标Y

//    //找关键点 5和9
//    l=2;
//    for(i=IMG_H-1;i>=2;i--)  //左边找
//    {
//        if(img[i-1][1] - img[i][1] ==0XFF || i==2)  //找到黑变白
//        {
//            l = i;
//            break;
//        }
//    }
//    r=2;
//    for(i=IMG_H-1;i>=2;i--)  //右边找
//    {
//        if(img[i-1][IMG_W-1] - img[i][IMG_W-1] == 0XFF || i==2)  //找到黑变白
//        {
//            r = i;
//            break;
//        }
//    }

//    point[5][X]=1;  //5点赋值
//    point[5][Y]=l;
//    point[9][X]=IMG_W-1;  //9点赋值
//    point[9][Y]=r;

//    //找关键点10.13
//    l=1;
//    for(i=point[5][Y]-1;i>=1;i--)
//    {
//        if(img[i-1][1]!=img[i][1] || i==1)  //找到黑变白
//        {
//            l = i;
//            break;
//        }
//    }
//    r=1;
//   for(i=point[9][Y]-1;i>=1;i--)  //右边找
//   {
//       if(img[i-1][IMG_W-1]!= img[i][IMG_W-1] || i==1)  //找到黑变白
//       {
//           r = i;
//           break;
//       }
//   }

//   point[10][X]=1;  //10点赋值
//   point[10][Y]=l;
//   point[13][X]=IMG_W-1;  //13点赋值
//   point[13][Y]=r;


//    //求关键点6.7.8

//    x = IMG_H - 1;  //标志位清0
//    l = 0;

//    if(point[1][X] == 0)  //左下无黑
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
//    else  //左下有黑
//    {
//        i= IMG_H -2;
//        j=point[1][X];
//    }


//    for(;i>1 ; i--)  //自下向上找
//    {
//        for(;j<IMG_W - 1;j++)
//        {
//            if(img[i][j]==0xff)  //本行向右找到白
//            {
//                if(img[i-1][j-1]==0x00) //上行有黑,则继续向上找
//                {
//                    j-=1;
//                }
//                else  //上行无黑，说明找到尖角
//                {
//                    x=i;
//                    l = j-1;
//                }
//                break;
//            }
//        }
//        if(x != IMG_H - 1) break;
//    }
//    point[6][X]=j-1;  //6点赋值
//    point[6][Y]=i;

//    y = IMG_H - 1;  //标志位清0
//    r = IMG_W - 1;

//    if(point[3][X] == IMG_W-1)  //右下无黑
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
//    else  //右下有黑
//    {
//        i= IMG_H -2;
//        j =point[3][X];
//    }


//    for(;i>1 ; i--)  //自下向上找
//    {
//        for(; j >1; j--)
//        {
//            if(img[i][j]==0xff)  //本行向左找到白
//            {
//                if(img[i-1][j+1]==0x00) //上行有黑,则继续向上找
//                {
//                    j+=1;

//                }
//                else  //上行无黑，说明找到尖角
//                {
//                    y=i;
//                    r = j+1;
//                }
//                break;
//            }
//        }
//        if(y != IMG_H - 1) break;
//    }
//    point[8][X]=j+1;  //8点赋值
//    point[8][Y]=i;


//    if(point[6][X] < point[8][X]) //正常情况
//    {
//        if( point[6][Y] <  point[8][Y])  //左高右低
//        {
//            point[7][Y] = point[8][Y];
//            l = IMG_W/2 + (IMG_W/2 - point[8][X]);  //默认位置
//            for(i=point[8][X]-3 ; i>1 ; i--)
//            {
//                if(img[point[7][Y]][i]==0x00)  //向左找黑
//                {
//                    l = (i+point[8][X])/2;
//                    break;
//                }
//            }
//        }
//        else       //左低右高
//        {
//            point[7][Y] = point[6][Y];
//            l = IMG_W/2 + (IMG_W/2 - point[6][X]);  //默认位置
//            for(i=point[6][X]+3 ; i<IMG_W-1 ; i++)
//            {
//                if(img[point[7][Y]][i]==0x00)  //向右找黑
//                {
//                    l = (i+point[6][X])/2;
//                    break;
//                }
//            }
//        }
//        point[7][X]=l;  //7点赋值
//    }
//    else
//    {
//        point[7][X] = (point[6][X] +point[8][X])/2;  //特殊情况，7点取6点和8点中点
//        point[7][Y] = (point[6][Y] +point[8][Y])/2;
//    }



//   //找关键点11.12
//    l=1;
//    for(i=point[6][Y];i>1;i--)  //左边找
//    {
//      if(img[i][point[6][X]] - img[i-1][point[6][X]] == 0xff)  //找到白变黑
//      {
//          l = i;
//          break;
//      }
//    }
//    r=1;
//    for(i=point[8][Y];i>1;i--)  //右边找
//    {
//     if(img[i][point[8][X]] - img[i-1][point[8][X]] == 0xff)  //找到白变黑
//     {
//         r = i;
//         break;
//     }
//    }

//    point[11][X]=point[6][X];  //11点赋值
//    point[11][Y]=l;
//    point[12][X]=point[8][X];  //12点赋值
//    point[12][Y]=r;

//    //找关键点14

//    if(point[7][X] == point[2][X])  //一条直线
//    {
//        l= IMG_H-1;
//        r = point[2][X];

//        for(i=IMG_H-1;i>0;i--)
//        {
//            j=r;
//            if(img[i][j] == 0x00 || i==1) //找黑
//            {
//                l = i;
//                r = j;
//                break;
//            }
//        }
//    }
//    else
//    {
//        k = (float)(point[7][Y] - point[2][Y])/(point[7][X] - point[2][X]);   //求 7.2斜率
//        n = (float)(point[2][Y] -( k * point[2][X]));

//        l= IMG_H-1;
//        r = point[2][X];

//        for(i=IMG_H-1;i>0;i--)
//        {
//            j=(i-n)/k;
//            if(img[i][j] == 0x00 || i==1) //找黑
//            {
//                l = i;
//                r = j;
//                break;
//            }
//        }
//    }

//    point[14][X]=r;  //14点赋值
//    point[14][Y]=l;

////////////////////////////////////////////////////////////准备工作结束///////////////////////////////////////////////////////
//}


//void Binarization(void)  //取图并二值化
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
//    //求阈值
//    image_threshold = otsuThreshold(p, IMG_H, IMG_W) + HD_ERR;

//   // if(CAR_MODE==0) //看图二值化
//    //{
//        //二值化
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
//    else //正常跑二值化
//    {
//        //二值化
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

//    //////////////////////////////////////////////////////////准备找点工作///////////////////////////////////////////////////////
//    point_find();
////////////////////////////////////////////////////////////准备工作结束///////////////////////////////////////////////////////
///////////////////////////////////////////////////////坡道识别///////////////////////////////////////////////////////////////
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
//            if(CAR_MODE ==3 && YH_STEP <=0 && BMX_STEP <= 0 && P_STEP <= 0&& SC_STEP <=0 && SZLK_STEP <=0  &&  Y_gyro<-2000.0 && PO_L>10000 && i<IMG_H/2)  //判断坡道阈值
//            {
//                PO_STEP=1;
//                PO_L=0;
//                gpio_set_level( B11, 1);
//            }
//        }break;
//        case 1:
//        {
//            if((PO_L > 4000 &&  Y_gyro <-2000.0) || PO_L > 12000)  //判断坡道阈值
//            {
//                PO_STEP=2;
//                PO_L=0;
//            }
//        }break;
//        case 2:
//        {
//            if(PO_L > 5000)  //判断坡道阈值
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

//    ////////////////////////////////////////////////////判断斑马线开始//////////////////////////////////////////////////////////
//    switch(BMX_STEP)
//    {
//        case 0:
//        {
//            BMX_T=0;
//            for(i=IMG_H-2*ForesightMax+3;i>IMG_H-2*ForesightMax-2;i--)  //统计斑马线跳变点
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
//                if(point[6][Y]<point[8][Y])  //判断车库方向
//                {
//                    BMX_DIR = 1;  //右侧车库
//                }
//                else
//                {
//                    BMX_DIR = 0;  //左侧车库
//                }

//                if(CAR_MODE==3) BMX_N--;  //正常跑阶段



//                if(BMX_N) //不是最后入库
//                {
//                    gpio_set_level( B11, 1);
//                    BMX_STEP = 1;
//                    BMX_L =0;
//                }
//                else //最后入库
//                {
//                    gpio_set_level( B11, 1);
//                    FC_ANG = 0.0;  //角度积分
//                    FC_L = 0;
//                    CAR_MODE = 4;   //进入入库阶段
//                }
//            }
//        }break;
//        case 1:  //补线
//        {

//            if(BMX_L>4000)
//            {
//                BMX_STEP = 0;
//                gpio_set_level( B11, 0);
//                break;
//            }

//            for(i=IMG_H-ForesightMax*2-1;i<IMG_H;i++)  //斑马线涂白
//            {
//                for(j=IMG_W/2-i*3/4;j<IMG_W/2+i*3/4;j++)
//                {
//                    end_img[i][j] = 0xff;
//                    see_img[i][j] = 0xff;
//                }
//            }

//            //补左线
//            img_change(point[1][X],point[1][Y],point[8][X]-max_W,point[8][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//            //补右线
//            img_change(point[3][X]-1,point[3][Y],point[6][X]+max_W,point[6][Y],IMG_H-ForesightMax*2-1,IMG_H-1);

//           /* if(BMX_N) //不是最后入库
//            {
//                if(BMX_DIR == 0) //补左侧线
//                {
//                    //补左线
//                    img_change(point[1][X],point[1][Y],point[8][X]-max_W,point[8][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//                }
//                else //补右侧线
//                {
//                    //补右线
//                    img_change(point[3][X]-1,point[3][Y],point[6][X]+max_W,point[6][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//                }
//            }
//            else  //当前斑马线入库
//            {

//            }*/
//        }break;

//    }

//////////////////////////////////////////////////////判断斑马线结束//////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////识别十字路口并补线///////////////////////////////////////////////////
//    switch(SZLK_STEP)
//    {
//        case 0:
//        {      //6.8点高度差小于10              6.8高度都在前瞻范围内                                                   最远点高度小于5      左侧或右侧5.6点7.8点差值小于7                                    有赛道宽度大于200%
//            if( CAR_MODE ==3 &&  PO_STEP <=0 && BMX_STEP <= 0 && YH_STEP <= 0 && P_STEP<=0 && SC_STEP<=0 && abs(point[6][Y]-point[8][Y])<10 && point[6][Y]>IMG_H-2*ForesightMax && point[8][Y]>IMG_H-2*ForesightMax && point[14][Y] < 5 && (abs(point[5][Y]-point[6][Y])<7 || abs(point[8][Y]-point[9][Y])<7 ) && MAX_W_K>2000)
//            {
//              SZLK_STEP =1;
//              SZLK_L = 0;
//              gpio_set_level( B11, 1);
//            }
//        }break;
//        case 1:  //进入路口第一阶段
//        {
//            if((SZLK_L>5000) || (point[1][X] == 0 || point[3][X] == IMG_W-1))  //判读那第一阶段结束
//            {
//                SZLK_STEP = 2;
//                SZLK_L = 0;
//                break;
//            }
//            //补左线
//            img_change(point[1][X],point[1][Y],point[6][X],point[6][Y],IMG_H-ForesightMax*2-1,IMG_H-1);

//            //补右线
//            img_change(point[3][X],point[3][Y],point[8][X],point[8][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//        }break;
//        case 2:
//        {
//            if(SZLK_L>5000)  //判读那第2阶段结束
//            {
//                SZLK_STEP = 0;
//                SZLK_L = 0;
//                gpio_set_level(B11, 0);
//                break;
//            }
//            //补左线
//            img_change(1,IMG_H-1,IMG_W/2-11,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//            //补右线
//            img_change(IMG_W-2,IMG_H-1,IMG_W/2+11,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//        }break;
//    }
///////////////////////////////////////////////////////////识别十字路口结束///////////////////////////////////////////////////

///////////////////////////////////////////////////////////识别三岔路口开始///////////////////////////////////////////////////
//    switch(SC_STEP)
//    {
//        case 0:  //识别三岔路口
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
//            //补线
//            if(SC_DIR == 0)  //向左走
//            {
//                if(point[8][Y]<10 || SC_L>6000 || fabs(SC_ANG) >100.0) //判断终止条件
//                {
//                    SC_STEP =2;
//                    SC_L=0;
//                    break;
//                }
//                //补右线
//                img_change(IMG_W-2,IMG_H-1,point[14][X],point[14][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//            else //向右走
//            {
//                if(point[6][Y]<10 || SC_L>6000 || fabs(SC_ANG) >100.0) //判断终止条件
//                {
//                    SC_STEP =2;
//                    SC_L=0;
//                    break;
//                }
//                //补左线
//                img_change(1,IMG_H-1,point[14][X],point[14][Y],IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//        }break;
//        case 2:
//        {
//            if(SC_DIR==0) ////向左走
//            {
//                if(point[3][X]<IMG_W-2 || SC_L>6000 || fabs(SC_ANG) >120.0)  //判断终止条件
//                {
//                    SC_STEP =3;
//                    SC_L=0;
//                    break;
//                }
//                //补右线
//                img_change(IMG_W-2,IMG_H-1,10,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//            else //向右走
//            {
//                if(point[1][X]>1 || SC_L>6000 || fabs(SC_ANG) >120.0) //判断终止条件
//               {
//                   SC_STEP =3;
//                   SC_L=0;
//                   break;
//               }
//                //补左线
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
//    /////////////////////////////////////////////////////////识别三岔路口结束///////////////////////////////////////////////////

//    /////////////////////////////////////////////////////////识别圆环开始///////////////////////////////////////////////////////

//    switch(YH_STEP)
//    {
//        case 0:  //等待识别圆环
//        {
//            if( YH_L > 10000 && CAR_MODE ==3 &&  PO_STEP <=0 && BMX_STEP <= 0 && P_STEP <= 0&& SC_STEP <=0 && SZLK_STEP <=0  &&(point[6][Y]<5 || point[8][Y]<5)&& abs(point[6][Y]-point[8][Y]) > IMG_H-2*ForesightMax &&  point[14][Y] < 5 && point[6][X]<point[8][X])
//            {
//                if(point[6][Y]<point[8][Y]) //右环
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
//                else //左环
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
//        case 1:  //开始圆环第一阶段补线
//        {
//            if(YH_DIR == 0)  //左环
//            {
//                if(point[6][Y]<IMG_H-2*ForesightMax && YH_L > 2500) //判断终止条件
//                {
//                    YH_STEP =2;
//                    YH_L=0;
//                   // gpio_set_level( B11, 0);
//                    break;
//                }
//                //补线
//                i = point[11][Y]-2;
//                j = point[11][X];
//                y = i;
//                for(;i>1 ; i--)  //自下向上找
//                    {
//                        for(;j<IMG_W - 1;j++)
//                        {
//                            if(img[i][j]==0xff)  //本行向右找到白
//                            {
//                                if(img[i-1][j-2]==0x00) //上行有黑,则继续向上找
//                                {
//                                    j-=2;
//                                }
//                                else  //上行无黑，说明找到尖角
//                                {
//                                    y=i;
//                                    l = j-1;
//                                }
//                                break;
//                            }
//                        }
//                        if(y != i) break;
//                    }
//                x=j-1; //得到切点坐标
//                y=i;
//                img_change(x,y,point[6][X],point[6][Y],y,point[6][Y]);
//            }
//            else //右环
//            {
//               if(point[8][Y]<IMG_H-2*ForesightMax && YH_L > 2500) //判断终止条件
//               {
//                   YH_STEP =2;
//                   YH_L=0;
//                  // gpio_set_level( B11, 0);
//                   break;
//               }
//                //补线
//                i = point[12][Y]-2;
//                j = point[12][X];
//                y = i;
//                for(;i>1 ; i--)  //自下向上找
//                {
//                    for(; j >1; j--)
//                    {
//                        if(img[i][j]==0xff)  //本行向左找到白
//                        {
//                            if(img[i-1][j+2]==0x00) //上行有黑,则继续向上找
//                            {
//                                j+=2;
//                            }
//                            else  //上行无黑，说明找到尖角
//                            {
//                                y=i;
//                                r = j+1;
//                            }
//                            break;
//                        }
//                    }
//                    if(y != i ) break;
//                }
//                x=j+1; //得到切点坐标
//                y=i;
//                img_change(x,y,point[8][X],point[8][Y],y,point[8][Y]);
//            }
//        }break;
//        case 2: //进环二阶段补线
//            {
//                if(YH_DIR == 0)  //左环
//                {
//                    if(point[1][X]>5 && YH_L > 1500)
//                    {
//                       YH_STEP =3;
//                       YH_L=0;
//                       gpio_set_level( B11, 0);
//                       break;
//                    }
//                    //补线
//                    img_change(5,IMG_H-1,IMG_W/2-max_W/2,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//                }
//                else //右环
//                {
//                    if(point[3][X]<IMG_W-5 && YH_L > 1500)
//                    {
//                       YH_STEP =3;
//                       YH_L=0;
//                       gpio_set_level( B11, 0);
//                       break;
//                    }
//                    //补线
//                    img_change(IMG_W-5,IMG_H-1,IMG_W/2+max_W/2,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//                }
//            }break;
//        case 3:
//        {
//            if(point[8][X] < point[6][X] && point[14][Y] > 2) //说明是P路口
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
//        case 4: //进环第三阶段补线
//        {
//            if(YH_L > 25000 && fabs(YH_ANG)>180.0)
//            {
//                YH_STEP = 5;
//                YH_L=0;
//            }
//            if(YH_DIR==0) //左环
//            {
//                //补线
//                img_change(IMG_W-2,IMG_H-1,IMG_W/2-max_W,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//            }
//            else //右环
//            {
//                //补线
//                img_change(1,IMG_H-1,IMG_W/2+max_W,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//        }break;
//        case 5:  //环内正常跑
//        {
//            if(YH_DIR==0) //左环
//            {
//                if((point[8][X]>IMG_W/2 || fabs(YH_ANG)>200.0) && YH_L>3000)
//                {
//                    YH_STEP = 6;
//                    YH_L =0;
//                }
//                //补线
//                img_change(IMG_W-1,IMG_H-1,IMG_W/2-max_W,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//            }
//            else //右环
//            {
//                if((point[6][X]<IMG_W/2 ||  fabs(YH_ANG)>200.0) && YH_L>3000)
//                {
//                    YH_STEP = 6;
//                    YH_L =0;
//                }
//                //补线
//                img_change(1,IMG_H-1,IMG_W/2+max_W,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//            }
//        }break;
//        case 6:  //出环一阶段补线
//        {
//          if(YH_DIR==0) //左环
//          {
//              if((point[8][X]<10 || fabs(YH_ANG)>220.0) && YH_L>2000)
//              {
//                  gpio_set_level( B11, 1);
//                  YH_STEP = 7;
//                  YH_L =0;
//              }
//              //补线
//              img_change(IMG_W-10,IMG_H-1,1,10,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//          else //右环
//          {
//               if((point[6][X]>IMG_W-10  || fabs(YH_ANG)>220.0) && YH_L>2000)
//                {
//                   gpio_set_level( B11, 1);
//                    YH_STEP = 7;
//                    YH_L =0;
//                }
//              //补线
//              img_change(10,IMG_H-1,IMG_W-2,10,IMG_H-ForesightMax*2-1,IMG_H-1);
//          }
//        }break;
//        case 7: //出环二阶段补线
//        {
//          if(YH_DIR==0) //左环
//          {
//              if(((point[9][Y]>IMG_H-8 || point[9][Y]<5 ) && YH_L>5000)  || fabs(YH_ANG)>330.0)
//              {
//                  YH_STEP = 8;
//                  YH_L =0;
//              }
//              //补线
//              img_change(IMG_W-10,IMG_H-1,1,10,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//          else //右环
//          {
//              if(((point[5][Y]>IMG_H-8 || point[5][Y]<5) && YH_L>5000)  || fabs(YH_ANG)>330.0)
//             {
//                YH_STEP = 8;
//                YH_L =0;
//             }
//              //补线
//              img_change(10,IMG_H-1,IMG_W-2,10,IMG_H-ForesightMax*2-1,IMG_H-1);
//          }
//        }break;
//        case 8://出环第三阶段补线
//        {
//          if(YH_DIR==0) //左环
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
//              //补线
//              img_change(1,IMG_H-1,point[8][X]-max_W/2,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//          else //右环
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
//              //补线
//              img_change(IMG_W-2,IMG_H-1,point[6][X]+max_W/2,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//        }break;
//        case 9:
//        {
//              if(YH_DIR==0) //左环
//              {
//                  if(point[1][X]>0 && YH_L>2000  || fabs(YH_ANG)>330.0)
//                   {

//                      YH_STEP = 0;
//                      SC_L=0;
//                      YH_L =10000;
//                   }
//                  //补线
//                  img_change(1,IMG_H-1,point[6][X]+max_W/2,point[6][Y],IMG_H-ForesightMax*2-1,IMG_H-1);

//              }
//              else //右环
//              {
//                  if(point[3][X]<IMG_W-1 && YH_L>2000  || fabs(YH_ANG)>330.0)
//                 {
//                    YH_STEP = 0;
//                    SC_L=0;
//                    YH_L =10000;
//                 }
//                  //补线
//                  img_change(IMG_W-2,IMG_H-1,point[8][X]-max_W/2,point[8][Y],IMG_H-ForesightMax*2-1,IMG_H-1);

//              }
//        }break;

//    }

//    /////////////////////////////////////圆环处理结束//////////////////////////////////////////////////

//    ///////////////////////////////////P路口处理 /////////////////////////////////////////////////////////////////////////////////////////////////
//    switch(P_STEP)
//    {
//        case 0:break; //等待入P
//        case 1:  //等待识别出P
//        {
//          if(P_DIR==0) //左P
//          {
//              if(point[8][X]>IMG_W/2+8 && P_L > 20000 && fabs(P_ANG)>230.0)
//              {
//                  gpio_set_level( B11, 1);
//                  P_STEP = 2;
//                  P_L=0;
//              }
//          }
//          else //右P
//          {
//              if(point[6][X]<IMG_W/2-8 && P_L > 20000 && fabs(P_ANG)>230.0)
//              {
//                  gpio_set_level( B11, 1);
//                  P_STEP = 2;
//                  P_L=0;
//              }
//          }
//        }break;
//        case 2: //出P补线
//        {
//           if(P_L > 10000)  //判断终止条件
//           {
//              if(P_DIR==0)  //,判断是否P接圆环，左P，看右8点Y
//              {
//                  for(i=IMG_H-1;i>1;i--)
//                  {
//                      if(img[i][IMG_W-1] - img[i-1][IMG_W-1]== 0xFF || i==2) break;
//                  }

//                  if(point[6][Y]<15 && i>5 && TJP==0)  //左P结束接圆环
//                  {
//                      YH_STEP = 2;
//                        YH_DIR = 1;
//                        YH_L=0;
//                        P_STEP =0;
//                        P_L=0;
//                        SC_L=0;

//                  }
//                  else  //左P结束
//                  {
//                        gpio_set_level( B11, 0);
//                        P_STEP =0;
//                        YH_L=0;
//                        SC_L=0;
//                        P_L=0;
//                        SC_L=0;
//                  }

//              }
//              else //右P，看左点Y
//              {
//                for(i=IMG_H-1;i>1;i--)
//                {
//                    if(img[i][0] - img[i-1][0]== 0xFF || i==2) break;
//                }
//                if((point[8][Y]<15 && i>5) || TJP==1)  //右P结束接左圆环
//                {
//                    YH_STEP = 2;
//                    YH_DIR = 0;
//                    YH_L=0;
//                    P_STEP =0;
//                    P_L=0;
//                    SC_L=0;
//                }
//                else  //右P结束
//                {
//                    gpio_set_level( B11, 0);
//                    P_STEP =0;
//                    P_L=0;
//                    SC_L=0;
//                }
//              }

//           }

//          if(P_DIR==0) //左P
//          {
//              //找补线关键点
//              if(point[8][X] == point[3][X])  //一条直线
//              {
//                  l= point[8][Y]-1;
//                  r = point[3][X];

//                  for(i=point[8][Y]-1;i>0;i--)
//                  {
//                      j=r;
//                      if(img[i][j] == 0x00 || i==1) //找黑
//                      {
//                          l = i;
//                          r = j;
//                          break;
//                      }
//                  }
//              }
//              else
//              {
//                  k = (float)(point[8][Y] - point[3][Y])/(point[8][X] - point[3][X]);   //求 7.2斜率
//                  n = (float)(point[3][Y] -( k * point[3][X]));

//                  l= point[8][Y]-1;
//                  r = point[3][X];

//                  for(i=point[8][Y]-1;i>0;i--)
//                  {
//                      j=(i-n)/k;
//                      if(img[i][j] == 0x00 || i==1) //找黑
//                      {
//                          l = i;
//                          r = j;
//                          break;
//                      }
//                  }
//              }

//              x=r;  //14点赋值
//              y=l;

//              img_change(1,IMG_H-1,IMG_W-2,1,IMG_H-ForesightMax*2-1,IMG_H-1);

//          }
//          else //右P
//          {
//              //找补线关键点
//            if(point[6][X] == point[1][X])  //一条直线
//            {
//                l= point[6][Y]-1;
//                r = point[1][X];

//                for(i=point[6][Y]-1;i>0;i--)
//                {
//                    j=r;
//                    if(img[i][j] == 0x00 || i==1) //找黑
//                    {
//                        l = i;
//                        r = j;
//                        break;
//                    }
//                }
//            }
//            else
//            {
//                k = (float)(point[6][Y] - point[1][Y])/(point[6][X] - point[1][X]);   //求 7.2斜率
//                n = (float)(point[1][Y] -( k * point[1][X]));

//                l= point[6][Y]+1;
//                r = point[1][X];

//                for(i=point[6][Y]-1;i>0;i--)
//                {
//                    j=(i-n)/k;
//                    if(img[i][j] == 0x00 || i==1) //找黑
//                    {
//                        l = i;
//                        r = j;
//                        break;
//                    }
//                }
//            }

//            x=r;  //14点赋值
//            y=l;

//            img_change(IMG_W-2,IMG_H-1,1,1,IMG_H-ForesightMax*2-1,IMG_H-1);
//          }
//        }break;
//    }
//    ////////////////////////////////////////P路口结束///////////////////////////////////////////////////////////////////////////////////////////////

//}





//void img_change(int8 X1,int8 Y1,int8 X2,int8 Y2,int8 H0,int8 H1)  //给两点，在范围内补线
//{
//    uint8 i,j;
//    float k,n;

//    if(H0>H1) //确定行高低
//    {
//        i=H0;
//        H0=H1;
//        H1=i;
//    }

//    if(X1<1)    X1=1; //坐标限幅
//    if(X2<1)    X2=1;
//    if(Y1<1)    Y1=1;
//    if(Y2<1)    Y2=1;
//    if(X1>IMG_W-2)    X1=IMG_W-2;
//    if(X2>IMG_W-2)    X2=IMG_W-2;
//    if(Y1>IMG_H-1)    Y1=IMG_H-1;
//    if(Y1>IMG_H-1)    Y2=IMG_H-1;

//    if(X1 == X2)  //补一条垂直直线
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
//    else  //补斜线
//    {
//        k = (float)(Y2 - Y1)/(X2 - X1);   //求 6.1斜率
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


////寻找中线
//void findMidline()
//{
//    int8 l = 0 ,r = IMG_W - 1;

//    //中线数组赋初值
//    for(int i = 0; i < IMG_H; i++)
//    {
//        midline[i] = IMG_W / 2;
//        liftLine[i] = 0;
//        rightLine[i] = IMG_W - 1;
//        nextLine[i] = IMG_W / 2;
//    }

//    midline[IMG_H - 1] = point[2][X];       //求取并记录中点
//    nextLine[IMG_H - 2] = point[2][X];       //迭代

//    W_K[IMG_H - 1] = abs(point[3][X] - point[1][X])*1000/((IMG_H - 1)*(min_W-max_W)/(IMG_H - 1)+max_W);
//    MAX_W_K = W_K[IMG_H - 1];  //开始计算赛道宽度比例系数

//    for(int i = IMG_H - 2; i > 0; i--)
//    {
//        liftLine[i] = 0;
//        rightLine[i] = IMG_W - 1;
//        //中线限幅
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


//        nextLine[i - 1] = (liftLine[i] + rightLine[i]) / 2; //计算中线
//        midline[i] = (liftLine[i] + rightLine[i]) / 2;

//        W_K[i] = abs(liftLine[i] - rightLine[i])*1000/((i)*(min_W-max_W)/(IMG_H-1)+max_W);  //计算赛道宽度比例

//        if(W_K[i] > MAX_W_K)    MAX_W_K = W_K[i];  //记录赛道最大宽度比例

//     }
//    for (int i = 0; i < IMG_H - 1; i++)
//    {
//       see_img[i][midline[i]] = 0x00;
//    }
//    //oled_dis_bmp(IMG_H, IMG_W, see_img, image_threshold);

//}

////计算方向PID
//void direction_PID()
//{
//    float curvature;    //曲率

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

//    for(uint8 i=0;i<IMG_W;i++) //图像显示前瞻
//    {
//        see_img[(int)(B_y)][i] = 0x00;
//        see_img[(int)(C_y)][i] = 0x00;
//    }

//    K_AB = (B_y - A_y) / (B_x - A_x);       //计算AB曲率
//    K_BC = (C_y - B_y) / (C_x - B_x);       //计算BC曲率

//    //AB 和 BC的曲率相等，三点共线，曲率 = 0
//    if(K_AB == K_BC)
//    {
//        curvature = 0;
//    }
//    else
//    {
//        L_AB = sqrt((A_x - B_x) * (A_x - B_x) + (A_y - B_y) * (A_y - B_y));   // 求三边边长
//        L_AC = sqrt((A_x - C_x) * (A_x - C_x) + (A_y - C_y) * (A_y - C_y));
//        L_BC = sqrt((B_x - C_x) * (B_x - C_x) + (B_y - C_y) * (B_y - C_y));

//        A = L_AC * L_AC + L_BC * L_BC - L_AB * L_AB;          //余弦定律
//        COS_A = A / (2 * L_AC * L_BC);
//        COS_A = sqrt(1 - COS_A * COS_A);      //求正弦
//        curvature = COS_A / (0.5 * L_AB);


//        if (C_x > B_x && B_x > A_x)            //判断曲率极性
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
//   // if(DIS_MODE) dir_out*=0.6;///手推模式下方向系数减小
//    dir_out_old  = dir_out;

//    if(dir_out<-90)dir_out=-90;
//    if(dir_out>90)dir_out=90;

////    pwm_set_duty(ATOM2_CH1_P33_5,dir_out + DJ_INIT);
//}

//#pragma section all restore
