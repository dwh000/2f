//**************************************************************************
//整理：聂小猛。该资料来自“51单片机世界”http://go.163.com/~dz2000,欢迎访问。
// 对24C02的读、写
//*****************************************************************************
//*******************************************
#include "FM24C04.H"
sbit SCL  =  P0^3; //FM24C04的串行时钟

sbit SDA  =  P0^2; //FM24C04的串行数据

sbit EE_WP = P3^0;



/***************************************************************************/
#define WriteDeviceAddress 0xa0
#define ReadDviceAddress 0xa1

/***************************************************************************/

void delay(void)
	{
	u8bit cnt;
	for(cnt = 0; cnt < 30;cnt++) _nop_();
	}

/***************************************************************************/
void Start() 
{
    SDA=1;delay();
    SCL=1;delay();
    SDA=0;delay();
    SCL=0;delay();
}

/***************************************************************************/
void Stop() 
{
    SCL=0;delay();
    SDA=0;delay();
    SCL=1;delay();
    SDA=1;delay();
}

/***************************************************************************/
void Ack() 
{
    SDA=0;delay();
    SCL=1;delay();
    SCL=0;delay();
    SDA=1;delay();
}

/***************************************************************************/
void NoAck() 
{
    SDA=1;delay();
    SCL=1;delay();
    SCL=0;delay();
}

/***************************************************************************/
bit TestAck() 
{
    bit ErrorBit;
    SDA=1;delay();
    SCL=1;delay();
    ErrorBit=SDA;
    SCL=0;delay();
    return(ErrorBit);
}

/***************************************************************************/
void Write8Bit(unsigned char input) 
{
    unsigned char temp;
    for(temp=8;temp!=0;temp--)
       {
        SDA=(bit)(input&0x80);
		delay();
        SCL=1;delay();
        SCL=0;delay();
        input=input<<1;
        }
}

/***************************************************************************/
void Write24c04(unsigned char *Wdata,unsigned char RomAddress,unsigned char number) 
{
	EE_WP = 0;
    Start();
    Write8Bit(WriteDeviceAddress);
    TestAck();
    Write8Bit(RomAddress);
    TestAck();
    for(;number!=0;number--) 
       {
        Write8Bit(*Wdata);
        TestAck();
        Wdata++;
        }
    Stop();
	EE_WP = 1;
   //DelayMs(10);
}

/***************************************************************************/
unsigned char Read8Bit() 
{
    unsigned char temp,rbyte=0;
    for(temp=8;temp!=0;temp--) 
       {
        SCL=1;delay();
        rbyte=rbyte<<1;
        rbyte=rbyte|((unsigned char)(SDA));delay();
        SCL=0;delay();
        }
    return(rbyte);
}

/***************************************************************************/
void Read24c04(unsigned char *RamAddress,unsigned char RomAddress,unsigned char bytes) 
{
//    unsigned char temp,rbyte;
    Start();
    Write8Bit(WriteDeviceAddress);
    TestAck();
    Write8Bit(RomAddress);
    TestAck();
    Start();
    Write8Bit(ReadDviceAddress);
    TestAck();
    while(bytes!=1) 
        {
         *RamAddress=Read8Bit();
         Ack();
         RamAddress++;
         bytes--;
        }
    *RamAddress=Read8Bit();
    NoAck();
    Stop();
}

/***************************************************************************/


