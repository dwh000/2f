#ifndef __disp_h
	#define __disp_h
#include "public.h"


//数码管字符宏定义**************************************************************
#define SYM_A	10
#define SYM_B	11
#define SYM_C	12
#define SYM_c	13
#define SYM_D	14
#define SYM_E	15
#define SYM_F	16
#define SYM_H	17
#define SYM_h	18
#define SYM_L	19
#define SYM_n	20
#define SYM_N	21
#define SYM_O	22
#define SYM_P	23
#define SYM_R	24
#define SYM_T	25
#define SYM_U	26
#define SYM__	27	
#define SYM_ 	28	
#define SYM__1	29
#define SYM_S	5
#define SYM___	30
#define SYM_G	9
#define SYM_I	31


void run_disp(s32bit disp_data);
void weight_disp(s32bit disp_data);
void flash_disp(s32bit disp_data);
void disp_symbol(u8bit disp_code);
void disp_int(u16bit disp_data);
void disp_seg(u8bit seg_code,u8bit bit_addr);

#define DispZeroClr()		disp_seg(seg_sym[SYM_C],BIT5)	//清零点显示清零操作
#define DispZeroLoc()		disp_seg(seg_sym[SYM_c],BIT5)	//清零点显示无清零操作
#define DispZeroRst()		disp_seg(seg_sym[SYM_],BIT5)	//清零点消除显示
#define DispDpERRSet()		disp_seg(seg_sym[SYM_E],BIT5)	//清零点消除显示
#define Disp50kgLoc()		disp_seg(seg_dot[SYM_],BIT5)	//50公斤点显示
#define Disp50kgRst()		disp_seg(seg_sym[SYM_],BIT5)	//50公斤点消除显示
#define	DispDropEn()		disp_seg(seg_dot[SYM_],BIT5)	//掉袋使能显示
#define DispDropDis()		disp_seg(seg_sym[SYM_],BIT5)	//掉袋使能隐藏显示
#define	DispDropLoc()		disp_seg(seg_sym[SYM_D],BIT5)	//掉袋点显示	
#define DispDropRst()		disp_seg(seg_sym[SYM_],BIT5)	//掉袋点隐藏显示
#define DispBagDetLoc()		disp_seg(seg_dot[SYM_],BIT4)	//插袋检测显示
#define DispBagDetRst()		disp_seg(seg_sym[SYM_],BIT4)	//插袋检测隐藏显示
#define DispDropEnDropLoc()	disp_seg(seg_sym[SYM_D]&seg_dot[SYM_],BIT5)
#define DispDropEnZeroClr()	disp_seg(seg_sym[SYM_C]&seg_dot[SYM_],BIT5)
#define DispDropEnZeroLoc()	disp_seg(seg_sym[SYM_c]&seg_dot[SYM_],BIT5)
#endif