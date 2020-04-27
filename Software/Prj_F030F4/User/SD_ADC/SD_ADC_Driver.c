/*
 *-----------------------------------------------------------------------------
 * SD_ADC_Driver.c
 *
 *-----------------------------------------------------------------------------
 */
#include "SD_ADC_Driver.h"


/*-------------------------------------------------------
 * private functions
 */

static void Fun_SdAdc_Delay(unsigned short delayTime){
	
}

/*-------------------------------------------------------
 * 当SCLK保持LOW超过687us通信口复位，但芯片不复位
 */
static void Fun_SdAdc_PIN_Init(void)
{
}

static void Fun_SdAdc_PIN_DeInit(void)
{
}

static void Fun_SdAdc_WR_Byte(unsigned char byteData)
{
}

static unsigned char Fun_SdAdc_RD_Byte(void)
{
	unsigned char RdByte;

	return	RdByte;
}

static void Fun_SdAdc_WR_REG(unsigned char byteAddr,unsigned char byteData)
{

}

static unsigned char Fun_SdAdc_RD_REG(unsigned char byteAddr)
{
	unsigned char RD_data;

	return RD_data ;
}

// 1 ,无数据
// 0 ,有数据
static unsigned char Fun_SdAdc_ChkAdcRDY(void)
{
    unsigned char Temp;

    return Temp;
}

static void Fun_SdAdc_RD_ADC(void)
{

}



static void Fun_SdAdc_GetAdc(unsigned char ChannelValue)
{

}


/*-------------------------------------------------------
 * public functions
 */

//--------------------------------------------------------------
//----
//----
//
int Fun_SdAdc_Reset(void) 
{
}

//--------------------------------------------------------------
//----
//----
//
void Fun_SdAdc_Init(void)
{
	
}

//--------------------------------------------------------------
//----
//----
//
void Fun_SdAdc_PowerDown(void)
{
}

//--------------------------------------------------------------
//----
//----
//

void Fun_SdAdc_test(void)
{
}

