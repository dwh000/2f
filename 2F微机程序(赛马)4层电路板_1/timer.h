#ifndef     __timer_h
#define     __timer_h
#include "public.h"

sfr16 RCAP3    = 0xCA;                 // Timer3 capture/reload
sfr16 TMR3     = 0xCC;                 // Timer3
sfr16 RCAP4    = 0xCA;                 // Timer4 capture/reload
sfr16 TMR4     = 0xCC;                 // Timer4

void time01_init(void);
void time3_init();
void time4_init();
void t1_100ms(u8bit cnt);
void t1_stop(void);
void T0DelayMs(u8bit cnt);
void discharge_pulse100ms(u8bit cnt);                       //脉冲宽度设定函数.
void t4_50ms_cl_track(u8bit a_t);                           //闭环校正定时器启动函数

#define delay_ms(cnt)   T0DelayMs(cnt)

#endif

