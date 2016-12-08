/*******************************************************************************
*文件名: 2F1主程序.c
*作  者: 王文辉
*单  位: 唐山智能电子有限公司
*日  期: 2012-9-21
*版  本: 实验版本
*功能描述: 2f包机程序
*******************************************************************************/

/*头文件引用*******************************************************************/
#include "public.h"			//延时函数,端口定义,类型定义及宏定义
#include "disp.h"			//显示函数
#include "24c04.h"			//参数保存及读取
#include "key_func.h"		//按键相关函数
#include "menu_func.h"		//菜单相关函数
#include "timer.h"			//定时器初始化及配置
#include "weighting.h"		//AD,称重,标度变换及滤波
#include "terminal.h"		//串口初始化及串口读写
#include <stdio.h>			//C标准IO函数


/*全局变量定义*****************************************************************/
s16bit xdata    drop_weight,				//手动落差值
                residual_weight,			//袋重净差值
                zero_scale_value;			//零标度值
u32bit xdata 	filter2_out = 0,			//一阶低通滤波器输出值
				filter1_out,				//中值平均值滤波输出
				load_cell_span,				//传感器测量范围
				tare_weight,				//皮重
				scale_output_val,			//标定点砝码输出值
				scale_counterweight_val;	//标定点砝码值
u32bit xdata    DropCounter _at_ 0x180;		//掉包计数器,指定存储地址为0x180,xdata区域,并且该区域内存不清零
u16bit xdata 	sp_weight,					//袋重设置值
				sf_weight,					//粗细流切换重量
                sf_weight_adj_val,          //
				weight_correct_val,			//袋重修正值
				shut_fb_w;					//关闸板判别值
u8bit xdata     ZeroFlag,                   //过清零点标志
                ZeroCnt = 0,                    //清零点计数.
                DpErrCnt = 0,               //用于DP通讯错误的计时
                DpErrFlag = 0,              //DP通讯错误标志
                t1_cnt,						//t1定时器计数个数
				shut_cnt,					//关闸板判别计数
				filter_coefficient,			//滤波系数
				filter_coefficient1,		//计算后的滤波系数
				err_code = 0,				//错误代码
				sf_switch,					//粗细流开关
				ol_track_sw,				//开环追踪开关
				track_bags,					//追踪袋数
				w_save_cnt = 0,				//袋重保存计数
				cl_correct_sw,				//闭环修正开关
				arrival_time,				//抵达时间
				A_T_time = 0,				//抵达时间暂存值
				counter_sw,					//计数开关
				disp_cache,					//断码显示缓存
				CommAddr,					//通信地址
				DpSwitch,					//通信功能开关
				DispCnt,					//显示计数器
				flashboard_cnt;				//关闸板定时时间,单位0.1s
bit				t1_flag,					//T1定时溢出标志
				startup_flag = 0,			//开机标志
				DropFlag = 0,				//掉袋标志
				AutoZeroFlag = 0,			//自动清零标志
				discharge_bag_loc_flag = 0,	//掉袋点标志
				flashboard_pulse_flag,		//关闸板定时溢出标志
				re_fill_flag,				//重新灌装标志
				DpEnFlag = 0,				//Pb数据交换软件使能.
				discharge_pulse_flag = 0,	//掉袋定时溢出标志
				shut_flag = 0,				//关闸板判别标志
				disp_flag = 1;				//显示标志
u16bit xdata	weight[10],				//追踪时,袋重备份;用于修正关闸判别值.
                WeightOfLast;
s32bit xdata	adc,adc_disp;					//AD转换换算后的袋重值


/*外部变量引用*****************************************************************/
extern u8bit code	seg_sym[40];			//字符段码
extern u8bit code	seg_dot[40];
extern u8bit xdata	TxBuf[70],RxBuf[60];


/*函数声明*********************************************************************/
void mcu_init();							//单片机初始化函数
void update_shut_fb_w(u8bit bags);
void ZeroPointDet(void);
void ShutAndCorrect(void);


/*输入端口位定义****************************************************************
sbit	discharge_bag_en		= P1^0;	/* 皮带连锁
sbit	zero_loc				= P2^0;	/* 清零点
sbit	discharge_bag_loc		= P2^1;	/* 掉袋点 
sbit	open_flashboard_det		= P2^2;	/* 开闸门信号 *
sbit	gate_opened_loc			= P2^3;	/* 闸门已开启 *
sbit	bag_det					= P2^4;	/* 插袋信号 *
sbit	add_correct				= P2^5;	/* 检重秤+校正信号 *
sbit	reduce_correct			= P2^6;	/* 检重秤-校正信号 *
sbit	into_bag_loc			= P2^7;	 插袋点 

sbit FullOut					=	P3^1;		//袋重装满输出
sbit SizeFlowOut				=	p3^2;		//粗细流切换输出
//输出端口位定义****************************************************************
sbit cyl_sw_out					=	P3^1;		//气缸开关
sbit fine_flow_out				=	P3^2;		//粗细流切换输出
sbit discharge_bag_sw_out		=	P3^3;		//卸袋
sbit flashboard_sw_out			=	P3^4;		//关闸板
sbit fill_mot_sw_out			=	P3^5;		//电机使能
sbit clamping_bag_out			= 	P3^4;		//压袋*************************/




/*主函数***********************************************************************/
void main(void)
{
    mcu_init();                                             //单片机初始化

    /*上电自动清零*************************************************************/
    zero_scale_value = 0; 
    zero_scale_value = NW_scale();
    /*while((zero_scale_value < -3500) || (zero_scale_value > 3500)){*/
        if(zero_scale_value > 3500){
            disp_symbol(ERR_OH);
            zero_scale_value = 0;
        }
        else if(zero_scale_value < -3500){
            disp_symbol(ERR_OL);
            zero_scale_value = 0;
        }
        menu_func();                                        //调用菜单函数
        tare_zero_func();                                   //调用去皮清零函数
    //}

    #if saima
    FullOut = SHUT;
    SizeFlowOut = SHUT;

    while(1){
        s32bit xdata shut_error;
        #if DP_ON
            if(PbRestart() == TIMEOUT){                                    //检测PB状态并重启PB连接
                DpErrCnt ++ ;
                if(DpErrCnt > 3){
                    DpSwitch = OFF;
                    DpErrFlag = 1;
                }
            }
            PbTare();                                       //联网去皮操作
            PbNW_measure();                                 //联网标称数据刷新
        #endif
        //参数修改及显示时重
        menu_func();                                        //调用菜单函数
        dm_sp_weight();                                     //调用直接修改设定值函数
        tare_zero_func();                                   //调用去皮清零函数
        adc = NW_scale();
        {/*刷新显示数据*/
            if(zero_loc == ACTIVE){
                if(ZeroCnt == 1){
                    DispZeroLoc();
                }
                else if(ZeroCnt == 2){
                    Disp50kgLoc();
                }
                ZeroFlag = 1;
            }
            else if(DpErrFlag)   DispDpERRSet();
            else{
                DispZeroRst();
                if(ZeroFlag == 1){
                    if(ZeroCnt == 1)    ZeroCnt = 2;
                    else if(ZeroCnt == 2)    ZeroCnt = 1;
                    ZeroFlag = 0;
                }
            }
            DispBagDetRst();
            if(adc_disp - adc > 200)    disp_flag = 1;
            if(adc - adc_disp > 200)    disp_flag = 1;
            if(disp_flag){
                adc_disp = adc;
                run_disp(adc_disp);
                DispCnt = 0;
                disp_flag = 0;
            }
        }

        if(adc >= 5000){
            if(sf_switch == ON){
                if(adc < 20000){
                    SizeFlowOut = SHUT;
                }
                else if(adc>=sf_weight){
                    SizeFlowOut = OPEN;
                }
            }
            if(adc > (shut_fb_w - 3000)) DpEnFlag = 0;
            //关闸板判别程序
            shut_error = adc - shut_fb_w;
            if(shut_error > 500){
                ShutAndCorrect();
            }
            else if((shut_error > 200) && (shut_flag == 1)){
                ShutAndCorrect();
            }
            else if(shut_error >= 0){
                shut_flag = 1;
                shut_cnt++;
                if(shut_cnt == 3)   ShutAndCorrect();
            }
            else{
                shut_cnt = 0;
            }
        }
        else    ZeroPointDet();
    }
    #endif  //end of saima
}


/*******************************************************************************
*原  型:void ZeroPointDet(void)
*形  参:无
*功  能:用于过零点检测及过零点清零
*返回值:无.
*******************************************************************************/
void ZeroPointDet(void)
{
    s16bit xdata czero_scale_value;
    if(startup_flag)    return;
    if((DropFlag) && (zero_loc == ACTIVE)){
        czero_scale_value = zero_scale_value;
        zero_scale_value = 0;
        adc = NW_scale_clr();
        if((adc > 3500) || (adc < -3500)){//清零点测量值超过清零范围,则
            zero_scale_value = czero_scale_value;
            if(adc > 3500) disp_symbol(ERR_OH);
            else if(adc < -3500) disp_symbol(ERR_OL);
        }
        else{//清零点测量值在清零范围内,则
            DispZeroClr();
            run_disp(adc);
            zero_scale_value = adc;
        }
        DropFlag = 0;
        while(zero_loc == ACTIVE);
        ZeroCnt = 2;
        ZeroFlag = 0;
    }
}

void ShutAndCorrect(void)
{
    u16bit DropVal = (sp_weight/5)<<1;                      //掉袋判别值
    disp_flag = 1;
    SizeFlowOut = OPEN;
    FullOut = OPEN;
    DpEnFlag = 1;
    shut_cnt = 0;
    shut_flag = 0;
    Disp50kgRst();
    DispZeroRst();
    while(adc >= DropVal){
        adc = NW_scale();
        #if DP_ON
        PbNW_measure();                                     //联网标称数据刷新
        #endif
        if(zero_loc == ACTIVE){
            Disp50kgLoc();
            t1_100ms(10);
            disp_flag = 0;
            while(zero_loc == ACTIVE);
            Disp50kgRst();
            WeightOfLast = (u16bit)adc;               //备份当前袋重
            weight[w_save_cnt] = WeightOfLast;
            w_save_cnt++;
            if(w_save_cnt == track_bags) w_save_cnt = 0;
        }
        else Disp50kgRst();
        DispBagDetRst();
        if(disp_flag)   run_disp(adc);
        if(t1_flag){
            t1_stop();
            t1_flag = 0;
            disp_flag = 1;
        }
    }
    ZeroCnt = 1;
    ZeroFlag = 0;
    FullOut = SHUT;
    SizeFlowOut = SHUT;
    t1_stop();
    DropFlag = 1;
    if(counter_sw == ON)    DropCounter++;

    startup_flag = 0;
    if(cl_correct_sw == ON)     t4_50ms_cl_track(arrival_time);
    else if(ol_track_sw == ON)  update_shut_fb_w(track_bags);
}


















































//****************************************************************************//
//							公共部分子程序									  //
//****************************************************************************//

/*******************************************************************************
*原  型:void Port_IO_Init(void);
*形  参:无.
*功  能:IO端口配置.
*返回值:无.
*******************************************************************************/
void Port_IO_Init(void)
{
    SFRPAGE   = CONFIG_PAGE;
    P0MDOUT   = 0x90;
    P1MDOUT   = 0x06;
    P3MDOUT   = 0xFE;
    P4MDOUT   = 0xE0;
    P6MDOUT   = 0xFF;
    P7MDOUT   = 0xFF;
    XBR0      = 0x04;//0x05;
    XBR2      = 0x40;
    
    P1 = 0XFF;
    P2 = 0XFF;
    P3 = 0XFF;
    P4 = 0XFF;
    P5 = 0XFF;
    P6 = 0XFF;
    P7 = 0XFF;
}
/*******************************************************************************
*原  型:void stop_wdt(void);
*形  参:无.
*功  能:关闭看门狗.
*返回值:无.
*******************************************************************************/
void stop_wdt(void)
{
	EA = 0;
	WDTCN = 0XDE;
	WDTCN = 0XAD;
}
/*******************************************************************************
*原  型:void sysclk_init(void);
*形  参:无.
*功  能:系统时钟初始化.
*返回值:无.
*******************************************************************************/
void sysclk_init(void)
{
	u16bit i;
	SFRPAGE = CONFIG_PAGE;
	OSCXCN = 0X67;
	for(i=0;i<3000;i++);
	while((OSCXCN & 0x80) == 0)	;
	CLKSEL = 0X01;
	OSCICN = 0x03;
	return;
}
void save_all(void)
{
	u8bit Start_1stFlag = ON;
	//保存DP开关
	DpSwitch = OFF;
	eeprom_write(&DpSwitch,DP_SW_ADDR,1);
	
	//保存DP地址
	CommAddr = 1;
	eeprom_write(&CommAddr,COMMADDR_ADDR,1);
	
	//保存滤波系数
	filter_coefficient = 80;
	eeprom_write(&filter_coefficient,FILTER_ADDR,1);
	
	//保存设定值
	sp_weight = 50000;
	eeprom_write((u8bit *)&sp_weight,SP_WEIGHT_ADDR,2);
	
	//保存传感器量程
	load_cell_span = 350000;
	eeprom_write((u8bit *)&load_cell_span,CELL_SPAN_ADDR,4);
	
	//保存标定输出值
	scale_output_val = 34306;
	eeprom_write((u8bit *)&scale_output_val,SCALE_OUTPUT_ADDR,4);
	
	//保存标定砝码重量
	scale_counterweight_val = 40000;
	eeprom_write((u8bit *)&scale_counterweight_val,COUNTERWEIGHT_ADDR,4);
	
	//保存追踪袋数
	track_bags = 5;
	eeprom_write(&track_bags,TRACK_BAGS_ADDR,1);
	
	//保存粗细流切换开关
	sf_switch = OFF;
	eeprom_write(&sf_switch,SF_SWITCH_ADDR,1);
	
	//保存粗细流切换值
	sf_weight_adj_val = 5000;
	eeprom_write((u8bit *)&sf_weight_adj_val,SF_WEIGHT_ADDR,2);
    
	//保存落差
	drop_weight = 0;
	eeprom_write((u8bit *)&drop_weight,DROP_WEIGHT_ADDR,2);
	
	//保存净差
	residual_weight = 0;
	eeprom_write((u8bit *)&residual_weight,R_WEIGHT_ADDR,2);
	
	//保存袋重修正值
	weight_correct_val = 0;
	eeprom_write((u8bit *)&weight_correct_val,WEIGHT_CORRECT_ADDR,2);
	
	//保存抵达时间
	arrival_time = 0;
	eeprom_write(&arrival_time,ARRIVAL_TIME_ADDR,1);
	
	//保存开环追踪开关
	ol_track_sw = OFF;
	eeprom_write(&ol_track_sw,OL_TRACK_SW_ADDR,1);
	
	//保存闭环校正开关
	cl_correct_sw = OFF;
	eeprom_write(&cl_correct_sw,CL_CORRECT_SW_ADDR,1);
	
	//保存计数器开关
	counter_sw = OFF;
	eeprom_write(&counter_sw,COUTER_SW_ADDR,1);
	
	eeprom_write(&Start_1stFlag,START_1ST_ADDR,1);
}
void read_all(void)
{
	u8bit cnt;
	#if DP_ON
	u8bit err_temp = GOOD;
	#endif
	
	//读取DP通信开关
	eeprom_read(&DpSwitch,DP_SW_ADDR,1);
	//读取DP通信地址.
	eeprom_read(&CommAddr,COMMADDR_ADDR,1);
	while(CommAddr > 60 || CommAddr == 0){
		disp_symbol(E15);
		menu_func();
	}
	
	#if DP_ON
    cnt = 0;
	while(DpSwitch == ON){
		EA = 0;
		if(err_temp == GOOD) err_temp = pb_init();
		EA = 1;
		if(err_temp == GOOD)    break;
		else    disp_symbol(E11);
		menu_func();
	}

	#endif
	DpEnFlag = 1;

	//读取滤波系数
	eeprom_read(&filter_coefficient,FILTER_ADDR,1);

	if(filter_coefficient > 90){
		filter_coefficient = 60;
		eeprom_write(&filter_coefficient,FILTER_ADDR,1);
	}
	filter_coefficient1 = (uchar)filter_coefficient * 1.1;
		
	//读取设定值	
	eeprom_read((u8bit *)&sp_weight,SP_WEIGHT_ADDR,2);

	while((sp_weight < 22000) || (sp_weight > 65000)){
		disp_symbol(ERR_SP);
		menu_func();
	}
	
	//读取传感器量程	
	eeprom_read((u8bit *)&load_cell_span,CELL_SPAN_ADDR,4);

	while((load_cell_span != 100000) && (load_cell_span != 150000)
		&& (load_cell_span != 200000) && (load_cell_span != 250000)
		&& (load_cell_span != 300000) && (load_cell_span != 350000)){
		disp_symbol(ERR_LS);
		menu_func();
	}

	//读取标定输出值
	eeprom_read((u8bit *)&scale_output_val,SCALE_OUTPUT_ADDR,4);
	while((scale_output_val < 19000) || (scale_output_val > 62000)){
		disp_symbol(E01);
		menu_func();
	}

	//读取标定砝码重量
	eeprom_read((u8bit *)&scale_counterweight_val,COUNTERWEIGHT_ADDR,4);
	while((scale_counterweight_val<20000)||(scale_counterweight_val>60000)){
		disp_symbol(E02);
		menu_func();
	}

	//读取追踪袋数		
	eeprom_read(&track_bags,TRACK_BAGS_ADDR,1);
	if ((track_bags == 0) || (track_bags > 10)){
		track_bags = 5;
		eeprom_write(&track_bags,TRACK_BAGS_ADDR,1);
	}
	
	//读取皮重值
	eeprom_read((u8bit *)&tare_weight,TW_ADDR,4);
	/*while(tare_weight <= 10000){
		disp_symbol(E07);
		menu_func();
	}*/

	//读取粗细流切换开关
	eeprom_read(&sf_switch,SF_SWITCH_ADDR,1);
	
	//读取粗细流切换值
	eeprom_read((u8bit *)&sf_weight_adj_val,SF_WEIGHT_ADDR,2);
	while((sf_weight_adj_val < 100) || (sf_weight_adj_val > 10000)){
		disp_symbol(ERR_HP);
		menu_func();
	}

	//读取落差
	eeprom_read((u8bit *)&drop_weight,DROP_WEIGHT_ADDR,2);
	while((drop_weight < -2500) || (drop_weight > 2500)){
		disp_symbol(E08);
		menu_func();
	}

	
	//读取净差
	eeprom_read((u8bit *)&residual_weight,R_WEIGHT_ADDR,2);
	while((residual_weight < -2500) || (residual_weight > 2500)){
		disp_symbol(E09);
		menu_func();
	}

	//袋重修正值
	eeprom_read((u8bit *)&weight_correct_val,WEIGHT_CORRECT_ADDR,2);
	while(weight_correct_val > 1500){
		disp_symbol(E10);
		menu_func();

	}

	//读取抵达时间
	eeprom_read(&arrival_time,ARRIVAL_TIME_ADDR,1);
	//读取开环跟踪开关
	eeprom_read(&ol_track_sw,OL_TRACK_SW_ADDR,1);
	
	//读取闭环校正开关
	eeprom_read(&cl_correct_sw,CL_CORRECT_SW_ADDR,1);

	if((ol_track_sw == ON) && (cl_correct_sw == ON)){
		ol_track_sw = OFF;
		cl_correct_sw = OFF;
		disp_symbol(E12);
	}
	//读取计数开关
	eeprom_read(&counter_sw,COUTER_SW_ADDR,1);
	//初始化关闸板判别值
	shut_fb_w = sp_weight - drop_weight;
    sf_weight = shut_fb_w - sf_weight_adj_val;
	//初始化自追踪队列
	for(cnt = 0;cnt < 10;cnt++)	weight[cnt] = sp_weight + residual_weight;
}

void ClearDropCounter(void)
{
    SFRPAGE = 0;
    if(RSTSRC & BIT1)   DropCounter = 0;
    return;
}
/*******************************************************************************
*原  型:void mcu_init(void);
*形  参:无.
*功  能:单片机的初始化函数.
*返回值:无.
*******************************************************************************/
void mcu_init(void)
{
    u8bit led_test,cnt;
    stop_wdt();
    sysclk_init();
    ClearDropCounter();
    Port_IO_Init();
    time01_init();
    iic_init();
    adc_init();
    uart0_init(BAUDRATE);
    time3_init();
    time4_init();
    if(get_key(SET_CLOSED) == SET_CLOSED){
        save_all();
    }
    else{
        read_all();
    }
    for(led_test = 0;led_test < 10;led_test ++){
        disp_seg(seg_sym[led_test],0x3f);
        zero_scale_value = 0;
        for(cnt = 0 ;cnt < 20 ;cnt++)   NW_scale();
        //delay_ms(100);
    }
    startup_flag = 1;
}
/*******************************************************************************
*原  型:void update_shut_fb_w(u8bit bags);
*形  参:  bags    追踪袋数 
*功  能:更新关闸板设定值,用于开环追踪功能.
*返回值:无.
*******************************************************************************/
void update_shut_fb_w(u8bit bags)
{
    u8bit cnt;
    u32bit xdata sum = 0;
    for(cnt = 0; cnt < bags; cnt++) sum += weight[cnt];
    sum /= bags;
    shut_fb_w = shut_fb_w + (sp_weight + residual_weight - sum)/2;
    sf_weight = shut_fb_w - sf_weight_adj_val;
}




