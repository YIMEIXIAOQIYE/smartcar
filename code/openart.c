#include "zf_common_headfile.h"
#include "zf_driver_uart.h"
#include "openart.h"
#define locate_sz 12   
#define expect_pic_x 173-5   
#define expect_pic_y 128 


uint8 uart1_rx_buffer[40]={0};
lpuart_transfer_t   uart1_receivexfer;
lpuart_handle_t     uart1_g_lpuartHandle;

uint8 uart4_rx_buffer[40]={0};;
lpuart_transfer_t   uart4_receivexfer;
lpuart_handle_t     uart4_g_lpuartHandle;

uint8* uart_data1=NULL;
uint8* uart_data4=NULL;

uint8 get_location=0;
uint8 get_data = 0;



uint8 uart_get_data[64];                                                        // ���ڽ������ݻ�����
uint8 fifo_get_data[64];                                                        // fifo �������������

  


fifo_struct uart_data_fifo;
fifo_struct uart_location_fifo;

uint8 gpio_status;

fifo_struct uart_data_fifo;


fifo_struct uart_location_fifo;

uint8 pic_class;
uint8 sort_flag;
uint8 carry_flag;
uint8 get_sort;

uint8 pic_x=expect_pic_x,pic_y=expect_pic_y;
uint8 correct_flag=0;//λ�ý�����־λ
uint8 correct_no_sign=1;//û�н��ܵ������ź�

float now_postion_x=0,now_postion_y=0;
float expect_postion_x=0,expect_postion_y=0;


uint8 boundary_xy[10]={0};//ͼƬ�߽�����
uint8 boundaryData_count=0;


uint8 pic_count=0;

uint8 object_xy[10]={0};
uint8 objectData_count=0;

uint8 pic_xy[10]={0};//ͼƬ���ĵ�����
uint8 picData_count=0;


uint8 openart_MapFlag_go=0;
uint8 openart_MapFlag1=0;
uint8 openart_CorrectFlag=0;
uint8 openart_SortFlag=0;
uint8 openart_ObjectFlag=0;
uint8 openart_BoundaryFlag=0;


uint8 boundary_angle=0;
uint8 boundary_x=0;
uint8 boundary_y=0;


uint8 agreement_flag=0;
uint8 agreement_flag1=0;
uint8 agreement_flag2=0;

void art1_communicate_agreement()
{
//	uint8 data_swap=0;
//	uint8 vaild_data=0;

//	//У�������Ƿ���ȷ���粻��ȷ���е���
//	if(uart_data1[0]==0xff&&uart_data1[3]==0xfe) 
//	{
//		agreement_flag=1;
//	}
////	else agreement_flag=0;
////	
////	if(agreement_flag==0)
////	{
////		for(uint8 i=0;i<3;i++)
////		{
////			data_swap=uart_data1[i];
////			uart_data1[i]=uart_data1[i+1];
////			uart_data1[i+1]=data_swap;	
////		} 
////	}
//	
//	//��������ȷ������һ������
//	if(agreement_flag==1)
//	{
//		vaild_data=uart_data1[0];
//		//��⵽λ�ý�����־λ����ȡͼƬ����x��y�����
//		if(vaild_data==0x7a) openart_CorrectFlag=1;//204	
//		//��ȡλ�ý�������
//		if(openart_CorrectFlag==1)
//		{
//			if(vaild_data!=0x7a&&vaild_data!=0x77)
//			{
//				pic_xy[picData_count]=vaild_data;
//				picData_count++;
//			} 
//			if(vaild_data==0x77) 
//			{
//				if(picData_count==3) openart_CorrectFlag=2;//ֻ�е����һ��xy����ʱ���Ż����־λ��ֵ
//				picData_count=0;
//			}
//		}
//		//����ͼƬ���ĵ�����
//		if(openart_CorrectFlag==2)
//		{ 
//			correct_no_sign=0;
//			pic_y=pic_xy[1];
//			pic_x=pic_xy[2];
//			if(pic_y==0&&pic_x==0)
//			{
//				//��û�н��ܵ����ݣ�
//				pic_y=expect_pic_y;
//				pic_x=expect_pic_x;	
//				correct_no_sign=1;				
//			}
//			openart_CorrectFlag=0;
//		}
//	}		
uint8 data_swap=0;
	uint8 vaild_data=0;

	//У�������Ƿ���ȷ���粻��ȷ���е���
	if(uart_data1[0]==0xff&&uart_data1[2]==0xfe) 
	{
		agreement_flag1=1;
	}
	else agreement_flag1=0;
	
	if(agreement_flag1==0)
	{
		for(uint8 i=0;i<3-1;i++)
		{
			data_swap=uart_data1[i];
		    uart_data1[i]=uart_data1[i+1];
			uart_data1[i+1]=data_swap;	
		} 
	}
	
	//��������ȷ������һ������
	if(agreement_flag1==1)
	{
		vaild_data=uart_data1[1];
		
		//��⵽λ�ý�����־λ����ȡͼƬ����x��y�����
		if(vaild_data==0xcc) openart_CorrectFlag=1;
		if(vaild_data==0x99) openart_BoundaryFlag=1;
		
		//��ȡλ�ý�������
		if(openart_CorrectFlag==1)
		{
			if(vaild_data!=0xcc&&vaild_data!=0xbb)
			{
				pic_xy[picData_count]=vaild_data;
				picData_count++;
			} 
			if(vaild_data==0xbb) 
			{
				if(picData_count==2) openart_CorrectFlag=2;//ֻ�е����һ��xy����ʱ���Ż����־λ��ֵ
				picData_count=0;
			}
		}
		//����ͼƬ���ĵ�����
		if(openart_CorrectFlag==2)
		{ 
			correct_no_sign=0;
			pic_y=pic_xy[0];
			pic_x=pic_xy[1];
			
			if(pic_y==0&&pic_x==0)
			{
				//��û�н��ܵ����ݣ�
				pic_y=expect_pic_y;
				pic_x=expect_pic_x;	
				correct_no_sign=1;				
			}
			openart_CorrectFlag=0;
		}

		

		
		//��ȡ�߽�Ƕ�
		if(openart_BoundaryFlag==1)
		{
			if(vaild_data!=0x99&&vaild_data!=0xbb)
			{
				boundary_xy[boundaryData_count]=vaild_data;
				boundaryData_count++;
			}
			if(vaild_data==0xbb)
			{
				if(boundaryData_count==3) openart_BoundaryFlag=2;
				boundaryData_count=0;			
			}
		}
		if(openart_BoundaryFlag==2)
		{ 
			boundary_angle=boundary_xy[0];
			boundary_y=boundary_xy[1];
			boundary_x=boundary_xy[2];
			
			openart_BoundaryFlag=0;
		}

		
		
		
		
		
	}
}
void art4_communicate_agreement()
{
		uint8 data_swap=0;
		uint8 vaild_data=0;

		//У�������Ƿ���ȷ���粻��ȷ���е���
		if(uart_data4[0]==0xff&&uart_data4[2]==0xfe) 
		{
			agreement_flag=1;
		}
		else agreement_flag=0;
		
		if(agreement_flag==0)
		{
			for(uint8 i=0;i<3-1;i++)
			{
				data_swap=uart_data1[i];
				uart_data1[i]=uart_data1[i+1];
				uart_data1[i+1]=data_swap;	
			} 
		}	
}
void uart4_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        uart_data4 = uart4_rx_buffer;//��example_rx_buffer�ĵ�ַ����uart_data
				
			
				//�����˼ǵ�ɾ��
    }
    
    handle->rxDataSize = uart4_receivexfer.dataSize;  //��ԭ����������
    handle->rxData = uart4_receivexfer.data;          //��ԭ��������ַ
}

void uart1_uart_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
    if(kStatus_LPUART_RxIdle == status)
    {
        uart_data1 = uart1_rx_buffer;//��example_rx_buffer�ĵ�ַ����uart_data	
				
//			 art1_communicate_agreement();
			
    }
    
    handle->rxDataSize = uart1_receivexfer.dataSize;  //��ԭ����������
    handle->rxData = uart1_receivexfer.data;          //��ԭ��������ַ
}

void openart_init()
{
	fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // ��ʼ�� fifo ���ػ�����
	uart_init (UART_1, 115200,UART1_TX_B12,UART1_RX_B13);	
	NVIC_SetPriority(LPUART1_IRQn,0);         //���ô����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
	uart_rx_interrupt(UART_1,1);     
	//���ô��ڽ��յĻ�����������������
	uart1_receivexfer.dataSize =4;
	uart1_receivexfer.data =(uint8 *) &uart1_rx_buffer;
	//�����жϺ����������
	uart_set_handle(UART_1, &uart1_g_lpuartHandle, uart1_uart_callback, NULL, 0, uart1_receivexfer.data, 4); 

	

	//����UART8���ڣ����ߴ��ڣ�WIFI
	//��ʼ��UART8����
	uart_init (UART_4, 115200,UART4_TX_C16,UART4_RX_C17);	
	NVIC_SetPriority(LPUART4_IRQn,1);         //���ô����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ��
	uart_rx_interrupt(UART_4,1);     
	//���ô��ڽ��յĻ�����������������
	uart4_receivexfer.dataSize =7;
	uart4_receivexfer.data =(uint8 *) &uart4_rx_buffer;
	//�����жϺ����������
	uart_set_handle(UART_4, &uart4_g_lpuartHandle, uart4_uart_callback, NULL, 0, uart4_receivexfer.data, 7); 

}
void uart1_rx_interrupt_handler (void)
{ 
//    get_data = uart_read_byte(UART_INDEX);                                      // �������� while �ȴ�ʽ ���������ж�ʹ��
    uart_query_byte(UART_1, &get_location);                                     // �������� ��ѯʽ �����ݻ᷵�� TRUE û�����ݻ᷵�� FALSE
		fifo_write_buffer(&uart_location_fifo, &get_location, 1); 
}
void uart4_rx_interrupt_handler (void)
{ 
//    get_data = uart_read_byte(UART_INDEX);                                      // �������� while �ȴ�ʽ ���������ж�ʹ��
    uart_query_byte(UART_4, &get_data);                                     // �������� ��ѯʽ �����ݻ᷵�� TRUE û�����ݻ᷵�� FALSE
		fifo_write_buffer(&uart_data_fifo, &get_data, 1); 
}