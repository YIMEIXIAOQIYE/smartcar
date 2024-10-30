#include "zf_common_headfile.h"
#include "math.h"
#define Row    90               //ͼ������
#define Col    188              //ͼ������
#define GrayScale 256
#define CONTROLL_H_MAX  100
#define CONTROLL_H_MIN  60
int Pixle[MT9V03X_H][MT9V03X_W];
int midline[MT9V03X_H] = {0};
int nextline[MT9V03X_H] = {0};
int leftline[MT9V03X_H] = {0};
int rightline[MT9V03X_H] = {0};
uint8 image_yuanshi[MT9V03X_H][MT9V03X_W];      //ԭʼͼ��
int image_01[MT9V03X_H][MT9V03X_W];           //��ֵ��ͼ��
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
//  double OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��; 
//  int16 MinValue, MaxValue; 
//  uint8 Threshold = 0;
//  uint8 HistoGram[256];              // 
//	uint8 tmImage[MT9V03X_H][MT9V03X_W];
// 
//  for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ 
//  
//  for (j = 0; j < MT9V03X_H; j++) 
//  { 
//    for (i = 0; i < MT9V03X_W; i++) 
//    { 
//      HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
//    } 
//  } 
//  
//  for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
//  for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ
//      
//  if (MaxValue == MinValue)     return MaxValue;         // ͼ����ֻ��һ����ɫ    
//  if (MinValue + 1 == MaxValue)  return MinValue;        // ͼ����ֻ�ж�����ɫ
//    
//  for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  ��������
//    
//  PixelIntegral = 0;
//  for (j = MinValue; j <= MaxValue; j++)
//  {
//    PixelIntegral += HistoGram[j] * j;//�Ҷ�ֵ����
//  }
//  SigmaB = -1;
//  for (j = MinValue; j < MaxValue; j++)
//  {
//    PixelBack = PixelBack + HistoGram[j];   //ǰ�����ص���
//    PixelFore = Amount - PixelBack;         //�������ص���
//    OmegaBack = (double)PixelBack / Amount;//ǰ�����ذٷֱ�
//    OmegaFore = (double)PixelFore / Amount;//�������ذٷֱ�
//    PixelIntegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
//    PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
//    MicroBack = (double)PixelIntegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
//    MicroFore = (double)PixelIntegralFore / PixelFore;   //�����ҶȰٷֱ�
//    Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//������䷽��
//    if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
//    {
//      SigmaB = Sigma;
//      Threshold = j;
//    }
//  }
//  return Threshold;                        //���������ֵ;
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
//      uint8* data = image;  //ָ���������ݵ�ָ��
//      for (i = 0; i < GrayScale; i++)
//      {
//        pixelCount[i] = 0;
//        pixelPro[i] = 0;
//      }

//      uint32 gray_sum = 0;
//      //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
//      for (i = 0; i < height; i += 1)
//      {
//        for (j = 0; j < width; j += 1)
//        {
//          // if((sun_mode&&data[i*width+j]<pixel_threshold)||(!sun_mode))
//          //{
//          pixelCount[(
//              int)data[i * width + j]]++;  //����ǰ�ĵ������ֵ��Ϊ����������±�
//          gray_sum += (int)data[i * width + j];  //�Ҷ�ֵ�ܺ�
//          //}
//        }
//      }

//      //����ÿ������ֵ�ĵ�������ͼ���еı���
//      for (i = 0; i < GrayScale; i++)
//      {
//        pixelPro[i] = (float)pixelCount[i] / pixelSum;
//      }

//      //�����Ҷȼ�[0,255]
//      float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
//      w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
//      for (j = 0; j < pixel_threshold; j++)
//      {
//        w0 +=
//            pixelPro[j];  //��������ÿ���Ҷ�ֵ�����ص���ռ����֮�� ���������ֵı���
//        u0tmp += j * pixelPro[j];  //�������� ÿ���Ҷ�ֵ�ĵ�ı��� *�Ҷ�ֵ

//        w1 = 1 - w0;
//        u1tmp = gray_sum / pixelSum - u0tmp;

//        u0 = u0tmp / w0;    //����ƽ���Ҷ�
//        u1 = u1tmp / w1;    //ǰ��ƽ���Ҷ�
//        u = u0tmp + u1tmp;  //ȫ��ƽ���Ҷ�
//        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
//        if (deltaTmp > deltaMax)
//        {
//          deltaMax = deltaTmp;
//          threshold = (uint8)j;     //��������û��ǿ������ת����,���Լ��ӵ�
//        }
//        if (deltaTmp < deltaMax)
//        {
//          break;
//        }
//      }
//  return threshold;
//}

//-----------------------------------------------------------------------------------------
//  @brief      ͼ��ת��
//  @date       �ѵ�һ�����������ͼ�񴫸��ڶ���ͼ�����飬��������������������
//  @author     ����ɭ
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
    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
        }
    }

    //����ÿ������������ͼ���еı���
    float maxPro = 0.0;
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        if (pixelPro[i] > maxPro)
        {
            maxPro = pixelPro[i];
        }
    }

    //�����Ҷȼ�[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < GrayScale; i++)     // i��Ϊ��ֵ
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {
            if (j <= i)   //��������
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //ǰ������
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
//* �������ƣ�Get01change_Dajin()
//* �������룺��
//* �����������
//* ����˵������ֵ������ͼ�����ص�
//***************************************************************/
uint8 Threshold;                //��ֵ
uint8 Threshold_static = 55;   //��ֵ��̬����225
uint16 Threshold_detach = 300;  //�����㷨�ָ���ֵ
void Get01change_Dajin()
{
      Threshold = otsuThreshold(image_yuanshi[0],MT9V03X_W, MT9V03X_H);

      if (Threshold < Threshold_static)
      {
          Threshold = Threshold_static;
      }

      uint8 thre;
      for(uint8 y = 0; y < MT9V03X_H; y++)  //���￼�ǵ���ͼ���Ե�Ĺ���ƫ��������
      {
        for(uint8 x = 0; x < MT9V03X_W; x++)
        {
          if (x <= 15)                      //��Ӱ��ı�Ե��Χ
            thre = Threshold - 10;          //�޸Ŀɵ���ͼ���Ե��������
          else if (x >= MT9V03X_W-15)
            thre = Threshold - 10;
          else
            thre = Threshold;

          if (image_yuanshi[y][x] >thre)         //��ֵԽ����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����
            image_01[y][x] =0xFFFF;  //��
          else
            image_01[y][x] = 0x0000;   //��
        }
      }
}
uint8 search_line_end = 0;
int16 l_line_x[MT9V03X_H], r_line_x[MT9V03X_H], m_line_x[MT9V03X_H];  //����ԭʼͼ������ұ߽������
uint8 l_lose_value = 0, r_lose_value = 0;  //���Ҷ�����
uint8 l_search_flag[MT9V03X_H], r_search_flag[MT9V03X_H];  //�Ƿ��ѵ��ߵı�־
uint8 l_width, r_width;  //ѭ��������
uint8 l_search_start, r_search_start;  //������ʼx����
uint8 l_line_x_yuanshi[MT9V03X_H], r_line_x_yuanshi[MT9V03X_H];
uint8 r_losemax, l_losemax;
uint8 road_width[MT9V03X_H];
//-----------------------------------------------------------------------------------------
//  @brief      �����ұ���
//  @param      void
//  @return     void
//  Sample usage:    Search_Line();
//-----------------------------------------------------------------------------------------

void Search_Line()
{
    uint8 l_flag=0, r_flag=0;

    r_lose_value = l_lose_value = 0;                              //����֮ǰ������������

    for(uint8 y = MT9V03X_H - 1; y > search_line_end; y--)        //ȷ��ÿ�е�������ʼ������
    {
        if( (y > MT9V03X_H - 5) || ( (l_line_x[y+1] == 0) && (r_line_x[y+1] == MT9V03X_W -1) && (y < MT9V03X_H - 4) ))   //ǰ���У��������Ҷ����ߵ���
        {
            l_search_start = r_search_start = MT9V03X_W/2;
        }
        else if((l_line_x[y+1] != 0) && (r_line_x[y+1] != MT9V03X_W - 1) && (y < MT9V03X_H - 4))   //���Ҷ�������
        {
            l_search_start = l_line_x[y+1] + 5;
            r_search_start = r_line_x[y+1] - 5;
        }
        else if((l_line_x[y+1] != 0 && r_line_x[y+1] == MT9V03X_W - 1) && (y < MT9V03X_H - 4))   //�󲻶���,�Ҷ���
        {
            l_search_start = l_line_x[y+1] + 5;
            r_search_start = MT9V03X_W/2;
        }
        else if((l_line_x[y+1] == 0 && r_line_x[y+1] != MT9V03X_W - 1) && (y < MT9V03X_H - 4))   //�Ҳ�����,����
        {
            l_search_start = MT9V03X_W/2;
            r_search_start = r_line_x[y+1] - 5;
        }
        for(l_width = l_search_start; l_width > 1; l_width--)      //�������
        {
           if(image_01[y][l_width -2] == 0 && image_01[y][l_width - 1] == 0 && image_01[y][l_width] != 0 && l_width > 2)
           {//�ںڰ�
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

         for(r_width = r_search_start; r_width < (MT9V03X_W - 2); r_width++)      //�ұ�����
            {
                if(image_01[y][r_width] != 0 && image_01[y][r_width +1] == 0 && image_01[y][r_width +2] == 0 && r_width < MT9V03X_W - 3)
                {//�׺ں�
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
int16 u_line_x[MT9V03X_W], d_line_x[MT9V03X_W], mi_line_x[MT9V03X_W];  //����ԭʼͼ������ұ߽������
uint8 u_lose_value = 0, d_lose_value = 0;  //���Ҷ�����
uint8 u_search_flag[MT9V03X_W], d_search_flag[MT9V03X_W];  //�Ƿ��ѵ��ߵı�־
uint8 u_width, d_width;  //ѭ��������
uint8 u_search_start, d_search_start;  //������ʼx����
uint8 u_line_x_yuanshi[MT9V03X_W], d_line_x_yuanshi[MT9V03X_W];
uint8 d_losemax, u_losemax;
uint8 roads_width[MT9V03X_W];
void Horizontal_line(void)
{
    uint8 u_flag=0, d_flag=0;

    d_lose_value = u_lose_value = 0;                              //����֮ǰ������������

    for(uint8 y = MT9V03X_W - 1; y > search_lines_end; y--)        //ȷ��ÿ�е�������ʼ������
    {
        if( (y > MT9V03X_W - 5) || ((u_line_x[y+1] == 0) && (d_line_x[y+1] == MT9V03X_H -1) && (y < MT9V03X_W - 4) ))   //ǰ���У��������Ҷ����ߵ���
        {
            u_search_start = d_search_start = MT9V03X_H/2;
        }
        else if((u_line_x[y+1] != 0) && (d_line_x[y+1] != MT9V03X_H - 1) && (y < MT9V03X_W - 4))   //���Ҷ�������
        {
            u_search_start = u_line_x[y+1] + 5;
            d_search_start = d_line_x[y+1] - 5;
        }
        else if((u_line_x[y+1] != 0 && d_line_x[y+1] == MT9V03X_H - 1) && (y < MT9V03X_W - 4))   //�󲻶���,�Ҷ���
        {
            u_search_start = u_line_x[y+1] + 5;
            d_search_start = MT9V03X_H/2;
        }
        else if((u_line_x[y+1] == 0 && d_line_x[y+1] != MT9V03X_H - 1) && (y < MT9V03X_W - 4))   //�Ҳ�����,����
        {
            u_search_start = MT9V03X_H/2;
            d_search_start = d_line_x[y+1] - 5;
        }
        for(u_width = u_search_start; u_width > 1; u_width--)      //�������
        {
           if(image_01[y][u_width -2] == 0 && image_01[y][u_width - 1] == 0 && image_01[y][u_width] != 0 && u_width > 2)
           {//�ںڰ�
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

         for(d_width = u_search_start; d_width < (MT9V03X_H - 2); d_width++)      //�ұ�����
            {
                if(image_01[y][d_width] != 0 && image_01[y][d_width +1] == 0 && image_01[y][d_width +2] == 0 && d_width < MT9V03X_H - 3)
                {//�׺ں�
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
int32 offset_3;  //����ͷ����õ���ƫ��
float offset5;    //����ͷ����õ���ƫ��
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
int32 offset_1;  //����ͷ����õ���ƫ��
float offset;    //����ͷ����õ���ƫ��
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
				offset_2=(m_line_x[90]-MT9V03X_W/2)*2;    //����ƫ�����ߵ����
        offset = (float)(offset_1/15	);					//���߱仯ʱС��Ӧ��ȡ�õ�������
}

//�����ߺ�����(Һ    ������,�����Ļ��ʾ��ͼ����������žͲ�������)
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
void Camera_All_Deal(void) //����ͷ����ȫ����
{


    if(mt9v03x_finish_flag)   //mt9v03x_finish_flag ����ɿ����泡�жϵı�־λ
    {
        Transfer_Camera(mt9v03x_image[0], image_yuanshi[0], MT9V03X_W*MT9V03X_H);  //ͼ��ת�棬������ͷ�ɼ�����ͼ��ת�浽image_yuanshi[0]ԭʼͼ����
       // mt9v03x_finish_flag = 0;                      //��ͼ��ʹ����Ϻ�  ��������־λ�����򲻻Ὺʼ�ɼ���һ��ͼ��
        Get01change_Dajin();                          //����ֵ����ֵ��
        Search_Line();                                //����
	//		Horizontal_line();
        Calculate_Offset();                           //����ƫ��
	//		calculate_Offset();
		
//         Outside_protect();//���ֲ���Ҫ����

//        tft180_show_gray_image(0, 0, (const uint8 *) image_01, MT9V03X_W, MT9V03X_H, 160, 128, 1);
//				ips200_show_gray_image(0, 0, image_yuanshi[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H,otsuThreshold(mt9v03x_image[0],MT9V03X_W, MT9V03X_H));
//        Blacking();

        mt9v03x_finish_flag = 0;                      //��ͼ��ʹ����Ϻ�  ��������־λ�����򲻻Ὺʼ�ɼ���һ��ͼ��
    }
}
/************************************************************
        
���������ơ�Horizontal_line
����    �ܡ�����Ѳ�ߺ���
����    ������
���� �� ֵ����
��ʵ    ����Horizontal_line();
��ע�������
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

//    //�������鸳��ֵ
//    for(int i = 0; i < MT9V03X_H; i++)
//    {
//        midline[i] = MT9V03X_W / 2;
//        leftline[i] = 0;
//        rightline[i] = MT9V03X_W - 1;
//        nextline[i] = MT9V03X_W / 2;
//    }

//    midline[MT9V03X_H - 1] = point[2][X];       //��ȡ����¼�е�
//    nextline[MT9V03X_H - 2] = point[2][X];       //����

//    W_K[MT9V03X_H - 1] = abs(point[3][X] - point[1][X])*1000/((MT9V03X_H - 1)*(min_W-max_W)/(MT9V03X_H - 1)+max_W);
//    MAX_W_K = W_K[MT9V03X_H - 1];  //��ʼ����������ȱ���ϵ��

//    for(int i = MT9V03X_H - 2; i > 0; i--)
//    {
//        leftline[i] = 0;
//        rightline[i] = MT9V03X_W - 1;
//        //�����޷�
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


//        nextline[i - 1] = (leftline[i] + rightline[i]) / 2; //��������
//        midline[i] = (leftline[i] + rightline[i]) / 2;

//        W_K[i] = abs(leftline[i] - rightline[i])*1000/((i)*(min_W-max_W)/(MT9V03X_H-1)+max_W);  //����������ȱ���

//        if(W_K[i] > MAX_W_K)    MAX_W_K = W_K[i];  //��¼��������ȱ���

//     }
//    for (int i = 0; i < MT9V03X_H - 1; i++)
//    {
//       see_img[i][midline[i]] = 0x00;
//    }
//    //oled_dis_bmp(MT9V03X_H, MT9V03X_W, see_img, image_threshold);

//}