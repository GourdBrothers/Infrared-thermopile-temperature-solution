/*
 *-----------------------------------------------------------------------------
 * SD_ADC_Driver.h
 *
 *
 *-----------------------------------------------------------------------------
 */
 
#ifndef  __SD_ADC_H__
#define  __SD_ADC_H__

// SD_ADC Chip Register Address definition
#define  SD_ADC_REG_SYS    (unsigned char)0x00
#define  SD_ADC_REG_ADC0   (unsigned char)0x01
#define  SD_ADC_REG_ADC1   (unsigned char)0x02
#define  SD_ADC_REG_ADC2   (unsigned char)0x03
#define  SD_ADC_REG_ADC3   (unsigned char)0x04
#define  SD_ADC_REG_ADC4   (unsigned char)0x05
#define  SD_ADC_REG_ADC5   (unsigned char)0x06
#define  SD_ADC_REG_BIM0   (unsigned char)0x07
#define  SD_ADC_REG_BIM1   (unsigned char)0x08
#define  SD_ADC_REG_ADO    (unsigned char)0x09
#define  SD_ADC_REG_ADS    (unsigned char)0x0A

#define  SD_ADC_REG_CONFIG	(unsigned char)0x10
#define  SD_ADC_REG_VREFT	(unsigned char)0x11
#define  SD_ADC_REG_LDOT	(unsigned char)0x12
#define  SD_ADC_REG_OSCT	(unsigned char)0x13
#define  SD_ADC_REG_TST1	(unsigned char)0x14
#define  SD_ADC_REG_TST2	(unsigned char)0x15
#define  SD_ADC_REG_TMUX	(unsigned char)0x16
#define  SD_ADC_REG_OTPCON	(unsigned char)0x59
#define  SD_ADC_REG_TEST	(unsigned char)0x5A

//=======================================================
// MCU driver pin definition
#define  SD_ADC_PIN_CS		GPIO_PA0
#define  SD_ADC_PIN_SCL		GPIO_PA1
#define  SD_ADC_PIN_SDA		GPIO_PA2

//=======================================================
#define	 SET_SD_ADC_CS


//=======================================================
// Driver function declaration
int	 Fun_SdAdc_Reset(void);
void Fun_SdAdc_Init(void);
void Fun_SdAdc_PowerDown(void);

void Fun_SdAdc_test(void);

#endif
