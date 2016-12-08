#ifndef __public_h
	#define	__public_h
	
#include <c8051f060.h>
#include "VerCtrl.h"
#include <intrins.h>


//���������ض���****************************************************************
#define	schar	signed char				//8bits		0 to 255
#define	uchar	unsigned char			//8bits		-128 to 127
#define	sint	signed int				//16bits	-32768 to 32767
#define	uint	unsigned int			//16bits	0 to 65535
#define	sshort	signed short			//16bits	-32768 to 32767
#define	ushort	unsigned short			//16bits	0 to 65535
#define	slong	signed long				//32bits	-2147483648 to 2147483647
#define	ulong	unsigned long			//32bits	4294967295

#define	s8bit	signed char				//8bits		0 to 255
#define	u8bit	unsigned char			//8bits		-128 to 127
#define	s16bit	signed int				//16bits	-32768 to 32767
#define	u16bit	unsigned int			//16bits	0 to 65535
#define	s32bit	signed long				//32bits	-2147483648 to 2147483647
#define	u32bit	unsigned long			//32bits	4294967295

//����˿�λ����****************************************************************
sbit        cyl_sw_out                  =   P3^1;           //���׿���
sbit        fine_flow_out               =   P3^2;           //��ϸ���л����
sbit        discharge_bag_sw_out        =   P3^3;           //ж��
sbit        flashboard_sw_out           =   P3^4;           //��բ��
sbit        fill_mot_sw_out             =   P3^5;           //���ʹ��
sbit        clamping_bag_out            =   P3^4;           //ѹ��

sbit        FullOut                     =   P3^1;           //����װ�����
sbit        SizeFlowOut                 =   P3^2;           //��ϸ���л����

//����˿�λ����****************************************************************
sbit        discharge_bag_en            = P2^1;             /* Ƥ������ */
sbit        zero_loc                    = P2^7;             /* ����� */
sbit        discharge_bag_loc           = P2^3;             /* ������ */
sbit        open_flashboard_det         = P2^2;             /* ��բ���ź� */
sbit        gate_opened_loc             = P2^0;             /* բ���ѿ��� */
sbit        bag_det                     = P2^6;             /* ����ź� */
sbit        add_correct                 = P2^5;             /* ���س�+У���ź� */
sbit        reduce_correct              = P2^4;             /* ���س�-У���ź� */
sbit        into_bag_loc                = P2^0;             /* ����� */
//��ʾ����궨��****************************************************************
#define CLR_SYM     0X00                                    //����ܸ�2λ����ʾ�κ��ַ�
#define OE_H        0x01                                    //��ʾoL,���������
#define OE_L        0X02                                    //��ʾ-1,���������

#define CLR_ALL     0X10                                    //����ܲ���ʾ�κ��ַ�
#define SET         0X11                                    //�������ʾSEt
#define RD_DONE     0X13                                    //��EEPROM���
#define WR_DONE     0X14                                    //дEEPROM���
#define CAL         0X15
#define TEST        0X16
#define FUNC        0X17
#define VER         0X18
#define DPSET       0X19
#define NOINPUT     0X20

#define MF01        0x21
#define MF02        0X22
#define MF03        0X23
#define MF04        0X24
#define MF05        0X25
#define MF06        0X26
#define MF07        0X27                                    //Ƥ�ض�ʧ!
#define MF08        0X28
#define MF09        0X29
#define MF10        0X2A
#define MF11        0X2B
#define MF12        0X2C
#define GOOD        0x2d
#define ERR_CL      0X2E                                    //������������
#define ERR_HL      0X2F                                    //��������������

#define MC01        0X31
#define MC02        0X32
#define MC03        0X33
#define MC04        0X34

#define MD01        0X38                                    //DPͨ�ŵ�ַ
#define MD02        0X39                                    //DPͨ�ſ���

#define DI01        0X40
#define DQ01        0X41
#define	DQ02        0X42
#define DQ03        0X43
#define DQ04        0X44
#define DQ05        0X45
#define DQ06        0X46

#define O1_ON       0X61
#define O2_ON       0X62
#define O3_ON       0X63
#define O4_ON       0X64
#define O5_ON       0X65
#define O1_OFF      0X66
#define O2_OFF      0X67
#define O3_OFF      0X68
#define O4_OFF      0X69
#define O5_OFF      0X6A

#define E00         0X80                                    //��ʾErr_00,PBδ��ɳ�ʼ������
#define E01         0X81                                    //�궨���ֵ������Χ
#define E02         0X82                                    //�궨����ֵ������Χ
#define E03         0X83                                    //EEPROM������
#define E04         0X84                                    //EEPROMд����
#define E05         0X85                                    //дEEPROMʱ,����У�����.
#define E06         0X86                                    //���ݴ���,sign������
#define E07         0X87                                    //Ƥ��С��10����
#define E08         0X88                                    //�ֶ�������Χ
#define E09         0X89                                    //���ؾ������Χ
#define E10         0X8A                                    //��������ֵ������Χ
#define E11         0X8B                                    //pb-oem��ʼ������
#define E12         0X8C                                    //����׷�ٿ�����ջ�У�������г�ͻ.
#define E13         0X8D                                    //�����ӽ����ع���
#define E14         0X8E                                    //��������޻�
#define E15         0X8F                                    //ͨ�ŵ�ַ������Χ.
#define E16         0X90                                    //pb-oem��ģ��


#define I01         0X91
#define I02         0X92
#define	I03         0X93
#define I04         0X94
#define I05         0X95
#define I06         0X96
#define I07         0X97
#define I08         0X98
#define I09         0X99


#define ERR_SP      0XA0                                    //�趨ֵ����Χ
#define ERR_LS      0XA1                                    //���������̴���
#define ERR_HP      0xA2                                    //��ϸ���л���������
#define ERR_OH      0XA3                                    //�Զ�����ֵ������
#define ERR_OL      0XA4                                    //�Զ�����ֵ������
#define TIMEOUT     0XA5

#define OFF         0X55
#define ON          0XAA
#define NO_OPT      0XFF
#define EXSTART     0XF0
#define B_SUMCHECK  0XFC
#define TIME_OUT    0XFD
#define BAD_VAL     0XFE

#define SHUT        1
#define OPEN        0
#define ACTIVE      0

#define COARSE      1
#define FINE        0


#define BIT0        0x01
#define BIT1        0X02
#define BIT2        0x04
#define BIT3        0x08
#define BIT4        0X10
#define BIT5        0x20
#define BIT6        0X40
#define BIT7        0X80

#endif