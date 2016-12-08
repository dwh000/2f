#ifndef		__key_func_h
#define		__key_func_h
#include "public.h"
//��ֵ����************************************************************************************
#define SET_CLOSED		0XF0			//���ü�����
#define	ENT_CLOSED		0XB8			//ȷ�ϼ�����
#define	UP_CLOSED		0XD8			//���ϼ�����
#define DWN_CLOSED		0XE8			//���¼�����
#define CLR_CLOSED		0X78			//ȥƤ/���������
#define NOKEY_CLOSED	0XF8			//�޼�����

#define SET_RELEASE		0X0F			//���ü��ͷ�
#define ENT_RELEASE		0X47			//ȷ�ϼ��ͷ�
#define UP_RELEASE		0X27			//���ϼ��ͷ�
#define DWN_RELEASE		0X17			//���¼��ͷ�
#define CLR_RELEASE		0X87			//ȥƤ/������ͷ�
#define UD_RELEASE		0X37			//�������¼����ͷ�

#define ENT_ONCE		0XB7			//ȷ�ϼ�����һ��

#define CHK_ALL_KEY		0X07			//������м�ֵ


u8bit get_key(u8bit chk_val);
u8bit get_input(void);

#endif