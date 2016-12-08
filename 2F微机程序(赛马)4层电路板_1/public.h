#ifndef __public_h
	#define	__public_h
	
#include <c8051f060.h>
#include "VerCtrl.h"
#include <intrins.h>


//数据类型重定义****************************************************************
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

//输出端口位定义****************************************************************
sbit        cyl_sw_out                  =   P3^1;           //气缸开关
sbit        fine_flow_out               =   P3^2;           //粗细流切换输出
sbit        discharge_bag_sw_out        =   P3^3;           //卸袋
sbit        flashboard_sw_out           =   P3^4;           //关闸板
sbit        fill_mot_sw_out             =   P3^5;           //电机使能
sbit        clamping_bag_out            =   P3^4;           //压袋

sbit        FullOut                     =   P3^1;           //袋重装满输出
sbit        SizeFlowOut                 =   P3^2;           //粗细流切换输出

//输入端口位定义****************************************************************
sbit        discharge_bag_en            = P2^1;             /* 皮带连锁 */
sbit        zero_loc                    = P2^7;             /* 清零点 */
sbit        discharge_bag_loc           = P2^3;             /* 掉袋点 */
sbit        open_flashboard_det         = P2^2;             /* 开闸门信号 */
sbit        gate_opened_loc             = P2^0;             /* 闸门已开启 */
sbit        bag_det                     = P2^6;             /* 插袋信号 */
sbit        add_correct                 = P2^5;             /* 检重秤+校正信号 */
sbit        reduce_correct              = P2^4;             /* 检重秤-校正信号 */
sbit        into_bag_loc                = P2^0;             /* 插袋点 */
//显示代码宏定义****************************************************************
#define CLR_SYM     0X00                                    //数码管高2位不显示任何字符
#define OE_H        0x01                                    //显示oL,超上限溢出
#define OE_L        0X02                                    //显示-1,超下限溢出

#define CLR_ALL     0X10                                    //数码管不显示任何字符
#define SET         0X11                                    //数码管显示SEt
#define RD_DONE     0X13                                    //读EEPROM完成
#define WR_DONE     0X14                                    //写EEPROM完成
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
#define MF07        0X27                                    //皮重丢失!
#define MF08        0X28
#define MF09        0X29
#define MF10        0X2A
#define MF11        0X2B
#define MF12        0X2C
#define GOOD        0x2d
#define ERR_CL      0X2E                                    //砝码重量超下
#define ERR_HL      0X2F                                    //砝码重量超上限

#define MC01        0X31
#define MC02        0X32
#define MC03        0X33
#define MC04        0X34

#define MD01        0X38                                    //DP通信地址
#define MD02        0X39                                    //DP通信开关

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

#define E00         0X80                                    //显示Err_00,PB未完成初始化错误
#define E01         0X81                                    //标定输出值超出范围
#define E02         0X82                                    //标定砝码值超出范围
#define E03         0X83                                    //EEPROM读错误
#define E04         0X84                                    //EEPROM写错误
#define E05         0X85                                    //写EEPROM时,数据校验出错.
#define E06         0X86                                    //数据错误,sign检测出错
#define E07         0X87                                    //皮重小于10公斤
#define E08         0X88                                    //手动落差超出范围
#define E09         0X89                                    //袋重净差超出范围
#define E10         0X8A                                    //袋重修正值超出范围
#define E11         0X8B                                    //pb-oem初始化错误
#define E12         0X8C                                    //开环追踪开关与闭环校正开关有冲突.
#define E13         0X8D                                    //清零点接近开关故障
#define E14         0X8E                                    //堵嘴或者无灰
#define E15         0X8F                                    //通信地址超过范围.
#define E16         0X90                                    //pb-oem无模块


#define I01         0X91
#define I02         0X92
#define	I03         0X93
#define I04         0X94
#define I05         0X95
#define I06         0X96
#define I07         0X97
#define I08         0X98
#define I09         0X99


#define ERR_SP      0XA0                                    //设定值超范围
#define ERR_LS      0XA1                                    //传感器量程错误
#define ERR_HP      0xA2                                    //粗细流切换重量错误
#define ERR_OH      0XA3                                    //自动清零值超上限
#define ERR_OL      0XA4                                    //自动清零值超下限
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