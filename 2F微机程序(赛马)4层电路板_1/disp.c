/***********************************************************************************
*文件名: disp.c
*作  者: 王文辉
*单  位: 唐山智能电子有限公司
*日  期: 2012-9-21
*版  本: 实验版本
*功能描述: 显示相关的函数,包含了端口定时,显示字符定时及显示输出.
***********************************************************************************/
#include "disp.h"
#include "timer.h"
//宏定义******************************************************************************
#define UPPERLIMIT		65180
#define LOWERLIMIT		-5000
#define DISP_ADDR		P6				//数码显示段码输出端口定义
#define DIGIT_ADDR		P7				//数码显示位控制端口定义
//显示位控制端口位定义***************************************************************
sbit DIGIT1_ADDR = DIGIT_ADDR^0;
sbit DIGIT2_ADDR = DIGIT_ADDR^1;
sbit DIGIT3_ADDR = DIGIT_ADDR^2;
sbit DIGIT4_ADDR = DIGIT_ADDR^3;
sbit DIGIT5_ADDR = DIGIT_ADDR^4;
sbit DIGIT6_ADDR = DIGIT_ADDR^5; 
//段码译码数组定义,存放于程序区******************************************************
/*0,1,2,3,4,5,6,7,8,9,A,b,C,c,d,E,F,H,h,L,n,N,o,P,r,t,U,-, ,0x47,0xa3,-1,_*/
u8bit code seg_sym[40] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,
						  0x88,0x83,0xC6,0xA7,0xA1,0x86,0x8E,0x89,0x8B,0xC7,
						  0xAB,0xC8,0xA3,0x8C,0xAF,0x87,0xC1,0xBF,0xff,0xb9,
						  0xf7,0XEF};
u8bit code seg_dot[40] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,
						  0x88,0x83,0xC6,0x27,0xA1,0x86,0x8E,0x89,0x8B,0xC7,
						  0xAB,0xC8,0xA3,0x8C,0xAF,0x87,0xC1,0xBF,0x7f,0xb9,
						  0xf7,0XEF};

/*断码显示函数*****************************************************************
形参:
	seg_code	:要显示的段码
	bit_addr	:显示段码的位,从高到低为0x20,0x10,0x08,0x04,0x02,0x01;
返回值:
*******************************************************************************/	
void disp_seg(u8bit seg_code,u8bit bit_addr)
{
	SFRPAGE = CONFIG_PAGE;
	DIGIT_ADDR |= bit_addr;
	DISP_ADDR = seg_code; 
	DIGIT_ADDR &= 0Xc0;
}
	
/*称重运行时的显示函数*********************************************************
形参:
	disp_data	:需要显示的数据,实际显示时,只显示两位小数,最低位不显示.
返回值:
*******************************************************************************/	
void run_disp(s32bit disp_data)
{
	bit sign_flag;
	u8bit xdata n,disp[6];
	
	if(disp_data > UPPERLIMIT){				//超上限报警,返回
		disp_symbol(OE_H);
		return;
	}
	if(disp_data < LOWERLIMIT){				//超下限报警,返回
		disp_symbol(OE_L);
		return;
	}
	if(disp_data >= 0)	sign_flag = 0;		//disp_data为正数	
	else{									//disp_data为负数
		sign_flag = 1;
		disp_data = 0 - disp_data;	
	}	
	for(n = 0;n<6;n++){						//求数据每一位的值
		disp[n] = disp_data%10;
		disp_data /= 10;
	}
	if(sign_flag == 0){						//处理第4位显示的内容
		if(disp[4] == 0)	disp[4] = SYM_ ;//' '
	}
	else{
		if(sign_flag == 1)	disp[4] = SYM__;//'-'
		else{
			disp_symbol(E06);				//Err_6
			return;			
		}
	}
	disp_seg(seg_sym[disp[1]],BIT0);			//显示百分位
	disp_seg(seg_sym[disp[2]],BIT1);			//显示十分位
	disp_seg(seg_dot[disp[3]],BIT2);			//显示个位
	disp_seg(seg_sym[disp[4]],BIT3);			//显示十位					
	return;
}
	
/*标定时的显示函数*************************************************************
形参:
	disp_data	:需要显示的数据,显示三位小数
返回值:
*******************************************************************************/
void weight_disp(s32bit disp_data)
	{
	bit sign_flag;
	u8bit xdata n,disp[6];
	
	DIGIT_ADDR |= 0X3F;
	DISP_ADDR = 0XFF;
	DIGIT_ADDR &= 0XC0;						//显示清屏
	if(disp_data >= 0)	sign_flag = 0;		//disp_data为正数	
	else									//disp_data为负数
		{
		sign_flag = 1;
		disp_data = 0 - disp_data;	
		}
	for(n = 0;n<6;n++)						//求数据每一位的值
		{
		disp[n] = disp_data%10;
		disp_data /= 10;
		}
	if(sign_flag == 0)
		{
		if(disp[5] == 0)
			{
			if(disp[4] == 0)	disp[4] = SYM_;		//' '
			disp[5] = SYM_;							//' '		
			}
		}
	else
		{
		if(sign_flag == 1)
			{
			if(disp[5] == 0)
				{
				if(disp[4] == 0)
					{					//W3
					disp[4] = SYM__;	//'-'
					disp[5] = SYM_;		//' '
					}
				else	disp[5] = SYM__;//W6 '-'		
				}
			else	disp[5] = SYM__1;		//W5 '-1'							
			}
		else
			{
			disp_symbol(E06);
			return;
			}
		}
	disp_seg(seg_sym[disp[0]],BIT0);			//显示千分位
	disp_seg(seg_sym[disp[1]],BIT1);			//显示百分位
	disp_seg(seg_sym[disp[2]],BIT2);			//显示十分位
	disp_seg(seg_dot[disp[3]],BIT3);			//显示个位
	disp_seg(seg_sym[disp[4]],BIT4);			//显示十位
	disp_seg(seg_sym[disp[5]],BIT5);			//显示百位	
	delay_ms(1);
	return;	
	}
/*字符显示函数*****************************************************************
形参:
	disp_code	:显示字符的代码
返回值:
*******************************************************************************/
void disp_symbol(u8bit disp_code)
	{
	u8bit xdata disp[6] = {28,28,28,28,28,28};	
		switch(disp_code)
			{
			case OE_H:
				disp[3] = SYM_O;
				disp[2] = SYM_L;			//oL
				break;
			case OE_L:
				disp[3] = SYM__1;			//-1
				break;
			case CLR_ALL:
				break;
			case NO_OPT:
				return;
			case SET:
				disp[5] = SYM_S;
				disp[4] = SYM_E;
				disp[3] = SYM_T;
				break;
			case CAL:
				disp[5] = SYM_C;
				disp[4] = SYM_A;
				disp[3] = SYM_L;				
				break;
			case FUNC:
				disp[5] = SYM_F;
				disp[4] = SYM_U;
				disp[3] = SYM_N;
				disp[2] = SYM_C;
				break;
			case TEST:
				disp[5] = SYM_T;
				disp[4] = SYM_E;
				disp[3] = SYM_S;
				disp[2] = SYM_T;
				break;
			case DPSET:
				disp[5] = SYM_D;
				disp[4] = SYM_P;
				disp[3] = SYM_S;
				disp[2] = SYM_E;
				disp[1] = SYM_T;
				break;
			case VER:
				disp[5] = SYM_U;
				disp[4] = SYM_E;
				disp[3] = SYM_R;
				break;	
			case GOOD:
				disp[5] = SYM_G;
				disp[4] = SYM_O;
				disp[3] = SYM_O;
				disp[2] = SYM_D;
				break;
			case OFF:
				disp[2] = SYM_O;
				disp[1] = SYM_F;
				disp[0] = SYM_F;
				break;
			case ON:
				disp[1] = SYM_O;
				disp[0] = SYM_N;
				break;
			case MC01:
				disp[5] = SYM_S;
				disp[4] = SYM_P;
				disp[3] = SYM_A;
				disp[2] = SYM_N;
				break;
			case MC02:
				disp[5] = SYM_T;
				disp[4] = SYM_A;
				disp[3] = SYM_R;
				disp[2] = SYM_E;
				break;
			case MC03:
				disp[5] = SYM_G;
				disp[4] = SYM_A;
				disp[3] = SYM_I;
				disp[2] = SYM_N;
				break;
			case ERR_CL:
				disp[5] = SYM_E;
				disp[4] = SYM_R;
				disp[3] = SYM_R;
				disp[2] = SYM__;
				disp[1] = SYM_C;
				disp[0] = SYM_L;
				break;
			case ERR_HL:
				disp[5] = SYM_E;
				disp[4] = SYM_R;
				disp[3] = SYM_R;
				disp[2] = SYM__;
				disp[1] = SYM_H;
				disp[0] = SYM_L;
				break;
			case DI01:
				disp[5] = SYM_I;
				disp[4] = SYM_N;
				disp[3] = SYM_P;
				disp[2] = SYM_U;
				disp[1] = SYM_T;
				break;
			case NOINPUT:
				disp[5] = SYM_N;
				disp[4] = SYM_O;
				disp[3] = SYM__;
				disp[2] = SYM_I;
				disp[1] = SYM_N;
				break;
			case DQ01:
				disp[5] = SYM_O;
				disp[4] = SYM_U;
				disp[3] = SYM_T;
				disp[2] = SYM_P;
				disp[1] = SYM_U;
				disp[0] = SYM_T;
				break;
			case DQ02:
				disp[5] = SYM_D;
				disp[4] = SYM_O;
				disp[3] = SYM__;
				disp[2] = 1;
				break;
			case DQ03:
				disp[5] = SYM_D;
				disp[4] = SYM_O;
				disp[3] = SYM__;
				disp[2] = 2;
				break;
			case DQ04:
				disp[5] = SYM_D;
				disp[4] = SYM_O;
				disp[3] = SYM__;
				disp[2] = 3;
				break;
			case DQ05:
				disp[5] = SYM_D;
				disp[4] = SYM_O;
				disp[3] = SYM__;
				disp[2] = 4;
				break;
			case DQ06:
				disp[5] = SYM_D;
				disp[4] = SYM_O;
				disp[3] = SYM__;
				disp[2] = 5;
				break;
			case ERR_SP:
				disp[5] = SYM_E;
				disp[4] = SYM_R;
				disp[3] = SYM_R;
				disp[2] = SYM__;
				disp[1] = SYM_S;
				disp[0] = SYM_P;
				break;
			case ERR_LS:
				disp[5] = SYM_E;
				disp[4] = SYM_R;
				disp[3] = SYM_R;
				disp[2] = SYM__;
				disp[1] = SYM_L;
				disp[0] = SYM_S;
				break;
			case ERR_HP:
				disp[5] = SYM_E;
				disp[4] = SYM_R;
				disp[3] = SYM_R;
				disp[2] = SYM__;
				disp[1] = SYM_H;
				disp[0] = SYM_P;
				break;
			case ERR_OH:
				disp[5] = SYM_E;
				disp[4] = SYM_R;
				disp[3] = SYM_R;
				disp[2] = SYM__;
				disp[1] = SYM_O;
				disp[0] = SYM_H;
				break;
			case ERR_OL:
				disp[5] = SYM_E;
				disp[4] = SYM_R;
				disp[3] = SYM_R;
				disp[2] = SYM__;
				disp[1] = SYM_O;
				disp[0] = SYM_L;
				break;		
			case E00:
			case E01:
			case E02:
			case E03:
			case E04:
			case E05:
			case E06:
			case E07:
			case E08:
			case E09:
			case E10:
			case E11:
			case E12:
			case E13:
			case E14:
			case E15:
				disp[0] = (disp_code - 0X80)%10;	//错误编号低位
				disp[1] = (disp_code - 0X80)/10;	//错误编号高位
				disp[2] = SYM__;					
				disp[3] = SYM_R;					
				disp[4] = SYM_R;					
				disp[5] = SYM_E;					
				break;
			case MF01:
			case MF02:
			case MF03:
			case MF04:
			case MF05:
			case MF06:
			case MF07:
			case MF08:
			case MF09:
			case MF10:
			case MF11:
			case MF12:	
				disp[1] = (disp_code - 0X20)%10;	//错误编号低位
				disp[2] = (disp_code - 0X20)/10;	//错误编号高位						
				disp[3] = SYM___;					
				disp[4] = SYM___;					
				disp[5] = SYM_F;					
				break;
			case MD01:
			case MD02:
				disp[1] = (disp_code - 0X37)%10;	//错误编号低位
				disp[2] = (disp_code - 0X37)/10;	//错误编号高位						
				disp[3] = SYM___;					
				disp[4] = SYM_P;					
				disp[5] = SYM_D;
				break;
			case 0x91:
			case 0x92:
			case 0x93:
			case 0x94:
			case 0x95:
			case 0x96:
			case 0x97:
			case 0x98:
			case 0x99:
				disp[0] = SYM_N;
				disp[1] = SYM_O;
				disp[2] = SYM__;
				disp[3] = disp_code - 0x90;
				disp[4] = SYM_I;
				break;
			case O1_ON:
			case O2_ON:
			case O3_ON:
			case O4_ON:
			case O5_ON:
				disp[0] = SYM_N;
				disp[1] = SYM_O;
				disp[2] = SYM__;
				disp[3] = disp_code - 0x60;
				disp[4] = SYM_O;
				break;
			case O1_OFF:
			case O2_OFF:
			case O3_OFF:
			case O4_OFF:
			case O5_OFF:
				disp[0] = SYM_F;
				disp[1] = SYM_F;
				disp[2] = SYM_O;
				disp[3] = SYM__;
				disp[4] = disp_code - 0x65;
				disp[5] = SYM_O;
				break;
            case TIMEOUT:
                disp[0] = SYM_T;
				disp[1] = SYM_U;
				disp[2] = SYM_O;
				disp[3] = SYM__;
				disp[4] = SYM_T;
                break;
			default :
				disp[0] = SYM_E;
				disp[1] = SYM_D;
				disp[2] = SYM_O;
				disp[3] = SYM_C;
				disp[4] = SYM_O;
				disp[5] = SYM_N;
			}
	disp_seg(seg_sym[disp[0]],BIT0);
	disp_seg(seg_sym[disp[1]],BIT1);
	disp_seg(seg_sym[disp[2]],BIT2);
	disp_seg(seg_sym[disp[3]],BIT3);
	disp_seg(seg_sym[disp[4]],BIT4);
	disp_seg(seg_sym[disp[5]],BIT5);
	//delay_ms(1);
	}
/*闪烁显示函数*****************************************************************
形参:
	disp_data	:显示数据,三位小数点
返回值:
*******************************************************************************/
void flash_disp(s32bit disp_data)
	{
	disp_symbol(CLR_ALL);
	delay_ms(100);
	weight_disp(disp_data);
	delay_ms(100);
	return;
	}
/*整型数据显示函数*************************************************************
形参:
	disp_data	:显示数据,无小数点
返回值:
*******************************************************************************/
void disp_int(u16bit disp_data)
	{
	u8bit xdata n,disp[6] = {28,28,28,28,28,28};
	for(n = 0;n<6;n++)						//求数据每一位的值
		{
		disp[n] = disp_data%10;
		disp_data /= 10;
		}
	if(disp[5] == 0)	disp[5] = SYM_;
	if((disp[4] == 0) && (disp[5] == SYM_))	disp[4] = SYM_;
	if((disp[3] == 0) && (disp[4] == SYM_))	disp[3] = SYM_;
	if((disp[2] == 0) && (disp[3] == SYM_))	disp[2] = SYM_;
	if((disp[1] == 0) && (disp[2] == SYM_))	disp[1] = SYM_;
		
	disp_seg(seg_sym[disp[0]],BIT0);
	disp_seg(seg_sym[disp[1]],BIT1);
	disp_seg(seg_sym[disp[2]],BIT2);
	disp_seg(seg_sym[disp[3]],BIT3);
	disp_seg(seg_sym[disp[4]],BIT4);
	disp_seg(seg_sym[disp[5]],BIT5);
	delay_ms(1);
	return;					
	}
