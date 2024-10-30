#include "zf_common_headfile.h"
#include "other.h"
#include  <math.h>

//���û�������
extern const uint8 Image_Flags[][9][8];     //����ͼ�ϵ����ֱ��
int image_two_value[MT9V03X_H][MT9V03X_W];//��ֵ�����ԭ����
volatile int Left_Line[MT9V03X_H]; //���������
volatile int Right_Line[MT9V03X_H];//�ұ�������
volatile int Mid_Line[MT9V03X_H];  //��������
volatile int Road_Wide[MT9V03X_H]; //��������
volatile int White_Column[MT9V03X_W];    //ÿ�а��г���
volatile int Search_Stop_Line;     //������ֹ��,ֻ��¼���ȣ���Ҫ������Ҫ����Ұ�߶ȼ�ȥ��ֵ
volatile int Boundry_Start_Left;   //���ұ߽���ʼ��
volatile int Boundry_Start_Right;  //��һ���Ƕ��ߵ�,����߽���ʼ��
volatile int Left_Lost_Time;       //�߽綪����
volatile int Right_Lost_Time;
volatile int Both_Lost_Time;//����ͬʱ������
int Longest_White_Column_Left[2]; //�����,[0]������еĳ��ȣ�Ҳ����Search_Stop_Line������ֹ�У�[1���ǵ�ĳ��
int Longest_White_Column_Right[2];//�����,[0]������еĳ��ȣ�Ҳ����Search_Stop_Line������ֹ�У�[1���ǵ�ĳ��
int Left_Lost_Flag[MT9V03X_H] ; //�������飬������1��û������0
int Right_Lost_Flag[MT9V03X_H]; //�Ҷ������飬������1��û������0

//---Ԫ����
//��ţ�����ͷ��־λ��Ĭ������ͷ
extern volatile uint8 Electromagnet_Flag;

//����
extern volatile int Island_State;     //����״̬��־
extern volatile int Left_Island_Flag; //���һ�����־
extern volatile int Right_Island_Flag;//���һ�����־

//�µ�
volatile int Ramp_Flag=0;//�µ���־

//ʮ��
volatile int Cross_Flag=0;
volatile int Left_Down_Find=0; //ʮ��ʹ�ã��ҵ�����������û�ҵ�����0
volatile int Left_Up_Find=0;   //�ĸ��յ��־
volatile int Right_Down_Find=0;
volatile int Right_Up_Find=0;

//������
volatile int Zebra_Stripes_Flag=0;//������

//���Ʊ�
volatile uint8 Obstacle_Dir=0; //0�ҹգ�1���
volatile uint8 Island_Switch=1;//����ʶ������־λ
volatile uint8 Straight_Flag=0;//��ֱ��ʶ���
volatile uint8 Ramp_Switch=0;  //�µ�ʶ���־λ

//���
extern volatile float Err;//����ͷ���

//ͼ����ʧ
volatile uint8 Img_Disappear_Flag=0; //ͼ����ʧ��־λ��1��˵����ͼ��
volatile uint8 Outside_Edge_flag=0;  //���������һ����˼�������Ĵ����ûɾ��������ʵ�ò�������
volatile uint8 Stop_Flag=0;          //ֹͣ��

//���·�ϱ�־λ
volatile uint8 Barricade_Flag=0;     //��ϣ���1~4����״̬��0˵�����ں����

//���ʱ�򱣻�
extern volatile uint8 Electromagnet_Flag;//0������ͷ��1�ǵ��

//��׼���������ӷ��ڳ�ֱ������ʵ�⣬������ֵ�����ο�
const uint8 Standard_Road_Wide[MT9V03X_H]=
{ 10, 12, 14, 16, 18, 20, 22, 24, 26, 28,
  30, 32, 34, 36, 38, 40, 42, 44, 46, 48,
  50, 52, 54, 56, 58, 60, 62, 64, 66, 68,
  70, 72, 74, 76, 78, 80, 82, 84, 86, 88,
  90, 92, 94, 96, 98,100,102,104,106,108,
 110,112,114,116,118,120,122,124,126,128,
 130,132,134,136,138,140,142,144,146,148};

/*-------------------------------------------------------------------------------------------------------------------
  @brief     ���ٴ������ֵ������ɽ��
  @param     image       ͼ������
             col         �� �����
             row         �У�����
  @return    null
  Sample     threshold=my_adapt_threshold(mt9v03x_image[0],MT9V03X_W, MT9V03X_H);//ɽ�����ٴ��
  @note      ��˵�ȴ�ͳ��򷨿�һ�㣬ʹ��Ч�����
-------------------------------------------------------------------------------------------------------------------*/
int my_adapt_threshold(uint8 *image, uint16 col, uint16 row)   //ע�������ֵ��һ��Ҫ��ԭͼ��
{
    #define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j;
    int pixelSum = width * height/4;
    int threshold = 0;
    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }
    uint32 gray_sum=0;
    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //����ǰ�ĵ������ֵ��Ϊ����������±�
            gray_sum+=(int)data[i * width + j];       //�Ҷ�ֵ�ܺ�
        }
    }
    //����ÿ������ֵ�ĵ�������ͼ���еı���
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
    }
    //�����Ҷȼ�[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
    for (j = 0; j < GrayScale; j++)
    {
        w0 += pixelPro[j];  //��������ÿ���Ҷ�ֵ�����ص���ռ����֮��   ���������ֵı���
        u0tmp += j * pixelPro[j];  //�������� ÿ���Ҷ�ֵ�ĵ�ı��� *�Ҷ�ֵ
        w1=1-w0;
        u1tmp=gray_sum/pixelSum-u0tmp;
        u0 = u0tmp / w0;              //����ƽ���Ҷ�
        u1 = u1tmp / w1;              //ǰ��ƽ���Ҷ�
        u = u0tmp + u1tmp;            //ȫ��ƽ���Ҷ�
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = j;
        }
        if (deltaTmp < deltaMax)
        {
            break;
        }
    }
    return threshold;
}

///*-------------------------------------------------------------------------------------------------------------------
//  @brief     ��ͨ�������ֵ
//  @param     image       ͼ������
//             col         �� �����
//             row         �У�����
//  @return    threshold   ����int���͵ĵ���ֵ
//  Sample     threshold=my_adapt_threshold(mt9v03x_image[0],MT9V03X_W, MT9V03X_H);//��ͨ���
//  @note      ��˵û��ɽ�����죬�Ҹо��������𲻴�
//-------------------------------------------------------------------------------------------------------------------*/
int My_Adapt_Threshold(uint8*image,uint16 width, uint16 height)   //����㷨��ע�������ֵ��һ��Ҫ��ԭͼ��
{
    #define GrayScale 256
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j;
    int pixelSum = width * height/4;
    int  threshold = 0;
    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }
    uint32 gray_sum=0;
    for (i = 0; i < height; i+=2)//ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    {
        for (j = 0; j <width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //����ǰ�ĵ������ֵ��Ϊ����������±�
            gray_sum+=(int)data[i * width + j];       //�Ҷ�ֵ�ܺ�
        }
    }
    for (i = 0; i < GrayScale; i++) //����ÿ������ֵ�ĵ�������ͼ���еı���
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
    }
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
    for (j = 0; j < GrayScale; j++)//�����Ҷȼ�[0,255]
    {
        w0 += pixelPro[j];  //��������ÿ���Ҷ�ֵ�����ص���ռ����֮��   ���������ֵı���
        u0tmp += j * pixelPro[j];  //�������� ÿ���Ҷ�ֵ�ĵ�ı��� *�Ҷ�ֵ
        w1=1-w0;
        u1tmp=gray_sum/pixelSum-u0tmp;
        u0 = u0tmp / w0;              //����ƽ���Ҷ�
        u1 = u1tmp / w1;              //ǰ��ƽ���Ҷ�
        u = u0tmp + u1tmp;            //ȫ��ƽ���Ҷ�
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);//ƽ��
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;//�����䷽�
            threshold = j;
        }
        if (deltaTmp < deltaMax)
        {
            break;
        }
    }
    if(threshold>255)
        threshold=255;
    if(threshold<0)
        threshold=0;
  return threshold;
}

///*-------------------------------------------------------------------------------------------------------------------
//  @brief     ͼ���ֵ��������
//  @param     ԭʼͼ�����飬�߶ȣ���ȣ���ֵ����ֵ
//  @return    ��ֵ��֮���ͼ������
//  Sample     Image_Binarization(Threshold);//ͼ���ֵ��
//  @note      ��ֵ������0x00�ڣ�0xff�ǰף��Ѿ��ú궨���滻����
//-------------------------------------------------------------------------------------------------------------------*/
//void Image_Binarization(int threshold)//ͼ���ֵ��
//{
//    uint16 i,j;
//    for(i=0;i<MT9V03X_H;i++)
//    {
//        for(j=0;j<MT9V03X_W;j++)
//        {
//            if(mt9v03x_image[i][j]>=threshold)
//                image_two_value[i][j]=0xFFFF;//��
//            else
//                image_two_value[i][j]=0x0000;//��
//        }
//    }
//}

///*-------------------------------------------------------------------------------------------------------------------
//  @brief     ˫�����Ѳ��
//  @param     null
//  @return    null
//  Sample     Longest_White_Column_Left();
//  @note      �����Ѳ�ߣ�Ѱ�ҳ�ʼ�߽磬���ߣ�����еȻ���Ԫ�أ�������ȡ��Щ��������������ʶ��
//-------------------------------------------------------------------------------------------------------------------*/
//void Longest_White_Column()//�����Ѳ��
//{
//    int i, j;
//    int start_column=20;//����е���������
//    int end_column=MT9V03X_W-20;
//    int left_border = 0, right_border = 0;//��ʱ�洢����λ��
//    Longest_White_Column_Left[0] = 0;//�����,[0]������еĳ��ȣ�[1���ǵ�ĳ��
//    Longest_White_Column_Left[1] = 0;//�����,[0]������еĳ��ȣ�[1���ǵ�ĳ��
//    Longest_White_Column_Right[0] = 0;//�����,[0]������еĳ��ȣ�[1���ǵ�ĳ��
//    Longest_White_Column_Right[1] = 0;//�����,[0]������еĳ��ȣ�[1���ǵ�ĳ��
//    Right_Lost_Time = 0;    //�߽綪����
//    Left_Lost_Time  = 0;
//    Boundry_Start_Left  = 0;//��һ���Ƕ��ߵ�,����߽���ʼ��
//    Boundry_Start_Right = 0;
//    Both_Lost_Time = 0;//����ͬʱ������

//    for (i = 0; i <=MT9V03X_H-1; i++)//��������
//    {
//        Right_Lost_Flag[i] = 0;
//        Left_Lost_Flag[i] = 0;
//        Left_Line[i] = 0;
//        Right_Line[i] = MT9V03X_W-1;
//    }
//    for(i=0;i<=MT9V03X_W-1;i++)
//    {
//        White_Column[i] = 0;
//    }

////������Ҫ������з�Χ�����޶�������3״̬�Ҳ����Ͻǵ㣬�����޸���������
//    //����3״̬��Ҫ�ı������Ѱ�ҷ�Χ
//    if(Right_Island_Flag==1)//�һ�
//    {
//        if(Island_State==3)
//        {
//            start_column=40;
//            end_column=MT9V03X_W-20;
//        }
//    }
//    else if(Left_Island_Flag==1)//��
//    {
//        if(Island_State==3)
//        {
//            start_column=20;
//            end_column=MT9V03X_W-40;
//        }
//    }

//    //�����ң��������ϣ�����ȫͼ��¼��Χ�ڵ�ÿһ�а׵�����
//    for (j =start_column; j<=end_column; j++)
//    {
//        for (i = MT9V03X_H - 1; i >= 0; i--)
//        {
//            if(image_two_value[i][j] == 0x0000)
//                break;
//            else
//                White_Column[j]++;
//        }
//    }

//    //����������������
//    Longest_White_Column_Left[0] =0;
//    for(i=start_column;i<=end_column;i++)
//    {
//        if (Longest_White_Column_Left[0] < White_Column[i])//�������һ��
//        {
//            Longest_White_Column_Left[0] = White_Column[i];//��0���ǰ��г���
//            Longest_White_Column_Left[1] = i;              //��1�����±꣬��j��
//        }
//    }
//    //���ҵ���������������
//    Longest_White_Column_Right[0] = 0;//��0���ǰ��г���
//    for(i=end_column;i>=start_column;i--)//��������ע���������ҵ���������λ�þͿ���ͣ��
//    {
//        if (Longest_White_Column_Right[0] < White_Column[i])//�������һ��
//        {
//            Longest_White_Column_Right[0] = White_Column[i];//��0���ǰ��г���
//            Longest_White_Column_Right[1] = i;              //��1�����±꣬��j��
//        }
//    }

//    Search_Stop_Line = Longest_White_Column_Left[0];//������ֹ��ѡȡ����������𲻴�����������������һ����
//    for (i = MT9V03X_H - 1; i >=MT9V03X_H-Search_Stop_Line; i--)//����Ѳ��
//    {
//        for (j = Longest_White_Column_Right[1]; j <= MT9V03X_W - 1 - 2; j++)
//        {
//            if (image_two_value[i][j] ==0xFFFF && image_two_value[i][j + 1] == 0x0000 && image_two_value[i][j + 2] == 0x0000)//�׺ںڣ��ҵ��ұ߽�
//            {
//                right_border = j;
//                Right_Lost_Flag[i] = 0; //�Ҷ������飬������1����������0
//                break;
//            }
//            else if(j>=MT9V03X_W-1-2)//û�ҵ��ұ߽磬����Ļ���Ҹ�ֵ���ұ߽�
//            {
//                right_border = j;
//                Right_Lost_Flag[i] = 1; //�Ҷ������飬������1����������0
//                break;
//            }
//        }
//        for (j = Longest_White_Column_Left[1]; j >= 0 + 2; j--)//�����ɨ��
//        {
//            if (image_two_value[i][j] ==0xFFFF && image_two_value[i][j - 1] == 0x0000 && image_two_value[i][j - 2] == 0x0000)//�ںڰ���Ϊ������߽�
//            {
//                left_border = j;
//                Left_Lost_Flag[i] = 0; //�������飬������1����������0
//                break;
//            }
//            else if(j<=0+2)
//            {
//                left_border = j;//�ҵ�ͷ��û�ҵ��ߣ��Ͱ���Ļ�����ҵ����߽�
//                Left_Lost_Flag[i] = 1; //�������飬������1����������0
//                break;
//            }
//        }
//        Left_Line [i] = left_border;       //�����������
//        Right_Line[i] = right_border;      //�ұ���������
//    }

//    for (i = MT9V03X_H - 1; i >= 0; i--)//�������ݳ�������
//    {
//        if (Left_Lost_Flag[i]  == 1)//���߶�����
//            Left_Lost_Time++;
//        if (Right_Lost_Flag[i] == 1)
//            Right_Lost_Time++;
//        if (Left_Lost_Flag[i] == 1 && Right_Lost_Flag[i] == 1)//˫�߶�����
//            Both_Lost_Time++;
//        if (Boundry_Start_Left ==  0 && Left_Lost_Flag[i]  != 1)//��¼��һ���Ƕ��ߵ㣬�߽���ʼ��
//            Boundry_Start_Left = i;
//        if (Boundry_Start_Right == 0 && Right_Lost_Flag[i] != 1)
//            Boundry_Start_Right = i;
//        Road_Wide[i]=Right_Line[i]-Left_Line[i];
//    }
//    
//    //debugʹ�ã���Ļ��ʾ��ز���
////    ips200_show_int(0,0, Longest_White_Column_Right[0],3);//��0���ǰ��г���
////    ips200_show_int(0,1, Longest_White_Column_Right[1],3);//��1�����±꣬��j��)
////    ips200_show_int(0,2, Longest_White_Column_Left[0],3);//��0���ǰ��г���
////    ips200_show_int(0,3, Longest_White_Column_Left[1],3);//��1�����±꣬��j��)
//}

///*-------------------------------------------------------------------------------------------------------------------
//  @brief     �߽���ʾ������ͼ������ʾ����Ļ�ϣ�
//  @param     null
//  @return    null
//  Sample     ֱ�ӵ���
//  @note      ��ʾ�����ұ߽磬���ߣ�
//                                           ��������²�Ҫ�ã���Ϊֱ����ԭͼ��д���˱߽���Ϣ
//                                           ���Ԫ���ж���ɸ��ŵģ�����ʱ�����
//-------------------------------------------------------------------------------------------------------------------*/
//void Show_Boundry(void)
//{
//    int16 i;
//    for(i=MT9V03X_H-1;i>=MT9V03X_H-Search_Stop_Line;i--)//�����������ɨ��
//    {
//        image_two_value[i][Left_Line[i]+1]=0x0000;
//        image_two_value[i][(Left_Line[i]+Right_Line[i])>>1]=0x0000;
//        image_two_value[i][Right_Line[i]-1]=0x0000;
//    }

//    //����Ļ�������ߴ���ʾ���ߣ����ڵ�������ͷ
//    //ips200_draw_line ( MT9V03X_W/2, MT9V03X_H-10, MT9V03X_W/2, MT9V03X_H, RGB565_RED);
//}

///*-------------------------------------------------------------------------------------------------------------------
//  @brief     ����
//  @param     ���ߵ���㣬�յ�
//  @return    null
//  Sample     Left_Add_Line(int x1,int y1,int x2,int y2);
//  @note      ����ֱ���Ǳ߽磬������ǿ��Ŷȸߵ�,��Ҫ�Ҳ�
//-------------------------------------------------------------------------------------------------------------------*/
//void Left_Add_Line(int x1,int y1,int x2,int y2)//����,�����Ǳ߽�
//{
//    int i,max,a1,a2;
//    int hx;
//    if(x1>=MT9V03X_W-1)//��ʼ��λ��У�����ų�����Խ��Ŀ���
//       x1=MT9V03X_W-1;
//    else if(x1<=0)
//        x1=0;
//     if(y1>=MT9V03X_H-1)
//        y1=MT9V03X_H-1;
//     else if(y1<=0)
//        y1=0;
//     if(x2>=MT9V03X_W-1)
//        x2=MT9V03X_W-1;
//     else if(x2<=0)
//             x2=0;
//     if(y2>=MT9V03X_H-1)
//        y2=MT9V03X_H-1;
//     else if(y2<=0)
//             y2=0;
//    a1=y1;
//    a2=y2;
//    if(a1>a2)//���껥��
//    {
//        max=a1;
//        a1=a2;
//        a2=max;
//    }
//    for(i=a1;i<=a2;i++)//����б�ʲ��߼���
//    {
//        hx=(i-y1)*(x2-x1)/(y2-y1)+x1;
//        if(hx>=MT9V03X_W)
//            hx=MT9V03X_W;
//        else if(hx<=0)
//            hx=0;
//        Left_Line[i]=hx;
//    }
//}

///*-------------------------------------------------------------------------------------------------------------------
//  @brief     �Ҳ���
//  @param     ���ߵ���㣬�յ�
//  @return    null
//  Sample     Right_Add_Line(int x1,int y1,int x2,int y2);
//  @note      ����ֱ���Ǳ߽磬������ǿ��Ŷȸߵģ���Ҫ�Ҳ�
//-------------------------------------------------------------------------------------------------------------------*/
//void Right_Add_Line(int x1,int y1,int x2,int y2)//�Ҳ���,�����Ǳ߽�
//{
//    int i,max,a1,a2;
//    int hx;
//    if(x1>=MT9V03X_W-1)//��ʼ��λ��У�����ų�����Խ��Ŀ���
//       x1=MT9V03X_W-1;
//    else if(x1<=0)
//        x1=0;
//    if(y1>=MT9V03X_H-1)
//        y1=MT9V03X_H-1;
//    else if(y1<=0)
//        y1=0;
//    if(x2>=MT9V03X_W-1)
//        x2=MT9V03X_W-1;
//    else if(x2<=0)
//        x2=0;
//    if(y2>=MT9V03X_H-1)
//        y2=MT9V03X_H-1;
//    else if(y2<=0)
//         y2=0;
//    a1=y1;
//    a2=y2;
//    if(a1>a2)//���껥��
//    {
//        max=a1;
//        a1=a2;
//        a2=max;
//    }
//    for(i=a1;i<=a2;i++)//����б�ʲ��߼���
//    {
//        hx=(i-y1)*(x2-x1)/(y2-y1)+x1;
//        if(hx>=MT9V03X_W)
//            hx=MT9V03X_W;
//        else if(hx<=0)
//            hx=0;
//        Right_Line[i]=hx;
//    }
//}


///*-------------------------------------------------------------------------------------------------------------------
//  @brief     ������������յ㣬��ʮ��ʹ��
//  @param     �����ķ�Χ��㣬�յ�
//  @return    �޸�����ȫ�ֱ���
//             Right_Down_Find=0;
//             Left_Down_Find=0;
//  Sample     Find_Down_Point(int start,int end)
//  @note      ������֮��鿴��Ӧ�ı�����ע�⣬û�ҵ�ʱ��Ӧ��������0
//-------------------------------------------------------------------------------------------------------------------*/
//void Find_Down_Point(int start,int end)
//{
//    int i,t;
//    Right_Down_Find=0;
//    Left_Down_Find=0;
//    if(start<end)
//    {
//        t=start;
//        start=end;
//        end=t;
//    }
//    if(start>=MT9V03X_H-1-5)//����5�����ݲ��ȶ���������Ϊ�߽�����жϣ�����
//        start=MT9V03X_H-1-5;
//    if(end<=MT9V03X_H-Search_Stop_Line)
//        end=MT9V03X_H-Search_Stop_Line;
//    if(end<=5)
//       end=5;
//    for(i=start;i>=end;i--)
//    {
//        if(Left_Down_Find==0&&//ֻ�ҵ�һ�����������ĵ�
//           abs(Left_Line[i]-Left_Line[i+1])<=5&&//�ǵ����ֵ���Ը���
//           abs(Left_Line[i+1]-Left_Line[i+2])<=5&&
//           abs(Left_Line[i+2]-Left_Line[i+3])<=5&&
//              (Left_Line[i]-Left_Line[i-2])>=8&&
//              (Left_Line[i]-Left_Line[i-3])>=15&&
//              (Left_Line[i]-Left_Line[i-4])>=15)
//        {
//            Left_Down_Find=i;//��ȡ��������
//        }
//        if(Right_Down_Find==0&&//ֻ�ҵ�һ�����������ĵ�
//           abs(Right_Line[i]-Right_Line[i+1])<=5&&//�ǵ����ֵ���Ը���
//           abs(Right_Line[i+1]-Right_Line[i+2])<=5&&
//           abs(Right_Line[i+2]-Right_Line[i+3])<=5&&
//              (Right_Line[i]-Right_Line[i-2])<=-8&&
//              (Right_Line[i]-Right_Line[i-3])<=-15&&
//              (Right_Line[i]-Right_Line[i-4])<=-15)
//        {
//            Right_Down_Find=i;
//        }
//        if(Left_Down_Find!=0&&Right_Down_Find!=0)//�����ҵ����˳�
//        {
//            break;
//        }
//    }
//}

///*-------------------------------------------------------------------------------------------------------------------
//  @brief     ������������յ㣬��ʮ��ʹ��
//  @param     �����ķ�Χ��㣬�յ�
//  @return    �޸�����ȫ�ֱ���
//             Left_Up_Find=0;
//             Right_Up_Find=0;
//  Sample     Find_Up_Point(int start,int end)
//  @note      ������֮��鿴��Ӧ�ı�����ע�⣬û�ҵ�ʱ��Ӧ��������0
//-------------------------------------------------------------------------------------------------------------------*/
//void Find_Up_Point(int start,int end)
//{
//    int i,t;
//    Left_Up_Find=0;
//    Right_Up_Find=0;
//    if(start<end)
//    {
//        t=start;
//        start=end;
//        end=t;
//    }
//    if(end<=MT9V03X_H-Search_Stop_Line)
//        end=MT9V03X_H-Search_Stop_Line;
//    if(end<=5)//��ʱ����зǳ�����ҲҪ�������ֵ㣬��ֹ����Խ��
//        end=5;
//    if(start>=MT9V03X_H-1-5)//����5�����ݲ��ȶ���������Ϊ�߽�����жϣ�����
//        start=MT9V03X_H-1-5;
//    for(i=start;i>=end;i--)
//    {
//        if(Left_Up_Find==0&&//ֻ�ҵ�һ�����������ĵ�
//           abs(Left_Line[i]-Left_Line[i-1])<=5&&
//           abs(Left_Line[i-1]-Left_Line[i-2])<=5&&
//           abs(Left_Line[i-2]-Left_Line[i-3])<=5&&
//              (Left_Line[i]-Left_Line[i+2])>=8&&
//              (Left_Line[i]-Left_Line[i+3])>=15&&
//              (Left_Line[i]-Left_Line[i+4])>=15)
//        {
//            Left_Up_Find=i;//��ȡ��������
//        }
//        if(Right_Up_Find==0&&//ֻ�ҵ�һ�����������ĵ�
//           abs(Right_Line[i]-Right_Line[i-1])<=5&&//��������λ�ò��
//           abs(Right_Line[i-1]-Right_Line[i-2])<=5&&
//           abs(Right_Line[i-2]-Right_Line[i-3])<=5&&
//              (Right_Line[i]-Right_Line[i+2])<=-8&&
//              (Right_Line[i]-Right_Line[i+3])<=-15&&
//              (Right_Line[i]-Right_Line[i+4])<=-15)
//        {
//            Right_Up_Find=i;//��ȡ��������
//        }
//        if(Left_Up_Find!=0&&Right_Up_Find!=0)//���������ҵ��ͳ�ȥ
//        {
//            break;
//        }
//    }
//    if(abs(Right_Up_Find-Left_Up_Find)>=30)//����˺�ѹ�����Ϊ����
//    {
//        Right_Up_Find=0;
//        Left_Up_Find=0;
//    }
//}

///*-------------------------------------------------------------------------------------------------------------------
//  @brief     ʮ�ּ��
//  @param     null
//  @return    null
//  Sample     Cross_Detect(void);
//  @note      �����ĸ��յ��б����������ĸ��ǵ㣬�����ҵ��յ�ĸ��������Ƿ���
//-------------------------------------------------------------------------------------------------------------------*/
////void Cross_Detect()
////{
////    int down_search_start=0;//�µ�������ʼ��
////    Cross_Flag=0;
////    if(Island_State==0&&Ramp_Flag==0)//�뻷�����⿪
////    {
////        Left_Up_Find=0;
////        Right_Up_Find=0;
////        if(Both_Lost_Time>=10)//ʮ�ֱض���˫�߶��ߣ�����˫�߶��ߵ�������ٿ�ʼ�ҽǵ�
////        {
////            Find_Up_Point( MT9V03X_H-1, 0 );
////            if(Left_Up_Find==0&&Right_Up_Find==0)//ֻҪû��ͬʱ�ҵ������ϵ㣬ֱ�ӽ���
////            {
////                return;
////            }
////        }
////        if(Left_Up_Find!=0&&Right_Up_Find!=0)//�ҵ������ϵ㣬���ҵ�ʮ����
////        {
////            Cross_Flag=1;//��Ӧ��־λ�����ڸ�Ԫ�ػ����
////            down_search_start=Left_Up_Find>Right_Up_Find?Left_Up_Find:Right_Up_Find;//�������Ϲյ����꿿������Ϊ�µ����������
////            Find_Down_Point(MT9V03X_H-5,down_search_start+2);//���Ϲյ���2����Ϊ�µ�Ľ�ֹ��
////            if(Left_Down_Find<=Left_Up_Find)
////            {
////                Left_Down_Find=0;//�µ㲻���ܱ��ϵ㻹����
////            }
////            if(Right_Down_Find<=Right_Up_Find)
////            {
////                Right_Down_Find=0;//�µ㲻���ܱ��ϵ㻹����
////            }
////            if(Left_Down_Find!=0&&Right_Down_Find!=0)
////            {//�ĸ��㶼�ڣ��������ߣ����������Ȼ����
////                Left_Add_Line (Left_Line [Left_Up_Find ],Left_Up_Find ,Left_Line [Left_Down_Find ] ,Left_Down_Find);
////                Right_Add_Line(Right_Line[Right_Up_Find],Right_Up_Find,Right_Line[Right_Down_Find],Right_Down_Find);
////            }
////            else if(Left_Down_Find==0&&Right_Down_Find!=0)//11//����ʹ�õĶ���б�ʲ���
////            {//������                                     //01
////                Lengthen_Left_Boundry(Left_Up_Find-1,MT9V03X_H-1);
////                Right_Add_Line(Right_Line[Right_Up_Find],Right_Up_Find,Right_Line[Right_Down_Find],Right_Down_Find);
////            }
////            else if(Left_Down_Find!=0&&Right_Down_Find==0)//11
////            {//������                                     //10
////                Left_Add_Line (Left_Line [Left_Up_Find ],Left_Up_Find ,Left_Line [Left_Down_Find ] ,Left_Down_Find);
////                Lengthen_Right_Boundry(Right_Up_Find-1,MT9V03X_H-1);
////            }
////            else if(Left_Down_Find==0&&Right_Down_Find==0)//11
////            {//�����ϵ�                                   //00
////                Lengthen_Left_Boundry (Left_Up_Find-1,MT9V03X_H-1);
////                Lengthen_Right_Boundry(Right_Up_Find-1,MT9V03X_H-1);
////            }
////        }
////        else
////        {
////            Cross_Flag=0;
////        }
////    }
////    //�ǵ���ر�����debugʹ��
////    //ips200_showuint8(0,12,Cross_Flag);
//////    ips200_showuint8(0,13,Island_State);
//////    ips200_showuint8(50,12,Left_Up_Find);
//////    ips200_showuint8(100,12,Right_Up_Find);
//////    ips200_showuint8(50,13,Left_Down_Find);
//////    ips200_showuint8(100,13,Right_Down_Find);
////}


/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     ��ͼ���
////  @param     null
////  @return    null
////  Sample     Stop_Detect(void)
////  @note      ����к̣ܶ��߽粻������ͣ��
////-------------------------------------------------------------------------------------------------------------------*/
////void Img_Disappear_Detect(void)
////{
////    if(Barricade_Flag!=0||Stop_Flag!=0||Ramp_Flag!=0)//���ʱ��Ҫ�ص���ͣ��֮��ҲҪ�ص�
////    {
////        return;
////    }
////    int i=0;
////    uint8 black_line_count=0;
////    uint8 continuity_change_right_flag=0;
////    uint8 continuity_change_left_flag=0;
////    continuity_change_left_flag= Continuity_Change_Left (MT9V03X_H-1,MT9V03X_H-10);//�������ж�
////    continuity_change_right_flag=Continuity_Change_Right(MT9V03X_H-1,MT9V03X_H-10);

//////��ز�����debugʹ��
//////    ips200_show_int(0,16*10,Search_Stop_Line,3);
//////    ips200_show_int(0,16*11,(Longest_White_Column_Left[1]-Longest_White_Column_Right[1]),3);
//////    ips200_show_int(0,16*12,Road_Wide[(MT9V03X_H-Search_Stop_Line)+1],3);
//////    ips200_show_int(0,16*13,Road_Wide[(MT9V03X_H-Search_Stop_Line)+2],3);
//////    ips200_show_int(0,16*14,(Standard_Road_Wide[(MT9V03X_H-Search_Stop_Line)+2]-Road_Wide[(MT9V03X_H-Search_Stop_Line)+2]),3);
//////    ips200_show_int(0,16*15,(Standard_Road_Wide[(MT9V03X_H-Search_Stop_Line)+1]-Road_Wide[(MT9V03X_H-Search_Stop_Line)+1]),3);
//////    ips200_show_int(0,16*16,Boundry_Start_Left+Left_Lost_Time,3);
//////    ips200_show_int(0,16*17,Boundry_Start_Right+Right_Lost_Time,3);

////    if(continuity_change_left_flag!=0&&continuity_change_right_flag!=0&&Search_Stop_Line<=10)
////    {//����������������ֹ�зǳ���
////        Img_Disappear_Flag=1;//��Ϊ��ͼ
////        return;
////    }//�������ר��Ϊ������·׼���ģ�ͼ���������������ļ�⣬�и�������
////    else if(Search_Stop_Line<=45&&//��ֹ�бȽ϶�
////            (abs(Longest_White_Column_Left[1]-Longest_White_Column_Right[1])<15)&&//���������λ�ý�
////            (Road_Wide[(MT9V03X_H-Search_Stop_Line)+1]<=30)&&
////            (Road_Wide[(MT9V03X_H-Search_Stop_Line)+2]<=30)&&//��ֹ�����������С
////            (Standard_Road_Wide[(MT9V03X_H-Search_Stop_Line)+2]-Road_Wide[(MT9V03X_H-Search_Stop_Line)+2])>10&&
////            (Standard_Road_Wide[(MT9V03X_H-Search_Stop_Line)+1]-Road_Wide[(MT9V03X_H-Search_Stop_Line)+1])>10&&//��������漸��������ȱ�������
////            (Boundry_Start_Left +Left_Lost_Time ==MT9V03X_H-1)&&//������+��ʼ��==MT9V03X_H-1��˵�����Ķ�������ĵ㣬����û�ж���
////            (Boundry_Start_Right+Right_Lost_Time==MT9V03X_H-1)&&//������+��ʼ��==MT9V03X_H-1��˵�����Ķ�������ĵ�
////             Left_Lost_Time<10&&Right_Lost_Time<=10)//�������٣���֤������90����һ���������ȥ
////    {
////        Img_Disappear_Flag=1;
////        return;
////    }
////    else
////    {
////        for(i= MT9V03X_H-1; i>MT9V03X_H-1-10; i--)//ѡ������ȫ�ڣ���Ϊ��ͼ��
////        {
////            if(image_two_value[i][4]==0x0000&&image_two_value[i][5]==0x0000&&
////                    image_two_value[i][10]==0x0000&&image_two_value[i][15]==0x0000&&
////                    image_two_value[i][20]==0x0000&&image_two_value[i][25]==0x0000&&
////                    image_two_value[i][64]==0x0000&&image_two_value[i][65]==0x0000&&
////                    image_two_value[i][66]==0x0000&&image_two_value[i][67]==0x0000&&
////                    image_two_value[i][68]==0x0000&&image_two_value[i][69]==0x0000&&
////                    image_two_value[i][70]==0x0000&&image_two_value[i][75]==0x0000&&
////                    image_two_value[i][66]==0x0000&&image_two_value[i][67]==0x0000&&
////                    image_two_value[i][80]==0x0000&&image_two_value[i][90]==0x0000&&
////                    image_two_value[i][100]==0x0000&&image_two_value[i][110]==0x0000&&
////                    image_two_value[i][115]==0x0000&&image_two_value[i][120]==0x0000&&
////                    image_two_value[i][125]==0x0000&&image_two_value[i][130]==0x0000&&
////                    image_two_value[i][135]==0x0000&&image_two_value[i][136]==0x0000&&
////                    image_two_value[i][137]==0x0000&&image_two_value[i][138]==0x0000
////            )
////                black_line_count++;
////        }
////        if(black_line_count>=5)
////        {
////            Img_Disappear_Flag=1;
////        }
////    }
////}

/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     �µ����
////  @param     null
////  @return    null
////  Sample     Ramp_Detect();
////  @note      ���������ǰ���ж������������٣���ֹ�����治����
////-------------------------------------------------------------------------------------------------------------------*/
////void Ramp_Detect(void)
////{
////    int i=0;
////    int count=0;
////    if(Cross_Flag!=0||Island_State!=0||Barricade_Flag!=0)//����
////    {
////        return;
////    }

////    if(Search_Stop_Line>=66)//��ֹ�г�
////    {
////        for(i=MT9V03X_H-1;i>MT9V03X_H-Search_Stop_Line;i--)//�����������
////        {
////            if(Road_Wide[i]-Standard_Road_Wide[i]>10)//ͼ������ȱ�׼�����
////            {
////                count++;//���������
////            }
////        }

////    }
////    if(count>=10)//����������ĳһ��ֵ
////    {
////        dl1a_get_distance();//tof���
////        if(dl1a_distance_mm<500)//���⵽��ǰ���ж���
////        {
////            if(Ramp_Flag==0)//֮ǰ��0״̬��˵���Ǹս��µ�
////            {
////                Ramp_Flag=1;
////            }
////            else if(Ramp_Flag==3)//֮ǰ��3״̬��˵������������
////            {
////                Ramp_Flag=4;//��4֮��500ms�ڲ��У�����Ƕ�ʱ���жϴ���
////            }
////        }
////    }

////    if(Ramp_Flag!=0)//��������ʾ�µ�״̬
////    {
////        gpio_set_level(B11, 1);
////    }
////    else
////    {
////        gpio_set_level(B11, 0);
////    }

//////���������м�����debugʹ��
//////ips200_show_int(50,10*16,count,5);
////}

/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     �����߼��
////  @param     null
////  @return    null
////  Sample     Zebra_Stripes_Detect(void)
////  @note      �߽���ʼ���£�����нϳ���������ȹ�խ���Ҹ�����������
////-------------------------------------------------------------------------------------------------------------------*/
////void Zebra_Stripes_Detect(void)
////{
////    int i=0,j=0;
////    int change_count=0;//�������
////    int start_line=0;
////    int endl_ine=0;
////    int narrow_road_count=0;
////    if(Cross_Flag!=0||(1<=Ramp_Flag&&Ramp_Flag<=3)||Zebra_Stripes_Flag!=0||
////       Stop_Flag!=0 ||Electromagnet_Flag!=0||Barricade_Flag!=0)//Ԫ�ػ��⣬����ʮ�֣����ǣ������µ�������ͣ��
////    {
////        return;
////    }

////    ////����仯�а�����
////    if(Search_Stop_Line>=60&&
////       30<=Longest_White_Column_Left[1]&&Longest_White_Column_Left[1]<=MT9V03X_W-30&&
////       30<=Longest_White_Column_Right[1]&&Longest_White_Column_Right[1]<=MT9V03X_W-30&&
////       Boundry_Start_Left>=MT9V03X_H-15&&Boundry_Start_Right>=MT9V03X_H-15)
////    {//��ֹ�г���.����е�λ�������ĸ������߽���ʼ�㿿��
////        for(i=65;i>=20;i--)//�ڿ��µ��������Ѱ��������ȹ�խ�ĵط�
////        {
////            if((Standard_Road_Wide[i]-Road_Wide[i])>10)
////            {
////                narrow_road_count++;//���������խ������Ϊ�ǰ�����
////                if(narrow_road_count>=5)
////                {
////                    start_line=i;//��¼������Ⱥ�խ��λ��
////                    break;
////                }
////            }
////        }
////    }
////    if(start_line!=0)//���������խ������������խ��λ��Ϊ���ģ�����һ����Χ�������������
////    {
////        start_line=start_line+8;
////        endl_ine=start_line-15;
////        if(start_line>=MT9V03X_H-1)//�޷���������ֹ����Խ��
////        {
////            start_line=MT9V03X_H-1;
////        }
////        if(endl_ine<=0)//�޷���������ֹ����Խ��
////        {
////            endl_ine=0;
////        }
////        for(i=start_line;i>=endl_ine;i--)//�������������
////        {
////            for(j=Left_Line[i];j<=Right_Line[i];j++)
////            {
////                if(image_two_value[i][j+1]-image_two_value[i][j]!=0)
////                {
////                    change_count++;

////                }
////            }
////        }
//////        ips200_show_uint(0*16,100,change_count,5);//debugʹ�ã��鿴��������������Ӧ����
////    }
//// //�������򣬱�����bug��debugʹ��
//////        Draw_Line( Left_Line[start_line], start_line, Left_Line[endl_ine], endl_ine);
//////        Draw_Line( Left_Line[start_line], start_line, Right_Line[start_line], start_line);
//////        Draw_Line(Right_Line[endl_ine], endl_ine, Right_Line[start_line], start_line);
//////        Draw_Line(Right_Line[endl_ine], endl_ine, Left_Line[endl_ine], endl_ine);
//////        ips200_draw_line ( Left_Line[start_line], start_line, Left_Line[endl_ine], endl_ine, RGB565_RED);
//////        ips200_draw_line ( Left_Line[start_line], start_line, Right_Line[start_line], start_line, RGB565_RED);
//////        ips200_draw_line (Right_Line[endl_ine], endl_ine, Right_Line[start_line], start_line, RGB565_RED);
//////        ips200_draw_line (Right_Line[endl_ine], endl_ine, Left_Line[endl_ine], endl_ine, RGB565_RED);

////    if(change_count>30)//�������ĳһ��ֵ����Ϊ�ҵ��˰�����
////    {
////        Zebra_Stripes_Flag=1;
////    }
//////��ز�����ʾ��debugʹ��
//////    ips200_show_uint(0*16,50,narrow_road_count,5);
//////    ips200_show_uint(1*16,50,change_count,5);
////}

/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     ֱ�����
////  @param     null
////  @return    null
////  Sample     Straight_Detect()��
////  @note      ��������У��߽���ʼ�㣬������ʼ�㣬
////-------------------------------------------------------------------------------------------------------------------*/
////void Straight_Detect(void)
////{
////    Straight_Flag=0;
////    if(Search_Stop_Line>=65)//��ֹ�к�Զ
////    {
////        if(Boundry_Start_Left>=68&&Boundry_Start_Right>=65)//��ʼ�㿿��
////        {
////            if(-5<=Err&&Err<=5)//����С
////            {
////                Straight_Flag=1;//��Ϊ��ֱ��
////            }
////        }
////    }
////}

/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     ��·���
////  @param     null
////  @return    null
////  Sample     Break_Road_Detect()��
////  @note      ��������У��߽���ʼ�㣬������ʼ�㣬����Ҫ����л����Ѱ��
////-------------------------------------------------------------------------------------------------------------------*/
////void Break_Road_Detect(void)
////{
////    if(Barricade_Flag!=0||Ramp_Flag!=0)//���ʱ��Ҫ�ص���ͣ��֮��ҲҪ�ص�
////    {
////        return;
////    }
////    static uint8 break_road_state=0;

////    //ֱ�������·����ǰ�ж�
////    if(Search_Stop_Line<=45&&//�߽���ʼ�㿿�£���ֹ�в��������Ҷ��߶���
////       Boundry_Start_Left>=MT9V03X_H-10&&Boundry_Start_Right>=MT9V03X_H-10&&//�߽���ʼ�е�
////       Left_Lost_Time<=10&&Right_Lost_Time<=10&&
////       (Boundry_Start_Left +Left_Lost_Time ==MT9V03X_H-1)&&//������+��ʼ��==MT9V03X_H-1��˵�����Ķ�������ĵ㣬����û�ж���
////       (Boundry_Start_Right+Right_Lost_Time==MT9V03X_H-1)&&//������+��ʼ��==MT9V03X_H-1��˵�����Ķ�������ĵ�
////       Left_Line[(MT9V03X_H-Search_Stop_Line)+1]>=10&&Right_Line[(MT9V03X_H-Search_Stop_Line)+1]<=(MT9V03X_W-10)&&//��ֹ�����²��ܶ���
////       Left_Line[(MT9V03X_H-Search_Stop_Line)+2]>=10&&Right_Line[(MT9V03X_H-Search_Stop_Line)+2]<=(MT9V03X_W-10)&&
////       Left_Line[(MT9V03X_H-Search_Stop_Line)+3]>=10&&Right_Line[(MT9V03X_H-Search_Stop_Line)+3]<=(MT9V03X_W-10)&&
////       Left_Line[(MT9V03X_H-Search_Stop_Line)+4]>=10&&Right_Line[(MT9V03X_H-Search_Stop_Line)+4]<=(MT9V03X_W-10))
////    {
////        break_road_state=1;  //ͼ��ʧ+������������������·ģʽ
////        Electromagnet_Flag=1;//�л����Ѱ��
////    }
////    //��ͨ�������·
////    if(Electromagnet_Flag==0&&break_road_state==0&&Img_Disappear_Flag==1)
////    {//Ŀǰ״̬������ͷ�ܣ���·״̬��0��ͼ����
////        break_road_state=1;  //ͼ��ʧ+������������������·ģʽ
////        Electromagnet_Flag=1;//�л����Ѱ��
////    }

////    //�жϳ���·
////    if(break_road_state==1&&Search_Stop_Line>=50&&(Boundry_Start_Left>60||Boundry_Start_Right>60)&&(75<Longest_White_Column_Left[1]&&Longest_White_Column_Left[1]<105))
////    {//�ڶ�·״̬��������ֹ�иߣ��߽���ʼ�㿿��,����о���
////        break_road_state=0;//��ֹ�кܳ����߽���ʼ�㿿�£���Ϊ��������������ͷ
////        Electromagnet_Flag=0;
////        Img_Disappear_Flag=0;
////    }

////    //��ز�����debugʹ��
//////    ips200_show_float(0,16*6,Electromagnet_Flag,5,3);
//////    ips200_show_float(0,16*7,break_road_state,5,3);
//////    ips200_show_float(0,16*8,Img_Disappear_Flag,5,3);
////}
/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     ��߽��ӳ�
////  @param     �ӳ���ʼ�������ӳ���ĳ��
////  @return    null
////  Sample     Stop_Detect(void)
////  @note      ����ʼ��������5���㣬���б�ʣ������ӳ���ֱ��������
////-------------------------------------------------------------------------------------------------------------------*/
////void Lengthen_Left_Boundry(int start,int end)
////{
////    int i,t;
////    float k=0;
////    if(start>=MT9V03X_H-1)//��ʼ��λ��У�����ų�����Խ��Ŀ���
////        start=MT9V03X_H-1;
////    else if(start<=0)
////        start=0;
////    if(end>=MT9V03X_H-1)
////        end=MT9V03X_H-1;
////    else if(end<=0)
////        end=0;
////    if(end<start)//++���ʣ����껥��
////    {
////        t=end;
////        end=start;
////        start=t;
////    }

////    if(start<=5)//��Ϊ��Ҫ�ڿ�ʼ��������3���㣬������ʼ����ڿ��ϣ��������ӳ���ֻ��ֱ������
////    {
////         Left_Add_Line(Left_Line[start],start,Left_Line[end],end);
////    }

////    else
////    {
////        k=(float)(Left_Line[start]-Left_Line[start-4])/5.0;//�����k��1/б��
////        for(i=start;i<=end;i++)
////        {
////            Left_Line[i]=(int)(i-start)*k+Left_Line[start];//(x=(y-y1)*k+x1),��бʽ����
////            if(Left_Line[i]>=MT9V03X_W-1)
////            {
////                Left_Line[i]=MT9V03X_W-1;
////            }
////            else if(Left_Line[i]<=0)
////            {
////                Left_Line[i]=0;
////            }
////        }
////    }
////}

/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     ����߽��ӳ�
////  @param     �ӳ���ʼ�������ӳ���ĳ��
////  @return    null
////  Sample     Stop_Detect(void)
////  @note      ����ʼ��������3���㣬���б�ʣ������ӳ���ֱ��������
////-------------------------------------------------------------------------------------------------------------------*/
////void Lengthen_Right_Boundry(int start,int end)
////{
////    int i,t;
////    float k=0;
////    if(start>=MT9V03X_H-1)//��ʼ��λ��У�����ų�����Խ��Ŀ���
////        start=MT9V03X_H-1;
////    else if(start<=0)
////        start=0;
////    if(end>=MT9V03X_H-1)
////        end=MT9V03X_H-1;
////    else if(end<=0)
////        end=0;
////    if(end<start)//++���ʣ����껥��
////    {
////        t=end;
////        end=start;
////        start=t;
////    }

////    if(start<=5)//��Ϊ��Ҫ�ڿ�ʼ��������3���㣬������ʼ����ڿ��ϣ��������ӳ���ֻ��ֱ������
////    {
////        Right_Add_Line(Right_Line[start],start,Right_Line[end],end);
////    }
////    else
////    {
////        k=(float)(Right_Line[start]-Right_Line[start-4])/5.0;//�����k��1/б��
////        for(i=start;i<=end;i++)
////        {
////            Right_Line[i]=(int)(i-start)*k+Right_Line[start];//(x=(y-y1)*k+x1),��бʽ����
////            if(Right_Line[i]>=MT9V03X_W-1)
////            {
////                Right_Line[i]=MT9V03X_W-1;
////            }
////            else if(Right_Line[i]<=0)
////            {
////                Right_Line[i]=0;
////            }
////        }
////    }
////}


/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     ����
////  @param     ������ʼ�㣬�յ����꣬��һ�����Ϊ2�ĺ���
////  @return    null
////  Sample     Draw_Line(0, 0,MT9V03X_W-1,MT9V03X_H-1);
////             Draw_Line(MT9V03X_W-1, 0,0,MT9V03X_H-1);
////                                    ��һ�����
////  @note     ���ľ���һ���ߣ���Ҫ����ɨ��
////-------------------------------------------------------------------------------------------------------------------*/
////void Draw_Line(int startX, int startY, int endX, int endY)
////{
////    int i,x,y;
////    int start=0,end=0;
////    if(startX>=MT9V03X_W-1)//�޷�����
////        startX=MT9V03X_W-1;
////    else if(startX<=0)
////        startX=0;
////    if(startY>=MT9V03X_H-1)
////        startY=MT9V03X_H-1;
////    else if(startY<=0)
////        startY=0;
////    if(endX>=MT9V03X_W-1)
////        endX=MT9V03X_W-1;
////    else if(endX<=0)
////        endX=0;
////    if(endY>=MT9V03X_H-1)
////        endY=MT9V03X_H-1;
////    else if(endY<=0)
////        endY=0;
////    if(startX==endX)//һ������
////    {
////        if (startY > endY)//����
////        {
////            start=endY;
////            end=startY;
////        }
////        for (i = start; i <= end; i++)
////        {
////            if(i<=1)
////                i=1;
////            image_two_value[i][startX]=0x0000;
////            image_two_value[i-1][startX]=0x0000;
////        }
////    }
////    else if(startY == endY)//��һ������
////    {
////        if (startX > endX)//����
////        {
////            start=endX;
////            end=startX;
////        }
////        for (i = start; i <= end; i++)
////        {
////            if(startY<=1)
////                startY=1;
////            image_two_value[startY][i]=0x0000;
////            image_two_value[startY-1][i]=0x0000;
////        }
////    }
////    else //����������ˮƽ����ֱ��������������ǳ������
////    {
////        if(startY>endY)//��ʼ�����
////        {
////            start=endY;
////            end=startY;
////        }
////        else
////        {
////            start=startY;
////            end=endY;
////        }
////        for (i = start; i <= end; i++)//�����ߣ���֤ÿһ�ж��кڵ�
////        {
////            x =(int)(startX+(endX-startX)*(i-startY)/(endY-startY));//����ʽ����
////            if(x>=MT9V03X_W-1)
////                x=MT9V03X_W-1;
////            else if (x<=1)
////                x=1;
////            image_two_value[i][x] = 0x0000;
////            image_two_value[i][x-1] = 0x0000;
////        }
////        if(startX>endX)
////        {
////            start=endX;
////            end=startX;
////        }
////        else
////        {
////            start=startX;
////            end=endX;
////        }
////        for (i = start; i <= end; i++)//�����ߣ���֤ÿһ�ж��кڵ�
////        {

////            y =(int)(startY+(endY-startY)*(i-startX)/(endX-startX));//����ʽ����
////            if(y>=MT9V03X_H-1)
////                y=MT9V03X_H-1;
////            else if (y<=0)
////                y=0;
////            image_two_value[y][i] = 0x0000;
////        }
////    }
////}

/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     ��ϼ��
////  @param     null
////  @return    null
////  Sample
////  @note      ��ֹ�кܵͣ��߽���ʼ�㿿�£�tof�⵽ǰ���ж���
////-------------------------------------------------------------------------------------------------------------------*/
////void Barricade_Detect(void)
////{
////    if(Barricade_Flag!=0||Ramp_Flag!=0||Electromagnet_Flag!=0)
////    {//Ԫ�ػ���
////        return;
////    }
////    if(Boundry_Start_Left>=MT9V03X_H-10&&Boundry_Start_Right>=MT9V03X_H-10&&
////       Left_Lost_Time<=10&&Right_Lost_Time<=10&&Search_Stop_Line<=60&&
////       Left_Line[(MT9V03X_H-Search_Stop_Line)+1]>=10&&Right_Line[(MT9V03X_H-Search_Stop_Line)+1]<=(MT9V03X_W-10)&&//��ֹ�����²��ܶ���
////       Left_Line[(MT9V03X_H-Search_Stop_Line)+2]>=10&&Right_Line[(MT9V03X_H-Search_Stop_Line)+2]<=(MT9V03X_W-10)&&
////       Left_Line[(MT9V03X_H-Search_Stop_Line)+3]>=10&&Right_Line[(MT9V03X_H-Search_Stop_Line)+3]<=(MT9V03X_W-10)&&
////       Left_Line[(MT9V03X_H-Search_Stop_Line)+4]>=10&&Right_Line[(MT9V03X_H-Search_Stop_Line)+4]<=(MT9V03X_W-10))
////    {//�߽���ʼ�㿿�£���ֹ�в��������Ҷ��߶��٣���ֹ�����²�����
////        dl1a_get_distance();//���/
////        if(dl1a_distance_mm<1000)//���ǰ���ж�����������ģʽ
////        {
////            Barricade_Flag=1;
////        }
////    }
//////    ips200_show_uint(5*16,100,black_count,4);
//////    ips200_show_uint(5*16,120,dl1a_distance_mm,4);
////}

/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     Ԫ�ر�־λ��ʾ
////  @param     ��ֵ��ͼƬ����
////  @return    null
////  Sample     Barricade_Flag_Show(MT9V03X_W,image_two_value,Island_State);
////  @note      Ҫ��ͼƬ��ʾǰʹ�ã������־λ�ɸ���
////-------------------------------------------------------------------------------------------------------------------*/
////void Flag_Show_101(uint8 MT9V03XW,uint8(*InImg)[MT9V03XW],uint8 image_flag)
////{
////    for(uint8 H=1;H<8;H++)
////    {
////        for(uint8 W=MT9V03XW-20+1;W<MT9V03XW-20+8;W++)
////        {
////            switch (image_flag)
////            {
////                case 0:     *(*(InImg+H)+W)=Image_Flags[0][H][W-(MT9V03XW-20)];    break;
////                case 1:     *(*(InImg+H)+W)=Image_Flags[1][H][W-(MT9V03XW-20)];    break;
////                case 2:     *(*(InImg+H)+W)=Image_Flags[2][H][W-(MT9V03XW-20)];    break;
////                case 3:     *(*(InImg+H)+W)=Image_Flags[3][H][W-(MT9V03XW-20)];    break;
////                case 4:     *(*(InImg+H)+W)=Image_Flags[4][H][W-(MT9V03XW-20)];    break;
////                case 5:     *(*(InImg+H)+W)=Image_Flags[5][H][W-(MT9V03XW-20)];    break;
////                case 6:     *(*(InImg+H)+W)=Image_Flags[6][H][W-(MT9V03XW-20)];    break;
////                case 7:     *(*(InImg+H)+W)=Image_Flags[7][H][W-(MT9V03XW-20)];    break;
////                case 8:     *(*(InImg+H)+W)=Image_Flags[8][H][W-(MT9V03XW-20)];    break;
////                case 9:     *(*(InImg+H)+W)=Image_Flags[9][H][W-(MT9V03XW-20)];    break;
////                default:    break;
////            }
////        }
////    }
////}

/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     Ԫ�ر�־λ��ʾ
////  @param     ��ֵ��ͼƬ����
////  @return    null
////  Sample     Flag_Show_102(MT9V03X_W,image_two_value,Island_State);
////  @note      Ҫ��ͼƬ��ʾǰʹ�ã������־λ�ɸ���
////-------------------------------------------------------------------------------------------------------------------*/
////void Flag_Show_102(uint8 MT9V03XW,uint8(*InImg)[MT9V03XW],uint8 image_flag)
////{
////    for(uint8 H=1;H<8;H++)
////    {
////        for(uint8 W=MT9V03XW-10+1;W<MT9V03XW-10+8;W++)
////        {
////            switch (image_flag)
////            {
////                    case 0:     *(*(InImg+H)+W)=Image_Flags[0][H][W-(MT9V03XW-10)];    break;
////                    case 1:     *(*(InImg+H)+W)=Image_Flags[1][H][W-(MT9V03XW-10)];    break;
////                    case 2:     *(*(InImg+H)+W)=Image_Flags[2][H][W-(MT9V03XW-10)];    break;
////                    case 3:     *(*(InImg+H)+W)=Image_Flags[3][H][W-(MT9V03XW-10)];    break;
////                    case 4:     *(*(InImg+H)+W)=Image_Flags[4][H][W-(MT9V03XW-10)];    break;
////                    case 5:     *(*(InImg+H)+W)=Image_Flags[5][H][W-(MT9V03XW-10)];    break;
////                    case 6:     *(*(InImg+H)+W)=Image_Flags[6][H][W-(MT9V03XW-10)];    break;
////                    case 7:     *(*(InImg+H)+W)=Image_Flags[7][H][W-(MT9V03XW-10)];    break;
////                    case 8:     *(*(InImg+H)+W)=Image_Flags[8][H][W-(MT9V03XW-10)];    break;
////                    case 9:     *(*(InImg+H)+W)=Image_Flags[9][H][W-(MT9V03XW-10)];    break;
////                    default:    break;
////            }
////        }
////    }
////}
/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     Ԫ�ر�־λ��ʾ
////  @param     ��ֵ��ͼƬ����
////  @return    null
////  Sample     Flag_Show_201(MT9V03X_W,image_two_value,Island_State);
////  @note      �ڶ������һ������
////-------------------------------------------------------------------------------------------------------------------*/
////void Flag_Show_201(uint8 MT9V03XW,uint8(*InImg)[MT9V03XW],uint8 image_flag)
////{
////    for(uint8 H=10+1;H<10+8;H++)
////    {
////        for(uint8 W=MT9V03XW-20+1;W<MT9V03XW-20+8;W++)
////        {
////            switch (image_flag)
////            {
////                case 0:     *(*(InImg+H)+W)=Image_Flags[0][H-10][W-(MT9V03XW-20)];    break;
////                case 1:     *(*(InImg+H)+W)=Image_Flags[1][H-10][W-(MT9V03XW-20)];    break;
////                case 2:     *(*(InImg+H)+W)=Image_Flags[2][H-10][W-(MT9V03XW-20)];    break;
////                case 3:     *(*(InImg+H)+W)=Image_Flags[3][H-10][W-(MT9V03XW-20)];    break;
////                case 4:     *(*(InImg+H)+W)=Image_Flags[4][H-10][W-(MT9V03XW-20)];    break;
////                case 5:     *(*(InImg+H)+W)=Image_Flags[5][H-10][W-(MT9V03XW-20)];    break;
////                case 6:     *(*(InImg+H)+W)=Image_Flags[6][H-10][W-(MT9V03XW-20)];    break;
////                case 7:     *(*(InImg+H)+W)=Image_Flags[7][H-10][W-(MT9V03XW-20)];    break;
////                case 8:     *(*(InImg+H)+W)=Image_Flags[8][H-10][W-(MT9V03XW-20)];    break;
////                case 9:     *(*(InImg+H)+W)=Image_Flags[9][H-10][W-(MT9V03XW-20)];    break;
////                default:    break;
////            }
////        }
////    }
////}
/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     Ԫ�ر�־λ��ʾ
////  @param     ��ֵ��ͼƬ����
////  @return    null
////  Sample     Flag_Show_202(MT9V03X_W,image_two_value,Island_State);
////  @note      �ڶ��е����ڶ�������
////-------------------------------------------------------------------------------------------------------------------*/
////void Flag_Show_202(uint8 MT9V03XW,uint8(*InImg)[MT9V03XW],uint8 image_flag)
////{
////    for(uint8 H=10+1;H<10+8;H++)
////    {
////        for(uint8 W=MT9V03XW-10+1;W<MT9V03XW-10+8;W++)
////        {
////            switch (image_flag)
////            {
////                case 0:     *(*(InImg+H)+W)=Image_Flags[0][H-10][W-(MT9V03XW-10)];    break;
////                case 1:     *(*(InImg+H)+W)=Image_Flags[1][H-10][W-(MT9V03XW-10)];    break;
////                case 2:     *(*(InImg+H)+W)=Image_Flags[2][H-10][W-(MT9V03XW-10)];    break;
////                case 3:     *(*(InImg+H)+W)=Image_Flags[3][H-10][W-(MT9V03XW-10)];    break;
////                case 4:     *(*(InImg+H)+W)=Image_Flags[4][H-10][W-(MT9V03XW-10)];    break;
////                case 5:     *(*(InImg+H)+W)=Image_Flags[5][H-10][W-(MT9V03XW-10)];    break;
////                case 6:     *(*(InImg+H)+W)=Image_Flags[6][H-10][W-(MT9V03XW-10)];    break;
////                case 7:     *(*(InImg+H)+W)=Image_Flags[7][H-10][W-(MT9V03XW-10)];    break;
////                case 8:     *(*(InImg+H)+W)=Image_Flags[8][H-10][W-(MT9V03XW-10)];    break;
////                case 9:     *(*(InImg+H)+W)=Image_Flags[9][H-10][W-(MT9V03XW-10)];    break;
////                default:    break;
////            }
////        }
////    }
////}

/////*-------------------------------------------------------------------------------------------------------------------
////  @brief     �������ж�
////  @param     null
////  @return    null
////  Sample     Zebra_Detect();
////  @note      һ�����뷨����������У�ÿһ�е�����п��Կ��ɴ������ϵ������߽磬
////                                           ������������ʱ�����нϴ������˺�ѣ�һ�������߻�������˺��
////                                           ��ô�����������������Ƿ���ʶ��������أ��������£��ҾͲ�ȥ�����ˣ�����λ�Ĳ��Խ����
////-------------------------------------------------------------------------------------------------------------------*/
////void Zebra_Detect(void)
////{
////    int j=0;
////    int count=0;
////    //ǰ���Ԫ�ػ����λ���в�ȫ
////    if(Search_Stop_Line>=60)//��Ұ�ܳ�
////    {
////        for(j=10;j<=MT9V03X_W-10;j++)
////        {
////            if(abs(White_Column[j]-White_Column[j+1])>=30)
////            {
////                count++;
////            }
////        }
////    }
////    if(count>=8)
////    {
////        Zebra_Stripes_Flag=1;
////    }
////}
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