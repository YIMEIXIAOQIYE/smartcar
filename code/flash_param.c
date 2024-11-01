//#include "flash_param.h"
//#include "zf_driver_flash.h"
//#include "zf_common_headfile.h"
////
//#define PARAM_FLASH_SECTOR        (FLASH_PAGE_NUM-1)

////
//#define PARAM_FLASH_SECTOR_PAGE   FLASH_PAGE_0

//float thres=140;                 // 二值化阈值，主要用于找起始点(边线使用自适应阈值，不使用该阈值)
//float block_size=7;            // 自适应阈值的block大小
//float clip_value=2;            // 自适应阈值的阈值裁减量

//// flash一个page有256个字节，将最后4个字节作为加和校验，其余字节用于放置参数

//// 将flash的数据一次性读取出来，再进行校验位的检查
//uint32_t flash_buffer[64];

//// 实际程序参数的存放起始地址
//uint32_t * const flash_data = (void*)0x20200000;

//// 显式规定参数的地址，保证参数放置在0x20200000~0x20200100这片内存区域。便于保存到flash以及从flash中加载
////__attribute__((section(".ARM.__at_0x20200000"))) float pictureP = 0.15;
////__attribute__((section(".ARM.__at_0x20200004"))) float pictureI = 0;
////__attribute__((section(".ARM.__at_0x20200008"))) float pictureD = 0.03;
//__attribute__((section(".ARM.__at_0x2020000C"))) float begin_x = 32;
//__attribute__((section(".ARM.__at_0x20200010"))) float begin_y = 167;
//__attribute__((section(".ARM.__at_0x20200014"))) float line_blur_kernel = 7;
//__attribute__((section(".ARM.__at_0x20200018"))) float pixel_per_meter = 102;
//__attribute__((section(".ARM.__at_0x2020001C"))) float sample_dist = 0.02;
//__attribute__((section(".ARM.__at_0x20200020"))) float angle_dist = 0.2;
//__attribute__((section(".ARM.__at_0x20200024"))) float far_rate = 0.5;
//__attribute__((section(".ARM.__at_0x20200028"))) float aim_distance = 0.68;
//__attribute__((section(".ARM.__at_0x2020002C"))) bool adc_cross = false;

////__attribute__((section(".ARM.__at_0x20200030"))) float MileageKx=0.01079f;
////__attribute__((section(".ARM.__at_0x20200034"))) float MileageKy=0.00999f;
////__attribute__((section(".ARM.__at_0x20200038"))) float Angel_KP = 0.35f;
////__attribute__((section(".ARM.__at_0x2020003C"))) float Angel_KD = 1.5f;
////__attribute__((section(".ARM.__at_0x20200040")))float Angel_KI = 0;

//////记录PID系数
////__attribute__((section(".ARM.__at_0x20200044"))) float Position_KP =200;
////__attribute__((section(".ARM.__at_0x20200048"))) float Position_KI =20;
////__attribute__((section(".ARM.__at_0x2020004C"))) float Position_KD =5;


////float pictureP=0.15f,pictureI=0,pictureD=0.03f;



//// 最后4个字节放校验值
//__attribute__((section(".ARM.__at_0x202000FC"))) static uint32_t check = 0;


//// 初始化flash，并将整个page的数据一次性读取出来
//void flash_param_init(){
//    flash_init();
//    flash_read_page(PARAM_FLASH_SECTOR, PARAM_FLASH_SECTOR_PAGE, (uint32*)flash_buffer, 64);
//}

//// 检查校验值，用于判断flash是否存放了数据
//bool flash_param_check(){
//    uint32_t check_value = 0xA5;    // magic number作为初值。避免全片擦除后意外通过校验。
//    for(int i=0; i<63; i++){
//        check_value += flash_buffer[i];
//    }
//    return check_value == flash_buffer[63];
//}

//// 加载flash参数。即将flash的数据拷贝到参数对应的内存位置
//void flash_param_load(){
//    memcpy(flash_data, flash_buffer, 256);
//}

//// 写flash参数。
//void flash_param_write(){
//    check = 0;
//    for(int i=0; i<63; i++){
//        check += flash_data[i];
//    }
//    // 先擦除再写入，否则写入会失败
//    flash_erase_page (PARAM_FLASH_SECTOR,PARAM_FLASH_SECTOR_PAGE);
//    flash_write_page(PARAM_FLASH_SECTOR, PARAM_FLASH_SECTOR_PAGE, (uint32*)flash_data, 64);
//}
