/*******************************************************************************
*文件名: menu_func.c
*作  者: 王文辉
*单  位: 唐山智能电子有限公司
*日  期: 2012-9-21
*版  本: 实验版本
*功能描述: 2f微机设置菜单相关程序
*******************************************************************************/
#include "menu_func.h"
#include "key_func.h"
#include "disp.h"
#include "24c04.h"
#include "timer.h"
#include "weighting.h"
#include "terminal.h"
extern s16bit xdata drop_weight,residual_weight,zero_scale_value;
extern u16bit xdata sp_weight,sf_weight,sf_weight_adj_val,weight_correct_val,shut_fb_w;
extern u8bit xdata err_code,filter_coefficient,filter_coefficient1,sf_switch,ol_track_sw,track_bags;
extern u8bit xdata track_bags,cl_correct_sw,arrival_time,counter_sw;
extern u8bit xdata DpSwitch,CommAddr,DpErrFlag;
extern bit t0_flag,t1_flag;
extern u32bit xdata load_cell_span,scale_output_val,scale_counterweight_val,tare_weight,DropCounter;
extern u8bit code seg_sym[40];
extern u8bit code seg_dot[40];
bit t1_sta_flag,exit_flag;
u8bit xdata mr_menu,mf_menu,mc_menu,mt_menu,md_menu;
extern u8bit xdata	TxBuf[60];
/*******************************************************************************
*原  型:void dm_sp_weight(void);
*形  参:无.
*功  能:直接修改设定值
*返回值:无.
*******************************************************************************/
void dm_sp_weight(void)
{
	u8bit xdata copy_EIE1,copy_EIE2,copy_IE,key_val;
	u16bit xdata backup_sp_weight;
	bit ud_key_flag = 0;
	t1_sta_flag = 0;
	copy_EIE1 = EIE1;
	copy_EIE2 = EIE2;
	copy_IE = IE;									//备份中断允许
	IE = 0;
	IE = 0;
	EIE1 = 0;
	EIE2 = 0;										//关所有中断
	key_val = get_key(CHK_ALL_KEY);
	if(key_val == UP_CLOSED)	ud_key_flag = 1;
	else if(key_val == DWN_CLOSED)	ud_key_flag = 1;
	else{
		IE = copy_IE;
		IE = copy_IE;
		EIE1 = copy_EIE1;
		EIE2 = copy_EIE2;
		return;
	}
	run_disp(sp_weight);
	backup_sp_weight = sp_weight;
	while(ud_key_flag == 1){
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == UP_CLOSED)	sp_weight += 100;
		else if(key_val == DWN_CLOSED)	sp_weight -= 100;
		else if(key_val == ENT_CLOSED)	ud_key_flag = 0;
		else if(t1_sta_flag == 0){
			t1_100ms(10);
			t1_sta_flag = 1;
		}
		if(t1_flag == 1){
			if(get_key(CHK_ALL_KEY) == NOKEY_CLOSED)	ud_key_flag = 0;
			t1_sta_flag = 0;
			t1_stop();
			t1_flag = 0;
		}
		run_disp(sp_weight);
	}
	run_disp(sp_weight);
	//shut_fb_w = sp_weight - drop_weight;
	eeprom_write((u8bit *)&sp_weight,SP_WEIGHT_ADDR,2);
	shut_fb_w = shut_fb_w + sp_weight - backup_sp_weight;
    sf_weight = shut_fb_w - sf_weight_adj_val;
	EIE1 = copy_EIE1;
	EIE2 = copy_EIE2;
	IE = copy_IE;
	IE = copy_IE;
	return;	
}
/*******************************************************************************
*原  型:void tare_zero_func(void);
*形  参:无.
*功  能:去皮清零函数
*返回值:无.
*******************************************************************************/
void tare_zero_func(void)
{
	s32bit xdata nw_val,gw_val,copy_zero_scale_value;
	u8bit xdata copy_EIE1,copy_EIE2,copy_IE;
	bit t1_sta_flag = 0;
	copy_EIE1 = EIE1;
	copy_EIE2 = EIE2;
	copy_IE = IE;									//备份中断允许
	IE = 0;
	IE = 0;
	EIE1 = 0;
	EIE2 = 0;										//关所有中断
	if(get_key(CLR_CLOSED) == CLR_CLOSED){
		if(t1_sta_flag == 0){
			t1_100ms(20);
			t1_sta_flag = 1;
		}
		copy_zero_scale_value = zero_scale_value;
		zero_scale_value = 0;
		while((get_key(CLR_RELEASE) != CLR_RELEASE) && (t1_flag != 1)){
			nw_val = NW_scale();
			weight_disp(nw_val);
		}
		if(t1_flag != 1){						//TZP03,执行清零程序
			if((nw_val > 2500) || (nw_val < -2500))
				zero_scale_value = copy_zero_scale_value;
			else	zero_scale_value = nw_val;
			nw_val = NW_scale();
			weight_disp(nw_val);
			t1_stop();
		}
		else{									//TZP01,执行去皮程序
			t1_stop();
			t1_sta_flag = 0;
			while((get_key(CLR_RELEASE)!=CLR_RELEASE))
				weight_disp(GW_measure());
			while(get_key(CLR_CLOSED) != CLR_CLOSED){
				if(t1_sta_flag == 0){
					t1_100ms(20);
					t1_sta_flag = 1;
				}
				if(t1_flag == 1){
					zero_scale_value = copy_zero_scale_value;
					t1_stop();
					EIE1 = copy_EIE1;
					EIE2 = copy_EIE2;
					IE = copy_IE;
					IE = copy_IE;
					return;
				}
			}
			t1_stop();
			while(get_key(CLR_RELEASE) != CLR_RELEASE) ;
			while(get_key(ENT_CLOSED) != ENT_CLOSED){
				if(t1_sta_flag == 0){
					t1_100ms(20);
					t1_sta_flag = 1;
				}
				if(t1_flag == 1){
					zero_scale_value = copy_zero_scale_value;
					t1_stop();
					EIE1 = copy_EIE1;
					EIE2 = copy_EIE2;
					IE = copy_IE;
					IE = copy_IE;
					return;
				}
				gw_val = GW_measure();
				flash_disp(gw_val);
			}
			t1_stop();
			while(get_key(ENT_RELEASE) != ENT_RELEASE) ;
			tare_weight = gw_val;
			zero_scale_value = 0;
			eeprom_write((u8bit *)&tare_weight,TW_ADDR,4); 
		}	
	}
	EIE1 = copy_EIE1;
	EIE2 = copy_EIE2;
	IE = copy_IE;
	IE = copy_IE;
	return;		
}
/*******************************************************************************
*原  型:void sp_weight_adj(void);
*形  参:无.
*功  能:设定值修改函数
*返回值:无.
*******************************************************************************/	
void sp_weight_adj(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit speed_conter,key_val = 0;
	u16bit xdata backup_sp_weight;
	err_code = 0;
	t1_stop();
	backup_sp_weight = sp_weight;
	weight_disp(sp_weight);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == NOKEY_CLOSED)	speed_conter = 0;
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	sp_weight += 1;
			else if(speed_conter < 20)	sp_weight += 10;
			else if(speed_conter < 30)	sp_weight += 100;
			else sp_weight += 500;
			para_change_flag = 1;			
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	sp_weight -= 1;
			else if(speed_conter < 20)	sp_weight -= 10;
			else if(speed_conter < 30)	sp_weight -= 100;
			else sp_weight -= 500;
			para_change_flag = 1;	
		}
		if(sp_weight > 65000)	sp_weight = 22000;
		else if(sp_weight < 22000)	sp_weight = 65000;
		weight_disp(sp_weight);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	sp_weight = backup_sp_weight;	//定时时间到,恢复备份
	else if(para_change_flag == 1){						//参数改变,保存参数
		t1_100ms(200);
		//shut_fb_w = sp_weight - drop_weight;
		shut_fb_w = shut_fb_w + sp_weight - backup_sp_weight;
        sf_weight = shut_fb_w - sf_weight_adj_val;
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&sp_weight,SP_WEIGHT_ADDR,2);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}	
	}
}
/*******************************************************************************
*原  型:void filter_para_adj(void);
*形  参:无.
*功  能:滤波系数修改函数
*返回值:无.
*******************************************************************************/
void filter_para_adj(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit backup_para;
	u8bit speed_conter,key_val = 0;
	t1_stop();
	err_code = 0;
	backup_para = filter_coefficient;
	disp_int(filter_coefficient);
	while(get_key(SET_RELEASE) != SET_RELEASE )	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == NOKEY_CLOSED)	speed_conter = 0;
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	filter_coefficient += 1;
			else if(speed_conter < 20)	filter_coefficient += 2;
			else filter_coefficient += 5;
			para_change_flag = 1;
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	filter_coefficient -= 1;
			else if(speed_conter < 20)	filter_coefficient -= 2;
			else filter_coefficient -= 5;
			para_change_flag = 1;	
		}
		if(filter_coefficient > 200)	filter_coefficient = 90;
		else if(filter_coefficient > 90)	filter_coefficient = 0;
		disp_int(filter_coefficient);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	filter_coefficient = backup_para;
	else if(para_change_flag == 1){	//参数改变,且不是因为定时时间到退出修改参数
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			filter_coefficient1 = (uchar) filter_coefficient * 1.1;
			err_code = eeprom_write(&filter_coefficient,FILTER_ADDR,1);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}
	}
}
/*******************************************************************************
*原  型:void sf_weight_adj(void);
*形  参:无.
*功  能:粗细流切换值设置函数
*返回值:无.
*******************************************************************************/
void sf_weight_adj(void)					//size flow weight
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit speed_conter,key_val = 0;
	u16bit backup_para = sf_weight_adj_val;
	t1_stop();
	err_code = 0;
	weight_disp(sf_weight_adj_val);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == NOKEY_CLOSED)	speed_conter = 0;
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <30) speed_conter++;
			if(speed_conter < 10)	sf_weight_adj_val += 1;
			else if(speed_conter < 20)	sf_weight_adj_val += 10;
			else if(speed_conter <= 30)	sf_weight_adj_val += 100;
			para_change_flag = 1;
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <30) speed_conter++;
			if(speed_conter < 10)	sf_weight_adj_val -= 1;
			else if(speed_conter < 20)	sf_weight_adj_val -= 10;
			else if(speed_conter <= 30)	sf_weight_adj_val -= 100;
			para_change_flag = 1;
		}
		if(sf_weight_adj_val > 10000)       sf_weight_adj_val = 100;
		else if(sf_weight_adj_val < 100)    sf_weight_adj_val = 10000;
		weight_disp(sf_weight_adj_val);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE);
	if(t1_flag == 1)	sf_weight_adj_val = backup_para;
	else if(para_change_flag == 1){
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&sf_weight_adj_val,SF_WEIGHT_ADDR,2);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}
        sf_weight = shut_fb_w - sf_weight_adj_val;
	}
}
/*******************************************************************************
*原  型:void sf_switch_adj(void);
*形  参:无.
*功  能:粗细流切换开关设置函数
*返回值:无.
*******************************************************************************/
void sf_switch_adj(void)					//size flow switch
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit key_val = 0,backup_para = sf_switch;
	err_code = 0;
	t1_stop();
	disp_symbol(sf_switch);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((sf_switch == ON) || (sf_switch == OFF))	sf_switch = ~sf_switch;
			else sf_switch = ON;
			para_change_flag = 1;			
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((sf_switch == OFF) || (sf_switch == ON))	sf_switch = ~sf_switch;
			else sf_switch = OFF;
			para_change_flag = 1;	
		}
		disp_symbol(sf_switch);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	sf_switch = backup_para;
	else if(para_change_flag == 1){				//参数改变
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&sf_switch,SF_SWITCH_ADDR,1);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}	
	}
}
/********************************************************************************原  型:void drop_weight_adj(void);
*形  参:无.
*功  能:落差设置函数
*返回值:无.
*******************************************************************************/
void drop_weight_adj(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit speed_conter,key_val = 0;
	s16bit xdata backup_para = drop_weight;
	err_code = 0;
	t1_stop();
	weight_disp(drop_weight);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == NOKEY_CLOSED)	speed_conter = 0;
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	drop_weight += 1;
			else if(speed_conter < 20)	drop_weight += 10;
			else	drop_weight += 100;
			para_change_flag = 1;			
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	drop_weight -= 1;
			else if(speed_conter < 20)	drop_weight -= 10;
			else	drop_weight -= 100;
			para_change_flag = 1;	
		}
		if(drop_weight > 2500)	drop_weight = -2500;
		else if(drop_weight < -2500)	drop_weight = 2500;
		weight_disp(drop_weight);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	drop_weight = backup_para;		//定时时间到,恢复备份
	else if(para_change_flag == 1){						//参数改变,保存参数
		t1_100ms(200);
		shut_fb_w = shut_fb_w + drop_weight - backup_para;
        sf_weight = shut_fb_w - sf_weight_adj_val;
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&drop_weight,DROP_WEIGHT_ADDR,2);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}
	}
}
/********************************************************************************原  型:void ol_track_sw_adj(void)
*形  参:无.
*功  能:开环追踪开关设置函数
*返回值:无.
*******************************************************************************/
void ol_track_sw_adj(void)					//open loop track switch
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit key_val = 0,backup_para = ol_track_sw;
	t1_stop();
	err_code = 0;
	disp_symbol(ol_track_sw);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((ol_track_sw == ON) || (ol_track_sw == OFF))
				ol_track_sw = ~ol_track_sw;
			else ol_track_sw = ON;
			para_change_flag = 1;			
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((ol_track_sw == OFF) || (ol_track_sw == ON))
				ol_track_sw = ~ol_track_sw;
			else ol_track_sw = OFF;
			para_change_flag = 1;	
		}
		disp_symbol(ol_track_sw);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	ol_track_sw = backup_para;
	else if(para_change_flag == 1){				//参数改变
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			cl_correct_sw = OFF;
			err_code = eeprom_write((u8bit *)&ol_track_sw,OL_TRACK_SW_ADDR,1);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
			else{
				err_code = eeprom_write((u8bit *)&cl_correct_sw,CL_CORRECT_SW_ADDR,1);
				if(err_code == E04)	disp_symbol(E04);
				else if (err_code == E05)	disp_symbol(E05);
			}
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}	
	}
}
/*******************************************************************************
*原  型:void track_bags_adj(void)
*形  参:无.
*功  能:追踪袋数设置函数
*返回值:无.
*******************************************************************************/
void track_bags_adj(void)				//追踪袋数
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit backup_para = track_bags,key_val = 0;
	t1_stop();
	err_code = 0;
	disp_int(track_bags);
	while(get_key(SET_RELEASE) != SET_RELEASE )	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			track_bags += 1;
			para_change_flag = 1;			
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			track_bags -= 1;
			para_change_flag = 1;	
		}
		if(track_bags > 200)	track_bags = 10;
		else if(track_bags > 10)	track_bags = 0;
		disp_int(track_bags);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	track_bags = backup_para;
	else if(para_change_flag == 1){	//参数改变,且不是因为定时时间到退出修改参数
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write(&track_bags,TRACK_BAGS_ADDR,1);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}	
	}
}
/***********************************************************************************
*原  型:void residual_weight_adj(void)
*形  参:无.
*功  能:净差设置函数
*返回值:无.
***********************************************************************************/
void residual_weight_adj(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit speed_conter,key_val = 0;
	s16bit xdata backup_para = residual_weight;
	err_code = 0;
	t1_stop();
	weight_disp(residual_weight);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == NOKEY_CLOSED)	speed_conter = 0;
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	residual_weight += 1;
			else if(speed_conter < 20)	residual_weight += 10;
			else	residual_weight += 100;
			para_change_flag = 1;			
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter < 40)	speed_conter++;
			if(speed_conter < 10)	residual_weight -= 1;
			else if(speed_conter < 20)	residual_weight -= 10;
			else	residual_weight -= 100;
			para_change_flag = 1;	
		}
		if(residual_weight > 2500)	residual_weight = -2500;
		else if(residual_weight < -2500)	residual_weight = 2500;
		weight_disp(residual_weight);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	residual_weight = backup_para;	//定时时间到,恢复备份
	else if(para_change_flag == 1){						//参数改变,保存参数
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&residual_weight,R_WEIGHT_ADDR,2);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}	
	}
}
/***********************************************************************************
*原  型:void cl_correct_sw_adj(void)
*形  参:无.
*功  能:闭环校正开关设置
*返回值:无.
***********************************************************************************/
void cl_correct_sw_adj(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit key_val = 0,backup_para = cl_correct_sw;
	t1_stop();
	err_code = 0;
	disp_symbol(cl_correct_sw);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((cl_correct_sw == ON) || (cl_correct_sw == OFF))
				cl_correct_sw = ~cl_correct_sw;
			else cl_correct_sw = ON;
			para_change_flag = 1;			
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((cl_correct_sw == OFF) || (cl_correct_sw == ON))
				cl_correct_sw = ~cl_correct_sw;
			else cl_correct_sw = OFF;
			para_change_flag = 1;	
		}
		disp_symbol(cl_correct_sw);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	cl_correct_sw = backup_para;
	else if(para_change_flag == 1){				//参数改变
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			ol_track_sw = OFF;
			err_code = eeprom_write((u8bit *)&ol_track_sw,OL_TRACK_SW_ADDR,1);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
			else{
				err_code = eeprom_write((u8bit *)&cl_correct_sw,CL_CORRECT_SW_ADDR,1);
				if(err_code == E04)	disp_symbol(E04);
				else if (err_code == E05)	disp_symbol(E05);
			}
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}
	}
}
/*******************************************************************************
*原  型:void weight_correct_val_adj(void)
*形  参:无.
*功  能:袋重修正值设置函数.
*返回值:无.
*******************************************************************************/
void weight_correct_val_adj(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit speed_conter,key_val = 0;
	s16bit xdata backup_para = weight_correct_val;
	err_code = 0;
	t1_stop();
	weight_disp(weight_correct_val);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == NOKEY_CLOSED)	speed_conter = 0;
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	weight_correct_val += 1;
			else if(speed_conter < 20)	weight_correct_val += 10;
			else	weight_correct_val += 100;
			para_change_flag = 1;
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	weight_correct_val -= 1;
			else if(speed_conter < 20)	weight_correct_val -= 10;
			else	weight_correct_val -= 100;
			para_change_flag = 1;
		}
		if(weight_correct_val > 9900)	weight_correct_val = 1500;
		else if(weight_correct_val > 1500)	weight_correct_val = 0;
		weight_disp(weight_correct_val);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	weight_correct_val = backup_para;//定时时间到,恢复备份
	else if(para_change_flag == 1){						//参数改变,保存参数
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code=eeprom_write((u8bit *)&weight_correct_val,WEIGHT_CORRECT_ADDR,2);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}
	}
}
/*******************************************************************************
*原  型:void arrival_time_adj(void)
*形  参:无.
*功  能:抵达时间设置函数.
*返回值:无.
*******************************************************************************/
void arrival_time_adj(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit speed_conter,key_val = 0;
	u8bit xdata backup_para = arrival_time;
	err_code = 0;
	t1_stop();
	disp_int(arrival_time);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == NOKEY_CLOSED)	speed_conter = 0;
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	arrival_time += 1;
			else if(speed_conter < 20)	arrival_time += 2;
			else	arrival_time += 4;
			para_change_flag = 1;			
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	arrival_time -= 1;
			else if(speed_conter < 20)	arrival_time -= 2;
			else	arrival_time -= 4;
			para_change_flag = 1;	
		}
		disp_int(arrival_time);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	arrival_time = backup_para;		//定时时间到,恢复备份
	else if(para_change_flag == 1){						//参数改变,保存参数
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&arrival_time,ARRIVAL_TIME_ADDR,1);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}	
	}
}
/*******************************************************************************
*原  型:void couter_sw_adj(void)
*形  参:无.
*功  能:技术开关设置函数.
*返回值:无.
*******************************************************************************/
void couter_sw_adj(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit key_val = 0,backup_para = counter_sw;
	err_code = 0;
	t1_stop();
	disp_symbol(counter_sw);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((counter_sw == ON)||(counter_sw == OFF))counter_sw=~counter_sw;
			else counter_sw = ON;
			para_change_flag = 1;
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((counter_sw == OFF)||(counter_sw == ON))counter_sw=~counter_sw;
			else counter_sw = OFF;
			para_change_flag = 1;
		}
		disp_symbol(counter_sw);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	counter_sw = backup_para;
	else if(para_change_flag == 1){				//参数改变
		t1_100ms(200);
        DropCounter = 0;
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&counter_sw,COUTER_SW_ADDR,1);
			if(err_code == E04)	disp_symbol(E04);
			else if(err_code == E05) disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}	
	}
}

/*******************************************************************************
*原  型:void func_func(void)
*形  参:无.
*功  能:参数设置函数.
*返回值:无.
*******************************************************************************/
void func_func(void)
{
	u8bit xdata key_val;
	if(t1_sta_flag == 0){
		t1_100ms(200);
		t1_sta_flag = 1;
	}
	disp_symbol(mf_menu);
	key_val = get_key(CHK_ALL_KEY);
	if(key_val != NOKEY_CLOSED){
		t1_stop();
		t1_sta_flag = 0;
	}
	if(key_val == ENT_CLOSED)	exit_flag = 1;
	else{	
		switch(mf_menu){
			case MF01:
				if(key_val == SET_CLOSED)	sp_weight_adj();
				else if(key_val == DWN_CLOSED)	mf_menu = MF02;
				else if(key_val == UP_CLOSED)	mf_menu = MF12;
				break;
			case MF02:
				if(key_val == SET_CLOSED)	filter_para_adj();
				else if(key_val == DWN_CLOSED)	mf_menu = MF03;
				else if(key_val == UP_CLOSED)	mf_menu = MF01;
				break;
			case MF03:
				if(key_val==SET_CLOSED)	sf_weight_adj();//size flow粗细流切换
				else if(key_val == DWN_CLOSED)	mf_menu = MF04;
				else if(key_val == UP_CLOSED)	mf_menu = MF02;
				break;
			case MF04:
				if(key_val == SET_CLOSED)	sf_switch_adj();
				else if(key_val == DWN_CLOSED)	mf_menu = MF05;
				else if(key_val == UP_CLOSED)	mf_menu = MF03;
				break;
			case MF05:
				if(key_val == SET_CLOSED)	drop_weight_adj();
				else if(key_val == DWN_CLOSED)	mf_menu = MF06;
				else if(key_val == UP_CLOSED)	mf_menu = MF04;
				break;
			case MF06:
				if(key_val == SET_CLOSED)	ol_track_sw_adj();//open loop track
				else if(key_val == DWN_CLOSED)	mf_menu = MF07;
				else if(key_val == UP_CLOSED)	mf_menu = MF05;
				break;
			case MF07:
				if(key_val == SET_CLOSED)	track_bags_adj();	//
				else if(key_val == DWN_CLOSED)	mf_menu = MF08;
				else if(key_val == UP_CLOSED)	mf_menu = MF06;
				break;
			case MF08:
				if(key_val == SET_CLOSED)	residual_weight_adj();//袋重净差设置
				else if(key_val == DWN_CLOSED)	mf_menu = MF09;
				else if(key_val == UP_CLOSED)	mf_menu = MF07;
				break;
			case MF09:
				if(key_val == SET_CLOSED)	cl_correct_sw_adj();//
				else if(key_val == DWN_CLOSED)	mf_menu = MF10;
				else if(key_val == UP_CLOSED)	mf_menu = MF08;
				break;
			case MF10:
				if(key_val == SET_CLOSED)	weight_correct_val_adj();
				else if(key_val == DWN_CLOSED)	mf_menu = MF11;
				else if(key_val == UP_CLOSED)	mf_menu = MF09;
				break;
			case MF11:
				if(key_val == SET_CLOSED)	arrival_time_adj();
				else if(key_val == DWN_CLOSED)	mf_menu = MF12;
				else if(key_val == UP_CLOSED)	mf_menu = MF10;
				break;
			case MF12:
				if(key_val == SET_CLOSED)	couter_sw_adj();
				else if(key_val == DWN_CLOSED)	mf_menu = MF01;
				else if(key_val == UP_CLOSED)	mf_menu = MF11;
				break;
		}
		exit_flag = 0;
	}
}
/*******************************************************************************
*原  型:void span_set(void)
*形  参:无.
*功  能:量程设置.
*返回值:无.
*******************************************************************************/
void span_set(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit key_val = 0;
	u32bit xdata backup_para = load_cell_span;
	err_code = 0;
	t1_stop();
	weight_disp(load_cell_span);
	while(get_key(SET_RELEASE) != SET_RELEASE);
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(load_cell_span == 100000)		load_cell_span = 350000;
			else if(load_cell_span == 150000)	load_cell_span = 100000;
			else if(load_cell_span == 200000)	load_cell_span = 150000;
			else if(load_cell_span == 250000)	load_cell_span = 200000;
			else if(load_cell_span == 300000)	load_cell_span = 250000;
			else if(load_cell_span == 350000)	load_cell_span = 300000;
			else	load_cell_span = 100000;
			para_change_flag = 1;
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			t1_sta_flag = 0;
			if(load_cell_span == 100000)		load_cell_span = 150000;
			else if(load_cell_span == 150000)	load_cell_span = 200000;
			else if(load_cell_span == 200000)	load_cell_span = 250000;
			else if(load_cell_span == 250000)	load_cell_span = 300000;
			else if(load_cell_span == 300000)	load_cell_span = 350000;
			else if(load_cell_span == 350000)	load_cell_span = 100000;
			else	load_cell_span = 350000;
			para_change_flag = 1;	
		}
		weight_disp(load_cell_span);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	load_cell_span = backup_para;	//定时时间到,恢复备份
	else if(para_change_flag == 1){						//参数改变,保存参数
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&load_cell_span,CELL_SPAN_ADDR,4);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}	
	}
}
/***********************************************************************************
*原  型:void tare(void)
*形  参:无.
*功  能:去皮函数.
*返回值:无.
***********************************************************************************/
void tare(void)
{
	s32bit xdata copy_zero_scale_value = zero_scale_value,copy_tw = tare_weight;
	bit para_change_flag = 0;
	t1_stop();
	zero_scale_value = 0;
	while(get_key(SET_RELEASE) != SET_RELEASE)	weight_disp(GW_measure());
	t1_100ms(200);
	while((t1_flag != 1) && (get_key(CLR_CLOSED) != CLR_CLOSED))	;
	if(t1_flag != 1){
		t1_100ms(200);
		while((t1_flag != 1) && (get_key(CLR_RELEASE) != CLR_RELEASE))	;
		if(t1_flag != 1){
			t1_stop();
			tare_weight = GW_measure();
			t1_100ms(200);
			while((get_key(ENT_CLOSED)!=ENT_CLOSED)&&(t1_flag!=1))
				flash_disp(NW_scale());
		}
	}
	if(t1_flag == 1){
		tare_weight = copy_tw;
		zero_scale_value = copy_zero_scale_value;
	}
	else{
		while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
		weight_disp(NW_scale());
		delay_ms(100);
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&tare_weight,TW_ADDR,4); 
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}
	}
	return;
}
/*******************************************************************************
*原  型:void gain(void)
*形  参:无.
*功  能:标定函数.
*返回值:无.
*******************************************************************************/
void gain(void)
{
	bit para_change_flag;
	u8bit xdata cnt,speed_conter,key_val = 0;
	u32bit xdata nw_val,backup_output = scale_output_val;
	u32bit xdata backup_counter = scale_counterweight_val;
	t1_stop();
	t1_flag = 0;
	err_code = 0XFF;
	for(cnt = 0;cnt < 19; cnt++)	NW_measure();
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while(get_key(SET_CLOSED) != SET_CLOSED){
		while(err_code != 0){
			nw_val = NW_measure();
			if(nw_val < 19000){						//砝码重量超下限
				disp_symbol(ERR_CL);
				err_code = ERR_CL;
				while(get_key(SET_CLOSED) != SET_CLOSED);
			}
			else if(nw_val > 62000){				//砝码重量超上限
				disp_symbol(ERR_HL);
				err_code = ERR_HL;
				while(get_key(SET_CLOSED) != SET_CLOSED);
			}
			else err_code = 0;
			if(err_code)
				while(get_key(SET_RELEASE) != SET_RELEASE);	
		}
		weight_disp(nw_val);
		err_code = 0XFF;	
	}
	scale_output_val = nw_val;
	scale_counterweight_val = scale_output_val;
	weight_disp(scale_counterweight_val);
	while(get_key(SET_RELEASE) != SET_RELEASE);
	err_code = 0;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){	//参数设置
		if(t1_sta_flag == 0){						//定时器未启动,则启动3S定时
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == NOKEY_CLOSED)	speed_conter = 0;
		if(key_val == UP_CLOSED){					//参数加调整
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	scale_counterweight_val += 1;
			else if(speed_conter < 20)	scale_counterweight_val += 10;
			else if(speed_conter < 30)	scale_counterweight_val += 100;
			else scale_counterweight_val += 500;
			para_change_flag = 1;			
		}
		else if(key_val == DWN_CLOSED){				//参数检调整
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	scale_counterweight_val -= 1;
			else if(speed_conter < 20)	scale_counterweight_val -= 10;
			else if(speed_conter < 30)	scale_counterweight_val -= 100;
			else scale_counterweight_val -= 500;
			para_change_flag = 1;	
		}
		if(scale_counterweight_val > 60000)	scale_counterweight_val = 20000;		
		//参数超范围调整
		else if(scale_counterweight_val<20000) scale_counterweight_val = 60000;
		weight_disp(scale_counterweight_val);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1){							//超过3秒没有按键,参数恢复备份值
		scale_counterweight_val = backup_counter;
		scale_output_val = backup_output;
	}
	else if(para_change_flag == 1){				//参数存贮
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&scale_counterweight_val,COUNTERWEIGHT_ADDR,4);
			if(err_code != WR_DONE)	disp_symbol(err_code);
			else{
				err_code = eeprom_write((u8bit *)&scale_output_val,SCALE_OUTPUT_ADDR,4);
				if(err_code != WR_DONE)	disp_symbol(err_code);
			}
		}
		if(err_code == WR_DONE){					//存储完成,显示good
			disp_symbol(GOOD);
			delay_ms(250);
			delay_ms(250);
		}
	}
}
/***********************************************************************************
*原  型:void cal_func(void)
*形  参:无.
*功  能:标定相关函数.
*返回值:无.
***********************************************************************************/
void cal_func(void)
{
	u8bit xdata key_val;
	if(t1_sta_flag == 0){
		t1_100ms(200);
		t1_sta_flag = 1;
	}
	disp_symbol(mc_menu);							//cal 菜单
	key_val = get_key(CHK_ALL_KEY);
	if(key_val != NOKEY_CLOSED){
		t1_stop();
		t1_sta_flag = 0;
	}
	if(key_val == ENT_CLOSED)	exit_flag = 1;
	else{		
		switch(mc_menu){
			case MC01:
				if(key_val == SET_CLOSED)	span_set();
				else if(key_val == DWN_CLOSED)	mc_menu = MC02;
				else if(key_val == UP_CLOSED)	mc_menu = MC03;
				break;
			case MC02:
				if(key_val == SET_CLOSED)	tare();
				else if(key_val == DWN_CLOSED)	mc_menu = MC03;
				else if(key_val == UP_CLOSED)	mc_menu = MC01;
				break;
			case MC03:
				if(key_val == SET_CLOSED)	gain();		//size flow 粗细流切换
				else if(key_val == DWN_CLOSED)	mc_menu = MC01;
				else if(key_val == UP_CLOSED)	mc_menu = MC02;
				break;
		}
		exit_flag = 0;
	}
}
/*******************************************************************************
*原  型:void input_test(void)
*形  参:无.
*功  能:输入测试函数
*返回值:无.
*******************************************************************************/
void input_test(void)
{
	t1_stop();
	while(get_key(SET_RELEASE) != SET_RELEASE);
	disp_symbol(CLR_ALL);
	while(get_key(ENT_CLOSED) != ENT_CLOSED)	disp_symbol(get_input());		
}
/*******************************************************************************
*原  型:void output_test(void)
*形  参:无.
*功  能:输出测试函数
*返回值:无.
*******************************************************************************/
void output_test(void)
{
	while(get_key(SET_RELEASE) != SET_RELEASE);
	mt_menu = DQ02;
}

void flashboard_test(void)
{
	u8bit key_val = 0;
	P3 |= 0X3E;					//所有的输出端口置1;
	while(get_key(SET_RELEASE) != SET_RELEASE);
	while(key_val != ENT_CLOSED){
		key_val = get_key(CHK_ALL_KEY);
		if((key_val == UP_CLOSED) || (key_val == DWN_CLOSED)){
			while(get_key(UD_RELEASE) != UD_RELEASE);	
			cyl_sw_out = !cyl_sw_out;
		}
		if(cyl_sw_out == SHUT)	disp_symbol(O1_OFF);
		else disp_symbol(O1_ON);
	}
	while(get_key(ENT_RELEASE) != ENT_RELEASE);
	cyl_sw_out = SHUT;
}

void size_flow_test(void)
{
	u8bit key_val = 0;
	P3 |= 0X3E;					//所有的输出端口置1;
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while(key_val != ENT_CLOSED){
		key_val = get_key(CHK_ALL_KEY);
		if((key_val == UP_CLOSED) || (key_val == DWN_CLOSED)){
			while(get_key(UD_RELEASE) != UD_RELEASE)	;	
			fine_flow_out = !fine_flow_out;
		}
		if(fine_flow_out == COARSE)	disp_symbol(O2_OFF);
		else disp_symbol(O2_ON);
	}
	while(get_key(ENT_RELEASE) != ENT_RELEASE);
	fine_flow_out = COARSE;
}

void discharge_bag_test(void)
{
	u8bit key_val = 0;
	P3 |= 0X3E;					//所有的输出端口置1;
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while(key_val != ENT_CLOSED){
		key_val = get_key(CHK_ALL_KEY);
		if((key_val == UP_CLOSED) || (key_val == DWN_CLOSED)){
			while(get_key(UD_RELEASE) != UD_RELEASE)	;	
			discharge_bag_sw_out = !discharge_bag_sw_out;
		}
		if(discharge_bag_sw_out == SHUT)	disp_symbol(O3_OFF);
		else disp_symbol(O3_ON);
	}
	while(get_key(ENT_RELEASE) != ENT_RELEASE);
	discharge_bag_sw_out = SHUT;
}

void clamp_bag_test(void)
{
	u8bit key_val = 0;
	P3 |= 0X3E;					//所有的输出端口置1;
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while(key_val != ENT_CLOSED){
		key_val = get_key(CHK_ALL_KEY);
		if((key_val == UP_CLOSED) || (key_val == DWN_CLOSED)){
			while(get_key(UD_RELEASE) != UD_RELEASE)	;	
			flashboard_sw_out = !flashboard_sw_out;
		}
		if(flashboard_sw_out == SHUT)	disp_symbol(O4_OFF);
		else disp_symbol(O4_ON);
	}
	while(get_key(ENT_RELEASE) != ENT_RELEASE);
	flashboard_sw_out = SHUT;
}

void fill_mot_sw_test(void)
{
	u8bit key_val = 0;
	P3 |= 0X3E;					//所有的输出端口置1;
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while(key_val != ENT_CLOSED){
		key_val = get_key(CHK_ALL_KEY);
		if((key_val == UP_CLOSED) || (key_val == DWN_CLOSED)){
			while(get_key(UD_RELEASE) != UD_RELEASE)	;	
			fill_mot_sw_out = !fill_mot_sw_out;
		}
		if(fill_mot_sw_out == SHUT)	disp_symbol(O5_OFF);
		else disp_symbol(O5_ON);
	}
	while(get_key(ENT_RELEASE) != ENT_RELEASE);
	fill_mot_sw_out = SHUT;
}

void test_func(void)
{
	u8bit xdata key_val;
	if(t1_sta_flag == 0){
		t1_100ms(200);
		t1_sta_flag = 1;
	}
	disp_symbol(mt_menu);			
	key_val = get_key(CHK_ALL_KEY);
	if(key_val != NOKEY_CLOSED){
		t1_stop();
		t1_sta_flag = 0;
	}		
	switch(mt_menu){
		case DI01:
			if(key_val == SET_CLOSED)	input_test();
			else if(key_val == DWN_CLOSED)	mt_menu = DQ01;
			else if(key_val == UP_CLOSED)	mt_menu = DQ01;
			else if(key_val == ENT_CLOSED)	exit_flag = 1;
			break;
		case DQ01:
			if(key_val == SET_CLOSED)	output_test();
			else if(key_val == DWN_CLOSED)	mt_menu = DI01;
			else if(key_val == UP_CLOSED)	mt_menu = DI01;
			else if(key_val == ENT_CLOSED)	exit_flag = 1;
			break;
		case DQ02:
			if(key_val == SET_CLOSED)	flashboard_test();	
			else if(key_val == DWN_CLOSED)	mt_menu = DQ03;
			else if(key_val == UP_CLOSED)	mt_menu = DQ06;
			else if(key_val == ENT_CLOSED)	mt_menu = DQ01;
			break;
		case DQ03:
			if(key_val == SET_CLOSED)	size_flow_test();	
			else if(key_val == DWN_CLOSED)	mt_menu = DQ04;
			else if(key_val == UP_CLOSED)	mt_menu = DQ02;
			else if(key_val == ENT_CLOSED)	mt_menu = DQ01;
			break;
		case DQ04:
			if(key_val == SET_CLOSED)	discharge_bag_test();	
			else if(key_val == DWN_CLOSED)	mt_menu = DQ05;
			else if(key_val == UP_CLOSED)	mt_menu = DQ03;
			else if(key_val == ENT_CLOSED)	mt_menu = DQ01;
			break;
		case DQ05:
			if(key_val == SET_CLOSED)	clamp_bag_test();	
			else if(key_val == DWN_CLOSED)	mt_menu = DQ06;
			else if(key_val == UP_CLOSED)	mt_menu = DQ04;
			else if(key_val == ENT_CLOSED)	mt_menu = DQ01;
			break;
		case DQ06:
			if(key_val == SET_CLOSED)	fill_mot_sw_test();	
			else if(key_val == DWN_CLOSED)	mt_menu = DQ02;
			else if(key_val == UP_CLOSED)	mt_menu = DQ05;
			else if(key_val == ENT_CLOSED)	mt_menu = DQ01;
			break;
	}
}
void DpAddrSet(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit speed_conter,key_val = 0;
	u8bit xdata backup_para = CommAddr;
	err_code = 0;
	t1_stop();
	disp_int(CommAddr);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == NOKEY_CLOSED)	speed_conter = 0;
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	CommAddr += 1;
			else if(speed_conter < 20)	CommAddr += 5;
			else	CommAddr += 10;
			para_change_flag = 1;
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if(speed_conter <40) speed_conter++;
			if(speed_conter < 10)	CommAddr -= 1;
			else if(speed_conter < 20)	CommAddr -= 5;
			else	CommAddr -= 10;
			para_change_flag = 1;
		}
		if(CommAddr > 200)	CommAddr = 60;
		else if(CommAddr > 60)	CommAddr = 1;
		disp_int(CommAddr);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE);
	if(t1_flag == 1)	CommAddr = backup_para;//定时时间到,恢复备份
	else if(para_change_flag == 1){						//参数改变,保存参数
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code=eeprom_write(&CommAddr,COMMADDR_ADDR,1);
			if(err_code == E04)	disp_symbol(E04);
			else if(err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			#if DP_ON
			if(DpSwitch == ON) pb_init();
			#endif
			delay_ms(250);
			delay_ms(250);
		}
	}
}
void DpSwSet(void)
{
	bit t1_sta_flag = 0,para_change_flag = 0;
	u8bit key_val = 0,backup_para = DpSwitch;
	err_code = 0;
	t1_stop();
	disp_symbol(DpSwitch);
	while(get_key(SET_RELEASE) != SET_RELEASE)	;
	while((t1_flag != 1) && (key_val != ENT_CLOSED)){
		if(t1_sta_flag == 0){
			t1_100ms(200);
			t1_sta_flag = 1;
		}
		key_val = get_key(CHK_ALL_KEY);
		if(key_val == UP_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((DpSwitch == ON)||(DpSwitch==OFF))DpSwitch=~DpSwitch;
			else DpSwitch = ON;
			para_change_flag = 1;
		}
		else if(key_val == DWN_CLOSED){
			t1_stop();
			t1_sta_flag = 0;
			if((DpSwitch == OFF)||(DpSwitch == ON))DpSwitch = ~DpSwitch;
			else DpSwitch = OFF;
			para_change_flag = 1;
		}
		disp_symbol(DpSwitch);
	}
	t1_stop();
	t1_sta_flag = 0;
	while(get_key(ENT_RELEASE) != ENT_RELEASE)	;
	if(t1_flag == 1)	DpSwitch = backup_para;
	else if(para_change_flag == 1){				//参数改变
        DpErrFlag = 0;
		t1_100ms(200);
		while((t1_flag != 1) && (err_code != WR_DONE)){
			err_code = eeprom_write((u8bit *)&DpSwitch,DP_SW_ADDR,1);
			if(err_code == E04)	disp_symbol(E04);
			else if (err_code == E05)	disp_symbol(E05);
		}
		if(err_code == WR_DONE){
			disp_symbol(GOOD);
			#if DP_ON
			if(DpSwitch == ON) pb_init();
			#endif
			delay_ms(250);
			delay_ms(250);
		}
	}
}
void DpSet(void)
{
	u8bit xdata key_val;
	if(t1_sta_flag == 0){
		t1_100ms(200);
		t1_sta_flag = 1;
	}
	disp_symbol(md_menu);
	key_val = get_key(CHK_ALL_KEY);
	if(key_val != NOKEY_CLOSED){
		t1_stop();
		t1_sta_flag = 0;
	}
	switch(md_menu){
		case MD01:
			if(key_val == SET_CLOSED)	DpAddrSet();
			else if(key_val == DWN_CLOSED)	md_menu = MD02;
			else if(key_val == UP_CLOSED)	md_menu = MD02;
			else if(key_val == ENT_CLOSED)	exit_flag = 1;
			break;
		case MD02:
			if(key_val == SET_CLOSED)	DpSwSet();
			else if(key_val == DWN_CLOSED)	md_menu = MD01;
			else if(key_val == UP_CLOSED)	md_menu = MD01;
			else if(key_val == ENT_CLOSED)	exit_flag = 1;
			break;
	}
}
void VerDisp(void)
{
	u8bit xdata key_val;
	u8bit *p_data = Version;
	if(t1_sta_flag == 0){
		t1_100ms(200);
		t1_sta_flag = 1;
	}			
	key_val = get_key(CHK_ALL_KEY);
	if(key_val != NOKEY_CLOSED){
		t1_stop();
		t1_sta_flag = 0;
	}	
	
	disp_seg(seg_sym[*p_data - 0x30],BIT5);	p_data++;
	disp_seg(seg_sym[SYM__],BIT4);			p_data++;
	disp_seg(seg_sym[*p_data - 0x30],BIT3);	p_data++;
	disp_seg(seg_dot[*p_data - 0x30],BIT2);	p_data++;
	disp_seg(seg_sym[*p_data - 0x30],BIT1);	p_data++;
	disp_seg(seg_sym[*p_data - 0x30],BIT0);
	if(key_val == ENT_CLOSED)	exit_flag = 1;
}
void mr_func(void)
{
	if(t1_sta_flag == 0){
		t1_100ms(200);
		t1_sta_flag = 1;
	}
	switch(mr_menu){
		case MR01:
			if(get_key(SET_CLOSED) == SET_CLOSED){
				t1_stop();
				mf_menu = MF01;
				t1_sta_flag = 0;
				exit_flag = 0;
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				while((t1_flag != 1) && (exit_flag == 0))	func_func();
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				disp_symbol(FUNC);
			}
			else if(get_key(DWN_CLOSED) == DWN_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR04;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(CAL);
			}
			else if(get_key(UP_CLOSED) == UP_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR07;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(VER);
			}	
			break;
		case MR04:
			if(get_key(SET_CLOSED) == SET_CLOSED){
				t1_stop();
				mc_menu = MC01;
				t1_sta_flag = 0;
				exit_flag = 0;
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				while((t1_flag != 1) && (exit_flag == 0))	cal_func();
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				disp_symbol(CAL);
			}		
			else if(get_key(DWN_CLOSED) == DWN_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR05;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(TEST);
			}
			else if(get_key(UP_CLOSED) == UP_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR01;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(FUNC);
			}
			break;
		case MR05:
			if(get_key(SET_CLOSED) == SET_CLOSED){
				t1_stop();
				mt_menu = DI01;
				t1_sta_flag = 0;
				exit_flag = 0;
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				while((t1_flag != 1) && (exit_flag == 0))	test_func();
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				disp_symbol(TEST);
			}
			else if(get_key(DWN_CLOSED) == DWN_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR06;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(DPSET);
			}
			else if(get_key(UP_CLOSED) == UP_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR04;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(CAL);
			}
			break;
		case MR06:
			if(get_key(SET_CLOSED) == SET_CLOSED){
				t1_stop();
				md_menu = MD01;
				t1_sta_flag = 0;
				exit_flag = 0;
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				while((t1_flag != 1) && (exit_flag == 0))	DpSet();
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				disp_symbol(DPSET);
			}
			else if(get_key(DWN_CLOSED) == DWN_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR07;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(VER);
			}
			else if(get_key(UP_CLOSED) == UP_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR05;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(TEST);
			}
			break;
		case MR07:
			if(get_key(SET_CLOSED) == SET_CLOSED){
				t1_stop();
				t1_sta_flag = 0;
				exit_flag = 0;
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				while((t1_flag != 1) && (exit_flag == 0))	VerDisp();
				while(get_key(ENT_RELEASE) != ENT_RELEASE);
				disp_symbol(VER);
			}
			else if(get_key(DWN_CLOSED) == DWN_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR01;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(FUNC);
			}
			else if(get_key(UP_CLOSED) == UP_CLOSED){
				while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
				mr_menu = MR06;
				t1_flag = 0;
				err_code = 0;
				t1_stop();
				t1_sta_flag = 0;
				disp_symbol(DPSET);
			}
			break;
	}
}	
void menu_func(void)
{
	u8bit xdata copy_EIE1,copy_EIE2,copy_IE;
	t1_sta_flag = 0;
	copy_EIE1 = EIE1;
	copy_EIE2 = EIE2;
	copy_IE = IE;									//备份中断允许
	IE = 0;
	IE = 0;
	EIE1 = 0;
	EIE2 = 0;										//关所有中断
	if(get_key(SET_CLOSED) == SET_CLOSED){
		t1_100ms(20);
		while((get_key(SET_RELEASE) != SET_RELEASE) && (t1_flag != 1))	run_disp(NW_scale());
		if(t1_flag == 1){
			t1_stop();
			disp_symbol(SET);
			while(get_key(CHK_ALL_KEY) != NOKEY_CLOSED);
			t1_flag = 0;
			err_code = 0;
			mr_menu = MR01;
			disp_symbol(FUNC);
			while((t1_flag!=1)&&(get_key(ENT_CLOSED) != ENT_CLOSED)) mr_func();
		}
	}
	t1_stop();
	t1_flag = 0;
	EIE1 = copy_EIE1;
	EIE2 = copy_EIE2;
	IE = copy_IE;
	IE = copy_IE;
	return;
}