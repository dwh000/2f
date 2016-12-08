
#line 1 "main.c" /0







 
 
 
  
#line 1 "public.h" /0
 
 
 
  
#line 1 "D:\Program Files\keil\C51\Inc\Cygnal\c8051f060.h" /0











 
 
 
 
 sfr P0            = 0x80;  
 sfr SP            = 0x81;  
 sfr DPL           = 0x82;  
 sfr DPH           = 0x83;  
 sfr SFRPAGE       = 0x84;  
 sfr SFRNEXT       = 0x85;  
 sfr SFRLAST       = 0x86;  
 sfr PCON          = 0x87;  
 sfr CPT0CN        = 0x88;  
 sfr CPT1CN        = 0x88;  
 sfr CPT2CN        = 0x88;  
 sfr TCON          = 0x88;  
 sfr CPT0MD        = 0x89;  
 sfr CPT1MD        = 0x89;  
 sfr CPT2MD        = 0x89;  
 sfr TMOD          = 0x89;  
 sfr OSCICN        = 0x8A;  
 sfr TL0           = 0x8A;  
 sfr OSCICL        = 0x8B;  
 sfr TL1           = 0x8B;  
 sfr OSCXCN        = 0x8C;  
 sfr TH0           = 0x8C;  
 sfr TH1           = 0x8D;  
 sfr CKCON         = 0x8E;  
 sfr PSCTL         = 0x8F;  
 sfr P1            = 0x90;  
 sfr SSTA0         = 0x91;  
 sfr SFRPGCN       = 0x96;  
 sfr CLKSEL        = 0x97;  
 sfr SCON0         = 0x98;  
 sfr SCON1         = 0x98;  
 sfr SBUF0         = 0x99;  
 sfr SBUF1         = 0x99;  
 sfr SPI0CFG       = 0x9A;  
 sfr SPI0DAT       = 0x9B;  
 sfr P4MDOUT       = 0x9C;  
 sfr P5MDOUT       = 0x9D;  
 sfr SPI0CKR       = 0x9D;  
 sfr P6MDOUT       = 0x9E;  
 sfr P7MDOUT       = 0x9F;  
 sfr P2            = 0xA0;  
 sfr EMI0TC        = 0xA1;  
 sfr EMI0CN        = 0xA2;  
 sfr EMI0CF        = 0xA3;  
 sfr P0MDOUT       = 0xA4;  
 sfr P1MDOUT       = 0xA5;  
 sfr P2MDOUT       = 0xA6;  
 sfr P3MDOUT       = 0xA7;  
 sfr IE            = 0xA8;  
 sfr SADDR0        = 0xA9;  
 sfr P1MDIN        = 0xAD;  
 sfr P2MDIN        = 0xAE;  
 sfr P3            = 0xB0;  
 sfr FLACL         = 0xB7;  
 sfr FLSCL         = 0xB7;  
 sfr IP            = 0xB8;  
 sfr SADEN0        = 0xB9;  
 sfr ADC0CPT       = 0xBA;  
 sfr AMX2CF        = 0xBA;  
 sfr ADC0CCF       = 0xBB;  
 sfr AMX0SL        = 0xBB;  
 sfr AMX2SL        = 0xBB;  
 sfr ADC0CF        = 0xBC;  
 sfr ADC1CF        = 0xBC;  
 sfr ADC2CF        = 0xBC;  
 sfr ADC0L         = 0xBE;  
 sfr ADC1L         = 0xBE;  
 sfr ADC2L         = 0xBE;  
 sfr ADC0H         = 0xBF;  
 sfr ADC1H         = 0xBF;  
 sfr ADC2H         = 0xBF;  
 sfr CAN0STA       = 0xC0;  
 sfr SMB0CN        = 0xC0;  
 sfr SMB0STA       = 0xC1;  
 sfr SMB0DAT       = 0xC2;  
 sfr SMB0ADR       = 0xC3;  
 sfr ADC0GTL       = 0xC4;  
 sfr ADC2GTL       = 0xC4;  
 sfr ADC0GTH       = 0xC5;  
 sfr ADC2GTH       = 0xC5;  
 sfr ADC0LTL       = 0xC6;  
 sfr ADC2LTL       = 0xC6;  
 sfr ADC0LTH       = 0xC7;  
 sfr ADC2LTH       = 0xC7;  
 sfr P4            = 0xC8;  
 sfr TMR2CN        = 0xC8;  
 sfr TMR3CN        = 0xC8;  
 sfr TMR4CN        = 0xC8;  
 sfr TMR2CF        = 0xC9;  
 sfr TMR3CF        = 0xC9;  
 sfr TMR4CF        = 0xC9;  
 sfr RCAP2L        = 0xCA;  
 sfr RCAP3L        = 0xCA;  
 sfr RCAP4L        = 0xCA;  
 sfr RCAP2H        = 0xCB;  
 sfr RCAP3H        = 0xCB;  
 sfr RCAP4H        = 0xCB;  
 sfr TMR2L         = 0xCC;  
 sfr TMR3L         = 0xCC;  
 sfr TMR4L         = 0xCC;  
 sfr TMR2H         = 0xCD;  
 sfr TMR3H         = 0xCD;  
 sfr TMR4H         = 0xCD;  
 sfr SMB0CR        = 0xCF;  
 sfr PSW           = 0xD0;  
 sfr REF0CN        = 0xD1;  
 sfr REF1CN        = 0xD1;  
 sfr REF2CN        = 0xD1;  
 sfr DAC0L         = 0xD2;  
 sfr DAC1L         = 0xD2;  
 sfr DAC0H         = 0xD3;  
 sfr DAC1H         = 0xD3;  
 sfr DAC0CN        = 0xD4;  
 sfr DAC1CN        = 0xD4;  
 sfr CAN0DATL      = 0xD8;  
 sfr DMA0CN        = 0xD8;  
 sfr P5            = 0xD8;  
 sfr PCA0CN        = 0xD8;  
 sfr CAN0DATH      = 0xD9;  
 sfr DMA0DAL       = 0xD9;  
 sfr PCA0MD        = 0xD9;  
 sfr CAN0ADR       = 0xDA;  
 sfr DMA0DAH       = 0xDA;  
 sfr PCA0CPM0      = 0xDA;  
 sfr CAN0TST       = 0xDB;  
 sfr DMA0DSL       = 0xDB;  
 sfr PCA0CPM1      = 0xDB;  
 sfr DMA0DSH       = 0xDC;  
 sfr PCA0CPM2      = 0xDC;  
 sfr DMA0IPT       = 0xDD;  
 sfr PCA0CPM3      = 0xDD;  
 sfr DMA0IDT       = 0xDE;  
 sfr PCA0CPM4      = 0xDE;  
 sfr PCA0CPM5      = 0xDF;  
 sfr ACC           = 0xE0;  
 sfr PCA0CPL5      = 0xE1;  
 sfr XBR0          = 0xE1;  
 sfr PCA0CPH5      = 0xE2;  
 sfr XBR1          = 0xE2;  
 sfr XBR2          = 0xE3;  
 sfr XBR3          = 0xE4;  
 sfr EIE1          = 0xE6;  
 sfr EIE2          = 0xE7;  
 sfr ADC0CN        = 0xE8;  
 sfr ADC1CN        = 0xE8;  
 sfr ADC2CN        = 0xE8;  
 sfr P6            = 0xE8;  
 sfr PCA0CPL2      = 0xE9;  
 sfr PCA0CPH2      = 0xEA;  
 sfr PCA0CPL3      = 0xEB;  
 sfr PCA0CPH3      = 0xEC;  
 sfr PCA0CPL4      = 0xED;  
 sfr PCA0CPH4      = 0xEE;  
 sfr RSTSRC        = 0xEF;  
 sfr B             = 0xF0;  
 sfr EIP1          = 0xF6;  
 sfr EIP2          = 0xF7;  
 sfr CAN0CN        = 0xF8;  
 sfr DMA0CF        = 0xF8;  
 sfr P7            = 0xF8;  
 sfr SPI0CN        = 0xF8;  
 sfr DMA0CTL       = 0xF9;  
 sfr PCA0L         = 0xF9;  
 sfr DMA0CTH       = 0xFA;  
 sfr PCA0H         = 0xFA;  
 sfr DMA0CSL       = 0xFB;  
 sfr PCA0CPL0      = 0xFB;  
 sfr DMA0CSH       = 0xFC;  
 sfr PCA0CPH0      = 0xFC;  
 sfr DMA0BND       = 0xFD;  
 sfr PCA0CPL1      = 0xFD;  
 sfr DMA0ISW       = 0xFE;  
 sfr PCA0CPH1      = 0xFE;  
 sfr WDTCN         = 0xFF;  
 
 
 
 
 
 sbit TF1 =        0x8F ;   
 sbit TR1 =        0x8E ;   
 sbit TF0 =        0x8D ;   
 sbit TR0 =        0x8C ;   
 sbit IE1 =        0x8B ;   
 sbit IT1 =        0x8A ;   
 sbit IE0 =        0x89 ;   
 sbit IT0 =        0x88 ;   
 
 
 sbit CP0EN =      0x8F ;   
 sbit CP0OUT =     0x8E ;   
 sbit CP0RIF =     0x8D ;   
 sbit CP0FIF =     0x8C ;   
 sbit CP0HYP1 =    0x8B ;   
 sbit CP0HYP0 =    0x8A ;   
 sbit CP0HYN1 =    0x89 ;   
 sbit CP0HYN0 =    0x88 ;   
 
 
 sbit CP1EN =      0x8F ;   
 sbit CP1OUT =     0x8E ;   
 sbit CP1RIF =     0x8D ;   
 sbit CP1FIF =     0x8C ;   
 sbit CP1HYP1 =    0x8B ;   
 sbit CP1HYP0 =    0x8A ;   
 sbit CP1HYN1 =    0x89 ;   
 sbit CP1HYN0 =    0x88 ;   
 
 
 sbit CP2EN =      0x8F ;   
 sbit CP2OUT =     0x8E ;   
 sbit CP2RIF =     0x8D ;   
 sbit CP2FIF =     0x8C ;   
 sbit CP2HYP1 =    0x8B ;   
 sbit CP2HYP0 =    0x8A ;   
 sbit CP2HYN1 =    0x89 ;   
 sbit CP2HYN0 =    0x88 ;   
 
 
 sbit SM00 =       0x9F ;   
 sbit SM10 =       0x9E ;   
 sbit SM20 =       0x9D ;   
 sbit REN0 =       0x9C ;   
 sbit TB80 =       0x9B ;   
 sbit RB80 =       0x9A ;   
 sbit TI0 =        0x99 ;   
 sbit RI0 =        0x98 ;   
 
 
 sbit S1MODE =     0x9F ;   
 sbit MCE1 =       0x9D ;   
 sbit REN1 =       0x9C ;   
 sbit TB81 =       0x9B ;   
 sbit RB81 =       0x9A ;   
 sbit TI1 =        0x99 ;   
 sbit RI1 =        0x98 ;   
 
 
 sbit EA =         0xAF ;   
 sbit ET2  =       0xAD ;   
 sbit ES0  =       0xAC ;   
 sbit ET1 =        0xAB ;   
 sbit EX1 =        0xAA ;   
 sbit ET0 =        0xA9 ;   
 sbit EX0 =        0xA8 ;   
 
 
 sbit PT2 =        0xBD ;   
 sbit PS =         0xBC ;   
 sbit PT1 =        0xBB ;   
 sbit PX1 =        0xBA ;   
 sbit PT0 =        0xB9 ;   
 sbit PX0 =        0xB8 ;   
 
 
 sbit BOFF =       0xC7 ;   
 sbit EWARN =      0xC6 ;   
 sbit EPASS =      0xC5 ;   
 sbit RXOK =       0xC4 ;   
 sbit TXOK =       0xC3 ;   
 sbit LEC2 =       0xC2 ;   
 sbit LEC1 =       0xC1 ;   
 sbit LEC0 =       0xC0 ;   
 
 
 sbit BUSY =       0xC7 ;   
 sbit ENSMB =      0xC6 ;   
 sbit STA  =       0xC5 ;   
 sbit STO =        0xC4 ;   
 sbit SI =         0xC3 ;   
 sbit AA =         0xC2 ;   
 sbit SMBFTE =     0xC1 ;   
 sbit SMBTOE =     0xC0 ;   
 
 
 sbit TF2 =        0xCF ;   
 sbit EXF2 =       0xCE ;   
 sbit EXEN2 =      0xCB ;   
 sbit TR2 =        0xCA ;   
 sbit CT2 =        0xC9 ;   
 sbit CPRL2 =      0xC8 ;   
 
 
 sbit TF3 =        0xCF ;   
 sbit EXF3 =       0xCE ;   
 sbit EXEN3 =      0xCB ;   
 sbit TR3 =        0xCA ;   
 sbit CT3 =        0xC9 ;   
 sbit CPRL3 =      0xC8 ;   
 
 
 sbit TF4 =        0xCF ;   
 sbit EXF4 =       0xCE ;   
 sbit EXEN4 =      0xCB ;   
 sbit TR4 =        0xCA ;   
 sbit CT4 =        0xC9 ;   
 sbit CPRL4 =      0xC8 ;   
 
 
 sbit CY =         0xD7 ;   
 sbit AC =         0xD6 ;   
 sbit F0 =         0xD5 ;   
 sbit RS1 =        0xD4 ;   
 sbit RS0 =        0xD3 ;   
 sbit OV =         0xD2 ;   
 sbit F1 =         0xD1 ;   
 sbit P =          0xD0 ;   
 
 
 sbit DMA0EN =     0xDF ;   
 sbit DMA0INT =    0xDE ;   
 sbit DMA0MD =     0xDD ;   
 sbit DMA0DE1 =    0xDC ;   
 sbit DMA0DE0 =    0xDB ;   
 sbit DMA0DOE =    0xDA ;   
 sbit DMA0DO1 =    0xD9 ;   
 sbit DMA0DO0 =    0xD8 ;   
 
 
 sbit CF =         0xDF ;   
 sbit CR =         0xDE ;   
 sbit CCF5 =       0xDD ;   
 sbit CCF4 =       0xDC ;   
 sbit CCF3 =       0xDB ;   
 sbit CCF2 =       0xDA ;   
 sbit CCF1 =       0xD9 ;   
 sbit CCF0 =       0xD8 ;   
 
 
 sbit AD0EN  =     0xEF ;   
 sbit AD0TM =      0xEE ;   
 sbit AD0INT =     0xED ;   
 sbit AD0BUSY =    0xEC ;   
 sbit AD0CM1   =   0xEB ;   
 sbit AD0CM0 =     0xEA ;   
 sbit AD0WINT =    0xE9 ;   
 
 
 sbit AD1EN  =     0xEF ;   
 sbit AD1TM =      0xEE ;   
 sbit AD1INT =     0xED ;   
 sbit AD1BUSY =    0xEC ;   
 sbit AD1CM2   =   0xEB ;   
 sbit AD1CM1 =     0xEA ;   
 sbit AD1CM0 =     0xE9 ;   
 
 
 sbit AD2EN  =     0xEF ;   
 sbit AD2TM =      0xEE ;   
 sbit AD2INT =     0xED ;   
 sbit AD2BUSY =    0xEC ;   
 sbit AD2CM1   =   0xEB ;   
 sbit AD2CM0 =     0xEA ;   
 sbit AD2WINT =    0xE9 ;   
 sbit AD2LJST =    0xE8 ;   
 
 
 sbit DMA0HLT =    0xFF ;   
 sbit DMA0XBY =    0xFE ;   
 sbit DMA0CIE =    0xFB ;   
 sbit DMA0CI =     0xFA ;   
 sbit DMA0EOE =    0xF9 ;   
 sbit DMA0EO =     0xF8 ;   
 
 
 sbit SPIF =       0xFF ;   
 sbit WCOL =       0xFE ;   
 sbit MODF =       0xFD ;   
 sbit RXOVRN =     0xFC ;   
 sbit NSSMD1 =     0xFB ;   
 sbit NSSMD0 =     0xFA ;   
 sbit TXBMT =      0xF9 ;   
 sbit SPIEN =      0xF8 ;   
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 4 "public.h" /0
 
  
#line 1 "VerCtrl.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 45 "VerCtrl.h" /1
  
 
#line 47 "VerCtrl.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 5 "public.h" /0
 
  
#line 1 "D:\Program Files\keil\C51\Inc\intrins.h" /0






 
 
 
 
 
 #pragma SAVE
 
 
#line 15 "D:\Program Files\keil\C51\Inc\intrins.h" /1
 
 
 
#line 18 "D:\Program Files\keil\C51\Inc\intrins.h" /0
 
 extern void          _nop_     (void);
 extern bit           _testbit_ (bit);
 extern unsigned char _cror_    (unsigned char, unsigned char);
 extern unsigned int  _iror_    (unsigned int,  unsigned char);
 extern unsigned long _lror_    (unsigned long, unsigned char);
 extern unsigned char _crol_    (unsigned char, unsigned char);
 extern unsigned int  _irol_    (unsigned int,  unsigned char);
 extern unsigned long _lrol_    (unsigned long, unsigned char);
 extern unsigned char _chkfloat_(float);
 
#line 29 "D:\Program Files\keil\C51\Inc\intrins.h" /1
 
 
#line 31 "D:\Program Files\keil\C51\Inc\intrins.h" /0
 
 extern void          _push_    (unsigned char _sfr);
 extern void          _pop_     (unsigned char _sfr);
 
 
 #pragma RESTORE
 
 
 
#line 6 "public.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sbit        cyl_sw_out                  =   P3^1;            
 sbit        fine_flow_out               =   P3^2;            
 sbit        discharge_bag_sw_out        =   P3^3;            
 sbit        flashboard_sw_out           =   P3^4;            
 sbit        fill_mot_sw_out             =   P3^5;            
 sbit        clamping_bag_out            =   P3^4;            
 
 sbit        FullOut                     =   P3^1;            
 sbit        SizeFlowOut                 =   P3^2;            
 
 
 sbit        discharge_bag_en            = P1^0;              
 sbit        zero_loc                    = P2^0;              
 sbit        discharge_bag_loc           = P2^1;              
 sbit        open_flashboard_det         = P2^2;              
 sbit        gate_opened_loc             = P2^3;              
 sbit        bag_det                     = P2^4;              
 sbit        add_correct                 = P2^5;              
 sbit        reduce_correct              = P2^6;              
 sbit        into_bag_loc                = P2^7;              
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 11 "main.c" /0
 
  
#line 1 "disp.h" /0
 
 
  
#line 1 "public.h" /0
 
#line 2 "public.h" /1
  
 
  
  
  
 
 
 
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
 
  
  
 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
 
  
  
  
  
  
  
  
 
  
  
  
 
  
  
 
 
  
  
  
  
  
  
  
  
 
 
#line 3 "disp.h" /0
#line 3 "disp.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 void run_disp(signed long disp_data);
 void weight_disp(signed long disp_data);
 void flash_disp(signed long disp_data);
 void disp_symbol(unsigned char disp_code);
 void disp_int(unsigned int disp_data);
 void disp_seg(unsigned char seg_code,unsigned char bit_addr);
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 12 "main.c" /0
 
  
#line 1 "24c04.h" /0
 
 
 
  
#line 1 "public.h" /0
 
#line 2 "public.h" /1
  
 
  
  
  
 
 
 
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
 
  
  
 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
 
  
  
  
  
  
  
  
 
  
  
  
 
  
  
 
 
  
  
  
  
  
  
  
  
 
 
#line 4 "24c04.h" /0
#line 4 "24c04.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






 
  unsigned char eeprom_read(unsigned char *ptr_data,unsigned char addr,unsigned char cnt);
 
 






 
  unsigned char eeprom_write(unsigned char *ptr_data,unsigned char addr,unsigned char cnt);
 
 
 void iic_init(void);
 
  unsigned char ee_write(unsigned char *ptr_data,unsigned char addr,unsigned char cnt) reentrant;
 
 
#line 13 "main.c" /0
 
  
#line 1 "key_func.h" /0
 
 
  
#line 1 "public.h" /0
 
#line 2 "public.h" /1
  
 
  
  
  
 
 
 
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
 
  
  
 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
 
  
  
  
  
  
  
  
 
  
  
  
 
  
  
 
 
  
  
  
  
  
  
  
  
 
 
#line 3 "key_func.h" /0
#line 3 "key_func.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  unsigned char get_key(unsigned char chk_val);
  unsigned char get_input(void);
 
 
#line 14 "main.c" /0
 
  
#line 1 "menu_func.h" /0
 
 
  
#line 1 "public.h" /0
 
#line 2 "public.h" /1
  
 
  
  
  
 
 
 
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
 
  
  
 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
 
  
  
  
  
  
  
  
 
  
  
  
 
  
  
 
 
  
  
  
  
  
  
  
  
 
 
#line 3 "menu_func.h" /0
#line 3 "menu_func.h" /0
 
 
 
 
 
 
 
 void menu_func(void);
 void tare_zero_func(void);		 
 void dm_sp_weight(void);		 
 
#line 15 "main.c" /0
 
  
#line 1 "timer.h" /0
 
 
  
#line 1 "public.h" /0
 
#line 2 "public.h" /1
  
 
  
  
  
 
 
 
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
 
  
  
 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
 
  
  
  
  
  
  
  
 
  
  
  
 
  
  
 
 
  
  
  
  
  
  
  
  
 
 
#line 3 "timer.h" /0
#line 3 "timer.h" /0
 
 
 sfr16 RCAP3    = 0xCA;                  
 sfr16 TMR3     = 0xCC;                  
 sfr16 RCAP4    = 0xCA;                  
 sfr16 TMR4     = 0xCC;                  
 
 void time01_init(void);
 void time3_init();
 void time4_init();
 void t1_100ms(unsigned char cnt);
 void t1_stop(void);
 void T0DelayMs(unsigned char cnt);
 void discharge_pulse100ms(unsigned char cnt);                        
 void t4_50ms_cl_track(unsigned char a_t);                            
 
 
 
 
 
#line 16 "main.c" /0
 
  
#line 1 "weighting.h" /0
 
 
  
#line 1 "public.h" /0
 
#line 2 "public.h" /1
  
 
  
  
  
 
 
 
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
 
  
  
 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
 
  
  
  
  
  
  
  
 
  
  
  
 
  
  
 
 
  
  
  
  
  
  
  
  
 
 
#line 3 "weighting.h" /0
#line 3 "weighting.h" /0
 
 void adc_init(void);
 
  unsigned long filter1_func(void);
  unsigned long filter2_func(unsigned long filter1_out);
  signed long NW_scale(void);
  unsigned long GW_measure(void);
  signed long NW_measure(void);
  signed long NW_scale_clr(void);
 
#line 17 "main.c" /0
 
  
#line 1 "terminal.h" /0
 
 
  
#line 1 "public.h" /0
 
#line 2 "public.h" /1
  
 
  
  
  
 
 
 
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
 
  
  
 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
 
  
  
  
  
  
  
  
 
  
  
  
 
  
  
 
 
  
  
  
  
  
  
  
  
 
 
#line 3 "terminal.h" /0
#line 3 "terminal.h" /0
 
 
 
 sbit nRST		= P0^7;
 sbit S_RTS		= P0^6;
 sbit REQ_IT		= P3^0;
  unsigned char pb_init(void);
 void PbRestart(void);
 void PbTare(void);
 void PbNW_measure(void);
  unsigned char DpDataExchange(void);
 
 
 
 
 
 
 
 










 
 void uart0_init(unsigned long baudrate);
 
#line 18 "main.c" /0
 
  
#line 1 "D:\Program Files\keil\C51\Inc\stdio.h" /0






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 typedef unsigned int size_t;
 
 
 #pragma SAVE
 #pragma REGPARMS
 extern char _getkey (void);
 extern char getchar (void);
 extern char ungetchar (char);
 extern char putchar (char);
 extern int printf   (const char *, ...);
 extern int sprintf  (char *, const char *, ...);
 extern int vprintf  (const char *, char *);
 extern int vsprintf (char *, const char *, char *);
 extern char *gets (char *, int n);
 extern int scanf (const char *, ...);
 extern int sscanf (char *, const char *, ...);
 extern int puts (const char *);
 
 #pragma RESTORE
 
 
 
#line 19 "main.c" /0
 
 
 
 
  signed int xdata    drop_weight,				 
 residual_weight,			 
 zero_scale_value;			 
  unsigned long xdata 	filter2_out = 0,			 
 filter1_out,				 
 load_cell_span,				 
 tare_weight,				 
 scale_output_val,			 
 scale_counterweight_val;	 
  unsigned long xdata    DropCounter _at_ 0x180;		 
  unsigned int xdata 	sp_weight,					 
 sf_weight,					 
 sf_weight_adj_val,           
 weight_correct_val,			 
 shut_fb_w;					 
  unsigned char xdata 	t1_cnt,						 
 shut_cnt,					 
 filter_coefficient,			 
 filter_coefficient1,		 
 err_code = 0,				 
 sf_switch,					 
 ol_track_sw,				 
 track_bags,					 
 w_save_cnt = 0,				 
 cl_correct_sw,				 
 arrival_time,				 
 A_T_time = 0,				 
 counter_sw,					 
 disp_cache,					 
 CommAddr,					 
 DpSwitch,					 
 DispCnt,					 
 flashboard_cnt;				 
 bit				t1_flag,					 
 startup_flag = 0,			 
 DropFlag = 0,				 
 ZeroFlag = 0,				 
 AutoZeroFlag = 0,			 
 discharge_bag_loc_flag = 0,	 
 flashboard_pulse_flag,		 
 re_fill_flag,				 
 DpEnFlag = 0,				 
 discharge_pulse_flag = 0,	 
 shut_flag = 0,				 
 disp_flag = 1;				 
  unsigned int xdata	weight[10];				 
  signed long xdata	adc,adc_disp;					 
 
 
 
 extern unsigned char code	seg_sym[40];			 
 extern unsigned char code	seg_dot[40];
 extern unsigned char xdata	TxBuf[70],RxBuf[60];
 
 
 
 void mcu_init();							 
 void update_shut_fb_w(unsigned char bags);
 void ZeroPointDet(void);
 void ShutAndCorrect(void);
 
 



















 
 
 
 
 
 
 void main(void)
 {
 mcu_init();                                              
 
 
 zero_scale_value = 0; 
 zero_scale_value = NW_scale();
 
 if(zero_scale_value > 3500){
 disp_symbol(0XA3);
 zero_scale_value = 0;
 }
 else if(zero_scale_value < -3500){
 disp_symbol(0XA4);
 zero_scale_value = 0;
 }
 menu_func();                                         
 tare_zero_func();                                    
 
 
 
 FullOut = 1;
 SizeFlowOut = 1;
 
 while(1){
  signed long xdata shut_error;
 
 PbRestart();                                     
 PbTare();                                        
 PbNW_measure();                                  
 
 
 menu_func();                                         
 dm_sp_weight();                                      
 tare_zero_func();                                    
 adc = NW_scale();
 { 
 if(zero_loc == 0)  disp_seg(seg_sym[13],0x20);
 else    disp_seg(seg_sym[28],0x20);
  disp_seg(seg_sym[28],0X10);
 if(adc_disp - adc > 200)    disp_flag = 1;
 if(adc - adc_disp > 200)    disp_flag = 1;
 if(disp_flag){
 adc_disp = adc;
 run_disp(adc_disp);
 DispCnt = 0;
 disp_flag = 0;
 }
 }
 
 if(adc >= 5000){
 if(sf_switch == 0XAA){
 if(adc < 20000){
 SizeFlowOut = 1;
 }
 else if(adc>=sf_weight){
 SizeFlowOut = 0;
 }
 }
 if(adc > (shut_fb_w - 3000)) DpEnFlag = 0;
 
 shut_error = adc - shut_fb_w;
 if(shut_error > 500){
 ShutAndCorrect();
 }
 else if((shut_error > 200) && (shut_flag == 1)){
 ShutAndCorrect();
 }
 else if(shut_error >= 0){
 shut_flag = 1;
 shut_cnt++;
 }
 else{
 shut_cnt = 0;
 }
 if(shut_cnt == 3)   ShutAndCorrect();
 }
 else    ZeroPointDet();
 }
 
 }
 
 





 
 void ZeroPointDet(void)
 {
  signed int xdata czero_scale_value;
 if(startup_flag)    return;
 if((DropFlag) && (zero_loc == 0)){
 czero_scale_value = zero_scale_value;
 zero_scale_value = 0;
 adc = NW_scale_clr();
 if((adc > 3500) || (adc < -3500)){ 
 zero_scale_value = czero_scale_value;
 if(adc > 3500) disp_symbol(0XA3);
 else if(adc < -3500) disp_symbol(0XA4);
 }
 else{ 
  disp_seg(seg_sym[12],0x20);
 run_disp(adc);
 zero_scale_value = adc;
 }
 DropFlag = 0;
 while(zero_loc == 0);
 }
 }
 
 void ShutAndCorrect(void)
 {
  unsigned int DropVal = (sp_weight/5)<<1;                       
 disp_flag = 1;
 SizeFlowOut = 0;
 FullOut = 0;
 DpEnFlag = 1;
 shut_cnt = 0;
 shut_flag = 0;
  disp_seg(seg_sym[28],0x20);
  disp_seg(seg_sym[28],0x20);
 while(adc >= DropVal){
 adc = NW_scale();
 
 PbNW_measure();                                      
 
 if(zero_loc == 0){
  disp_seg(seg_dot[28],0x20);
 t1_100ms(10);
 disp_flag = 0;
 while(zero_loc == 0);
  disp_seg(seg_sym[28],0x20);
 weight[w_save_cnt] = (unsigned int)adc;                
 w_save_cnt++;
 if(w_save_cnt == track_bags) w_save_cnt = 0;
 }
 else disp_seg(seg_sym[28],0x20);
  disp_seg(seg_sym[28],0X10);
 if(disp_flag)   run_disp(adc);
 if(t1_flag){
 t1_stop();
 t1_flag = 0;
 disp_flag = 1;
 }
 }
 FullOut = 1;
 SizeFlowOut = 1;
 t1_stop();
 DropFlag = 1;
 if(counter_sw == 0XAA)    DropCounter++;
 
 startup_flag = 0;
 if(cl_correct_sw == 0XAA)     t4_50ms_cl_track(arrival_time);
 else if(ol_track_sw == 0XAA)  update_shut_fb_w(track_bags);
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 





 
 void Port_IO_Init(void)
 {
 SFRPAGE   = 0x0F;
 P0MDOUT   = 0x90;
 P1MDOUT   = 0x06;
 P3MDOUT   = 0xFE;
 P4MDOUT   = 0xE0;
 P6MDOUT   = 0xFF;
 P7MDOUT   = 0xFF;
 XBR0      = 0x05;
 XBR2      = 0x40;
 
 P1 = 0XFF;
 P2 = 0XFF;
 P3 = 0XFF;
 P4 = 0XFF;
 P5 = 0XFF;
 P6 = 0XFF;
 P7 = 0XFF;
 }





 
 void stop_wdt(void)
 {
 EA = 0;
 WDTCN = 0XDE;
 WDTCN = 0XAD;
 }





 
 void sysclk_init(void)
 {
  unsigned int i;
 SFRPAGE = 0x0F;
 OSCXCN = 0X67;
 for(i=0;i<3000;i++);
 while((OSCXCN & 0x80) == 0)	;
 CLKSEL = 0X01;
 OSCICN = 0x03;
 SFRPAGE = 0;
 return;
 }
 void save_all(void)
 {
  unsigned char Start_1stFlag = 0XAA;
 
 DpSwitch = 0X55;
 eeprom_write(&DpSwitch,37,1);
 
 
 CommAddr = 1;
 eeprom_write(&CommAddr,36,1);
 
 
 filter_coefficient = 80;
 eeprom_write(&filter_coefficient,6,1);
 
 
 sp_weight = 50000;
 eeprom_write((unsigned char *)&sp_weight,0,2);
 
 
 load_cell_span = 350000;
 eeprom_write((unsigned char *)&load_cell_span,21,4);
 
 
 scale_output_val = 34306;
 eeprom_write((unsigned char *)&scale_output_val,32,4);
 
 
 scale_counterweight_val = 40000;
 eeprom_write((unsigned char *)&scale_counterweight_val,25,4);
 
 
 track_bags = 5;
 eeprom_write(&track_bags,13,1);
 
 
 sf_switch = 0X55;
 eeprom_write(&sf_switch,9,1);
 
 
 sf_weight_adj_val = 5000;
 eeprom_write((unsigned char *)&sf_weight_adj_val,7,2);
 
 
 drop_weight = 0;
 eeprom_write((unsigned char *)&drop_weight,10,2);
 
 
 residual_weight = 0;
 eeprom_write((unsigned char *)&residual_weight,14,2);
 
 
 weight_correct_val = 0;
 eeprom_write((unsigned char *)&weight_correct_val,17,2);
 
 
 arrival_time = 0;
 eeprom_write(&arrival_time,19,1);
 
 
 ol_track_sw = 0X55;
 eeprom_write(&ol_track_sw,12,1);
 
 
 cl_correct_sw = 0X55;
 eeprom_write(&cl_correct_sw,16,1);
 
 
 counter_sw = 0X55;
 eeprom_write(&counter_sw,20,1);
 
 eeprom_write(&Start_1stFlag,0XFF,1);
 }
 void read_all(void)
 {
  unsigned char cnt;
 
  unsigned char err_temp = 0x2d;
 
 
 
 eeprom_read(&DpSwitch,37,1);
 
 eeprom_read(&CommAddr,36,1);
 while(CommAddr > 60 || CommAddr == 0){
 disp_symbol(0X8F);
 menu_func();
 }
 
 
 cnt = 0;
 while(DpSwitch == 0XAA){
 EA = 0;
 if(err_temp == 0x2d) err_temp = pb_init();
 EA = 1;
 if(err_temp == 0x2d) break;
 else disp_symbol(err_temp);
 cnt ++ ;
 if(cnt > 30)    DpSwitch = 0X55;
 menu_func();
 }
 
 DpEnFlag = 1;
 
 
 eeprom_read(&filter_coefficient,6,1);
 
 if(filter_coefficient > 90){
 filter_coefficient = 60;
 eeprom_write(&filter_coefficient,6,1);
 }
 filter_coefficient1 = (unsigned char)filter_coefficient * 1.1;
 
 
 eeprom_read((unsigned char *)&sp_weight,0,2);
 
 while((sp_weight < 22000) || (sp_weight > 65000)){
 disp_symbol(0XA0);
 menu_func();
 }
 
 
 eeprom_read((unsigned char *)&load_cell_span,21,4);
 
 while((load_cell_span != 100000) && (load_cell_span != 150000)
 && (load_cell_span != 200000) && (load_cell_span != 250000)
 && (load_cell_span != 300000) && (load_cell_span != 350000)){
 disp_symbol(0XA1);
 menu_func();
 }
 
 
 eeprom_read((unsigned char *)&scale_output_val,32,4);
 while((scale_output_val < 19000) || (scale_output_val > 62000)){
 disp_symbol(0X81);
 menu_func();
 }
 
 
 eeprom_read((unsigned char *)&scale_counterweight_val,25,4);
 while((scale_counterweight_val<20000)||(scale_counterweight_val>60000)){
 disp_symbol(0X82);
 menu_func();
 }
 
 
 eeprom_read(&track_bags,13,1);
 if ((track_bags == 0) || (track_bags > 10)){
 track_bags = 5;
 eeprom_write(&track_bags,13,1);
 }
 
 
 eeprom_read((unsigned char *)&tare_weight,2,4);



 
 
 
 eeprom_read(&sf_switch,9,1);
 
 
 eeprom_read((unsigned char *)&sf_weight_adj_val,7,2);
 while((sf_weight_adj_val < 100) || (sf_weight_adj_val > 10000)){
 disp_symbol(0xA2);
 menu_func();
 }
 
 
 eeprom_read((unsigned char *)&drop_weight,10,2);
 while((drop_weight < -2500) || (drop_weight > 2500)){
 disp_symbol(0X88);
 menu_func();
 }
 
 
 
 eeprom_read((unsigned char *)&residual_weight,14,2);
 while((residual_weight < -2500) || (residual_weight > 2500)){
 disp_symbol(0X89);
 menu_func();
 }
 
 
 eeprom_read((unsigned char *)&weight_correct_val,17,2);
 while(weight_correct_val > 1500){
 disp_symbol(0X8A);
 menu_func();
 
 }
 
 
 eeprom_read(&arrival_time,19,1);
 
 eeprom_read(&ol_track_sw,12,1);
 
 
 eeprom_read(&cl_correct_sw,16,1);
 
 if((ol_track_sw == 0XAA) && (cl_correct_sw == 0XAA)){
 ol_track_sw = 0X55;
 cl_correct_sw = 0X55;
 disp_symbol(0X8C);
 }
 
 eeprom_read(&counter_sw,20,1);
 
 shut_fb_w = sp_weight - drop_weight;
 sf_weight = shut_fb_w - sf_weight_adj_val;
 
 for(cnt = 0;cnt < 10;cnt++)	weight[cnt] = sp_weight + residual_weight;
 }





 
 void para_init(void)
 {
 read_all();
 }
 void ClearDropCounter(void)
 {
 SFRPAGE = 0;
 if(RSTSRC & 0X02)   DropCounter = 0;
 return;
 }





 
 void mcu_init(void)
 {
  unsigned char led_test,cnt;
 stop_wdt();
 sysclk_init();
 ClearDropCounter();
 Port_IO_Init();
 time01_init();
 iic_init();
 adc_init();
 uart0_init(115200);
 time3_init();
 time4_init();
 if(get_key(0XF0) == 0XF0){
 save_all();
 }
 else{
 para_init();
 }
 for(led_test = 0;led_test < 10;led_test ++){
 disp_seg(seg_sym[led_test],0x3f);
 zero_scale_value = 0;
 for(cnt = 0 ;cnt < 20 ;cnt++)   NW_scale();
 
 }
 startup_flag = 1;
 }





 
 void update_shut_fb_w(unsigned char bags)
 {
  unsigned char cnt;
  unsigned long xdata sum = 0;
 for(cnt = 0; cnt < bags; cnt++) sum += weight[cnt];
 sum /= bags;
 shut_fb_w = shut_fb_w + (sp_weight + residual_weight - sum)/2;
 sf_weight = shut_fb_w - sf_weight_adj_val;
 }
 
 
 
 
