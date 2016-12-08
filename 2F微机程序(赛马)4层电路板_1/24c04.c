/*******************************************************************************
*�ļ���: 24c04.c
*��  ��: ���Ļ�
*��  λ: ��ɽ���ܵ������޹�˾
*��  ��: 2012-9-21
*��  ��: ʵ��汾
*��������: ʹ��c8051��Ӳ��I2C����д��I2Cģ�����,������ʼ���Ͷ�д����.
*******************************************************************************/
#include "24c04.h"
#include "timer.h"

#define WR  0
#define RD  1

sbit SDA    = P0^2;
sbit SCL    = P0^3;
sbit EE_WP  = P0^4;

//IOģ��I2CӲ�������..
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
//ԭ��:	void I2C_start(void);
//����:	i2c���߽�����ʼ����
//���:	��
//����:	��
//����ֵ:��
//*************************************************
void I2C_start(void)
{
    sda_1();

    scl_1();

    sda_0();

    scl_0();
}

//*************************************************
//ԭ��:	void I2C_stop(void);
//����:	i2c���߽�����������
//���:	��
//����:	��
//����ֵ:��
//*************************************************
void I2C_stop(void)
{
    scl_1();

    sda_0();

    sda_1();
}
//*************************************************
//ԭ��:	void ack(bool a);
//����:	i2c����Ӧ��
//
//����:	��
//����ֵ:��
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
//ԭ��:	bool I2C_ack();
//����:	i2c����Ӧ��
//
//����:	��
//����ֵ:��Ӧ��,����1;��Ӧ��,����0.
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
//ԭ��:	void  wr_byte(uchar c);
//����:	дһ���ֽڵ�����
//���:	c	��Ҫ���͵�����
//����:	��
//����ֵ:��
//**************************************************
void  wr_byte(uchar c)
{
    uchar BitCnt;

    for(BitCnt=0;BitCnt<8;BitCnt++){
        if((c<<BitCnt)&0x80) sda_1();
        else  sda_0();
        
        scl_1();                            //��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
        
        scl_0();
    }
}

//**************************************************
//ԭ��:	uchar rd_byte(void);
//����:	��һ���ֽڵ�����
//���:	��
//����:	��
//����ֵ:����������
//**************************************************
uchar rd_byte(void)
{
    uchar retc=0;
    uchar BitCnt;

    sda_1();

    for(BitCnt=0;BitCnt<8;BitCnt++){
        scl_1();
        
        retc<<=1;
        if(SDA) retc += 1; /*������λ,���յ�����λ����retc�� */

        scl_0();
    }

    return (retc);
}


//IIC���ߵĳ�ʼ������
void iic_init(void)
{
//    SFRPAGE =   SMB0_PAGE;
    EE_WP =     1;                      //eepromд��������
//    EIE1 &=     0XFD;                   //��ֹSMB0�ж�
//    SMB0CR =    236;                    //����ʱ��Ƶ�ʴ����400k,����ֵ������239,��ֵԽС,Ƶ��Խ��!
//    SMB0CN =    0x44;                   //ʹ��SMBus0,����ȷ���ź�;
//    SFRPAGE =   CONFIG_PAGE;
}
/*u8bit ee_read(u8bit *ptr_data,u8bit addr,u8bit cnt) reentrant
{
    u8bit count;
    u16bit i = 0;

    SFRPAGE = SMB0_PAGE;                //ѡ��SFRҳΪSMB0ҳ
    SI = 0;
    AA = 1;                             //AA��ʼ����Ϊ����Ӧ���ź�
    STA = 1;                            //1����һ����ʼ����
    for(count = 0;count < cnt ;){
        while(SI == 0){                 //������߳�ʱ��û�з�Ӧ,������ʧ�ܱ�ʶ
            if(++i > 20000){
                STO = 1;
                return 0xfe;
            }
        }
        switch(SMB0STA){
			case 0X00:                  //���ߴ���;	����ʧ�ܱ�־
				STO = 1;
				return 0X00;
			case 0X08:                  //2��ʼ�������;���ʹӵ�ַ+W,��STA
				SMB0DAT = 0Xa0 + WR;
				STA = 0;
				break;
			case 0x10:                  //5���������ѷ���;���ʹӵ�ַ+R,��STA
				SMB0DAT = 0Xa0 + RD;
				STA = 0;
				break;
			case 0X18:                  //3�ӵ�ַ+W�ѷ���,�յ�ACK;���Ͳ�����ַ
				SMB0DAT = addr;
				break;
			case 0X28:                  //4�����ֽ��ѷ���,�յ�ACK;	��λSTA,�����ظ���ʼ����
				STA = 1;
				break;
			case 0x40:                  //6�ӵ�ַ+R�ѷ���,�յ�ACK;���ֻ����1�ֽ�,��AA,
				if(cnt == 1)    AA = 0; //					�ȴ���������
				break;
			case 0X50:		//7�����ֽ����յ�,ACK�ѷ���;��SMB0DAT,�ȴ���һ�ֽ�
				*ptr_data = SMB0DAT;	//,������¸��ֽ����һ���ֽ�,��AA
				ptr_data++;
				count++;
				if(count == (cnt - 1))	AA = 0;
				break;
			case 0x48:		//�ӵ�ַ+R�ѷ���,�յ�NACK;����ʧ�ܱ�־
				STO = 1;
				return 0x48;
			case 0x58:		//8�����ֽ����յ�,NACK�ѷ���;��λSTO,���ͽ�������
				*ptr_data = SMB0DAT;
				STO = 1;
				count++;
				break;
			case 0x38:		//����ʧ��;	����ʧ�ܱ�־
				STO = 1;
				return 0x38;
			default:
				STO = 1;
				return SMB0STA;
		}
		SI = 0;
	}
	SFRPAGE = CONFIG_PAGE;
	return 0XFD;			//������ɱ�־
}
u8bit ee_write(u8bit *ptr_data,u8bit addr,u8bit cnt) reentrant 
{
	u8bit count;
	u16bit i = 0;
	
	EE_WP = 0;							//�ر�д����
	SFRPAGE = SMB0_PAGE;				//ѡ��SFRҳΪSMB0ҳ
	SI = 0;								
	
	STA = 1;			//1����һ����ʼ����
	for(count = 0;count < cnt + 1;){
		while(SI == 0){	//������߳�ʱ��û�з�Ӧ,������ʧ�ܱ�ʶ
			if(++i > 20000){
				STO = 1;
				return 0xfe;
			}
		}
		switch(SMB0STA){
			case 0X00:		//���ߴ���;����ʧ�ܱ�־
				STO = 1;
				return 0X00;
			case 0X08:		//2��ʼ�������;���ʹӵ�ַ+W/R,��STA
				SMB0DAT = 0Xa0 + WR;
				STA = 0;
				break;
			case 0X18:		//3�ӵ�ַ+W/R�ѷ���,�յ�ACK;���Ͳ�����ַ
				SMB0DAT = addr;
				break;
			case 0x28:		//4�����ֽ��ѷ���,�յ�ACK;��������
				if(count == cnt){
					STO = 1;
					count++;
					break;
				}
				SMB0DAT = *ptr_data;
				ptr_data++;
				count++;
				break;
			case 0x20:		//�ӵ�ַ+W�ѷ���,�յ�NACK;����ʧ�ܱ�־
				STO = 1;
				return 0x20;
			case 0x30:		//�����ֽ��ѷ���,�յ�NACK;����ʧ�ܱ�־
				STO = 1;
				return 0x30;
			case 0x38:		//����ʧ��;����ʧ�ܱ�־
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
	EE_WP = 1;							//����д����
	return 0XFD;						//������ɱ�־
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


/*eeprom��ȡ���ݳ���*********************************************
�β�:
    ptr_data        :���������׵�ַ
    addr            :��ȡ��Ŀ���ַ
    cnt             :Ҫ��ȡ�����ݵĸ���.
����ֵ:
******************************************************************/	
u8bit eeprom_read(u8bit *ptr_data,u8bit addr,u8bit cnt)
{
    u8bit err;
    err =  ee_read(ptr_data,addr,cnt);
    if(err == 0XFD) return RD_DONE;
    return E03;
}

/*eeprom�������ݳ���*********************************************
�β�:
    ptr_data        :���������׵�ַ
    addr            :�����Ŀ���ַ
    cnt             :Ҫ��������ݵĸ���.
����ֵ:
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