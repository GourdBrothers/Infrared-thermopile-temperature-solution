
/***************************************
*/

#include "stm32f0xx.h"
#include "delay.h"
#include "led.h"
#include "USART1.h"

/***************************************
*/
int main(void)
{
	delay_init();
	LED_Init();
	//USART1_Init(115200);
	//printf("Hi\r\n");
//================================	
	while (1)
	{		
		delay_ms(100);
		LED_TURN;
	}
}


/***************************************
*/
#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
