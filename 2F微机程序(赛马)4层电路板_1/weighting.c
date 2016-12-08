/*******************************************************************************
*�ļ���: weighting.c
*��  ��: ���Ļ�
*��  λ: ��ɽ���ܵ������޹�˾
*��  ��: 2012-9-21
*��  ��: ʵ��汾
*��������: ADת�������ز�������
*******************************************************************************/
#include "weighting.h"

#define SAMPLE_LENGTH	20
#define	POLAR	0			//0���嵥����,1����Ϊ˫����

extern s32bit xdata tare_weight;
extern s16bit xdata	zero_scale_value;
extern u32bit xdata filter2_out,load_cell_span;
extern u32bit xdata scale_output_val,scale_counterweight_val;
extern u8bit xdata filter_coefficient1;

sbit ADC_BP		= P5^0;	//=1Ϊ˫���Կ���,=0Ϊ�����Կ���
sbit ADC_SMODE	= P5^1;	//���нӿ�ģʽ����,1Ϊ��ͬ��ģʽ,0Ϊ�ⲿʱ��ͬ��ģʽ
sbit ADC_CS		= P5^2;	//Ƭѡ��,0Ϊ���ڿɱ��ⲿ�豸ʹ��,Ϊ1 SDO��SCLKΪ����̬.
sbit ADC_RDY	= P5^3;	//ת�����ָʾ,=0��ʾת�����,���ԴӴ��ڶ���;���ݶ�����
						//�ɺ�Ϊ1
sbit ADC_SCLK	= P5^4;	//����ʱ��
sbit ADC_SDO	= P5^5;	//��������
sbit ADC_CONV	= P5^7;	//=0����һ��ת��,���ת�����RDY��Ϊ0��,�˶˿���Ȼ��
						//����,����������һ��ת��
sbit ADC_RST	= P5^6;	//��λ���ƶ�.
/*˫����ת������,�����˸������ֽ���չ�͸���Ǩ��Ϊ��ĳ���*/
#if	POLAR
/*******************************************************************************
*ԭ  ��:void adc_init(void)
*��  ��:��.
*��  ��:ADת������ʼ������
*����ֵ:��.
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
	ADC_BP	= 1;				//˫����ת��
	ADC_SMODE = 0;				//�ⲿʱ��ͬ��ģʽ
	ADC_CS = 1;					//ADC���ڽ�ֹ
	ADC_SCLK = 0;				//ʱ��������
	ADC_CONV = 1;				//��ֹADCת��.
}
/*******************************************************************************
*ԭ  ��:u32bit get_adc(void)
*��  ��:��.
*��  ��:����һ��ADת��,����ȡת�����
*����ֵ:�޷���32λ��ֵ		ADת���Ľ��
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
/*����ת������*/
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
	ADC_BP	= 0;				//������ת��
	ADC_SMODE = 0;				//�ⲿʱ��ͬ��ģʽ
	ADC_CS = 1;					//ADC���ڽ�ֹ
	ADC_SCLK = 0;				//ʱ��������
	ADC_CONV = 1;				//��ֹADCת��.
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
*ԭ  ��:u32bit filter1_func(void)
*��  ��:��.
*��  ��:��ֵƽ��ֵ�˲�����
*����ֵ:�޷���32λ��ֵ		��ֵƽ��ֵ�˲��Ľ��
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
*ԭ  ��:u32bit filter1_clr(void)
*��  ��:��.
*��  ��:��ֵƽ��ֵ�˲�����
*����ֵ:�޷���32λ��ֵ		��ֵƽ��ֵ�˲��Ľ��
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
*ԭ  ��:u32bit filter2_func(void)
*��  ��:��.
*��  ��:һ�׵�ͨ�˲�����
*����ֵ:�޷���32λ��ֵ		һ�׵�ͨ�˲��Ľ��
*******************************************************************************/
u32bit filter2_func(u32bit filter1_out)
{
	filter2_out *= filter_coefficient1;
	filter2_out = filter2_out + (filter1_out * (100-filter_coefficient1));
	filter2_out /= 100;
	return filter2_out; 
}
	
	
u32bit GW_measure(void)					//���Ϊδ�궨ë��
{
	float result;
	result = filter2_func(filter1_func());
	result *= load_cell_span;
	result /= 0xffffff;
	return ((u32bit)result);
}
s32bit NW_measure(void)				//���Ϊδ�궨����
{
	s32bit result;
	result = GW_measure() - tare_weight;
	return result;
}

s32bit NW_measure_clr(void)				//���Ϊδ�궨����
{
	float result;
	filter2_out = filter1_clr();
	result = filter2_out;
	result *= load_cell_span;
	result /= 0xffffff;
	result = result - tare_weight;
	return ((s32bit)result);
}
/*u32bit GW_scale(void)					//���Ϊ�궨���ë��ֵ
	{
	float result;
	result = GW_measure() * scale_counterweight_val / scale_output_val;
	//���Ա궨���������ֵ
	return ((u32bit)result);
	}*/
s32bit NW_scale(void)				//���Ϊ�궨��ľ���ֵ
{
	float result;
	result = NW_measure();
	result *= scale_counterweight_val;
	result /= scale_output_val;
	result -= zero_scale_value;
	return ((s32bit)result);
}
s32bit NW_scale_clr(void)			//�������ר�ó���
{
	float result;
	result = NW_measure_clr();
	result *= scale_counterweight_val;
	result /= scale_output_val;
	result -= zero_scale_value;
	return ((s32bit)result);
}