/* Driver for the tpo JBT6K74-AS LCM ASIC
 *
 * Copyright (C) 2006-2007 by Openmoko, Inc.
 * Author: Harald Welte <laforge@openmoko.org>,
 *         Stefan Schmidt <stefan@openmoko.org>
 * Copyright (C) 2008 by Harald Welte <laforge@openmoko.org>
 * Copyright (C) 2017 by Wenting Zhang <zephray@cnvintage.org>
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */
#include "main.h"
#include "lcd.h"
#include "delay.h"


void LCD_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Delaycycle(unsigned int i)
{
  while(i--);
}

void LCD_WriteCmd(unsigned char c)
{
  unsigned char i;
  LCD_CS_LOW();
  //Command header 0x00
  LCD_MOSI_LOW();
  LCD_SCK_LOW();
  Delaycycle(100);
  LCD_SCK_HIGH();
  Delaycycle(100);
  //Actuall command
  for (i=0;i<8;i++)
  {
    if (c&0x80) { LCD_MOSI_HIGH(); } else { LCD_MOSI_LOW(); }
    LCD_SCK_LOW();
    c=c<<1;
    Delaycycle(100);
    LCD_SCK_HIGH();
    Delaycycle(100);
  }
  LCD_CS_HIGH();
}

void LCD_WriteDat(unsigned char d)
{
  unsigned char i;
  LCD_CS_LOW();
  //Data header 0x01
  LCD_MOSI_HIGH();
  LCD_SCK_LOW();
  Delaycycle(100);
  LCD_SCK_HIGH();
  Delaycycle(100);
  //Actual data
  for (i=0;i<8;i++)
  {
    if (d&0x80) { LCD_MOSI_HIGH(); } else { LCD_MOSI_LOW(); }
    LCD_SCK_LOW();
    d=d<<1;
    Delaycycle(100);
    LCD_SCK_HIGH();
    Delaycycle(100);
  }
  LCD_CS_HIGH();
}

void LCD_WriteReg(unsigned char reg, unsigned char dat)
{
  LCD_WriteCmd(reg);
  LCD_WriteDat(dat);
}

void LCD_WriteShortReg(unsigned char reg, unsigned short dat)
{
  LCD_WriteCmd(reg);
  LCD_WriteDat(dat >> 8);
  LCD_WriteDat(dat & 0xFF);
}

void LCD_Init()
{
  LCD_GPIO_Config();
  LCD_CS_HIGH();
  LCD_SCK_HIGH();
  LCD_MOSI_HIGH();
  LCD_RST_LOW();
  Delayms(100);
  LCD_RST_HIGH();
  Delayms(100);

  //Soft reset
  LCD_WriteCmd(0x01);
  Delayms(120);
  
  LCD_WriteCmd(0x00);
  Delayms(1);
  LCD_WriteCmd(0x00);
  Delayms(1);
  LCD_WriteCmd(0x00);
  Delayms(1);
  
  LCD_WriteReg(JBT_REG_POWER_ON_OFF, 0x17); //Deep standby out
  LCD_WriteReg(JBT_REG_DISPLAY_MODE, 0x80); //RGB I/F on, RAM write off, QVGA through, SIGCON enable
  LCD_WriteReg(JBT_REG_QUAD_RATE, 0x00);    //Quad mode off
  LCD_WriteReg(JBT_REG_POWER_ON_OFF, 0x16); //AVDD on, XVDD on
  LCD_WriteShortReg(JBT_REG_OUTPUT_CONTROL, 0xfff9); //Output control
  LCD_WriteCmd(JBT_REG_SLEEP_OUT); //Sleep mode off
  
  //at this point we have like 50% grey
  //initialize register set
  LCD_WriteReg(JBT_REG_DISPLAY_MODE1, 0x01); 
  LCD_WriteReg(JBT_REG_DISPLAY_MODE2, 0x00); 
  LCD_WriteReg(JBT_REG_RGB_FORMAT, 0x60); 
  LCD_WriteReg(JBT_REG_DRIVE_SYSTEM, 0x10); 
  LCD_WriteReg(JBT_REG_BOOSTER_OP, 0x56); 
  LCD_WriteReg(JBT_REG_BOOSTER_MODE, 0x33); 
  LCD_WriteReg(JBT_REG_BOOSTER_FREQ, 0x11); 
  LCD_WriteReg(JBT_REG_BOOSTER_FREQ, 0x11); 
  LCD_WriteReg(JBT_REG_OPAMP_SYSCLK, 0x02); 
  LCD_WriteReg(JBT_REG_VSC_VOLTAGE, 0x2b); 
  LCD_WriteReg(JBT_REG_VCOM_VOLTAGE, 0x40); 
  LCD_WriteReg(JBT_REG_EXT_DISPL, 0x03); 
  LCD_WriteReg(JBT_REG_DCCLK_DCEV, 0x04); 
  LCD_WriteReg(JBT_REG_ASW_SLEW, 0x04); 
  LCD_WriteReg(JBT_REG_DUMMY_DISPLAY, 0x00);
  
  LCD_WriteReg(JBT_REG_SLEEP_OUT_FR_A, 0x11); 
  LCD_WriteReg(JBT_REG_SLEEP_OUT_FR_B, 0x11); 
  LCD_WriteReg(JBT_REG_SLEEP_OUT_FR_C, 0x11); 
  LCD_WriteShortReg(JBT_REG_SLEEP_IN_LCCNT_D, 0x2040); 
  LCD_WriteShortReg(JBT_REG_SLEEP_IN_LCCNT_E, 0x60c0); 
  LCD_WriteShortReg(JBT_REG_SLEEP_IN_LCCNT_F, 0x1020); 
  LCD_WriteShortReg(JBT_REG_SLEEP_IN_LCCNT_G, 0x60c0); 
  
  LCD_WriteShortReg(JBT_REG_GAMMA1_FINE_1, 0x5533); 
  LCD_WriteReg(JBT_REG_GAMMA1_FINE_2, 0x00); 
  LCD_WriteReg(JBT_REG_GAMMA1_INCLINATION, 0x00); 
  LCD_WriteReg(JBT_REG_GAMMA1_BLUE_OFFSET, 0x00); 
  
  LCD_WriteShortReg(JBT_REG_HCLOCK_VGA, 0x1f0); 
  LCD_WriteReg(JBT_REG_BLANK_CONTROL, 0x02); 
  LCD_WriteShortReg(JBT_REG_BLANK_TH_TV, 0x0804); 
  
  LCD_WriteReg(JBT_REG_CKV_ON_OFF, 0x01); 
  LCD_WriteShortReg(JBT_REG_CKV_1_2, 0x0000); 
  
  LCD_WriteShortReg(JBT_REG_OEV_TIMING, 0x0d0e); 
  LCD_WriteShortReg(JBT_REG_ASW_TIMING_1, 0x11a4); 
  LCD_WriteReg(JBT_REG_ASW_TIMING_2, 0x0e); 
  
  LCD_WriteCmd(JBT_REG_DISPLAY_ON);
}
