		/*������Ⲣ����*/
		#if DEBUG
		MSG("\n\r\n\r Waiting for ZeroPoint !!!");
		#endif
		for(i=0;i<2;){		//��δ��⵽ȥ�����,��һֱִ�д˶γ���.
			//�����ȥ�����,����ʾ����
			if(zero_loc == ACTIVE)	{//��⵽�����
				i++;
				delay_ms(5);
			}
			else{//���û�м�⵽������ź�,��������²���
				menu_func();							//���ò˵�����
				dm_sp_weight();							//����ֱ���޸��趨ֵ����
				tare_zero_func();						//����ȥƤ���㺯��
				adc = NW_scale();
				/*�����Ⲣ��ʾ*/
				if(bag_det == ACTIVE)		disp_cache = 0x7f;	
				else	disp_cache = 0xff;
				disp_seg(disp_cache,BIT4);
				/*Ƥ���������������⴦����ʾ*/
				if(discharge_bag_en == ACTIVE)	disp_cache = 0x7f;
				else	disp_cache = 0xff;
				/*�������Ⲣ����******************************/
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
		if(i == 2)	{//������������
			s16bit xdata czero_scale_value;
			do	{//�����������ź�,��ѭ���������²���.
				czero_scale_value = zero_scale_value;
				zero_scale_value = 0;
				menu_func();						//���ò˵�����
				dm_sp_weight();						//����ֱ���޸��趨ֵ����
				tare_zero_func();					//����ȥƤ���㺯��
				adc = NW_scale();
				if(discharge_bag_en == ACTIVE)	disp_cache = 0x46;
				else	disp_cache = 0xff;
				if((adc > 3500) || (adc < -3500)){//��������ֵ�������㷶Χ,��
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
				else{//��������ֵ�����㷶Χ��,��
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
/*��բ���ź�,�������źż�Ⲣ����*/
		i=0;
		#if DEBUG
		MSG("\n\r\n\r Waiting for bag_det signal!!! ");
		#endif
		while(i<5){
			menu_func();			//���ò˵�����
			dm_sp_weight();			//����ֱ���޸��趨ֵ����
			tare_zero_func();		//����ȥƤ���㺯��	
			weight_detection_disp();//����,����ź�,Ƥ�������������⴦����ʾ	 
			/*�����Ⲣ����*/
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
			MSG("\n\r cyl(����) is on!!! ");
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
				MSG("\n\r cyl(����) is OFF!!! ");
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
			MSG("\n\r cyl(����) is OFF!!! ");
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
		




2013��3��19

P_temp = (u8bit *)&sp_weight;		//�����趨ֵ
TxBuf[1] = *P_temp++;
TxBuf[2] = *P_temp++;
TxBuf[3] = filter_coefficient;		//�˲�ϵ��
P_temp = (u8bit *)&sf_weight;		//��ϸ���л�ֵ
TxBuf[4] = *P_temp++;
TxBuf[5] = *P_temp++;
TxBuf[6] = sf_switch;				//��ϸ���л�����
P_temp = (u8bit *)&drop_weight;		//���
TxBuf[7] = *P_temp++;
TxBuf[8] = *P_temp++;
TxBuf[9] = ol_track_sw;				//����׷�ٿ���
TxBuf[10] = track_bags;				//׷�ٴ���
P_temp = (u8bit *)&residual_weight;	//����
TxBuf[11] = *P_temp++;
TxBuf[12] = *P_temp++;
TxBuf[13] = cl_correct_sw;				//�ջ�У������
P_temp = (u8bit *)&weight_correct_val;	//��������ֵ
TxBuf[14] = *P_temp++;
TxBuf[15] = *P_temp++;
TxBuf[16]=arrival_time;				//�ִ�ʱ��
TxBuf[17] = counter_sw;				//��������������
P_temp = (u8bit *)&load_cell_span;	//����������
TxBuf[18] = *P_temp++;
TxBuf[19] = *P_temp++;
TxBuf[20] = *P_temp++;
TxBuf[21] = *P_temp++;
P_temp = (u8bit *)&scale_output_val;//�������������ֵ
TxBuf[22] = *P_temp++;
TxBuf[23] = *P_temp++;
TxBuf[24] = *P_temp++;
TxBuf[25] = *P_temp++;
P_temp = (u8bit *)&scale_counterweight_val;//�������������ֵ
TxBuf[26] = *P_temp++;
TxBuf[27] = *P_temp++;
TxBuf[28] = *P_temp++;
TxBuf[29] = *P_temp++;
P_temp = (u8bit *)&tare_weight;		//Ƥ��
TxBuf[30] = *P_temp++;
TxBuf[31] = *P_temp++;
TxBuf[32] = *P_temp++;
TxBuf[33] = *P_temp++;
TxBuf[34] = �������ô���;			//�ڲ�����ʼ������
TxBuf[35] = �궨��������;			//�ڲ�����ʼ������
TxBuf[36] = Ӳ������;				//�ڲ�����ʼ������,
TxBuf[37] = ��װ���д���;
TxBuf[38] = ����״̬;
P_temp = (u8bit *)&DropCounter;		//����������,�ڼ�������λ�ø���
TxBuf[39] = *P_temp++;
TxBuf[40] = *P_temp++;
TxBuf[41] = *P_temp++;
TxBuf[42] = *P_temp++;
P_temp = (u8bit *)&WeightOfLastBag;	//�ϴε�������,��50������ʼ��
TxBuf[43] = *P_temp++;
TxBuf[44] = *P_temp++;
P_temp = (u8bit *)&CurrentWeight;	//���ع����г�ʼ��
TxBuf[45] = *P_temp++;
TxBuf[46] = *P_temp++;
TxBuf[47] = SetRevFlag;				//�ڲ������¹����г�ʼ��
