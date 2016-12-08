/*******************************************************************************
*�ļ���: 2F1������.c
*��  ��: ���Ļ�
*��  λ: ��ɽ���ܵ������޹�˾
*��  ��: 2012-9-21
*��  ��: ʵ��汾
*��������: 2f��������
*******************************************************************************/

/*ͷ�ļ�����*******************************************************************/
#include "public.h"			//��ʱ����,�˿ڶ���,���Ͷ��弰�궨��
#include "disp.h"			//��ʾ����
#include "24c04.h"			//�������漰��ȡ
#include "key_func.h"		//������غ���
#include "menu_func.h"		//�˵���غ���
#include "timer.h"			//��ʱ����ʼ��������
#include "weighting.h"		//AD,����,��ȱ任���˲�
#include "terminal.h"		//���ڳ�ʼ�������ڶ�д
#include <stdio.h>			//C��׼IO����


/*ȫ�ֱ�������*****************************************************************/
s16bit xdata    drop_weight,				//�ֶ����ֵ
                residual_weight,			//���ؾ���ֵ
                zero_scale_value;			//����ֵ
u32bit xdata 	filter2_out = 0,			//һ�׵�ͨ�˲������ֵ
				filter1_out,				//��ֵƽ��ֵ�˲����
				load_cell_span,				//������������Χ
				tare_weight,				//Ƥ��
				scale_output_val,			//�궨���������ֵ
				scale_counterweight_val;	//�궨������ֵ
u32bit xdata    DropCounter _at_ 0x180;		//����������,ָ���洢��ַΪ0x180,xdata����,���Ҹ������ڴ治����
u16bit xdata 	sp_weight,					//��������ֵ
				sf_weight,					//��ϸ���л�����
                sf_weight_adj_val,          //
				weight_correct_val,			//��������ֵ
				shut_fb_w;					//��բ���б�ֵ
u8bit xdata     ZeroFlag,                   //��������־
                ZeroCnt = 0,                    //��������.
                DpErrCnt = 0,               //����DPͨѶ����ļ�ʱ
                DpErrFlag = 0,              //DPͨѶ�����־
                t1_cnt,						//t1��ʱ����������
				shut_cnt,					//��բ���б����
				filter_coefficient,			//�˲�ϵ��
				filter_coefficient1,		//�������˲�ϵ��
				err_code = 0,				//�������
				sf_switch,					//��ϸ������
				ol_track_sw,				//����׷�ٿ���
				track_bags,					//׷�ٴ���
				w_save_cnt = 0,				//���ر������
				cl_correct_sw,				//�ջ���������
				arrival_time,				//�ִ�ʱ��
				A_T_time = 0,				//�ִ�ʱ���ݴ�ֵ
				counter_sw,					//��������
				disp_cache,					//������ʾ����
				CommAddr,					//ͨ�ŵ�ַ
				DpSwitch,					//ͨ�Ź��ܿ���
				DispCnt,					//��ʾ������
				flashboard_cnt;				//��բ�嶨ʱʱ��,��λ0.1s
bit				t1_flag,					//T1��ʱ�����־
				startup_flag = 0,			//������־
				DropFlag = 0,				//������־
				AutoZeroFlag = 0,			//�Զ������־
				discharge_bag_loc_flag = 0,	//�������־
				flashboard_pulse_flag,		//��բ�嶨ʱ�����־
				re_fill_flag,				//���¹�װ��־
				DpEnFlag = 0,				//Pb���ݽ������ʹ��.
				discharge_pulse_flag = 0,	//������ʱ�����־
				shut_flag = 0,				//��բ���б��־
				disp_flag = 1;				//��ʾ��־
u16bit xdata	weight[10],				//׷��ʱ,���ر���;����������բ�б�ֵ.
                WeightOfLast;
s32bit xdata	adc,adc_disp;					//ADת�������Ĵ���ֵ


/*�ⲿ��������*****************************************************************/
extern u8bit code	seg_sym[40];			//�ַ�����
extern u8bit code	seg_dot[40];
extern u8bit xdata	TxBuf[70],RxBuf[60];


/*��������*********************************************************************/
void mcu_init();							//��Ƭ����ʼ������
void update_shut_fb_w(u8bit bags);
void ZeroPointDet(void);
void ShutAndCorrect(void);


/*����˿�λ����****************************************************************
sbit	discharge_bag_en		= P1^0;	/* Ƥ������
sbit	zero_loc				= P2^0;	/* �����
sbit	discharge_bag_loc		= P2^1;	/* ������ 
sbit	open_flashboard_det		= P2^2;	/* ��բ���ź� *
sbit	gate_opened_loc			= P2^3;	/* բ���ѿ��� *
sbit	bag_det					= P2^4;	/* ����ź� *
sbit	add_correct				= P2^5;	/* ���س�+У���ź� *
sbit	reduce_correct			= P2^6;	/* ���س�-У���ź� *
sbit	into_bag_loc			= P2^7;	 ����� 

sbit FullOut					=	P3^1;		//����װ�����
sbit SizeFlowOut				=	p3^2;		//��ϸ���л����
//����˿�λ����****************************************************************
sbit cyl_sw_out					=	P3^1;		//���׿���
sbit fine_flow_out				=	P3^2;		//��ϸ���л����
sbit discharge_bag_sw_out		=	P3^3;		//ж��
sbit flashboard_sw_out			=	P3^4;		//��բ��
sbit fill_mot_sw_out			=	P3^5;		//���ʹ��
sbit clamping_bag_out			= 	P3^4;		//ѹ��*************************/




/*������***********************************************************************/
void main(void)
{
    mcu_init();                                             //��Ƭ����ʼ��

    /*�ϵ��Զ�����*************************************************************/
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
        menu_func();                                        //���ò˵�����
        tare_zero_func();                                   //����ȥƤ���㺯��
    //}

    #if saima
    FullOut = SHUT;
    SizeFlowOut = SHUT;

    while(1){
        s32bit xdata shut_error;
        #if DP_ON
            if(PbRestart() == TIMEOUT){                                    //���PB״̬������PB����
                DpErrCnt ++ ;
                if(DpErrCnt > 3){
                    DpSwitch = OFF;
                    DpErrFlag = 1;
                }
            }
            PbTare();                                       //����ȥƤ����
            PbNW_measure();                                 //�����������ˢ��
        #endif
        //�����޸ļ���ʾʱ��
        menu_func();                                        //���ò˵�����
        dm_sp_weight();                                     //����ֱ���޸��趨ֵ����
        tare_zero_func();                                   //����ȥƤ���㺯��
        adc = NW_scale();
        {/*ˢ����ʾ����*/
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
            //��բ���б����
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
*ԭ  ��:void ZeroPointDet(void)
*��  ��:��
*��  ��:���ڹ�����⼰���������
*����ֵ:��.
*******************************************************************************/
void ZeroPointDet(void)
{
    s16bit xdata czero_scale_value;
    if(startup_flag)    return;
    if((DropFlag) && (zero_loc == ACTIVE)){
        czero_scale_value = zero_scale_value;
        zero_scale_value = 0;
        adc = NW_scale_clr();
        if((adc > 3500) || (adc < -3500)){//��������ֵ�������㷶Χ,��
            zero_scale_value = czero_scale_value;
            if(adc > 3500) disp_symbol(ERR_OH);
            else if(adc < -3500) disp_symbol(ERR_OL);
        }
        else{//��������ֵ�����㷶Χ��,��
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
    u16bit DropVal = (sp_weight/5)<<1;                      //�����б�ֵ
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
        PbNW_measure();                                     //�����������ˢ��
        #endif
        if(zero_loc == ACTIVE){
            Disp50kgLoc();
            t1_100ms(10);
            disp_flag = 0;
            while(zero_loc == ACTIVE);
            Disp50kgRst();
            WeightOfLast = (u16bit)adc;               //���ݵ�ǰ����
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
//							���������ӳ���									  //
//****************************************************************************//

/*******************************************************************************
*ԭ  ��:void Port_IO_Init(void);
*��  ��:��.
*��  ��:IO�˿�����.
*����ֵ:��.
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
*ԭ  ��:void stop_wdt(void);
*��  ��:��.
*��  ��:�رտ��Ź�.
*����ֵ:��.
*******************************************************************************/
void stop_wdt(void)
{
	EA = 0;
	WDTCN = 0XDE;
	WDTCN = 0XAD;
}
/*******************************************************************************
*ԭ  ��:void sysclk_init(void);
*��  ��:��.
*��  ��:ϵͳʱ�ӳ�ʼ��.
*����ֵ:��.
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
	//����DP����
	DpSwitch = OFF;
	eeprom_write(&DpSwitch,DP_SW_ADDR,1);
	
	//����DP��ַ
	CommAddr = 1;
	eeprom_write(&CommAddr,COMMADDR_ADDR,1);
	
	//�����˲�ϵ��
	filter_coefficient = 80;
	eeprom_write(&filter_coefficient,FILTER_ADDR,1);
	
	//�����趨ֵ
	sp_weight = 50000;
	eeprom_write((u8bit *)&sp_weight,SP_WEIGHT_ADDR,2);
	
	//���洫��������
	load_cell_span = 350000;
	eeprom_write((u8bit *)&load_cell_span,CELL_SPAN_ADDR,4);
	
	//����궨���ֵ
	scale_output_val = 34306;
	eeprom_write((u8bit *)&scale_output_val,SCALE_OUTPUT_ADDR,4);
	
	//����궨��������
	scale_counterweight_val = 40000;
	eeprom_write((u8bit *)&scale_counterweight_val,COUNTERWEIGHT_ADDR,4);
	
	//����׷�ٴ���
	track_bags = 5;
	eeprom_write(&track_bags,TRACK_BAGS_ADDR,1);
	
	//�����ϸ���л�����
	sf_switch = OFF;
	eeprom_write(&sf_switch,SF_SWITCH_ADDR,1);
	
	//�����ϸ���л�ֵ
	sf_weight_adj_val = 5000;
	eeprom_write((u8bit *)&sf_weight_adj_val,SF_WEIGHT_ADDR,2);
    
	//�������
	drop_weight = 0;
	eeprom_write((u8bit *)&drop_weight,DROP_WEIGHT_ADDR,2);
	
	//���澻��
	residual_weight = 0;
	eeprom_write((u8bit *)&residual_weight,R_WEIGHT_ADDR,2);
	
	//�����������ֵ
	weight_correct_val = 0;
	eeprom_write((u8bit *)&weight_correct_val,WEIGHT_CORRECT_ADDR,2);
	
	//����ִ�ʱ��
	arrival_time = 0;
	eeprom_write(&arrival_time,ARRIVAL_TIME_ADDR,1);
	
	//���濪��׷�ٿ���
	ol_track_sw = OFF;
	eeprom_write(&ol_track_sw,OL_TRACK_SW_ADDR,1);
	
	//����ջ�У������
	cl_correct_sw = OFF;
	eeprom_write(&cl_correct_sw,CL_CORRECT_SW_ADDR,1);
	
	//�������������
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
	
	//��ȡDPͨ�ſ���
	eeprom_read(&DpSwitch,DP_SW_ADDR,1);
	//��ȡDPͨ�ŵ�ַ.
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

	//��ȡ�˲�ϵ��
	eeprom_read(&filter_coefficient,FILTER_ADDR,1);

	if(filter_coefficient > 90){
		filter_coefficient = 60;
		eeprom_write(&filter_coefficient,FILTER_ADDR,1);
	}
	filter_coefficient1 = (uchar)filter_coefficient * 1.1;
		
	//��ȡ�趨ֵ	
	eeprom_read((u8bit *)&sp_weight,SP_WEIGHT_ADDR,2);

	while((sp_weight < 22000) || (sp_weight > 65000)){
		disp_symbol(ERR_SP);
		menu_func();
	}
	
	//��ȡ����������	
	eeprom_read((u8bit *)&load_cell_span,CELL_SPAN_ADDR,4);

	while((load_cell_span != 100000) && (load_cell_span != 150000)
		&& (load_cell_span != 200000) && (load_cell_span != 250000)
		&& (load_cell_span != 300000) && (load_cell_span != 350000)){
		disp_symbol(ERR_LS);
		menu_func();
	}

	//��ȡ�궨���ֵ
	eeprom_read((u8bit *)&scale_output_val,SCALE_OUTPUT_ADDR,4);
	while((scale_output_val < 19000) || (scale_output_val > 62000)){
		disp_symbol(E01);
		menu_func();
	}

	//��ȡ�궨��������
	eeprom_read((u8bit *)&scale_counterweight_val,COUNTERWEIGHT_ADDR,4);
	while((scale_counterweight_val<20000)||(scale_counterweight_val>60000)){
		disp_symbol(E02);
		menu_func();
	}

	//��ȡ׷�ٴ���		
	eeprom_read(&track_bags,TRACK_BAGS_ADDR,1);
	if ((track_bags == 0) || (track_bags > 10)){
		track_bags = 5;
		eeprom_write(&track_bags,TRACK_BAGS_ADDR,1);
	}
	
	//��ȡƤ��ֵ
	eeprom_read((u8bit *)&tare_weight,TW_ADDR,4);
	/*while(tare_weight <= 10000){
		disp_symbol(E07);
		menu_func();
	}*/

	//��ȡ��ϸ���л�����
	eeprom_read(&sf_switch,SF_SWITCH_ADDR,1);
	
	//��ȡ��ϸ���л�ֵ
	eeprom_read((u8bit *)&sf_weight_adj_val,SF_WEIGHT_ADDR,2);
	while((sf_weight_adj_val < 100) || (sf_weight_adj_val > 10000)){
		disp_symbol(ERR_HP);
		menu_func();
	}

	//��ȡ���
	eeprom_read((u8bit *)&drop_weight,DROP_WEIGHT_ADDR,2);
	while((drop_weight < -2500) || (drop_weight > 2500)){
		disp_symbol(E08);
		menu_func();
	}

	
	//��ȡ����
	eeprom_read((u8bit *)&residual_weight,R_WEIGHT_ADDR,2);
	while((residual_weight < -2500) || (residual_weight > 2500)){
		disp_symbol(E09);
		menu_func();
	}

	//��������ֵ
	eeprom_read((u8bit *)&weight_correct_val,WEIGHT_CORRECT_ADDR,2);
	while(weight_correct_val > 1500){
		disp_symbol(E10);
		menu_func();

	}

	//��ȡ�ִ�ʱ��
	eeprom_read(&arrival_time,ARRIVAL_TIME_ADDR,1);
	//��ȡ�������ٿ���
	eeprom_read(&ol_track_sw,OL_TRACK_SW_ADDR,1);
	
	//��ȡ�ջ�У������
	eeprom_read(&cl_correct_sw,CL_CORRECT_SW_ADDR,1);

	if((ol_track_sw == ON) && (cl_correct_sw == ON)){
		ol_track_sw = OFF;
		cl_correct_sw = OFF;
		disp_symbol(E12);
	}
	//��ȡ��������
	eeprom_read(&counter_sw,COUTER_SW_ADDR,1);
	//��ʼ����բ���б�ֵ
	shut_fb_w = sp_weight - drop_weight;
    sf_weight = shut_fb_w - sf_weight_adj_val;
	//��ʼ����׷�ٶ���
	for(cnt = 0;cnt < 10;cnt++)	weight[cnt] = sp_weight + residual_weight;
}

void ClearDropCounter(void)
{
    SFRPAGE = 0;
    if(RSTSRC & BIT1)   DropCounter = 0;
    return;
}
/*******************************************************************************
*ԭ  ��:void mcu_init(void);
*��  ��:��.
*��  ��:��Ƭ���ĳ�ʼ������.
*����ֵ:��.
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
*ԭ  ��:void update_shut_fb_w(u8bit bags);
*��  ��:  bags    ׷�ٴ��� 
*��  ��:���¹�բ���趨ֵ,���ڿ���׷�ٹ���.
*����ֵ:��.
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




