/*
 *-----------------------------------------------------------------------------
 * CS1251.h
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *-----------------------------------------------------------------------------
 */
 
#ifndef  __CS1251_H__
#define  __CS1251_H__

// CS1251 Chip Register Address definition
#define  CS1251_REG_SYS    (unsigned char)0x00
#define  CS1251_REG_ADC0   (unsigned char)0x01
#define  CS1251_REG_ADC1   (unsigned char)0x02
#define  CS1251_REG_ADC2   (unsigned char)0x03
#define  CS1251_REG_ADC3   (unsigned char)0x04
#define  CS1251_REG_ADC4   (unsigned char)0x05
#define  CS1251_REG_ADC5   (unsigned char)0x06
#define  CS1251_REG_BIM0   (unsigned char)0x07
#define  CS1251_REG_BIM1   (unsigned char)0x08
#define  CS1251_REG_ADO    (unsigned char)0x09
#define  CS1251_REG_ADS    (unsigned char)0x0A

#define  ADDR_AFE_CONFIG	 (unsigned char)0x10
#define  ADDR_AFE_VREFT	   (unsigned char)0x11
#define  ADDR_AFE_LDOT	   (unsigned char)0x12
#define  ADDR_AFE_OSCT	   (unsigned char)0x13
#define  ADDR_AFE_TST1	   (unsigned char)0x14
#define  ADDR_AFE_TST2	   (unsigned char)0x15
#define  ADDR_AFE_TMUX	   (unsigned char)0x16
#define  ADDR_AFE_OTPCON	 (unsigned char)0x59
#define  ADDR_AFE_TEST	   (unsigned char)0x5A

//=======================================================
//通道与频率定义
#define  Short_FWR_5KHz				(unsigned char)0x30 //00110000B
#define  Short_FWR_50KHz   		(unsigned char)0x33 //00110011B
#define  Short_FWR_250KHz			(unsigned char)0x35 //00110101B

#define  Short_MIX_5KHz  			(unsigned char)0x70 //01110000B
#define  Short_MIX_50KHz 			(unsigned char)0x73 //01110011B
#define  Short_MIX_250KHz			(unsigned char)0x75 //01110101B

#define  Ref0_FWR_5KHz				(unsigned char)0x10 //00010000B
#define  Ref0_FWR_50KHz				(unsigned char)0x13 //00010011B
#define  Ref0_FWR_250KHz			(unsigned char)0x15 //00010101B

#define  Ref0_MIX_5KHz				(unsigned char)0x50 //01010000B
#define  Ref0_MIX_50KHz				(unsigned char)0x53 //01010011B
#define  Ref0_MIX_250KHz			(unsigned char)0x55 //01010101B

#define  Ref1_FWR_5KHz				(unsigned char)0x20 //00100000B
#define  Ref1_FWR_50KHz				(unsigned char)0x23 //00100011B
#define  Ref1_FWR_250KHz			(unsigned char)0x25 //00100101B

#define  Ref1_MIX_5KHz				(unsigned char)0x60 //01100000B
#define  Ref1_MIX_50KHz				(unsigned char)0x63 //01100011B
#define  Ref1_MIX_250KHz			(unsigned char)0x65 //01100101B

#define  Body_FWR_5KHz				(unsigned char)0x00 //00000000B
#define  Body_FWR_50KHz				(unsigned char)0x03 //00000011B
#define  Body_FWR_250KHz		  (unsigned char)0x05 //00000101B

#define  Body_MIX_5KHz				(unsigned char)0x40 //01000000B
#define  Body_MIX_50KHz				(unsigned char)0x43 //01000011B
#define  Body_MIX_250KHz		  (unsigned char)0x45 //01000101B


// ADC 通道选择
#define  CS1251_CFG_Short  (unsigned char)1
#define  CS1251_CFG_REF0   (unsigned char)2
#define  CS1251_CFG_REF1   (unsigned char)3
#define  CS1251_CFG_BIM    (unsigned char)4

// MCU driver pin definition
#define  CS1251_PIN_CS     GPIO_PA0
#define  CS1251_PIN_SCL    GPIO_PA1
#define  CS1251_PIN_SDA    GPIO_PA2

// CS1251 flow define
#define  CS1251_Flow_Start      (unsigned char)1
#define  CS1251_Flow_CfgShort   (unsigned char)2    //
#define  CS1251_Flow_CfgREF0    (unsigned char)3
#define  CS1251_Flow_CfgREF1    (unsigned char)4
#define  CS1251_Flow_CfgBIM14_1 (unsigned char)5
#define  CS1251_Flow_CfgBIM14   (unsigned char)6
#define  CS1251_Flow_CfgBIM41   (unsigned char)7
#define  CS1251_Flow_GetShort   (unsigned char)8    //
#define  CS1251_Flow_GetREF0    (unsigned char)9
#define  CS1251_Flow_GetREF1    (unsigned char)10
#define  CS1251_Flow_GetBIM14_1 (unsigned char)11
#define  CS1251_Flow_GetBIM14   (unsigned char)12
#define  CS1251_Flow_GetBIM41   (unsigned char)13
#define  CS1251_Flow_Stop       (unsigned char)14

// CS1251 channel define 
// CS1251 flow define
#define  CS1251_Cfg_CfgShort    (unsigned char)2    //
#define  CS1251_Cfg_CfgREF0     (unsigned char)3
#define  CS1251_Cfg_CfgREF1     (unsigned char)4
#define  CS1251_Cfg_CfgBIM14    (unsigned char)6
#define  CS1251_Cfg_CfgBIM41    (unsigned char)7

//CS1521 Variable Type
typedef struct{
	unsigned short InternalShort_ADC;
	unsigned short RefRes0_ADC;
	unsigned short RefRes1_ADC;
	unsigned short BodyRes14_ADC;
	unsigned short BodyRes41_ADC;
	unsigned short BodyRes_Value;
	unsigned short ADO_Value;
	unsigned short RES14_Value;
	unsigned short RES41_Value;
	unsigned short RES_KValue;
 	unsigned char  ProgFlow;
	unsigned char  Flag_ProgEN   : 1 ;
	unsigned char  Flag_AdcStable: 1 ;
}CS1251_TypeDef;


extern CS1251_TypeDef  CS1251_Struct;


// Driver function declaration
void CS1251_RESET(void);
void CS1251_Init(void);
void CS1251_PowerDown(void);
void CS1251_RUN(void);
void CS1251_test(void);
#endif
