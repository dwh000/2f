/*******************************************************************************
*文件名: weighting.c
*作  者: 王文辉
*单  位: 唐山智能电子有限公司
*日  期: 2012-9-21
*版  本: 实验版本
*功能描述: AD转换及称重测量程序
*******************************************************************************/
#include "weighting.h"

#define SAMPLE_LENGTH	20
#define	POLAR	0			//0定义单极性,1定义为双极性

extern s32bit xdata tare_weight;
extern s16bit xdata	zero_scale_value;
extern u32bit xdata filter2_out,load_cell_span;
extern u32bit xdata scale_output_val,scale_counterweight_val;
extern u8bit xdata filter_coefficient1;

sbit ADC_BP		= P5^0;	//=1为双极性控制,=0为单极性控制
sbit ADC_SMODE	= P5^1;	//串行接口模式控制,1为自同步模式,0为外部时钟同步模式
sbit ADC_CS		= P5^2;	//片选端,0为串口可被外部设备使用,为1 SDO及SCLK为高阻态.
sbit ADC_RDY	= P5^3;	//转换完成指示,=0表示转换完成,可以从串口读出;数据读出完
						//成后为1
sbit ADC_SCLK	= P5^4;	//串口时钟
sbit ADC_SDO	= P5^5;	//串口数据
sbit ADC_CONV	= P5^7;	//=0启动一个转换,如果转换完成RDY变为0后,此端口依然被
						//置零,会重新启动一次转换
sbit ADC_RST	= P5^6;	//复位控制端.
/*双极性转换程序,包含了负数的字节扩展和负数迁移为零的程序*/
#if	POLAR
/*******************************************************************************
*原  型:void adc_init(void)
*形  参:无.
*功  能:AD转换器初始化程序
*返回值:无.
*******************************************************************************/
void adc_init(void)
{
	u8bit cnt;
	SFRPAGE = CONFIG_PAGE;
	ADC_RST = 0;
	_nop_();
	_nop_();
	_nop_();
	ADC_RST = 1;
	ADC_BP	= 1;				//双极性转换
	ADC_SMODE = 0;				//外部时钟同步模式
	ADC_CS = 1;					//ADC串口禁止
	ADC_SCLK = 0;				//时钟线拉低
	ADC_CONV = 1;				//禁止ADC转换.
}
/*******************************************************************************
*原  型:u32bit get_adc(void)
*形  参:无.
*功  能:进行一次AD转换,并读取转换结果
*返回值:无符号32位数值		AD转换的结果
*******************************************************************************/
u32bit get_adc(void)
{
	u8bit i,sign_flag = 0;
	s32bit ad_buf = 0;
	u32bit ad_result;
	SFRPAGE = CONFIG_PAGE;
	EA = 0;
	ADC_CONV = 0;
	for(i=0; i<220;i++)	;
	ADC_CONV = 1;
	while(ADC_RDY == 1)	_nop_();
	_nop_();
	ADC_CS = 0;
	_nop_();
	if(ADC_SDO == 1)	sign_flag = 1;
	else	sign_flag = 0;
	for(i=0; i<24;){
		ad_buf <<= 1;
		if(ADC_SDO == 1)	ad_buf += 1;
		ADC_SCLK = 1;
		i++;
		ADC_SCLK = 0;
	}
	ADC_CS = 1;
	if(sign_flag == 1)	ad_buf |= 0xff000000;
	ad_buf *= 2;
	ad_result = ad_buf + 0x800000;
	EA = 1;
	return ad_result;
}
/*单性转换程序*/
#else
void adc_init(void)
{
	//u8bit cnt;
	SFRPAGE = CONFIG_PAGE;
	ADC_RST = 0;
	_nop_();
	_nop_();
	_nop_();
	ADC_RST = 1;
	ADC_BP	= 0;				//单极性转换
	ADC_SMODE = 0;				//外部时钟同步模式
	ADC_CS = 1;					//ADC串口禁止
	ADC_SCLK = 0;				//时钟线拉低
	ADC_CONV = 1;				//禁止ADC转换.
}
	
u8bit get_adc(u32bit *pADVal)
{
	u8bit i;
	u16bit mmm = 0;
	u32bit ad_buf = 0;
	EA = 0;
	SFRPAGE = CONFIG_PAGE;
	adc_init();
	ADC_CONV = 0;
	while(ADC_RDY){
		mmm++;
		if(mmm>0x200)
		return BAD_VAL;
	}
	ADC_CONV = 1;
	_nop_();
	ADC_CS = 0;
	_nop_();
	for(i=0; i<24;){
		ad_buf <<= 1;
		if(ADC_SDO == 1) ad_buf += 1;
		else _nop_();
		ADC_SCLK = 1;
		i++;
		ADC_SCLK = 0;
	}
	ADC_CS = 1;
	EA = 1;
	*pADVal = ad_buf;
	if((ad_buf == 0)||(ad_buf == 0xffffff)) return BAD_VAL;
	return GOOD;
}

#endif
/*******************************************************************************
*原  型:u32bit filter1_func(void)
*形  参:无.
*功  能:中值平均值滤波函数
*返回值:无符号32位数值		中值平均值滤波的结果
*******************************************************************************/	
u32bit filter1_func(void) 
{
	u8bit  cnt;
	u32bit adc_val,adc_min,adc_max,adc_sum,filter1_out;
	while(get_adc(&adc_val) != GOOD) adc_init();
	adc_max = adc_val;
	adc_min = adc_val;
	adc_sum = adc_val;
	for(cnt = 0; cnt < (SAMPLE_LENGTH - 1);cnt++){
		while(get_adc(&adc_val) != GOOD) adc_init();
		adc_sum += adc_val;
		if(adc_val > adc_max)	adc_max = adc_val;
		else if(adc_val < adc_min)	adc_min = adc_val;
	}
	adc_sum -= adc_max;
	adc_sum -= adc_min;
	filter1_out = adc_sum/(SAMPLE_LENGTH - 2);
	return filter1_out;
}

/*******************************************************************************
*原  型:u32bit filter1_clr(void)
*形  参:无.
*功  能:中值平均值滤波函数
*返回值:无符号32位数值		中值平均值滤波的结果
*******************************************************************************/	
u32bit filter1_clr(void) 
{
	u8bit  cnt;
	u32bit adc_val,adc_min,adc_max,adc_sum,filter1_out;
	while(get_adc(&adc_val) != GOOD) ;//adc_init();
	adc_max = adc_val;
	adc_min = adc_val;
	adc_sum = adc_val;
	for(cnt = 0; cnt < 65;cnt++){
		while(get_adc(&adc_val) != GOOD) ;//adc_init();
		adc_sum += adc_val;
		if(adc_val > adc_max)	adc_max = adc_val;
		else if(adc_val < adc_min)	adc_min = adc_val;
	}
	adc_sum -= adc_max;
	adc_sum -= adc_min;
	filter1_out = adc_sum>>6;
	return filter1_out;
}
/*******************************************************************************
*原  型:u32bit filter2_func(void)
*形  参:无.
*功  能:一阶低通滤波函数
*返回值:无符号32位数值		一阶低通滤波的结果
*******************************************************************************/
u32bit filter2_func(u32bit filter1_out)
{
	filter2_out *= filter_coefficient1;
	filter2_out = filter2_out + (filter1_out * (100-filter_coefficient1));
	filter2_out /= 100;
	return filter2_out; 
}
	
	
u32bit GW_measure(void)					//结果为未标定毛重
{
	float result;
	result = filter2_func(filter1_func());
	result *= load_cell_span;
	result /= 0xffffff;
	return ((u32bit)result);
}
s32bit NW_measure(void)				//结果为未标定净重
{
	s32bit result;
	result = GW_measure() - tare_weight;
	return result;
}

s32bit NW_measure_clr(void)				//结果为未标定净重
{
	float result;
	filter2_out = filter1_clr();
	result = filter2_out;
	result *= load_cell_span;
	result /= 0xffffff;
	result = result - tare_weight;
	return ((s32bit)result);
}
/*u32bit GW_scale(void)					//结果为标定后的毛重值
	{
	float result;
	result = GW_measure() * scale_counterweight_val / scale_output_val;
	//除以标定点砝码输出值
	return ((u32bit)result);
	}*/
s32bit NW_scale(void)				//结果为标定后的净重值
{
	float result;
	result = NW_measure();
	result *= scale_counterweight_val;
	result /= scale_output_val;
	result -= zero_scale_value;
	return ((s32bit)result);
}
s32bit NW_scale_clr(void)			//零点清零专用程序
{
	float result;
	result = NW_measure_clr();
	result *= scale_counterweight_val;
	result /= scale_output_val;
	result -= zero_scale_value;
	return ((s32bit)result);
}