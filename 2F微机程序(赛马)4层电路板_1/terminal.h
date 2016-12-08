#ifndef __terminal_h
    #define __terminal_h
    #include "public.h"	

    #if DP_ON
    sbit nRST		= P0^7;
    sbit S_RTS		= P0^6;
    sbit REQ_IT		= P3^0;
    u8bit pb_init(void);
    u8bit PbRestart(void);
    void PbTare(void);
    void PbNW_measure(void);
    u8bit DpDataExchange(void);
    #endif	//end of DP_ON
    #define B300	300
    #define B600	600
    #define B1200	1200
    #define B2400	2400
    #define B4800	4800
    #define B9600	9600
    #define B115200	115200
    /*
    //从机传输错误信息定义		//标识码:95h
    #define ERR_CC		BIT7	//不可识别的控制码
    #define ERR_DB		BIT6	//数据错误,或者数据域长度与实际数据数量不符
    #define ERR_AD		BIT5	//地址域非法或者超范围
    #define ERR_EV		BIT4	//偶校验错误
    #define ERR_AC		BIT3	//累加和校验错误
    #define ERR_IC		BIT2	//不能识别的数据标识码
    #define ACK			6
    #define	NAK         21
    */
    void uart0_init(u32bit baudrate);
#endif		// end of __terminal_h