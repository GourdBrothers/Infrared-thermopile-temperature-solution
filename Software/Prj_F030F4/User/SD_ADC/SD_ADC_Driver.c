/*
 *-----------------------------------------------------------------------------
 * CS1251.c
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
#include "CS1251.h"
#include "csa37fx60_gpio.h"


/*-------------------------------------------------------
 * private functions
 */
CS1251_TypeDef  CS1251_Struct;

/*-------------------------------------------------------
 * private functions
 */

static void CS1251_Delay(unsigned short delayTime){
	unsigned short Index;
	Index = delayTime;
	while(Index--);
}

/*-------------------------------------------------------
 * 当SCLK保持LOW超过687us通信口复位，但芯片不复位
 */
static void CS1251_PIN_Init(void)
{
	GPIO_SetMode(CS1251_PIN_CS , GPIO_Mode_OUTPUT);
	GPIO_SetMode(CS1251_PIN_SCL, GPIO_Mode_OUTPUT);
	GPIO_SetMode(CS1251_PIN_SDA, GPIO_Mode_INPUT);
	GPIO_WriteBits(CS1251_PIN_CS  , 1);
	GPIO_WriteBits(CS1251_PIN_SCL , 1);
	// reset spi bus
	CS1251_Delay(100);
	GPIO_WriteBits(CS1251_PIN_CS , 0);
	CS1251_Delay(100);
	GPIO_WriteBits(CS1251_PIN_SCL , 0);
	CS1251_Delay(2300);
	GPIO_WriteBits(CS1251_PIN_CS  , 1);
	GPIO_WriteBits(CS1251_PIN_SCL , 1);
	CS1251_Delay(100);
}

static void CS1251_PIN_DeInit(void)
{
	GPIO_EnPullUp(CS1251_PIN_CS);
	GPIO_EnPullUp(CS1251_PIN_SCL);
	GPIO_EnPullUp(CS1251_PIN_SDA);
	GPIO_SetMode(CS1251_PIN_CS , GPIO_Mode_INPUT);
	GPIO_SetMode(CS1251_PIN_SCL, GPIO_Mode_INPUT);
	GPIO_SetMode(CS1251_PIN_SDA, GPIO_Mode_INPUT);
}

static void CS1251_WR_Byte(unsigned char byteData)
{
	  unsigned char Index;
    for(Index=0;Index<8;Index++){
			
			 if(byteData&0x80){
					GPIO_WriteBits(CS1251_PIN_SDA , 1);
			 }else{
					GPIO_WriteBits(CS1251_PIN_SDA , 0);
			 }
       CS1251_Delay(10);
       GPIO_WriteBits(CS1251_PIN_SCL , 1);
       CS1251_Delay(10);
       GPIO_WriteBits(CS1251_PIN_SCL , 0);
			 byteData<<=1;
    }
		CS1251_Delay(10);
}

static unsigned char CS1251_RD_Byte(void)
{
    unsigned char Index,RdByte;
    for(Index=0 ; Index<8 ; Index++){
      RdByte <<= 1;
      GPIO_WriteBits(CS1251_PIN_SCL , 1);
      CS1251_Delay(10);
      GPIO_WriteBits(CS1251_PIN_SCL , 0);
			CS1251_Delay(10);
      if(GPIO_ReadInputDataBit(CS1251_PIN_SDA)){
         RdByte |=0x01 ;
			}
    }
	  return RdByte;
}

static void CS1251_WR_REG(unsigned char byteAddr,unsigned char byteData)
{
	CS1251_PIN_Init();
	CS1251_Delay(10);
	GPIO_WriteBits(CS1251_PIN_SCL , 0);
	CS1251_Delay(10);
	GPIO_WriteBits(CS1251_PIN_CS , 0);
  GPIO_SetMode(CS1251_PIN_SDA, GPIO_Mode_OUTPUT);
	CS1251_Delay(10);
	CS1251_WR_Byte(byteAddr|0x80);
	CS1251_WR_Byte(byteData);
	CS1251_PIN_DeInit();
}

static unsigned char CS1251_RD_REG(unsigned char byteAddr)
{
	unsigned char RD_data;
	CS1251_PIN_Init();
//---
	GPIO_WriteBits(CS1251_PIN_SCL , 0);
	CS1251_Delay(10);
	GPIO_WriteBits(CS1251_PIN_CS , 0);
	GPIO_SetMode(CS1251_PIN_SDA, GPIO_Mode_OUTPUT);
	CS1251_Delay(10);
//---
	CS1251_WR_Byte(byteAddr);
//---
	GPIO_SetMode(CS1251_PIN_SDA,  GPIO_Mode_INPUT);
	RD_data = CS1251_RD_Byte();
	CS1251_PIN_DeInit();
	return RD_data ;
}

// 1 ,无数据
// 0 ,有数据
static unsigned char CS1251_ChkAdcRDY(void)
{
    unsigned char Temp;
		//Temp = CS1251_RD_REG(CS1251_REG_ADS);
	 while(GPIO_ReadInputDataBit(CS1251_PIN_SDA)==0)
   {}
		 
    Temp = 0x00;

    return Temp;
}

static void CS1251_RD_ADC(void)
{
	unsigned char RD_data;
	CS1251_PIN_Init();
//---
	GPIO_WriteBits(CS1251_PIN_SCL , 0);
	CS1251_Delay(10);
	GPIO_WriteBits(CS1251_PIN_CS , 0);
	GPIO_SetMode(CS1251_PIN_SDA, GPIO_Mode_OUTPUT);
	CS1251_Delay(10);
//---
	CS1251_WR_Byte(CS1251_REG_ADO);
//---
	GPIO_SetMode(CS1251_PIN_SDA,  GPIO_Mode_INPUT);
//---
	CS1251_Struct.ADO_Value = 0;
	RD_data = CS1251_RD_Byte();
	CS1251_Struct.ADO_Value = (RD_data^0x80)<<8;
	RD_data = CS1251_RD_Byte();
	CS1251_Struct.ADO_Value|= RD_data;
	RD_data = CS1251_RD_Byte();
//--
	CS1251_PIN_DeInit();
}



static void CS1251_GetAdc(unsigned char ChannelValue)
{
	unsigned int   AdcSum=0;
	unsigned char  AdcCnt=0;
	unsigned char  StableCnt=0;
	unsigned short AdcOutTemp=0,AdcDelter;
	/* Change channel */
  switch(ChannelValue){
		/*short adc*/
		case CS1251_Cfg_CfgShort:
	       CS1251_WR_REG(CS1251_REG_BIM1,Short_FWR_50KHz);
			break;
    /*REF0 adc */
		case CS1251_Cfg_CfgREF0 :
	       CS1251_WR_REG(CS1251_REG_BIM1,Ref0_FWR_50KHz);
			break;
		/*REF1 adc */
		case CS1251_Cfg_CfgREF1 :
			   CS1251_WR_REG(CS1251_REG_BIM1,Ref1_FWR_50KHz);
			break;
		/*body 14 adc */
		case CS1251_Cfg_CfgBIM14:
			   CS1251_WR_REG(CS1251_REG_BIM0,0x14);
         CS1251_WR_REG(CS1251_REG_BIM1,Body_FWR_50KHz);
			break;
		/*body 41 adc */
		case CS1251_Cfg_CfgBIM41:
				 CS1251_WR_REG(CS1251_REG_BIM0,0x41);
         CS1251_WR_REG(CS1251_REG_BIM1,Body_FWR_50KHz);
			break;
	}
	
	/* no use 3 out data */
	  for(AdcCnt=0;AdcCnt>3;AdcCnt++){
      while(CS1251_ChkAdcRDY());
			CS1251_RD_ADC();
		}

	/* rd and filter  */
		StableCnt =0;
		do{
       while(CS1251_ChkAdcRDY());
			 CS1251_RD_ADC();
			 if(AdcOutTemp>=CS1251_Struct.ADO_Value){
				 AdcDelter = AdcOutTemp-CS1251_Struct.ADO_Value;
			 }else{
				 AdcDelter = CS1251_Struct.ADO_Value-AdcOutTemp;
			 }
			 if(AdcDelter<10){
            AdcCnt = 0;
					  StableCnt++;
					  AdcSum+=CS1251_Struct.ADO_Value;
					 }else{
						AdcCnt++;
            StableCnt = 0;
						AdcSum = 0;
				}
				AdcOutTemp=CS1251_Struct.ADO_Value;
		}while(StableCnt<4);
	   CS1251_Struct.ADO_Value = AdcSum>>2;

	/* copy data */
  switch(ChannelValue){
		case CS1251_Cfg_CfgShort:
			CS1251_Struct.InternalShort_ADC = CS1251_Struct.ADO_Value;
			break;
		case CS1251_Cfg_CfgREF0 :
			CS1251_Struct.RefRes0_ADC = CS1251_Struct.ADO_Value;
			break;
		case CS1251_Cfg_CfgREF1 :
			CS1251_Struct.RefRes1_ADC = CS1251_Struct.ADO_Value;
			break;
		case CS1251_Cfg_CfgBIM14:
			CS1251_Struct.BodyRes14_ADC = CS1251_Struct.ADO_Value;
			break;
		case CS1251_Cfg_CfgBIM41:
			CS1251_Struct.BodyRes41_ADC = CS1251_Struct.ADO_Value;
			break;
	}
}

/*-------------------------------------------------------
 * public functions
 */

void CS1251_RESET(void) 
{
	  unsigned char Temp;
    do{
			CS1251_WR_REG(0xEA,0x96);
			CS1251_Delay(100);
			Temp=CS1251_RD_REG(CS1251_REG_ADS);
    }while((Temp&0x40)!=0x40);

    CS1251_WR_REG(ADDR_AFE_TEST,0x5A);
		CS1251_WR_REG(ADDR_AFE_CONFIG,0xBF);
}

void CS1251_Init(void)
{
    CS1251_WR_REG(CS1251_REG_SYS ,0xCA); // BIM测量模式，普通模式，VREF使能，ADC关闭.LDO使能,BIM关闭
    CS1251_WR_REG(CS1251_REG_ADC0,0xC8); // 
	  CS1251_WR_REG(CS1251_REG_ADC1,0x40); // ADc out 40HZ ,Gain=1
	  //CS1251_WR_REG(CS1251_REG_ADC1,0x20); // ADc out 20HZ ,Gain=1
	  CS1251_WR_REG(CS1251_REG_ADC2,0x00);
	  CS1251_WR_REG(CS1251_REG_ADC3,0x00);
	  CS1251_WR_REG(CS1251_REG_ADC4,0x42); // 2.8V LDO
	  CS1251_WR_REG(CS1251_REG_ADC5,0x00);
	  CS1251_WR_REG(CS1251_REG_BIM0,0x14);
	  CS1251_WR_REG(CS1251_REG_BIM1,Body_FWR_50KHz);
}


/*--------------------------------------------------------------
 *---- 当SCL从LOW到HIGH并保持超过172US,CS1251进入PowerDown
 *---- 当SCL拉低后，CS1251开始工作
 */
void CS1251_PowerDown(void)
{
	CS1251_WR_REG(CS1251_REG_SYS  ,0xC0);
//--
  GPIO_DisPullUp(CS1251_PIN_CS);
	GPIO_DisPullUp(CS1251_PIN_SCL);
	GPIO_EnPullUp(CS1251_PIN_SDA);
  GPIO_SetMode(CS1251_PIN_CS , GPIO_Mode_OUTPUT);
	GPIO_SetMode(CS1251_PIN_SCL, GPIO_Mode_OUTPUT);
	GPIO_SetMode(CS1251_PIN_SDA, GPIO_Mode_INPUT);
	GPIO_WriteBits(CS1251_PIN_CS  , 1);
	GPIO_WriteBits(CS1251_PIN_SCL , 1);
  CS1251_Delay(5000);
//==
  GPIO_WriteBits(CS1251_PIN_CS , 0);             // 1258_CS=0
  CS1251_Delay(50);
  GPIO_WriteBits(CS1251_PIN_SCL, 0);             // 1258_SCL=0
	CS1251_Delay(1000);
	GPIO_WriteBits(CS1251_PIN_SCL, 1);             // 1258_SCL=1
	CS1251_Delay(1000);                            // 这个延时很重要
	CS1251_PIN_DeInit();
	
}

void CS1251_test(void)
{
	unsigned short  ResValueTemp;
	CS1251_Init();
	CS1251_WR_REG(CS1251_REG_SYS ,0xCF);
	/* hot chip*/
	CS1251_GetAdc(CS1251_Cfg_CfgBIM14);
  /* do */
	CS1251_GetAdc(CS1251_Cfg_CfgShort);
	CS1251_GetAdc(CS1251_Cfg_CfgREF0);
	CS1251_GetAdc(CS1251_Cfg_CfgREF1);
	CS1251_GetAdc(CS1251_Cfg_CfgBIM14);
	CS1251_GetAdc(CS1251_Cfg_CfgBIM41);
	// 判断人体测量ADC是否正常
	CS1251_Struct.BodyRes_Value=0;
	if(CS1251_Struct.BodyRes14_ADC <= CS1251_Struct.InternalShort_ADC){
		return ;
	}
	if(CS1251_Struct.BodyRes41_ADC <= CS1251_Struct.InternalShort_ADC){
		return ;
	}
	// 计算RES14
	CS1251_Struct.RES14_Value = (CS1251_Struct.BodyRes14_ADC - CS1251_Struct.InternalShort_ADC)*700/
	                            (CS1251_Struct.RefRes1_ADC - CS1251_Struct.RefRes0_ADC -32);
	// 计算RES14
	CS1251_Struct.RES41_Value = (CS1251_Struct.BodyRes41_ADC - CS1251_Struct.InternalShort_ADC)*700/
	                            (CS1251_Struct.RefRes1_ADC - CS1251_Struct.RefRes0_ADC -32);
	// 判断电阻是否符合规定范围
	if( CS1251_Struct.RES14_Value<200 || CS1251_Struct.RES14_Value>1500 ){
      return;
	}
	if( CS1251_Struct.RES41_Value<200 || CS1251_Struct.RES41_Value>1500 ){
		  return;
	}
	// 判断14与41是否在合适的范围内
	if(CS1251_Struct.RES14_Value >= CS1251_Struct.RES41_Value){
		ResValueTemp = CS1251_Struct.RES14_Value - CS1251_Struct.RES41_Value;
	}else{
	  ResValueTemp = CS1251_Struct.RES41_Value - CS1251_Struct.RES14_Value;
	}
	if(ResValueTemp>300){
		return;
  }
	CS1251_Struct.BodyRes_Value = (CS1251_Struct.RES14_Value+CS1251_Struct.RES41_Value)>>1;
	// 计算K14值
// 	CS1251_Struct.RES_KValue = (CS1251_Struct.RefRes1_ADC - CS1251_Struct.RefRes0_ADC) 
// 	                         - ((CS1251_Struct.BodyRes14_ADC - CS1251_Struct.InternalShort_ADC)*700)/500;
	// 计算K41值
// 	CS1251_Struct.RES_KValue = (CS1251_Struct.RefRes1_ADC - CS1251_Struct.RefRes0_ADC) 
// 	                         - ((CS1251_Struct.BodyRes41_ADC - CS1251_Struct.InternalShort_ADC)*700)/500;
}

