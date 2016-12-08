#include "key_func.h"
#include "timer.h"

u8bit get_key(u8bit chk_val)
	{
	u8bit xdata key_value,i;
	for(i = 0;i < 4;i++)
		{
		key_value = (P1 & 0xf8);
		switch(chk_val)
			{
			case CHK_ALL_KEY:
				if(key_value == NOKEY_CLOSED)	return key_value;
				break;
			case SET_RELEASE:
			case ENT_RELEASE:
			case UP_RELEASE:
			case DWN_RELEASE:
			case CLR_RELEASE:
				if(key_value == (~chk_val))		return key_value;
				break;
			case UD_RELEASE:
				if(key_value == UP_CLOSED)		return NOKEY_CLOSED;
				if(key_value == DWN_CLOSED)		return NOKEY_CLOSED;
				break;
			case SET_CLOSED:
			case ENT_CLOSED:
			case UP_CLOSED:
			case DWN_CLOSED:
			case CLR_CLOSED:
				if(key_value != chk_val)		return NOKEY_CLOSED;
				break;
			default:
				return chk_val;	
			}
		delay_ms(30);
		}
	delay_ms(120);
	if(chk_val == CHK_ALL_KEY)	return key_value;
	else	return chk_val;
	}
	
u8bit get_input(void)
	{
	u8bit xdata key_value,i;
	for(i = 0;i < 4;i++)
		{
		if((P1 & 0X01) == 0X01)	break;
		delay_ms(3);
		}
	if(i == 4)	return 0x96;						//皮带连锁
	for(i = 0;i < 4;i++)
		{
		if(P2 == 0Xff)	return 0X20;
		delay_ms(3);
		}
	key_value =P2;
	if((key_value & BIT0) == 0)	return 0x95;		//插袋点
	if((key_value & BIT1) == 0)	return 0x96;		//皮带连锁信号
	if((key_value & BIT2) == 0)	return 0x97;		//开闸门信号
	if((key_value & BIT3) == 0)	return 0x98;		//掉袋点信号
	if((key_value & BIT4) == 0)	return 0x92;		//检重秤-校正信号
	if((key_value & BIT5) == 0)	return 0x91;		//检重秤+校正信号
	if((key_value & BIT6) == 0)	return 0x93;		//插袋信号
	if((key_value & BIT7) == 0)	return 0x94;		//清零点
	return 0X20;
	}
