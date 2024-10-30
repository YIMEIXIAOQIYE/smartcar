#include "zf_common_headfile.h"
#include "math.h"
#define Row    90               //图像行数
#define Col    188              //图像列数
#define GrayScale 256
#define CONTROLL_H_MAX  100
#define CONTROLL_H_MIN  60
int Pixle[MT9V03X_H][MT9V03X_W];
int midline[MT9V03X_H] = {0};
int nextline[MT9V03X_H] = {0};
int leftline[MT9V03X_H] = {0};
int rightline[MT9V03X_H] = {0};
uint8 image_yuanshi[MT9V03X_H][MT9V03X_W];      //原始图像
int image_01[MT9V03X_H][MT9V03X_W];           //二值化图像
#define CONTROLL_W_MAX  90
#define CONTROLL_W_MIN  20
//uint8 GetOSTU()
//{ 
//  int16 i,j; 
//  uint32 Amount = 0; 
//  uint32 PixelBack = 0; 
//  uint32 PixelIntegralBack = 0; 
//  uint32 PixelIntegral = 0; 
//  int32 PixelIntegralFore = 0; 
//  int32 PixelFore = 0; 
//  double OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差; 
//  int16 MinValue, MaxValue; 
//  uint8 Threshold = 0;
//  uint8 HistoGram[256];              // 
//	uint8 tmImage[MT9V03X_H][MT9V03X_W];
// 
//  for (j = 0; j < 256; j++)  HistoGram[j] = 0; //初始化灰度直方图 
//  
//  for (j = 0; j < MT9V03X_H; j++) 
//  { 
//    for (i = 0; i < MT9V03X_W; i++) 
//    { 
//      HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
//    } 
//  } 
//  
//  for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //获取最小灰度的值
//  for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //获取最大灰度的值
//      
//  if (MaxValue == MinValue)     return MaxValue;         // 图像中只有一个颜色    
//  if (MinValue + 1 == MaxValue)  return MinValue;        // 图像中只有二个颜色
//    
//  for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  像素总数
//    
//  PixelIntegral = 0;
//  for (j = MinValue; j <= MaxValue; j++)
//  {
//    PixelIntegral += HistoGram[j] * j;//灰度值总数
//  }
//  SigmaB = -1;
//  for (j = MinValue; j < MaxValue; j++)
//  {
//    PixelBack = PixelBack + HistoGram[j];   //前景像素点数
//    PixelFore = Amount - PixelBack;         //背景像素点数
//    OmegaBack = (double)PixelBack / Amount;//前景像素百分比
//    OmegaFore = (double)PixelFore / Amount;//背景像素百分比
//    PixelIntegralBack += HistoGram[j] * j;  //前景灰度值
//    PixelIntegralFore = PixelIntegral - PixelIntegralBack;//背景灰度值
//    MicroBack = (double)PixelIntegralBack / PixelBack;   //前景灰度百分比
//    MicroFore = (double)PixelIntegralFore / PixelFore;   //背景灰度百分比
//    Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//计算类间方差
//    if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
//    {
//      SigmaB = Sigma;
//      Threshold = j;
//    }
//  }
//  return Threshold;                        //返回最佳阈值;
//}
//uint8 Threshold_Deal(uint8* image, uint16 x, uint16 y )
//{
//      #define GrayScale 256
//			uint32 pixel_threshold;
//      uint16 width = x;
//      uint16 height = y;
//      int pixelCount[GrayScale];
//      float pixelPro[GrayScale];
//      int i, j;
//      int pixelSum = width * height;
//      uint8 threshold = 0;
//      uint8* data = image;  //指向像素数据的指针
//      for (i = 0; i < GrayScale; i++)
//      {
//        pixelCount[i] = 0;
//        pixelPro[i] = 0;
//      }

//      uint32 gray_sum = 0;
//      //统计灰度级中每个像素在整幅图像中的个数
//      for (i = 0; i < height; i += 1)
//      {
//        for (j = 0; j < width; j += 1)
//        {
//          // if((sun_mode&&data[i*width+j]<pixel_threshold)||(!sun_mode))
//          //{
//          pixelCount[(
//              int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
//          gray_sum += (int)data[i * width + j];  //灰度值总和
//          //}
//        }
//      }

//      //计算每个像素值的点在整幅图像中的比例
//      for (i = 0; i < GrayScale; i++)
//      {
//        pixelPro[i] = (float)pixelCount[i] / pixelSum;
//      }

//      //遍历灰度级[0,255]
//      float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
//      w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
//      for (j = 0; j < pixel_threshold; j++)
//      {
//        w0 +=
//            pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和 即背景部分的比例
//        u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

//        w1 = 1 - w0;
//        u1tmp = gray_sum / pixelSum - u0tmp;

//        u0 = u0tmp / w0;    //背景平均灰度
//        u1 = u1tmp / w1;    //前景平均灰度
//        u = u0tmp + u1tmp;  //全局平均灰度
//        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
//        if (deltaTmp > deltaMax)
//        {
//          deltaMax = deltaTmp;
//          threshold = (uint8)j;     //本来这里没有强制类型转换的,我自己加的
//        }
//        if (deltaTmp < deltaMax)
//        {
//          break;
//        }
//      }
//  return threshold;
//}

//-----------------------------------------------------------------------------------------
//  @brief      图像转存
//  @date       把第一个参数数组的图像传给第二个图像数组，第三个参数是像素数量
//  @author     吕德森
//  Sample usage:    Transfer_Camera();
//-----------------------------------------------------------------------------------------
void Transfer_Camera(uint8 *p, uint8 *q, int16 pixel_num)
{
    for(int16 i = 0; i < pixel_num; i++)
        *(q +i) = *(p +i);
}
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{

    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height;
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //将像素值作为计数数组的下标
        }
    }

    //计算每个像素在整幅图像中的比例
    float maxPro = 0.0;
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        if (pixelPro[i] > maxPro)
        {
            maxPro = pixelPro[i];
        }
    }

    //遍历灰度级[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < GrayScale; i++)     // i作为阈值
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {
            if (j <= i)   //背景部分
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //前景部分
            {
                w1 += pixelPro[j];
                u1tmp += j * pixelPro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = (uint8)i;
        }
    }

    return threshold;
}
///*************************************************************** 
//* 函数名称：Get01change_Dajin()
//* 函数输入：无
//* 函数输出：无
//* 功能说明：二值化处理图像像素点
//***************************************************************/
uint8 Threshold;                //阈值
uint8 Threshold_static = 55;   //阈值静态下限225
uint16 Threshold_detach = 300;  //阳光算法分割阈值
void Get01change_Dajin()
{
      Threshold = otsuThreshold(image_yuanshi[0],MT9V03X_W, MT9V03X_H);

      if (Threshold < Threshold_static)
      {
          Threshold = Threshold_static;
      }

      uint8 thre;
      for(uint8 y = 0; y < MT9V03X_H; y++)  //这里考虑到了图像边缘的光照偏弱的问题
      {
        for(uint8 x = 0; x < MT9V03X_W; x++)
        {
          if (x <= 15)                      //受影响的边缘范围
            thre = Threshold - 10;          //修改可调节图像边缘的清晰度
          else if (x >= MT9V03X_W-15)
            thre = Threshold - 10;
          else
            thre = Threshold;

          if (image_yuanshi[y][x] >thre)         //数值越大，显示的内容越多，较浅的图像也能显示出来
            image_01[y][x] =0xFFFF;  //白
          else
            image_01[y][x] = 0x0000;   //黑
        }
      }
}
uint8 search_line_end = 0;
int16 l_line_x[MT9V03X_H], r_line_x[MT9V03X_H], m_line_x[MT9V03X_H];  //储存原始图像的左右边界的列数
uint8 l_lose_value = 0, r_lose_value = 0;  //左右丢线数
uint8 l_search_flag[MT9V03X_H], r_search_flag[MT9V03X_H];  //是否搜到线的标志
uint8 l_width, r_width;  //循环变量名
uint8 l_search_start, r_search_start;  //搜线起始x坐标
uint8 l_line_x_yuanshi[MT9V03X_H], r_line_x_yuanshi[MT9V03X_H];
uint8 r_losemax, l_losemax;
uint8 road_width[MT9V03X_H];
//-----------------------------------------------------------------------------------------
//  @brief      搜左右边线
//  @param      void
//  @return     void
//  Sample usage:    Search_Line();
//-----------------------------------------------------------------------------------------

void Search_Line()
{
    uint8 l_flag=0, r_flag=0;

    r_lose_value = l_lose_value = 0;                              //搜线之前将丢线数清零

    for(uint8 y = MT9V03X_H - 1; y > search_line_end; y--)        //确定每行的搜线起始横坐标
    {
        if( (y > MT9V03X_H - 5) || ( (l_line_x[y+1] == 0) && (r_line_x[y+1] == MT9V03X_W -1) && (y < MT9V03X_H - 4) ))   //前四行，或者左右都丢线的行
        {
            l_search_start = r_search_start = MT9V03X_W/2;
        }
        else if((l_line_x[y+1] != 0) && (r_line_x[y+1] != MT9V03X_W - 1) && (y < MT9V03X_H - 4))   //左右都不丢线
        {
            l_search_start = l_line_x[y+1] + 5;
            r_search_start = r_line_x[y+1] - 5;
        }
        else if((l_line_x[y+1] != 0 && r_line_x[y+1] == MT9V03X_W - 1) && (y < MT9V03X_H - 4))   //左不丢线,右丢线
        {
            l_search_start = l_line_x[y+1] + 5;
            r_search_start = MT9V03X_W/2;
        }
        else if((l_line_x[y+1] == 0 && r_line_x[y+1] != MT9V03X_W - 1) && (y < MT9V03X_H - 4))   //右不丢线,左丢线
        {
            l_search_start = MT9V03X_W/2;
            r_search_start = r_line_x[y+1] - 5;
        }
        for(l_width = l_search_start; l_width > 1; l_width--)      //左边搜线
        {
           if(image_01[y][l_width -2] == 0 && image_01[y][l_width - 1] == 0 && image_01[y][l_width] != 0 && l_width > 2)
           {//黑黑白
               l_line_x[y] = l_width - 1;
               l_line_x_yuanshi[y] = l_width - 1;
               l_search_flag[y] = 1;
               break;
           }
           else if(l_width == 2)
           {
               if(l_flag==0)
               {
                   l_flag = 1;
                   l_losemax = y +1;
               }
               l_line_x[y] = 0;
               l_line_x_yuanshi[y] = 0;
               l_search_flag[y] = 0;
               l_lose_value++;
             break;
           }
         }

         for(r_width = r_search_start; r_width < (MT9V03X_W - 2); r_width++)      //右边搜线
            {
                if(image_01[y][r_width] != 0 && image_01[y][r_width +1] == 0 && image_01[y][r_width +2] == 0 && r_width < MT9V03X_W - 3)
                {//白黑黑
                    r_line_x[y] = r_width + 1;
                    r_line_x_yuanshi[y] = r_width + 1;
                    r_search_flag[y] = 1;
                    break;
                }
                else if(r_width == MT9V03X_W - 3)
                {
                    if(r_flag==0)
                    {
                        r_flag = 1;
                        r_losemax = y + 1;
                    }
                    r_line_x[y] = MT9V03X_W - 1;
                    r_line_x_yuanshi[y] = MT9V03X_W - 1;
                    r_search_flag[y] = 0;
                    r_lose_value++;
                    break;
               }
            }
          road_width[y] = r_line_x[y] - l_line_x[y];
        }
}

uint8 search_lines_end = 0;
int16 u_line_x[MT9V03X_W], d_line_x[MT9V03X_W], mi_line_x[MT9V03X_W];  //储存原始图像的左右边界的列数
uint8 u_lose_value = 0, d_lose_value = 0;  //左右丢线数
uint8 u_search_flag[MT9V03X_W], d_search_flag[MT9V03X_W];  //是否搜到线的标志
uint8 u_width, d_width;  //循环变量名
uint8 u_search_start, d_search_start;  //搜线起始x坐标
uint8 u_line_x_yuanshi[MT9V03X_W], d_line_x_yuanshi[MT9V03X_W];
uint8 d_losemax, u_losemax;
uint8 roads_width[MT9V03X_W];
void Horizontal_line(void)
{
    uint8 u_flag=0, d_flag=0;

    d_lose_value = u_lose_value = 0;                              //搜线之前将丢线数清零

    for(uint8 y = MT9V03X_W - 1; y > search_lines_end; y--)        //确定每行的搜线起始横坐标
    {
        if( (y > MT9V03X_W - 5) || ((u_line_x[y+1] == 0) && (d_line_x[y+1] == MT9V03X_H -1) && (y < MT9V03X_W - 4) ))   //前四行，或者左右都丢线的行
        {
            u_search_start = d_search_start = MT9V03X_H/2;
        }
        else if((u_line_x[y+1] != 0) && (d_line_x[y+1] != MT9V03X_H - 1) && (y < MT9V03X_W - 4))   //左右都不丢线
        {
            u_search_start = u_line_x[y+1] + 5;
            d_search_start = d_line_x[y+1] - 5;
        }
        else if((u_line_x[y+1] != 0 && d_line_x[y+1] == MT9V03X_H - 1) && (y < MT9V03X_W - 4))   //左不丢线,右丢线
        {
            u_search_start = u_line_x[y+1] + 5;
            d_search_start = MT9V03X_H/2;
        }
        else if((u_line_x[y+1] == 0 && d_line_x[y+1] != MT9V03X_H - 1) && (y < MT9V03X_W - 4))   //右不丢线,左丢线
        {
            u_search_start = MT9V03X_H/2;
            d_search_start = d_line_x[y+1] - 5;
        }
        for(u_width = u_search_start; u_width > 1; u_width--)      //左边搜线
        {
           if(image_01[y][u_width -2] == 0 && image_01[y][u_width - 1] == 0 && image_01[y][u_width] != 0 && u_width > 2)
           {//黑黑白
               u_line_x[y] = u_width - 1;
               u_line_x_yuanshi[y] = u_width - 1;
               u_search_flag[y] = 1;
               break;
           }
           else if(u_width == 2)
           {
               if(u_flag==0)
               {
                   u_flag = 1;
                   u_losemax = y +1;
               }
               u_line_x[y] = 0;
               u_line_x_yuanshi[y] = 0;
               u_search_flag[y] = 0;
               u_lose_value++;
             break;
           }
         }

         for(d_width = u_search_start; d_width < (MT9V03X_H - 2); d_width++)      //右边搜线
            {
                if(image_01[y][d_width] != 0 && image_01[y][d_width +1] == 0 && image_01[y][d_width +2] == 0 && d_width < MT9V03X_H - 3)
                {//白黑黑
                    d_line_x[y] = d_width + 1;
                    d_line_x_yuanshi[y] = d_width + 1;
                    d_search_flag[y] = 1;
                    break;
                }
                else if(d_width == MT9V03X_H - 3)
                {
                    if(u_flag==0)
                    {
                        u_flag = 1;
                        d_losemax = y + 1;
                    }
                    d_line_x[y] = MT9V03X_H - 1;
                    d_line_x_yuanshi[y] = MT9V03X_H - 1;
                    d_search_flag[y] = 0;
                    d_lose_value++;
                    break;
               }
            }
          roads_width[y] = d_line_x[y] - u_line_x[y];
        }
}
int32 offset_3;  //摄像头处理得到的偏差
float offset5;    //摄像头处理得到的偏差
float offset_4;
void calculate_Offset()
{
        offset_3 = 0;
        for(uint8 y = MT9V03X_W -1; y >= 10; y--)
        {
            mi_line_x[y] = (u_line_x[y] + d_line_x[y])/2;
        }

        for(uint8 y = CONTROLL_W_MAX; y >=CONTROLL_W_MIN; y=y-2)//for(uint8 y = MT9V03X_H -35; y >=MT9V03X_H -45; y--)
        {
            offset_4 += (mi_line_x[y] - MT9V03X_H/2);
        }
				offset_4=(mi_line_x[90]-MT9V03X_H/2);
        offset5 = (float)(offset_3/15)*80;
}
void blacking()
{
    for(uint8 y=(MT9V03X_W-1); y>search_lines_end; y--)
    {
			  ips200_draw_point(y, u_line_x[y], RGB565_GREEN);
        ips200_draw_point(y,d_line_x[y] , RGB565_YELLOW);
//			 ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H,otsuThreshold(image_yuanshi[0],MT9V03X_W, MT9V03X_H));
        ips200_draw_point(y,mi_line_x[y] , RGB565_BLUE);
    }

//    for(uint8 i =0; i<MT9V03X_W; i++)
//    {
//        tft180_draw_point(i, CONTROLL_H_MAX, RGB565_BLUE);
//        tft180_draw_point(i, CONTROLL_H_MIN, RGB565_RED);
//        tft180_draw_point(i, 20, RGB565_RED);
//    }
//    for(uint8 i=0; i<MT9V03X_H; i++)
//    {
//        tft180_draw_point(MT9V03X_W/2, i, RGB565_RED);
//    }
}
int32 offset_1;  //摄像头处理得到的偏差
float offset;    //摄像头处理得到的偏差
float offset_2;
void Calculate_Offset()
{
    offset_1 = 0;
        for(uint8 y = MT9V03X_H -1; y >= 10; y--)
        {
            m_line_x[y] = (l_line_x[y] + r_line_x[y])/2;
        }

        for(uint8 y = CONTROLL_H_MAX; y >=CONTROLL_H_MIN; y=y-2)//for(uint8 y = MT9V03X_H -35; y >=MT9V03X_H -45; y--)
        {
            offset_1 += (m_line_x[y] - MT9V03X_W/2-1);
        }
				offset_2=(m_line_x[90]-MT9V03X_W/2)*2;    //左右偏离中线的情况
        offset = (float)(offset_1/15	);					//中线变化时小车应该取得的自旋量
}

//画边线和中线(液    晶画点,如果屏幕显示的图像进行了缩放就不能适用)
void Blacking()
{
    for(uint8 y=(MT9V03X_H-1); y>search_line_end; y--)
    {
			  ips200_draw_point(l_line_x[y], y, RGB565_GREEN);
        ips200_draw_point(r_line_x[y], y, RGB565_YELLOW);
//			 ips200_show_gray_image(0, 0, mt9v03x_image[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H,otsuThreshold(image_yuanshi[0],MT9V03X_W, MT9V03X_H));
        ips200_draw_point(m_line_x[y], y, RGB565_BLUE);
    }

//    for(uint8 i =0; i<MT9V03X_W; i++)
//    {
//        tft180_draw_point(i, CONTROLL_H_MAX, RGB565_BLUE);
//        tft180_draw_point(i, CONTROLL_H_MIN, RGB565_RED);
//        tft180_draw_point(i, 20, RGB565_RED);
//    }
//    for(uint8 i=0; i<MT9V03X_H; i++)
//    {
//        tft180_draw_point(MT9V03X_W/2, i, RGB565_RED);
//    }
}
//void Get_Pixle(void)
//{  
//  uint8 Gate;
//  Gate = otsuThreshold(mt9v03x_image[0],MT9V03X_W, MT9V03X_H);
//  for(uint8 hang=0;hang<Row;hang++)
//    for(uint8 lie=0;lie<Col;lie++)
//    {
//      if(mt9v03x_image[hang][lie]>=Gate)
//        Pixle[hang][lie] = 0xFFFF;
//      else
//        Pixle[hang][lie] = 0x0000;
//    }
//}
void Camera_All_Deal(void) //摄像头处理全过程
{


    if(mt9v03x_finish_flag)   //mt9v03x_finish_flag 是逐飞库里面场中断的标志位
    {
        Transfer_Camera(mt9v03x_image[0], image_yuanshi[0], MT9V03X_W*MT9V03X_H);  //图像转存，将摄像头采集到的图像转存到image_yuanshi[0]原始图像中
       // mt9v03x_finish_flag = 0;                      //在图像使用完毕后  务必清除标志位，否则不会开始采集下一幅图像
        Get01change_Dajin();                          //求阈值，二值化
        Search_Line();                                //搜线
	//		Horizontal_line();
        Calculate_Offset();                           //计算偏差
	//		calculate_Offset();
		
//         Outside_protect();//独轮不需要保护

//        tft180_show_gray_image(0, 0, (const uint8 *) image_01, MT9V03X_W, MT9V03X_H, 160, 128, 1);
//				ips200_show_gray_image(0, 0, image_yuanshi[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H,otsuThreshold(mt9v03x_image[0],MT9V03X_W, MT9V03X_H));
//        Blacking();

        mt9v03x_finish_flag = 0;                      //在图像使用完毕后  务必清除标志位，否则不会开始采集下一幅图像
    }
}
/************************************************************
        
【函数名称】Horizontal_line
【功    能】横向巡线函数
【参    数】无
【返 回 值】无
【实    例】Horizontal_line();
【注意事项】无
***********************************************************/
//void Horizontal_line(void)
//{
//  uint8 i,j;
//  if(Pixle[Row-1][Col/2]==0)
//  {
//    if(Pixle[Row-1][5]==0xFFFF)
//      midline[Row]=5;
//    else if(Pixle[Row-1][Col-5]==0xFFFF)
//      midline[Row]=Col-5;
//    else
//      midline[Row]=Col/2;
//  }
//  else
//	{
//    midline[Row]=Col/2;		
//	}
//	
//  for(i=Row-1;i>0;i--)
//  {
//    for(j=midline[i+1];j>=0;j--)
//    {
//      if(Pixle[i][j]==0||j==0)
//      {
//        leftline[i]=j;
//        break;
//      }
//    }
//    for(j=midline[i+1];j<=Col-1;j++)
//    {
//      if(Pixle[i][j]==0||j==Col-1)
//      {
//        rightline[i]=j;
//        break;
//      }
//    }
//    midline[i]=(leftline[i]+rightline[i])/2;
//   if(Pixle[i-1][midline[i]]==0||i==0)
//    {
//			 for(j=i;j>0;j--)
//			 {
//					midline[j]=midline[i];
//					leftline[j]=midline[i];
//					rightline[j]=midline[i];
//				 
//			 }
//       break;
//    }
//				ips200_show_int(0,16*8,leftline[1],3);
//				ips200_show_int(0,16*9,rightline[1],3);
//				ips200_show_int(10,16*10,midline[1],3);
//		
//			ips200_draw_line(midline[1], 0, midline[1], 100, RGB565_RED);
//		
//				
//  }
//}

//void findMidline()
//{
//    int8 l = 0 ,r = MT9V03X_W - 1;

//    //中线数组赋初值
//    for(int i = 0; i < MT9V03X_H; i++)
//    {
//        midline[i] = MT9V03X_W / 2;
//        leftline[i] = 0;
//        rightline[i] = MT9V03X_W - 1;
//        nextline[i] = MT9V03X_W / 2;
//    }

//    midline[MT9V03X_H - 1] = point[2][X];       //求取并记录中点
//    nextline[MT9V03X_H - 2] = point[2][X];       //迭代

//    W_K[MT9V03X_H - 1] = abs(point[3][X] - point[1][X])*1000/((MT9V03X_H - 1)*(min_W-max_W)/(MT9V03X_H - 1)+max_W);
//    MAX_W_K = W_K[MT9V03X_H - 1];  //开始计算赛道宽度比例系数

//    for(int i = MT9V03X_H - 2; i > 0; i--)
//    {
//        leftline[i] = 0;
//        rightline[i] = MT9V03X_W - 1;
//        //中线限幅
//        if(nextline[i] < 1)
//        {
//            nextline[i] = 1;
//        }
//        if(nextline[i] > MT9V03X_W-2)
//        {
//            nextline[i] = MT9V03X_W-2;
//        }


//        for(int j = nextline[i]; j > 1; j -= 1)
//        {
//            if(end_img[i][j] != end_img[i][j - 1])
//            {
//                leftline[i] = j;
//                break;
//            }
//        }

//        for(int k = nextline[i]; k < MT9V03X_W - 2; k += 1)
//        {
//            if(end_img[i][k] != end_img[i][k + 1])
//            {
//                rightline[i] = k;
//                break;
//            }
//        }


//        nextline[i - 1] = (leftline[i] + rightline[i]) / 2; //计算中线
//        midline[i] = (leftline[i] + rightline[i]) / 2;

//        W_K[i] = abs(leftline[i] - rightline[i])*1000/((i)*(min_W-max_W)/(MT9V03X_H-1)+max_W);  //计算赛道宽度比例

//        if(W_K[i] > MAX_W_K)    MAX_W_K = W_K[i];  //记录赛道最大宽度比例

//     }
//    for (int i = 0; i < MT9V03X_H - 1; i++)
//    {
//       see_img[i][midline[i]] = 0x00;
//    }
//    //oled_dis_bmp(MT9V03X_H, MT9V03X_W, see_img, image_threshold);

//}