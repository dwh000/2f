
#line 1 "terminal.c" /0







 
  
#line 1 "terminal.h" /0
 
 
  
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
 
#line 9 "terminal.c" /0
 
  
#line 1 "24c04.h" /0
 
 
 
  
#line 1 "public.h" /0
 
#line 2 "public.h" /1
  
 
  
  
  
 
 
 
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
 
  
  
 
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
  
  
  
 
 
  
  
  
  
  
  
 
  
  
  
  
  
  
  
 
  
  
  
 
  
  
 
 
  
  
  
  
  
  
  
  
 
 
#line 4 "24c04.h" /0
#line 4 "24c04.h" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






 
  unsigned char eeprom_read(unsigned char *ptr_data,unsigned char addr,unsigned char cnt);
 
 






 
  unsigned char eeprom_write(unsigned char *ptr_data,unsigned char addr,unsigned char cnt);
 
 
 void iic_init(void);
 
  unsigned char ee_write(unsigned char *ptr_data,unsigned char addr,unsigned char cnt) reentrant;
 
 
#line 10 "terminal.c" /0
 
  
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
 
#line 11 "terminal.c" /0
 
  
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
 
 
 
 
 
#line 12 "terminal.c" /0
 
 extern signed int xdata drop_weight,residual_weight,zero_scale_value;
 extern unsigned int xdata sp_weight,sf_weight,sf_weight_adj_val,weight_correct_val,shut_fb_w;
 extern unsigned char xdata  err_code,filter_coefficient,sf_switch,ol_track_sw,
 w_save_cnt,filter_coefficient1,DpSwitch;
 extern unsigned char xdata  track_bags,cl_correct_sw,arrival_time,counter_sw,
 CommAddr,weight[10];
 extern bit          t0_flag,t1_flag;
 extern unsigned long xdata load_cell_span,scale_output_val,scale_counterweight_val,
 tare_weight,DropCounter,bags;
 extern signed long xdata adc;
 bit RxDoneFlag;
 bit ResetFlag = 0;
  unsigned char xdata RxBuf[60],TxBuf[70];
 
  unsigned char data_in_len;                                           
  unsigned char dil;                                                   
  unsigned char data_out_len;                                          
  unsigned char dol;                                                   
  unsigned char user_prm_len;                                          
  unsigned char br_num = 5;
 
 
 sfr16 RCAP2    = 0xCA;                                       
 sfr16 TMR2     = 0xCC;                                       
 
 
 
 
 
 
 void uart0_init(unsigned long baudrate)
 {
 char SFRPAGE_SAVE;
 SFRPAGE_SAVE = SFRPAGE;              
 SFRPAGE = 0x00;
 TMR2CN = 0x00;                       
 TMR2CF = 0x08;                       
 RCAP2 = - ((long) 22118400L/baudrate/16);
 TMR2 = RCAP2;
 TR2 = 1;                             
 SFRPAGE = 0x00;
 SCON0 = 0xD0;                        
 SSTA0 = 0x15;                        
 
 
 
 
 
 ES0 = 0;
 TI0 = 1;
 SFRPAGE = SFRPAGE_SAVE;              
 }
 
 
  unsigned char UartPutchar(unsigned char ch)reentrant
 {
 SFRPAGE     = 0x00;
 while(TI0 == 0);                     
 TI0         = 0;
 ACC         = ch;
 TB80        = P;                            
 SBUF0       = ACC;
 SFRPAGE     = 0x0F;
 return ch;
 }
 
 
 
  unsigned char PbGetchar(unsigned char *ch)reentrant
 {
  unsigned char pErr_flag = 0;
 SFRPAGE = 0x00;
 while(!RI0){                                             
 if(S_RTS==0) return 0XA5;
 }
 if(RI0){
 ACC = SBUF0;
 if(P != RB80) pErr_flag=1;                           
 *ch = ACC;                                           
 RI0 = 0;
 }
 SFRPAGE = 0x0F;
 return pErr_flag;
 }
  unsigned char pb_init(void)
 {
 bit pbinit_flag = 0;
  unsigned long TimeOutCnt = 0;
  unsigned char i,x,cnt = 0;
 
 
 data_in_len =48+1+1;                                         
 user_prm_len=0;                                              
 data_out_len=64+1+1;                                         
 TxBuf[0]    =CommAddr;                                       
 TxBuf[1]    =0x06;                                           
 TxBuf[2]    =0xfa;                                           
 TxBuf[3]    =7;                                              
 TxBuf[4]    =0x1f;                                           
 TxBuf[5]    =0x2f;                 
 TxBuf[6]    =0x1f;
 TxBuf[7]    =0x2f;
 TxBuf[8]    =0x1f;
 TxBuf[9]    =0x2f;
 TxBuf[10]   =0x1f;
 TxBuf[24]   =data_in_len;                                   
 TxBuf[25]   =data_out_len;                                  
 TxBuf[26]   =user_prm_len;                                  
 
 
 TxBuf[48]   =0;
 for(i=0;i<48;i++)   TxBuf[48]=TxBuf[48]+TxBuf[i];
 
 while(1){
 nRST        = 0;
 TimeOutCnt  = 50000;
 while(--TimeOutCnt);
 nRST        = 1;
 TimeOutCnt  = 0;
 while(S_RTS){                                        
 if(++TimeOutCnt > 1105920) return 0XA5;
 }
 for(i=0;i<49;i++) UartPutchar(TxBuf[i]);             
 TimeOutCnt = 0;
 while(!S_RTS){                                       
 if(++TimeOutCnt > 1105920) return 0XA5;
 }
 
 for(i=0;i<49;i++){                                   
 x = PbGetchar(&RxBuf[i]);
 if(x) break;                                     
 }
 
 if(x == 0){
 for(i=0;i<48;i++) x+=RxBuf[i];                   
 if(x==RxBuf[48]){                                
 if(RxBuf[0]==br_num){                        
 if(RxBuf[1]==0){                         
 for(i=2;i<48;i++){                   
 if(RxBuf[i]!=0xaa) break;
 }
 if(i==48) break;                     
 else cnt++;                          
 if(cnt > 20) return 0X8B;             
 }
 }
 }
 }
 }
 for(i=0;i<60;i++)   RxBuf[i]=0;
 return 0x2d;
 }
 
 void PbRestart(void)
 {
 if((DpSwitch == 0XAA) && REQ_IT){
 EA=0;
 pb_init();
 EA=1;
 }
 }
 
 void PbTare(void)
 {
 if(DpSwitch == 0XAA){
 if(RxBuf[31] & 0x01){                                
 if((TxBuf[48] & 0x01) == 0){
 zero_scale_value = 0;
 tare_weight = GW_measure();
 eeprom_write((unsigned char *)&tare_weight,2,4);
 TxBuf[48] |= 0x01;
 }
 }
 else TxBuf[48] &= ~0x01;
 }
 }
 
 void PbNW_measure(void)
 {
  signed long adcval;
  unsigned char *p_temp;
 if(DpSwitch == 0XAA){
 adcval = NW_measure();
 p_temp = (unsigned char *)&adcval;
 TxBuf[50] = *p_temp++;
 TxBuf[51] = *p_temp++;
 TxBuf[52] = *p_temp++;
 TxBuf[53] = *p_temp++;
 }
 }
  unsigned char DpDataExchange(void)
 {
  unsigned char i=0,error;
  unsigned int upara16;
  signed int spara16;
  unsigned long upara32,TimeOutCnt = 0;
  unsigned char *ppp;
 dil=data_in_len-1;
 dol=data_out_len-1;
 {
 
 TxBuf[0]    = 0;                                     
 ppp         = (unsigned char *)&sp_weight;                   
 TxBuf[1]    = *ppp++;
 TxBuf[2]    = *ppp++;
 TxBuf[3]    = filter_coefficient;                    
 ppp         = (unsigned char *)&sf_weight_adj_val;           
 TxBuf[4]    = *ppp++;
 TxBuf[5]    = *ppp++;
 TxBuf[6]    = sf_switch;                             
 ppp         = (unsigned char *)&drop_weight;                 
 TxBuf[7]    = *ppp++;
 TxBuf[8]    = *ppp++;
 TxBuf[9]    = ol_track_sw;                           
 TxBuf[10]   = track_bags;                            
 ppp         = (unsigned char *)&residual_weight;             
 TxBuf[11]   = *ppp++;
 TxBuf[12]   = *ppp++;
 TxBuf[13]   = cl_correct_sw;                         
 ppp         = (unsigned char *)&weight_correct_val;          
 TxBuf[14]   = *ppp++;
 TxBuf[15]   = *ppp++;
 TxBuf[16]   = arrival_time;                          
 TxBuf[17]   = counter_sw;                            
 ppp         = (unsigned char *)&load_cell_span;              
 TxBuf[18]   = *ppp++;
 TxBuf[19]   = *ppp++;
 TxBuf[20]   = *ppp++;
 TxBuf[21]   = *ppp++;
 ppp         = (unsigned char *)&scale_output_val;            
 TxBuf[22]   = *ppp++;
 TxBuf[23]   = *ppp++;
 TxBuf[24]   = *ppp++;
 TxBuf[25]   = *ppp++;
 ppp         = (unsigned char *)&scale_counterweight_val;     
 TxBuf[26]   = *ppp++;
 TxBuf[27]   = *ppp++;
 TxBuf[28]   = *ppp++;
 TxBuf[29]   = *ppp++;
 ppp         = (unsigned char *)&tare_weight;                 
 TxBuf[30]   = *ppp++;
 TxBuf[31]   = *ppp++;
 TxBuf[32]   = *ppp++;
 TxBuf[33]   = *ppp++;
 
 
 TxBuf[36]   = 0;                                     
 TxBuf[37]   = 0;                                     
 if(!SizeFlowOut)    TxBuf[38] |= 0X80;
 else TxBuf[38] &= ~0X80;
 if(!FullOut)    TxBuf[38] |= 0X40;
 else TxBuf[38] &= ~0X40;
 if(!discharge_bag_sw_out) TxBuf[38] |= 0x20;
 else TxBuf[38] &= ~0x20;
 if(!clamping_bag_out) TxBuf[38] |= 0X10;
 else TxBuf[38] &= ~0X10;
 if(!fill_mot_sw_out)    TxBuf[38] |= 0x08;
 else TxBuf[38] &= ~0x08;
 
 ppp         = (unsigned char *)&DropCounter;                 
 TxBuf[39]   = *ppp++;
 TxBuf[40]   = *ppp++;
 TxBuf[41]   = *ppp++;
 TxBuf[42]   = *ppp++;
 
 ppp         = (unsigned char *)&weight[w_save_cnt == 0?9:(w_save_cnt-1)];
 TxBuf[43]   = *ppp++;
 TxBuf[44]   = *ppp++;
 
 if(adc < 0) upara16 = 0;
 else        upara16 = (unsigned int)adc;
 ppp         = (unsigned char *)&upara16;
 TxBuf[45]   = *ppp++;
 TxBuf[46]   = *ppp++;
 
 
 
 
 
 }
 TxBuf[dil]  = 0;
 for(i=0;i<dol;i++) TxBuf[dol]=TxBuf[dol]+TxBuf[i];       
 
 TimeOutCnt  = 0;
 while(S_RTS){                                            
 if(++TimeOutCnt > 1105920) return 0XA5;
 }
 
 for(i=0;i<data_out_len;i++) UartPutchar(TxBuf[i]);
 
 TimeOutCnt  = 0;
 while(!S_RTS){                                           
 if(++TimeOutCnt > 1105920) return 0XA5;
 }
 
 for(i=0;i<data_in_len;i++){                             
 error = PbGetchar(&RxBuf[i]);
 if(error) break;
 }
 if(error == 0){                                          
 error = 0;
 for(i=0;i<dil;i++)      error = error + RxBuf[i];    
 if(error != RxBuf[dil]) error = 0XFC;          
 else error = 0;
 }
 if(error) return error;
 
 { 
 if(RxBuf[32]&0x04){                                  
 cyl_sw_out = 1;
 fine_flow_out = 1;
 }
 if(RxBuf[32]&0X02){
 fill_mot_sw_out = 1;                          
 }
 
 if((RxBuf[30] & 0x01) == 0x01){                      
 if((TxBuf[47] & 0x01) == 0){
 ppp = (unsigned char *)&upara16;
 *ppp++ = RxBuf[1];
 *ppp++ = RxBuf[2];
 if((upara16>=22000) && (upara16<=65000)){
 shut_fb_w = shut_fb_w + upara16 - sp_weight; 
 sf_weight = shut_fb_w - sf_weight_adj_val;
 sp_weight = upara16;
 ee_write((unsigned char *)&sp_weight,0,2);
 TxBuf[34] &= ~0X40;                      
 }
 else TxBuf[34] |= 0X40;                      
 
 if(RxBuf[3] <= 90){
 filter_coefficient = RxBuf[3];
 ee_write(&filter_coefficient,6,1);
 filter_coefficient1 = (unsigned char)filter_coefficient * 1.1;
 TxBuf[34] &= ~0X80;                      
 }
 else TxBuf[34] |= 0X80;                      
 
 TxBuf[47] |= 0x01;
 }
 }
 else TxBuf[47] &= ~0x01;                             
 
 if((RxBuf[30] & 0X02) == 0X02){                      
 if((TxBuf[47] & 0X02) == 0){
 ppp = (unsigned char *)&upara16;
 *ppp++ = RxBuf[4];
 *ppp++ = RxBuf[5];
 if((upara16>=100) && (upara16<=10000)){
 sf_weight_adj_val = upara16;
 sf_weight = shut_fb_w - sf_weight_adj_val;
 ee_write((unsigned char *)&sf_weight_adj_val,7,2);
 TxBuf[34] &= ~0x20;                      
 }
 else TxBuf[34] |= 0x20;                      
 if((RxBuf[6] == 0XAA) || (RxBuf[6] == 0X55)){
 sf_switch = RxBuf[6];
 ee_write(&sf_switch,9,1);
 }
 TxBuf[47] |= 0X02;
 }
 }
 else TxBuf[47] &= ~0X02;                             
 
 if((RxBuf[30] & 0x04) == 0x04){                      
 if((TxBuf[47] & 0x04) == 0){
 ppp = (unsigned char *)&upara32;
 *ppp++ = RxBuf[18];
 *ppp++ = RxBuf[19];
 *ppp++ = RxBuf[20];
 *ppp++ = RxBuf[21];
 if((upara32 == 100000) || (upara32 == 150000) ||
 (upara32 == 200000) || (upara32 == 250000) ||
 (upara32 == 300000) || (upara32 == 350000)){
 load_cell_span = upara32;
 ee_write((unsigned char *)&load_cell_span,21,4);
 TxBuf[35] &= ~0X80;                      
 }
 else TxBuf[35] |= 0X80;                      
 
 ppp = (unsigned char *)&upara32;
 *ppp++ = RxBuf[22];
 *ppp++ = RxBuf[23];
 *ppp++ = RxBuf[24];
 *ppp++ = RxBuf[25];
 if((upara32 >= 19000) && (upara32 <= 62000)){
 scale_output_val = upara32;
 ee_write((unsigned char *)&scale_output_val,32,4);
 TxBuf[35] &= ~0X10;                      
 }
 else TxBuf[35] |= 0X10;                      
 
 ppp = (unsigned char *)&upara32;
 *ppp++ = RxBuf[26];
 *ppp++ = RxBuf[27];
 *ppp++ = RxBuf[28];
 *ppp++ = RxBuf[29];
 if((upara32 >= 20000) && (upara32 <= 60000)){
 scale_counterweight_val = upara32;
 ee_write((unsigned char *)&scale_counterweight_val,25,4);
 TxBuf[35] &= ~0x08;                      
 }
 else TxBuf[35] |= 0x08;                      
 TxBuf[47] |= 0x04;
 }
 }
 else TxBuf[47] &= ~0x04;                             
 
 if((RxBuf[30] & 0x08) == 0x08){                      
 if((TxBuf[47] & 0x08) == 0){
 ppp = (unsigned char *)&spara16;
 *ppp++ = RxBuf[7];
 *ppp++ = RxBuf[8];
 if((spara16 >= -2500) && (spara16 <= 2500)){
 shut_fb_w = shut_fb_w + spara16 - drop_weight; 
 sf_weight = shut_fb_w - sf_weight_adj_val;
 drop_weight = spara16;
 ee_write((unsigned char *)&drop_weight,10,2);
 TxBuf[34] &= ~0X10;                      
 }
 else TxBuf[34] |= 0X10;
 ppp = (unsigned char *)&spara16;
 *ppp++ = RxBuf[11];
 *ppp++ = RxBuf[12];
 if((spara16 >= -2500) && (spara16 <= 2500)){
 residual_weight = spara16;
 ee_write((unsigned char *)&residual_weight,14,2);
 TxBuf[34] &= ~0x08;                      
 }
 else TxBuf[34] |= 0x08;
 TxBuf[47] |= 0x08;
 }
 }
 else TxBuf[47] &= ~0x08;                             
 
 if((RxBuf[30] & 0X10) == 0X10){                      
 if((TxBuf[47] & 0X10) == 0){
 if((RxBuf[9] == 0XAA) || (RxBuf[9] == 0X55)){
 ol_track_sw = RxBuf[9];
 if((ol_track_sw == 0XAA) && (cl_correct_sw == 0XAA)){
 ol_track_sw = 0X55;
 cl_correct_sw = 0X55;
 TxBuf[34] |= 0x01;
 }
 else TxBuf[34] &= ~0x01;                 
 ee_write(&ol_track_sw,12,1);
 }
 if((RxBuf[10] < 11) && (RxBuf[10] > 0)){
 track_bags = RxBuf[10];
 ee_write(&track_bags,13,1);
 TxBuf[35] &= ~0X02;                      
 }
 else TxBuf[35] |= 0X02;                      
 TxBuf[47] |= 0X10;
 }
 }
 else TxBuf[47] &= ~0X10;                             
 
 if((RxBuf[30] & 0x20) == 0x20){                      
 if((TxBuf[47] & 0x20) == 0){
 if((RxBuf[17] == 0XAA) || (RxBuf[17] == 0X55)){
 counter_sw = RxBuf[17];
 TxBuf[17] = counter_sw;
 ee_write(&counter_sw,20,1);
 }
 TxBuf[47] |= 0x20;
 }
 }
 else TxBuf[47] &= ~0x20;                             
 
 if((RxBuf[30] & 0X40) == 0X40){                      
 if((TxBuf[47] & 0X40) == 0){
 ppp = (unsigned char *)&upara16;
 *ppp++ = RxBuf[14];
 *ppp++ = RxBuf[15];
 if((upara16 >= 0) && (upara16 <= 1500)){
 weight_correct_val = upara16;
 ee_write((unsigned char *)&weight_correct_val,17,2);
 TxBuf[34] &= ~0x04;                      
 }
 else TxBuf[34] |= 0x04;                      
 
 if((RxBuf[13] == 0XAA) || (RxBuf[13] == 0X55)){
 cl_correct_sw = RxBuf[13];
 if((ol_track_sw == 0XAA) && (cl_correct_sw == 0XAA)){
 ol_track_sw = 0X55;
 cl_correct_sw = 0X55;
 TxBuf[34] |= 0x01;                   
 }
 else TxBuf[34] &= ~0x01;
 ee_write(&cl_correct_sw,16,1);
 }
 if(RxBuf[16] != 0){
 arrival_time = RxBuf[16];
 ee_write(&arrival_time,19,1);
 TxBuf[34] &= ~0X02;                      
 }
 else TxBuf[34] |= 0X02;
 TxBuf[47] |= 0X40;
 }
 }
 else TxBuf[47] &= ~0X40;                             
 
 if((RxBuf[30] & 0X80) == 0X80){                      
 if((TxBuf[47] & 0X80) == 0){
 DropCounter = 0;
 TxBuf[47] |= 0X80;
 }
 }
 else TxBuf[47] &= ~0X80;                             
 }
 return 0x2d;                                             
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
