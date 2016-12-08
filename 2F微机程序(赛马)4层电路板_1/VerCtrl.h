#ifndef  verctrl_h__
	#define	 verctrl_h__

//以下为编译可以配置选项
#define saima	1		//赛马改造程序,2e气动流程,增加DP通信模块

#define DP_ON	1		//配置DP模块,1为使用DP代码.0为不使用DP代码

#define BAUDRATE	115200

//可配置选项结束


#if saima
	//#define Version "0-0000"	//仅针对赛马改造的产品
	//--------------------------------------------------------------------------
	//日期:2013xxxx-20130417
	//作者:wwh
	//内容:编写调试完成了赛马改造要求的功能能.
	//--------------------------------------------------------------------------
	#if DP_ON > 0
	//#define Version "0-0004"	//仅针对赛马改造的正式发行版本 ,DP程序编译,2013-6-27 编译
								//修改滤波平局值的个数为24
								//细流灌装时禁止数据交互
								//检查并修改DP数据造成的死循环
	//#define Version "0-0005"	//仅针对赛马改造的正式发行版本 ,DP程序编译,2013-6-27 编译
								//滤波系数平均值个数恢复为18
								//关闸板输出程序处,增加一行代码,完成第一次关闸板输出
								//修改上电清零程序,清零范围超出,则零点值为零,使包机运行中复位
								//仍可继续工作.
	//#define Version "0-0006"	//2013年12月2日				编译
								//基于四层板硬件的ADC程序
								//只能使用第一版的GSD文件进行组态
								//修改了几个测试菜单的显示错误.
								//修改了网络标定时,未标定净重值的刷新方式
								//增加了参数的初始化代码,其使用方法为:按住SET按键复位,可以初始化设定参数
								//修改了DP通信程序禁止条件,其条件更改为大于(设定值-3KG)禁止
//    #define Version "0-0010"    //2014年2月22日13:59:13
                                //修改二次关闸板的设定方式及相关内容,修改的参数为二次关闸板调整值.
                                //新的二次关闸板值的计算方法: 二次关闸板值 = 关闸板判别值 - 二次关闸板调整值!
                                //修改掉包计数器变量的定义方式,并给出了掉包计数器初始化的相关代码,保证非上电复位
                                //掉包计数器的值不清零.
                                //增加掉包计数器开关操作时,掉包计数器值清零的操作
//#define Version "0-0016"        //2015年3月12日,从10版本的重新更新程序,修改了通信中上袋袋重错误的问题.
                                //2014年12月23日2:19:12,"0-0012"版本,0016版本尚未更新.
                                //修改清零逻辑.
//                                更新内容:
//                                1.更新了上电清零程序.当清零超过范围时报警,可以通过按键进行参数设计及清零去皮操作;
//                                2.通过设置增加了时钟丢失检测超时复位,可以防止时钟停振导致的死机.
//                                3.增加了复位判别程序,根据复位源的不同,进入不同的复位初始化程序.
//                                4.复位源及其程序动作说明:
//                                 a.上电复位:清零掉包计数器(只上电复位清零,否则只能通过菜单和联网清零);读取参数及通讯初始化;上电清零.
//                                 b.RST管脚复位(复位按键复位):检测设置键,有则初始参数写入24C04,并产生一个软件强制复位(修复参数用);检测设置键,有则
//                                   产生一个软件强制复位(特殊情况下,读取参数用);如果无按键,则通讯初始化(省去了参数读取及上电自动清零).
//                                 c.看门狗复位(暂时未使用):只通讯初始化.
//                                 d.时钟丢失检测超时复位:只通讯初始化.
//                                 e.软件强制复位:读取参数及通讯初始化;上电清零.除了没有掉包计数器清零外其他与上电复位的操作相同.
//                                 f.其他复位(未配置):但放入了通讯初始化程序.

                                    //2015年1月21日,0-0014更新.0016版更新已完成.
//                                  1.更新了I2C代码,采用IO模拟的方式实现I2C,避免硬件死锁.
//                                  2.修复了写参数时可能引起复位的BUG.
//#define Version "0-1000"            //2015年5月20日,修正清零点与50公斤点显示混乱的问题.降成本硬件
#define Version "0-1001"            //2016年1月28日,1.修改采样次数为20.
                                    //2.修改输入信号对应的DI显示.
#else
	#define Version "0-0002"	//仅针对赛马改造的正式发行版本 ,DP程序不编译
	#endif
	//--------------------------------------------------------------------------
	//日期:20130417-201300604
	//作者:wwh
	//内容:修改了AD的采样程序,目前采用双极性方式
	//--------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------
//							公共部分代码更新记录
//
//日期:20130416
//作者:wwh
//内容:	1.波特率更改为1152000,刷新频率更改为10Hz.
//		2.增加了AD错误的诊断代码,避免因AD错误而引起死机.
//		3.调整参数读取时读取DP地址和DP开关的顺序,DP开关不开则不读取DP地址参数.
//
//
//日期:20130417
//作者:wwh
//内容:	1.完成了初次上电初始化程序,并调试通过.
//------------------------------------------------------------------------------
#endif			//end of verctrl_h__