#ifndef		__FM24C04_H
#define			__FM24C04_H
#include "public.h"


void Write24c04(unsigned char *Wdata,unsigned char RomAddress,unsigned char number) ;
void Read24c04(unsigned char *RamAddress,unsigned char RomAddress,unsigned char bytes);
#endif