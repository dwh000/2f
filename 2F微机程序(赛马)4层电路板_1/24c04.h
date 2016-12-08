#ifndef __24c04_h
    #define __24c04_h

#include    "public.h"
#define SP_WEIGHT_ADDR          0
#define TW_ADDR                 2                           //tare weight
#define FILTER_ADDR             6
#define SF_WEIGHT_ADDR          7                           //size flow	SF_WEIGHT_ADDR
#define SF_SWITCH_ADDR          9
#define DROP_WEIGHT_ADDR        10
#define OL_TRACK_SW_ADDR        12
#define TRACK_BAGS_ADDR         13
#define R_WEIGHT_ADDR           14
#define CL_CORRECT_SW_ADDR      16
#define WEIGHT_CORRECT_ADDR     17
#define ARRIVAL_TIME_ADDR       19
#define COUTER_SW_ADDR          20
#define CELL_SPAN_ADDR          21
#define COUNTERWEIGHT_ADDR      25
#define SCALE_OUTPUT_ADDR       32
#define COMMADDR_ADDR           36
#define DP_SW_ADDR              37
#define START_1ST_ADDR          0XFF
/*eeprom读取数据程序*********************************************
形参:
	ptr_data	:数据区的首地址
	addr		:读取的目标地址
	cnt			:要读取的数据的个数.
返回值:
******************************************************************/		
u8bit eeprom_read(u8bit *ptr_data,u8bit addr,u8bit cnt);


/*eeprom保存数据程序*********************************************
形参:
	ptr_data	:数据区的首地址
	addr		:保存的目标地址
	cnt			:要保存的数据的个数.
返回值:
******************************************************************/
u8bit eeprom_write(u8bit *ptr_data,u8bit addr,u8bit cnt)reentrant;

//IIC总线的初始化程序
void iic_init(void);

u8bit ee_write(u8bit *ptr_data,u8bit addr,u8bit cnt) reentrant;
#endif

