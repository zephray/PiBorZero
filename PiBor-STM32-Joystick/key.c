
#include "key.h" 
#include "lcd.h"


void Key_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//要先开时钟，再重映射；关闭jtag，保留swd。      

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 

  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|
                                GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{	
   if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0 ) 
  {	   
    Delayms(10);
    if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 0 )  
    {	 
	/*等待按键释放 */ 
	return 	KEY_ON;	 
    }
    else
	return KEY_OFF;
  }
  else
    return KEY_OFF;
}
