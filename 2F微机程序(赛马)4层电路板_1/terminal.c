/*******************************************************************************
*文件名: terminal.c
*作  者: 王文辉
*单  位: 唐山智能电子有限公司
*日  期: 2012-9-21
*版  本: 实验版本
*功能描述: 串口的初始化及发送接收程序
*******************************************************************************/
#include "terminal.h"
#include "24c04.h"
#include "weighting.h"
#include "timer.h"
extern s16bit xdata drop_weight,residual_weight,zero_scale_value;
extern u16bit xdata sp_weight,sf_weight,sf_weight_adj_val,weight_correct_val,
                    shut_fb_w,WeightOfLast;
extern u8bit xdata  err_code,filter_coefficient,sf_switch,ol_track_sw,
                    w_save_cnt,filter_coefficient1,DpSwitch;
extern u8bit xdata  track_bags,cl_correct_sw,arrival_time,counter_sw,
                    CommAddr;
extern bit          t0_flag,t1_flag;
extern u32bit xdata load_cell_span,scale_output_val,scale_counterweight_val,
                    tare_weight,DropCounter,bags;
extern s32bit xdata adc;
bit RxDoneFlag;
bit ResetFlag = 0;
u8bit xdata RxBuf[60],TxBuf[70];

u8bit data_in_len;                                          //数据交换输入（实验板发送）数据长度
u8bit dil;                                                  //不包括校验和的data_in_len长度
u8bit data_out_len;                                         //数据交换输出（实验板接收）数据长度
u8bit dol;                                                  //不包括校验和的data_out_len长度
u8bit user_prm_len;                                         //用户参数长度
u8bit br_num = 5;


sfr16 RCAP2    = 0xCA;                                      // Timer2 capture/reload
sfr16 TMR2     = 0xCC;                                      // Timer2


#define SYSCLK       22118400L



void uart0_init(u32bit baudrate)
{
    char SFRPAGE_SAVE;
    SFRPAGE_SAVE = SFRPAGE;             // Preserve SFRPAGE
    SFRPAGE = TMR2_PAGE;
    TMR2CN = 0x00;                      // Timer in 16-bit auto-reload up timer
    TMR2CF = 0x08;                      // SYSCLK is time base; no output;
    RCAP2 = - ((long) SYSCLK/baudrate/16);
    TMR2 = RCAP2;
    TR2 = 1;                            // Start Timer2
    SFRPAGE = UART0_PAGE;
    SCON0 = 0xD0;                       // 9-bit variable baud rate;
    SSTA0 = 0x15;                       // Clear all flags; enable baud rate
                                        // doubler (not relevant for these
                                        // timers);
                                        // Use Timer2 as RX and TX baud rate
                                        // source;
    //RI0 = 1;                          // Indicate TX0 ready
    ES0 = 0;
    TI0 = 1;
    SFRPAGE = SFRPAGE_SAVE;             // Restore SFRPAGE
}

#if DP_ON
u8bit UartPutchar(u8bit ch)reentrant
{
    SFRPAGE     = UART0_PAGE;
    while(TI0 == 0);                    // USCI_A0 TX buffer ready?
    TI0         = 0;
    ACC         = ch;
    TB80        = P;                           //第九位数据位偶校验位
    SBUF0       = ACC;
    SFRPAGE     = CONFIG_PAGE;
    return ch;
}


//这里写DP通信的程序
u8bit PbGetchar(u8bit *ch)
{
    u8bit pErr_flag = 0;
    
    SFRPAGE = UART0_PAGE;
    while(!RI0){                                            //在规定时间内能够完成数据交换的读取的前提下
        if(S_RTS==0) return TIMEOUT;
    }
    if(RI0){
        ACC = SBUF0;
        if(P != RB80) pErr_flag=1;                          //偶校验错，置偶校验错标志
        *ch = ACC;                                          //接收一个字符送串口输入缓冲区
        RI0 = 0;
    }
    SFRPAGE = CONFIG_PAGE;
    return pErr_flag;
}
u8bit pb_init(void)
{
    bit pbinit_flag = 0;
    u32bit TimeOutCnt = 0;
    u8bit i,x,cnt = 0;
    //形成接口板的初始化报文****************************************************

    data_in_len =64+1+1;                                        //输入数据报文长度=48+1+1=50
    user_prm_len=0;                                             //用户参数长度=0
    data_out_len=48+1+1;                                        //输入数据报文长度=64+1+1=66
    TxBuf[0]    =CommAddr;                                      //BYTE0=从站地址
    TxBuf[1]    =0x06;                                          //BYTE1=ID号高位
    TxBuf[2]    =0xfa;                                          //BYTE2=ID号低位
    TxBuf[3]    =7;                                             //I/O配置数据长度=7；
    TxBuf[4]    =0x1f;                                          //I/O配置数据：0x1f,0x2f,0x1f,0x2f,0x1f,0x2f,0x1f
    TxBuf[5]    =0x2f;                 
    TxBuf[6]    =0x1f;
    TxBuf[7]    =0x2f;
    TxBuf[8]    =0x1f;
    TxBuf[9]    =0x2f;
    TxBuf[10]   =0x1f;
    TxBuf[24]   =data_in_len;                                  //输入数据报文长度
    TxBuf[25]   =data_out_len;                                 //输出数据报文长度
    TxBuf[26]   =user_prm_len;                                 //用户参数长度

    //求校验和******************************************************************
    TxBuf[48]   =0;
    for(i=0;i<48;i++)   TxBuf[48]=TxBuf[48]+TxBuf[i];
    //发送初始化报文,直到初始化成功*********************************************
    while(1){
        nRST        = 0;
        TimeOutCnt  = 4888;
        while(--TimeOutCnt);
        nRST        = 1;
        TimeOutCnt  = 0;
        while(S_RTS){                                       //等待se进入准备好接收状态
            if(++TimeOutCnt > 110592) return TIMEOUT;
        }
        for(i=0;i<49;i++) UartPutchar(TxBuf[i]);            //发送初始化报文
        TimeOutCnt = 0;
        while(!S_RTS){                                      //等待SE接收完毕
            if(++TimeOutCnt > 110592) return TIMEOUT;
        }
        //发送完毕、等待接收回答************************************************
        for(i=0;i<49;i++){                                  //接受回答报文共49个字节
            x = PbGetchar(&RxBuf[i]);
            if(x) break;                                    //如果发生错误,退出循环.
        }
        //以下分析接口板SE的回答报文********************************************
        if(x == 0){
            for(i=0;i<48;i++) x+=RxBuf[i];                  //求校验和
            if(x==RxBuf[48]){                               //校验和正确?
                if(RxBuf[0]==br_num){                       //返回的波特率号是5?
                    if(RxBuf[1]==0){                        //初始化报文错误号N=0?
                        for(i=2;i<48;i++){                  //byte2~byte47都是0xaa?
                            if(RxBuf[i]!=0xaa) break;
                        }
                        if(i==48) break;                    //初始化成功,退出循环
                        else cnt++;                         //初始化失败,失败计数
                        if(cnt > 20) return E11;            //20次初始化失败后,放弃初始化返回.
                    }
                }
            }
        }
    }
    for(i=0;i<60;i++)   RxBuf[i]=0;
    return GOOD;
}

u8bit PbRestart(void)
{
    u8bit PbRerr = 0;
    if((DpSwitch == ON) && REQ_IT){
        EA=0;
        PbRerr = pb_init();
        EA=1;
    }
    return PbRerr;
}

void PbTare(void)
{
    if(DpSwitch == ON){
        if(RxBuf[31] & BIT0){                               //联网去皮
            if((TxBuf[48] & BIT0) == 0){
                zero_scale_value = 0;
                tare_weight = GW_measure();
                eeprom_write((u8bit *)&tare_weight,TW_ADDR,4);
                TxBuf[48] |= BIT0;
            }
        }
        else TxBuf[48] &= ~BIT0;
    }
}

void PbNW_measure(void)
{
    s32bit adcval;
    u8bit *p_temp;
    if(DpSwitch == ON){
        adcval = NW_measure();
        p_temp = (u8bit *)&adcval;
        TxBuf[50] = *p_temp++;
        TxBuf[51] = *p_temp++;
        TxBuf[52] = *p_temp++;
        TxBuf[53] = *p_temp++;
    }
}
u8bit DpDataExchange(void)
{
    u8bit i=0,error;
    u16bit upara16;
    s16bit spara16;
    u32bit upara32,TimeOutCnt = 0;
    u8bit *ppp;
    dil=data_in_len-1;
    dol=data_out_len-1;
    {
        //初始化计数器到PB主站的数据************************************************
        TxBuf[0]    = 0;                                    //没有用户参数，请求数据命令为0，请求A型报文
        ppp         = (u8bit *)&sp_weight;                  //袋重设定值,OK
        TxBuf[1]    = *ppp++;
        TxBuf[2]    = *ppp++;
        TxBuf[3]    = filter_coefficient;                   //滤波系数,OK
        ppp         = (u8bit *)&sf_weight_adj_val;          //粗细流切换值,OK
        TxBuf[4]    = *ppp++;
        TxBuf[5]    = *ppp++;
        TxBuf[6]    = sf_switch;                            //粗细流切换开关,OK
        ppp         = (u8bit *)&drop_weight;                //落差,OK
        TxBuf[7]    = *ppp++;
        TxBuf[8]    = *ppp++;
        TxBuf[9]    = ol_track_sw;                          //开环追踪开关,OK
        TxBuf[10]   = track_bags;                           //追踪袋数,OK
        ppp         = (u8bit *)&residual_weight;            //净差,OK
        TxBuf[11]   = *ppp++;
        TxBuf[12]   = *ppp++;
        TxBuf[13]   = cl_correct_sw;                        //闭环校正开关,OK
        ppp         = (u8bit *)&weight_correct_val;         //袋重修正值
        TxBuf[14]   = *ppp++;
        TxBuf[15]   = *ppp++;
        TxBuf[16]   = arrival_time;                         //抵达时间,OK
        TxBuf[17]   = counter_sw;                           //掉包计数器开关OK
        ppp         = (u8bit *)&load_cell_span;             //传感器量程,OK
        TxBuf[18]   = *ppp++;
        TxBuf[19]   = *ppp++;
        TxBuf[20]   = *ppp++;
        TxBuf[21]   = *ppp++;
        ppp         = (u8bit *)&scale_output_val;           //传感器砝码输出值,OK
        TxBuf[22]   = *ppp++;
        TxBuf[23]   = *ppp++;
        TxBuf[24]   = *ppp++;
        TxBuf[25]   = *ppp++;
        ppp         = (u8bit *)&scale_counterweight_val;    //传感器砝码输出值,OK
        TxBuf[26]   = *ppp++;
        TxBuf[27]   = *ppp++;
        TxBuf[28]   = *ppp++;
        TxBuf[29]   = *ppp++;
        ppp         = (u8bit *)&tare_weight;                //皮重,OK
        TxBuf[30]   = *ppp++;
        TxBuf[31]   = *ppp++;
        TxBuf[32]   = *ppp++;
        TxBuf[33]   = *ppp++;
        //TxBuf[34] = 参数设置错误;                          //于参数初始化更新
        //TxBuf[35] = 标定参数错误;                          //于参数初始化更新
        TxBuf[36]   = 0;                                    //系统错误标志1
        TxBuf[37]   = 0;                                    //系统错误标志2
        if(!SizeFlowOut)    TxBuf[38] |= BIT7;
        else TxBuf[38] &= ~BIT7;
        if(!FullOut)    TxBuf[38] |= BIT6;
        else TxBuf[38] &= ~BIT6;
        if(!discharge_bag_sw_out) TxBuf[38] |= BIT5;
        else TxBuf[38] &= ~BIT5;
        if(!clamping_bag_out) TxBuf[38] |= BIT4;
        else TxBuf[38] &= ~BIT4;
        if(!fill_mot_sw_out)    TxBuf[38] |= BIT3;
        else TxBuf[38] &= ~BIT3;
        
        ppp         = (u8bit *)&DropCounter;                //掉包计数器,于计数器增加位置更新
        TxBuf[39]   = *ppp++;
        TxBuf[40]   = *ppp++;
        TxBuf[41]   = *ppp++;
        TxBuf[42]   = *ppp++;
        
        ppp         = (u8bit *)&WeightOfLast;
        TxBuf[43]   = *ppp++;
        TxBuf[44]   = *ppp++;

        if(adc < 0) upara16 = 0;
        else        upara16 = (u16bit)adc;
        ppp         = (u8bit *)&upara16;
        TxBuf[45]   = *ppp++;
        TxBuf[46]   = *ppp++;
//        TxBuf[47] 更新完成标志
//        TxBuf[48] 更新完成标志2
//        TxBuf[49] 输入信号
//        TxBuf[50-53] 净重值.
        //其他参数于参数设置,初始化,及pb数据交互完成********************************
    }
    TxBuf[dil]  = 0;
    for(i=0;i<dil;i++) TxBuf[dil]=TxBuf[dil]+TxBuf[i];      //求校验和

    TimeOutCnt  = 0;
    while(S_RTS){                                           //等待se进入准备好接收状态
        if(++TimeOutCnt > 110592) return TIMEOUT;
    }

    for(i=0;i<data_in_len;i++) UartPutchar(TxBuf[i]);

    TimeOutCnt  = 0;
    while(!S_RTS){                                          //等待SE接收完毕
        if(++TimeOutCnt > 110592) return TIMEOUT;
    }

    for(i=0;i<data_out_len;i++){                            //等待接收接口板的应答报文 
        error = PbGetchar(&RxBuf[i]);
        if(error) break;
    }
    if(error == 0){                                         //实验板接收回答报文长度正确
        error = 0;
        for(i=0;i<dol;i++)      error = error + RxBuf[i];   //求校验和
        if(error != RxBuf[dol]) error = B_SUMCHECK;         //校验和错
        else error = 0;
    }
    if(error) return error;
    
    {//接收到的数据刷新
        if(RxBuf[32]&BIT2){                                 //强制关闸板
            cyl_sw_out = SHUT;
            fine_flow_out = SHUT;
        }
        if(RxBuf[32]&BIT1){
            fill_mot_sw_out = SHUT;                         //强制关灌装电机
        }

        if((RxBuf[30] & BIT0) == BIT0){                     //更新袋重设定值及滤波系数
            if((TxBuf[47] & BIT0) == 0){
                ppp = (u8bit *)&upara16;
                *ppp++ = RxBuf[1];
                *ppp++ = RxBuf[2];
                if((upara16>=22000) && (upara16<=65000)){
                    shut_fb_w = shut_fb_w + upara16 - sp_weight;//关闸板判别值调整
                    sf_weight = shut_fb_w - sf_weight_adj_val;
                    sp_weight = upara16;
                    ee_write((u8bit *)&sp_weight,SP_WEIGHT_ADDR,2);
                    TxBuf[34] &= ~BIT6;                     //清除设定值报警
                }
                else TxBuf[34] |= BIT6;                     //设定值报警
                    
                if(RxBuf[3] <= 90){
                    filter_coefficient = RxBuf[3];
                    ee_write(&filter_coefficient,FILTER_ADDR,1);
                    filter_coefficient1 = (uchar)filter_coefficient * 1.1;
                    TxBuf[34] &= ~BIT7;                     //清除滤波系数报警
                }
                else TxBuf[34] |= BIT7;                     //滤波系数报警
                    
                TxBuf[47] |= BIT0;
            }
        }
        else TxBuf[47] &= ~BIT0;                            //复位已更新标志
            
        if((RxBuf[30] & BIT1) == BIT1){                     //更新粗细流设定值,粗细流开关
            if((TxBuf[47] & BIT1) == 0){
                ppp = (u8bit *)&upara16;
                *ppp++ = RxBuf[4];
                *ppp++ = RxBuf[5];
                if((upara16>=100) && (upara16<=10000)){
                    sf_weight_adj_val = upara16;
                    sf_weight = shut_fb_w - sf_weight_adj_val;
                    ee_write((u8bit *)&sf_weight_adj_val,SF_WEIGHT_ADDR,2);
                    TxBuf[34] &= ~BIT5;                     //清除粗细流设定值报警
                }
                else TxBuf[34] |= BIT5;                     //粗细流报警
                if((RxBuf[6] == ON) || (RxBuf[6] == OFF)){
                    sf_switch = RxBuf[6];
                    ee_write(&sf_switch,SF_SWITCH_ADDR,1);
                }
                TxBuf[47] |= BIT1;
            }
        }
        else TxBuf[47] &= ~BIT1;                            //复位已更新标志

        if((RxBuf[30] & BIT2) == BIT2){                     //更新标定参数
            if((TxBuf[47] & BIT2) == 0){
                ppp = (u8bit *)&upara32;
                *ppp++ = RxBuf[18];
                *ppp++ = RxBuf[19];
                *ppp++ = RxBuf[20];
                *ppp++ = RxBuf[21];
                if((upara32 == 100000) || (upara32 == 150000) ||
                   (upara32 == 200000) || (upara32 == 250000) ||
                   (upara32 == 300000) || (upara32 == 350000)){
                    load_cell_span = upara32;
                    ee_write((u8bit *)&load_cell_span,CELL_SPAN_ADDR,4);
                    TxBuf[35] &= ~BIT7;                     //清除量程非法报警
                }
                else TxBuf[35] |= BIT7;                     //量程非法报警
                
                ppp = (u8bit *)&upara32;
                *ppp++ = RxBuf[22];
                *ppp++ = RxBuf[23];
                *ppp++ = RxBuf[24];
                *ppp++ = RxBuf[25];
                if((upara32 >= 19000) && (upara32 <= 62000)){
                    scale_output_val = upara32;
                    ee_write((u8bit *)&scale_output_val,SCALE_OUTPUT_ADDR,4);
                    TxBuf[35] &= ~BIT4;                     //清除标定输出值报警
                }
                else TxBuf[35] |= BIT4;                     //标定输出值报警
                    
                ppp = (u8bit *)&upara32;
                *ppp++ = RxBuf[26];
                *ppp++ = RxBuf[27];
                *ppp++ = RxBuf[28];
                *ppp++ = RxBuf[29];
                if((upara32 >= 20000) && (upara32 <= 60000)){
                    scale_counterweight_val = upara32;
                    ee_write((u8bit *)&scale_counterweight_val,COUNTERWEIGHT_ADDR,4);
                    TxBuf[35] &= ~BIT3;                     //清除标定砝码值报警
                }
                else TxBuf[35] |= BIT3;                     //标定砝码值报警
                TxBuf[47] |= BIT2;
            }
        }
        else TxBuf[47] &= ~BIT2;                            //复位已更新标志
            
        if((RxBuf[30] & BIT3) == BIT3){                     //更新手动落差,袋重净差
            if((TxBuf[47] & BIT3) == 0){
                ppp = (u8bit *)&spara16;
                *ppp++ = RxBuf[7];
                *ppp++ = RxBuf[8];
                if((spara16 >= -2500) && (spara16 <= 2500)){
                    shut_fb_w = shut_fb_w + spara16 - drop_weight;//更新关闸板判别值
                    sf_weight = shut_fb_w - sf_weight_adj_val;
                    drop_weight = spara16;
                    ee_write((u8bit *)&drop_weight,DROP_WEIGHT_ADDR,2);
                    TxBuf[34] &= ~BIT4;                     //清除落差报警
                }
                else TxBuf[34] |= BIT4;
                ppp = (u8bit *)&spara16;
                *ppp++ = RxBuf[11];
                *ppp++ = RxBuf[12];
                if((spara16 >= -2500) && (spara16 <= 2500)){
                    residual_weight = spara16;
                    ee_write((u8bit *)&residual_weight,R_WEIGHT_ADDR,2);
                    TxBuf[34] &= ~BIT3;                     //清除净差报警
                }
                else TxBuf[34] |= BIT3;
                TxBuf[47] |= BIT3;
            }
        }
        else TxBuf[47] &= ~BIT3;                            //复位已更新标志

        if((RxBuf[30] & BIT4) == BIT4){                     //更新开环追踪开关,跟踪袋数
            if((TxBuf[47] & BIT4) == 0){
                if((RxBuf[9] == ON) || (RxBuf[9] == OFF)){
                    ol_track_sw = RxBuf[9];
                    if((ol_track_sw == ON) && (cl_correct_sw == ON)){
                        ol_track_sw = OFF;
                        cl_correct_sw = OFF;
                        TxBuf[34] |= BIT0;
                    }
                    else TxBuf[34] &= ~BIT0;                //追踪开关与自校正开关冲突
                    ee_write(&ol_track_sw,OL_TRACK_SW_ADDR,1);
                }
                if((RxBuf[10] < 11) && (RxBuf[10] > 0)){
                    track_bags = RxBuf[10];
                    ee_write(&track_bags,TRACK_BAGS_ADDR,1);
                    TxBuf[35] &= ~BIT1;                     //清除袋重修正值报警
                }
                else TxBuf[35] |= BIT1;                     //袋重修正值报警
                TxBuf[47] |= BIT4;
            }
        }
        else TxBuf[47] &= ~BIT4;                            //复位已更新标志
                                    
        if((RxBuf[30] & BIT5) == BIT5){                     //更新掉包计数器开关
            if((TxBuf[47] & BIT5) == 0){
                if((RxBuf[17] == ON) || (RxBuf[17] == OFF)){
                    counter_sw = RxBuf[17];
                    TxBuf[17] = counter_sw;
                    ee_write(&counter_sw,COUTER_SW_ADDR,1);
                }
            TxBuf[47] |= BIT5;
            }
        }
        else TxBuf[47] &= ~BIT5;                            //复位已更新标志
            
        if((RxBuf[30] & BIT6) == BIT6){                     //更新袋重修正值,闭环校正开关,抵达时间
            if((TxBuf[47] & BIT6) == 0){
                ppp = (u8bit *)&upara16;
                *ppp++ = RxBuf[14];
                *ppp++ = RxBuf[15];
                if((upara16 >= 0) && (upara16 <= 1500)){
                    weight_correct_val = upara16;
                    ee_write((u8bit *)&weight_correct_val,WEIGHT_CORRECT_ADDR,2);
                    TxBuf[34] &= ~BIT2;                     //清除袋重修正值报警
                }
                else TxBuf[34] |= BIT2;                     //袋重修正值报警
                    
                if((RxBuf[13] == ON) || (RxBuf[13] == OFF)){
                    cl_correct_sw = RxBuf[13];
                    if((ol_track_sw == ON) && (cl_correct_sw == ON)){
                        ol_track_sw = OFF;
                        cl_correct_sw = OFF;
                        TxBuf[34] |= BIT0;                  //追踪开关与自校正开关冲突
                    }
                    else TxBuf[34] &= ~BIT0;
                    ee_write(&cl_correct_sw,CL_CORRECT_SW_ADDR,1);
                }
                if(RxBuf[16] != 0){
                    arrival_time = RxBuf[16];
                    ee_write(&arrival_time,ARRIVAL_TIME_ADDR,1);
                    TxBuf[34] &= ~BIT1;                     //清除抵达时间报警
                }
                else TxBuf[34] |= BIT1;
                TxBuf[47] |= BIT6;
            }
        }
        else TxBuf[47] &= ~BIT6;                            //复位已更新标志
            
        if((RxBuf[30] & BIT7) == BIT7){                     //更新掉包计数器清零.
            if((TxBuf[47] & BIT7) == 0){
                DropCounter = 0;
                TxBuf[47] |= BIT7;
            }
        }
        else TxBuf[47] &= ~BIT7;                            //复位已更新标志
    }
    return GOOD;                                            //返回数据交换完成标示
}

#endif  //end of DP_ON
