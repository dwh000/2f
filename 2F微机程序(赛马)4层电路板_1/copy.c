		/*清零点检测并处理*/
		#if DEBUG
		MSG("\n\r\n\r Waiting for ZeroPoint !!!");
		#endif
		for(i=0;i<2;){		//若未检测到去清零点,则一直执行此段程序.
			//清零点去抖检测,并显示处理
			if(zero_loc == ACTIVE)	{//检测到清零点
				i++;
				delay_ms(5);
			}
			else{//如果没有检测到清零点信号,则进行如下操作
				menu_func();							//调用菜单函数
				dm_sp_weight();							//调用直接修改设定值函数
				tare_zero_func();						//调用去皮清零函数
				adc = NW_scale();
				/*插袋检测并显示*/
				if(bag_det == ACTIVE)		disp_cache = 0x7f;	
				else	disp_cache = 0xff;
				disp_seg(disp_cache,BIT4);
				/*皮带连锁及掉袋点检测处理并显示*/
				if(discharge_bag_en == ACTIVE)	disp_cache = 0x7f;
				else	disp_cache = 0xff;
				/*掉袋点检测并处理******************************/
				for(i=0; i<2 ;){
					if(discharge_bag_loc == ACTIVE)	i++;
					else	break;
					delay_ms(5);
				}
				if(i == 2)	{
					disp_cache &= 0XA1;
					discharge_bag_loc_flag = 1;
				}
				disp_seg(disp_cache,BIT5);
				run_disp(adc);
				i=0;
			}
		}
		if(i == 2)	{//清零点清零操作
			s16bit xdata czero_scale_value;
			do	{//如果有清零点信号,则循环进行如下操作.
				czero_scale_value = zero_scale_value;
				zero_scale_value = 0;
				menu_func();						//调用菜单函数
				dm_sp_weight();						//调用直接修改设定值函数
				tare_zero_func();					//调用去皮清零函数
				adc = NW_scale();
				if(discharge_bag_en == ACTIVE)	disp_cache = 0x46;
				else	disp_cache = 0xff;
				if((adc > 3500) || (adc < -3500)){//清零点测量值超过清零范围,则
					zero_scale_value = czero_scale_value;
					if(adc > 3500){
						disp_symbol(ERR_OH);
						if(adc > shut_fb_w){
							m17();
							break;
						}
					}
					else if(adc < -3500)	disp_symbol(ERR_OL);
				}
				else{//清零点测量值在清零范围内,则
					if(zero_loc == ACTIVE)	disp_cache &= 0xc6;
					disp_seg(disp_cache,BIT5);
					if(bag_det == ACTIVE)	disp_seg(0x7f,BIT4);
					else	disp_seg(0XFF,BIT4);
					run_disp(adc);
					delay_ms(50);
					zero_scale_value = adc;
				}											
			}
			while(zero_loc == ACTIVE);
			#if DEBUG
			MSG("\n\r\n\r zero_scale_value is ");
			if(zero_scale_value > 0)
				rs485_tx(zero_scale_value);
			else{
				DBG('-');
				rs485_tx(-zero_scale_value);
			}
			MSG("\n\r ZeroPoint is done ...\n\r");
			#endif
		}
/*开闸板信号,插袋检测信号检测并处理*/
		i=0;
		#if DEBUG
		MSG("\n\r\n\r Waiting for bag_det signal!!! ");
		#endif
		while(i<5){
			menu_func();			//调用菜单函数
			dm_sp_weight();			//调用直接修改设定值函数
			tare_zero_func();		//调用去皮清零函数	
			weight_detection_disp();//袋重,插袋信号,皮带连锁掉袋点检测处理并显示	 
			/*插袋检测并处理*/
			for(i=0; i<5;){
				if(bag_det == ACTIVE)	i++;	
				else	break;
				delay_ms(5);	
			}
		}
		#if DEBUG
		MSG("\n\r\n\r bag_det is on!!! ");
		#endif
		t1_100ms(2);
		while(t1_flag == 0)	weight_detection_disp();
		t1_stop();
		t1_flag = 0;
		if(bag_det == ACTIVE){
			clamping_bag_out = OPEN;
			#if DEBUG
			MSG("\n\r Clamping_bag is on!!! ");
			#endif
			delay_ms(100);
			cyl_sw_out = OPEN;
			#if DEBUG
			MSG("\n\r cyl(气缸) is on!!! ");
			#endif
			fine_flow_out = OPEN;
			#if DEBUG
			MSG("\n\r ThickFill is on!!! ");
			#endif
			fill_mot_sw_out = OPEN;
			#if DEBUG
			MSG("\n\r Motor is on!!! ");
			MSG("\n\r\n\r BagFill is started!!! ");
			#endif
			t1_100ms(5);
			while(t1_flag == 0)	weight_detection_disp();	
			t1_stop();
		}
		if((bag_det == ACTIVE) && (t1_flag == 1)){
			adc = NW_scale();
			if(adc < -500)	{
				#if DEBUG
				MSG("\n\r\n\r 500ms later,bag_det is on,adc is ");
				if(adc > 0)
					rs485_tx(adc);
				else{
					DBG('-');
					rs485_tx(-adc);
				}
				MSG("\n\r adc < -500, BagFill will stop!");
				#endif
				fill_mot_sw_out = SHUT;
				cyl_sw_out = SHUT;
				fine_flow_out = SHUT;
				clamping_bag_out = SHUT;
				#if DEBUG
				MSG("\n\r Clamping_bag is OFF!!! ");
				MSG("\n\r cyl(气缸) is OFF!!! ");
				MSG("\n\r ThickFill is OFF!!! ");
				MSG("\n\r Motor is OFF!!! ");
				MSG("\n\r\n\r BagFill has been stoped!!! ");
				MSG("\n\r\n\r discharge_pulse will output!!! ");	
				#endif
				discharge_pulse100ms(4);
				#if DEBUG
				MSG("\n\r Waiting for discharge_bag_loc!!! ");	
				#endif
				while(discharge_bag_loc != ACTIVE)	weight_detection_disp();
				#if DEBUG
				MSG("\n\r discharge_bag_loc is active ,return!!! ");	
				#endif
			}
			else fill_measure_func();
		}	
		else{
			fill_mot_sw_out = SHUT;
			cyl_sw_out = SHUT;
			fine_flow_out = SHUT;
			clamping_bag_out = SHUT;
			#if DEBUG
			MSG("\n\r\n\r 500ms later,bag_det is off,shut up then return");
			MSG("\n\r Clamping_bag is OFF!!! ");
			MSG("\n\r cyl(气缸) is OFF!!! ");
			MSG("\n\r ThickFill is OFF!!! ");
			MSG("\n\r Motor is OFF!!! ");
			MSG("\n\r\n\r BagFill has been stoped!!! ");
			MSG("\n\r Waiting for discharge_bag_loc!!! ");	
			#endif
			while(discharge_bag_loc != ACTIVE)	weight_detection_disp();
			#if DEBUG
			MSG("\n\r discharge_bag_loc is active ,return!!! ");	
			#endif
		}
		




2013年3月19

P_temp = (u8bit *)&sp_weight;		//袋重设定值
TxBuf[1] = *P_temp++;
TxBuf[2] = *P_temp++;
TxBuf[3] = filter_coefficient;		//滤波系数
P_temp = (u8bit *)&sf_weight;		//粗细流切换值
TxBuf[4] = *P_temp++;
TxBuf[5] = *P_temp++;
TxBuf[6] = sf_switch;				//粗细流切换开关
P_temp = (u8bit *)&drop_weight;		//落差
TxBuf[7] = *P_temp++;
TxBuf[8] = *P_temp++;
TxBuf[9] = ol_track_sw;				//开环追踪开关
TxBuf[10] = track_bags;				//追踪袋数
P_temp = (u8bit *)&residual_weight;	//净差
TxBuf[11] = *P_temp++;
TxBuf[12] = *P_temp++;
TxBuf[13] = cl_correct_sw;				//闭环校正开关
P_temp = (u8bit *)&weight_correct_val;	//袋重修正值
TxBuf[14] = *P_temp++;
TxBuf[15] = *P_temp++;
TxBuf[16]=arrival_time;				//抵达时间
TxBuf[17] = counter_sw;				//掉包计数器开关
P_temp = (u8bit *)&load_cell_span;	//传感器量程
TxBuf[18] = *P_temp++;
TxBuf[19] = *P_temp++;
TxBuf[20] = *P_temp++;
TxBuf[21] = *P_temp++;
P_temp = (u8bit *)&scale_output_val;//传感器砝码输出值
TxBuf[22] = *P_temp++;
TxBuf[23] = *P_temp++;
TxBuf[24] = *P_temp++;
TxBuf[25] = *P_temp++;
P_temp = (u8bit *)&scale_counterweight_val;//传感器砝码输出值
TxBuf[26] = *P_temp++;
TxBuf[27] = *P_temp++;
TxBuf[28] = *P_temp++;
TxBuf[29] = *P_temp++;
P_temp = (u8bit *)&tare_weight;		//皮重
TxBuf[30] = *P_temp++;
TxBuf[31] = *P_temp++;
TxBuf[32] = *P_temp++;
TxBuf[33] = *P_temp++;
TxBuf[34] = 参数设置错误;			//于参数初始化更新
TxBuf[35] = 标定参数错误;			//于参数初始化更新
TxBuf[36] = 硬件错误;				//于参数初始化更新,
TxBuf[37] = 灌装运行错误;
TxBuf[38] = 开出状态;
P_temp = (u8bit *)&DropCounter;		//掉包计数器,于计数增加位置更新
TxBuf[39] = *P_temp++;
TxBuf[40] = *P_temp++;
TxBuf[41] = *P_temp++;
TxBuf[42] = *P_temp++;
P_temp = (u8bit *)&WeightOfLastBag;	//上次掉包袋重,于50公斤点初始化
TxBuf[43] = *P_temp++;
TxBuf[44] = *P_temp++;
P_temp = (u8bit *)&CurrentWeight;	//称重过程中初始化
TxBuf[45] = *P_temp++;
TxBuf[46] = *P_temp++;
TxBuf[47] = SetRevFlag;				//于参数更新过程中初始化
