#ifndef			__weighting_h
#define			__weighting_h
#include "public.h"
void adc_init(void);
//u32bit get_adc(void);
u32bit filter1_func(void);
u32bit filter2_func(u32bit filter1_out);
s32bit NW_scale(void);
u32bit GW_measure(void);
s32bit NW_measure(void);
s32bit NW_scale_clr(void);
#endif