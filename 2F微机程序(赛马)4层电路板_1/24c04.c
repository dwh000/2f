/*******************************************************************************
*文件名: 24c04.c
*作  者: 王文辉
*单  位: 唐山智能电子有限公司
*日  期: 2012-9-21
*版  本: 实验版本
*功能描述: 使用c8051的硬件I2C外设写的I2C模块程序,包含初始化和读写程序.
*******************************************************************************/
#include "24c04.h"
#include "timer.h"

#define WR  0
#define RD  1

sbit SDA    = P0^2;
sbit SCL    = P0^3;
sbit EE_WP  = P0^4;

//IO模拟I2C硬件层代码..
void scl_0(void)
{
    SCL = 0;
}
void scl_1(void)
{
    SCL = 1;
}
void sda_0(void)
{
    SDA = 0;
}
void sda_1(void)
{
    SDA = 1;
}
//*************************************************
//原型:	void I2C_start(void);
//功能:	i2c总线建立起始条件
//入口:	无
//出口:	无
//返回值:无
//*************************************************
void I2C_start(void)
{
    sda_1();

    scl_1();

    sda_0();

    scl_0();
}

//*************************************************
//原型:	void I2C_stop(void);
//功能:	i2c总线建立结束条件
//入口:	无
//出口:	无
//返回值:无
//*************************************************
void I2C_stop(void)
{
    scl_1();

    sda_0();

    sda_1();
}
//*************************************************
//原型:	void ack(bool a);
//功能:	i2c总线应答
//
//出口:	无
//返回值:无
//*************************************************
void ack(u8bit a)
{
    if(a)
        sda_0();
     else
        sda_1();

    scl_1();

    scl_0();
}

//*************************************************
//原型:	bool I2C_ack();
//功能:	i2c总线应答
//
//出口:	无
//返回值:有应答,返回1;无应答,返回0.
//*************************************************
u8bit I2C_ack()
{
    u8bit ack=1;
    //sda_1();
    scl_0();

    scl_1();

    if(SDA){
        ack=0;
    }

    scl_0();

    return ack;
}


//**************************************************
//原型:	void  wr_byte(uchar c);
//功能:	写一个字节的数据
//入口:	c	需要传送的数据
//出口:	无
//返回值:无
//**************************************************
void  wr_byte(uchar c)
{
    uchar BitCnt;

    for(BitCnt=0;BitCnt<8;BitCnt++){
        if((c<<BitCnt)&0x80) sda_1();
        else  sda_0();
        
        scl_1();                            //置时钟线为高，通知被控器开始接收数据位
        
        scl_0();
    }
}

//**************************************************
//原型:	uchar rd_byte(void);
//功能:	读一个字节的数据
//入口:	无
//出口:	无
//返回值:读出的数据
//**************************************************
uchar rd_byte(void)
{
    uchar retc=0;
    uchar BitCnt;

    sda_1();

    for(BitCnt=0;BitCnt<8;BitCnt++){
        scl_1();
        
        retc<<=1;
        if(SDA) retc += 1; /*读数据位,接收的数据位放入retc中 */

        scl_0();
    }

    return (retc);
}


//IIC总线的初始化程序
void iic_init(void)
{
//    SFRPAGE =   SMB0_PAGE;
    EE_WP =     1;                      //eeprom写保护开启
//    EIE1 &=     0XFD;                   //禁止SMB0中断
//    SMB0CR =    236;                    //设置时钟频率大概是400k,该数值不大于239,数值越小,频率越低!
//    SMB0CN =    0x44;                   //使能SMBus0,发送确认信号;
//    SFRPAGE =   CONFIG_PAGE;
}
/*u8bit ee_read(u8bit *ptr_data,u8bit addr,u8bit cnt) reentrant
{
    u8bit count;
    u16bit i = 0;

    SFRPAGE = SMB0_PAGE;                //选择SFR页为SMB0页
    SI = 0;
    AA = 1;                             //AA初始设置为发送应答信号
    STA = 1;                            //1发送一个起始条件
    for(count = 0;count < cnt ;){
        while(SI == 0){                 //如果总线长时间没有反应,将返回失败标识
            if(++i > 20000){
                STO = 1;
                return 0xfe;
            }
        }
        switch(SMB0STA){
			case 0X00:                  //总线错误;	返回失败标志
				STO = 1;
				return 0X00;
			case 0X08:                  //2起始条件完成;发送从地址+W,清STA
				SMB0DAT = 0Xa0 + WR;
				STA = 0;
				break;
			case 0x10:                  //5重启条件已发送;发送从地址+R,清STA
				SMB0DAT = 0Xa0 + RD;
				STA = 0;
				break;
			case 0X18:                  //3从地址+W已发出,收到ACK;发送操作地址
				SMB0DAT = addr;
				break;
			case 0X28:                  //4数据字节已发出,收到ACK;	置位STA,发送重复起始条件
				STA = 1;
				break;
			case 0x40:                  //6从地址+R已发出,收到ACK;如果只发送1字节,清AA,
				if(cnt == 1)    AA = 0; //					等待接收数据
				break;
			case 0X50:		//7数据字节已收到,ACK已发出;读SMB0DAT,等待下一字节
				*ptr_data = SMB0DAT;	//,如果是下个字节最后一个字节,清AA
				ptr_data++;
				count++;
				if(count == (cnt - 1))	AA = 0;
				break;
			case 0x48:		//从地址+R已发出,收到NACK;返回失败标志
				STO = 1;
				return 0x48;
			case 0x58:		//8数据字节已收到,NACK已发出;置位STO,发送结束条件
				*ptr_data = SMB0DAT;
				STO = 1;
				count++;
				break;
			case 0x38:		//竞争失败;	返回失败标志
				STO = 1;
				return 0x38;
			default:
				STO = 1;
				return SMB0STA;
		}
		SI = 0;
	}
	SFRPAGE = CONFIG_PAGE;
	return 0XFD;			//返回完成标志
}
u8bit ee_write(u8bit *ptr_data,u8bit addr,u8bit cnt) reentrant 
{
	u8bit count;
	u16bit i = 0;
	
	EE_WP = 0;							//关闭写保护
	SFRPAGE = SMB0_PAGE;				//选择SFR页为SMB0页
	SI = 0;								
	
	STA = 1;			//1发送一个起始条件
	for(count = 0;count < cnt + 1;){
		while(SI == 0){	//如果总线长时间没有反应,将返回失败标识
			if(++i > 20000){
				STO = 1;
				return 0xfe;
			}
		}
		switch(SMB0STA){
			case 0X00:		//总线错误;返回失败标志
				STO = 1;
				return 0X00;
			case 0X08:		//2起始条件完成;发送从地址+W/R,清STA
				SMB0DAT = 0Xa0 + WR;
				STA = 0;
				break;
			case 0X18:		//3从地址+W/R已发出,收到ACK;发送操作地址
				SMB0DAT = addr;
				break;
			case 0x28:		//4数据字节已发出,收到ACK;发送数据
				if(count == cnt){
					STO = 1;
					count++;
					break;
				}
				SMB0DAT = *ptr_data;
				ptr_data++;
				count++;
				break;
			case 0x20:		//从地址+W已发出,收到NACK;返回失败标志
				STO = 1;
				return 0x20;
			case 0x30:		//数据字节已发出,收到NACK;返回失败标志
				STO = 1;
				return 0x30;
			case 0x38:		//竞争失败;返回失败标志
				STO = 1;
				return 0x38;
			default:
				STO = 1;
				return SMB0STA;
		}
		SI = 0;
	}
	SFRPAGE = CONFIG_PAGE;
	//delay_ms(5);
	i=20000;
	while(i--);
	EE_WP = 1;							//开启写保护
	return 0XFD;						//返回完成标志
}

*/

u8bit ee_write(u8bit *ptr_data,u8bit addr,u8bit cnt) reentrant
{
    EE_WP =     0;
    delay_ms(10);
    I2C_start();

    wr_byte(0Xa0 + WR);
    if(!I2C_ack())  return 0;
        
    wr_byte(addr);
    if(!I2C_ack())  return 0;

    while(cnt){
        wr_byte(*ptr_data);
        if(!I2C_ack())  return 0;
        ptr_data++;
        cnt--;
    }
    I2C_stop();
    EE_WP =     1;
    return 0XFD;
}
ee_read(u8bit *ptr_data,u8bit addr,u8bit cnt) reentrant
{
    cnt--;

    I2C_start();

    wr_byte(0Xa0 + WR);
    if(!I2C_ack())  return 0;

    wr_byte(addr);
    if(!I2C_ack())  return 0;

    I2C_start();

    wr_byte(0Xa0 + RD);
    if(!I2C_ack())  return 0;

    while(cnt){
        *ptr_data=rd_byte();
        ptr_data++;
        cnt--;
        ack(1);
    }

    *ptr_data=rd_byte();
    ack(0);
    I2C_stop();
    return 0xfd;
}


/*eeprom读取数据程序*********************************************
形参:
    ptr_data        :数据区的首地址
    addr            :读取的目标地址
    cnt             :要读取的数据的个数.
返回值:
******************************************************************/	
u8bit eeprom_read(u8bit *ptr_data,u8bit addr,u8bit cnt)
{
    u8bit err;
    err =  ee_read(ptr_data,addr,cnt);
    if(err == 0XFD) return RD_DONE;
    return E03;
}

/*eeprom保存数据程序*********************************************
形参:
    ptr_data        :数据区的首地址
    addr            :保存的目标地址
    cnt             :要保存的数据的个数.
返回值:
******************************************************************/
u8bit eeprom_write(u8bit *ptr_data,u8bit addr,u8bit cnt) reentrant
{
    u8bit count,test[8];
    if(ee_write(ptr_data,addr,cnt) == 0XFD){
        if(ee_read(test,addr,cnt) == 0XFD){
            for(count = 0;count < cnt;count ++){
                if(test[count] != ptr_data[count])  return E05;
            }
            return WR_DONE;
        }
    }
    return E04;
}