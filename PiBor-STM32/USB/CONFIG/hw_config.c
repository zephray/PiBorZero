/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : hw_config.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "platform_config.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 
 
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
			  

//ÅäÖÃUSBÊ±ÖÓ,USBclk=48Mhz
void Set_USBClock(void)
{
	/* Select USBCLK source */
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
	
	/* Enable the USB clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);						 
}
 
/*******************************************************************************
* Function Name  : Enter_LowPowerMode.
* Description    : Power-off system clocks and power while entering suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
  bDeviceState = SUSPENDED;	  
  /* Request to enter STOP mode with regulator in low power mode */
  //PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
}			  

/*******************************************************************************
* Function Name  : Leave_LowPowerMode.
* Description    : Restores system clocks and power while exiting suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;
								   
													   
  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }
}

//USBÖÐ¶ÏÅäÖÃ
void USB_Interrupts_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	/* 2 bit for pre-emption priority, 2 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Configure the EXTI line 18 connected internally to the USB IP */
	EXTI_ClearITPendingBit(EXTI_Line18);
	EXTI_InitStructure.EXTI_Line = EXTI_Line18; // USB resume from suspend mode
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 	 

	/* Enable the USB interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USB Wake-up interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init(&NVIC_InitStructure);   
}
		    
/*******************************************************************************
* Function Name : Joystick_Send.
* Description   : prepares buffer to be sent containing Joystick event infos.
* Input         : Keys: keys received from terminal.
* Output        : None.
* Return value  : None.
*******************************************************************************/
void Joystick_Send(u8 buf0,u8 buf1,u8 buf2,u8 buf3)
{
  u8 Mouse_Buffer[5] = {2, 0, 0, 0, 0};
    
  /* prepare buffer to send */
  Mouse_Buffer[1]=buf0;
  Mouse_Buffer[2]=buf1;
  Mouse_Buffer[3]=buf2;
  Mouse_Buffer[4]=buf3;

  /*copy mouse position info in ENDP1 Tx Packet Memory Area*/
  UserToPMABufferCopy(Mouse_Buffer, GetEPTxAddr(ENDP1), 5);
  /* enable endpoint for transmission */
  SetEPTxValid(ENDP1);
}


/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
  u32 Device_Serial0, Device_Serial1, Device_Serial2;

  Device_Serial0 = *(u32*)(0x1FFFF7E8);
  Device_Serial1 = *(u32*)(0x1FFFF7EC);
  Device_Serial2 = *(u32*)(0x1FFFF7F0);

  if (Device_Serial0 != 0)
  {
    Joystick_StringSerial[2] = (u8)(Device_Serial0 & 0x000000FF);
    Joystick_StringSerial[4] = (u8)((Device_Serial0 & 0x0000FF00) >> 8);
    Joystick_StringSerial[6] = (u8)((Device_Serial0 & 0x00FF0000) >> 16);
    Joystick_StringSerial[8] = (u8)((Device_Serial0 & 0xFF000000) >> 24);

    Joystick_StringSerial[10] = (u8)(Device_Serial1 & 0x000000FF);
    Joystick_StringSerial[12] = (u8)((Device_Serial1 & 0x0000FF00) >> 8);
    Joystick_StringSerial[14] = (u8)((Device_Serial1 & 0x00FF0000) >> 16);
    Joystick_StringSerial[16] = (u8)((Device_Serial1 & 0xFF000000) >> 24);

    Joystick_StringSerial[18] = (u8)(Device_Serial2 & 0x000000FF);
    Joystick_StringSerial[20] = (u8)((Device_Serial2 & 0x0000FF00) >> 8);
    Joystick_StringSerial[22] = (u8)((Device_Serial2 & 0x00FF0000) >> 16);
    Joystick_StringSerial[24] = (u8)((Device_Serial2 & 0xFF000000) >> 24);
  }
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
