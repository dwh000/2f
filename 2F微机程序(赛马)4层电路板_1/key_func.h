#ifndef		__key_func_h
#define		__key_func_h
#include "public.h"
//键值定义************************************************************************************
#define SET_CLOSED		0XF0			//设置键按下
#define	ENT_CLOSED		0XB8			//确认键按下
#define	UP_CLOSED		0XD8			//向上键按下
#define DWN_CLOSED		0XE8			//向下键按下
#define CLR_CLOSED		0X78			//去皮/清零键按下
#define NOKEY_CLOSED	0XF8			//无键按下

#define SET_RELEASE		0X0F			//设置键释放
#define ENT_RELEASE		0X47			//确认键释放
#define UP_RELEASE		0X27			//向上键释放
#define DWN_RELEASE		0X17			//向下键释放
#define CLR_RELEASE		0X87			//去皮/清零键释放
#define UD_RELEASE		0X37			//向上向下键都释放

#define ENT_ONCE		0XB7			//确认键按下一次

#define CHK_ALL_KEY		0X07			//检测所有键值


u8bit get_key(u8bit chk_val);
u8bit get_input(void);

#endif