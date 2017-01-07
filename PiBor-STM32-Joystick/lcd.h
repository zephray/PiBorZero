#ifndef __LCD_H__
#define __LCD_H__

#define LCD_CS		GPIO_Pin_7;
#define LCD_RST		GPIO_Pin_6;
#define LCD_MOSI	GPIO_Pin_4;
#define LCD_SCK		GPIO_Pin_5;

#define LCD_CS_LOW()    GPIOA->BRR  = LCD_CS
#define LCD_CS_HIGH()   GPIOA->BSRR = LCD_CS
#define LCD_RST_LOW()   GPIOA->BRR  = LCD_RST
#define LCD_RST_HIGH()  GPIOA->BSRR = LCD_RST
#define LCD_MOSI_LOW()  GPIOA->BRR  = LCD_MOSI
#define LCD_MOSI_HIGH() GPIOA->BSRR = LCD_MOSI
#define LCD_SCK_LOW()   GPIOA->BRR  = LCD_SCK
#define LCD_SCK_HIGH()  GPIOA->BSRR = LCD_SCK

#define JBT_REG_SLEEP_IN                0x10
#define JBT_REG_SLEEP_OUT               0x11

#define JBT_REG_DISPLAY_OFF             0x28
#define JBT_REG_DISPLAY_ON              0x29

#define JBT_REG_RGB_FORMAT              0x3a
#define JBT_REG_QUAD_RATE               0x3b

#define JBT_REG_POWER_ON_OFF            0xb0
#define JBT_REG_BOOSTER_OP              0xb1
#define JBT_REG_BOOSTER_MODE            0xb2
#define JBT_REG_BOOSTER_FREQ            0xb3
#define JBT_REG_OPAMP_SYSCLK            0xb4
#define JBT_REG_VSC_VOLTAGE             0xb5
#define JBT_REG_VCOM_VOLTAGE            0xb6
#define JBT_REG_EXT_DISPL               0xb7
#define JBT_REG_OUTPUT_CONTROL          0xb8
#define JBT_REG_DCCLK_DCEV              0xb9
#define JBT_REG_DISPLAY_MODE1           0xba
#define JBT_REG_DISPLAY_MODE2           0xbb
#define JBT_REG_DISPLAY_MODE            0xbc
#define JBT_REG_ASW_SLEW                0xbd
#define JBT_REG_DUMMY_DISPLAY           0xbe
#define JBT_REG_DRIVE_SYSTEM            0xbf

#define JBT_REG_SLEEP_OUT_FR_A          0xc0
#define JBT_REG_SLEEP_OUT_FR_B          0xc1
#define JBT_REG_SLEEP_OUT_FR_C          0xc2
#define JBT_REG_SLEEP_IN_LCCNT_D        0xc3
#define JBT_REG_SLEEP_IN_LCCNT_E        0xc4
#define JBT_REG_SLEEP_IN_LCCNT_F        0xc5
#define JBT_REG_SLEEP_IN_LCCNT_G        0xc6

#define JBT_REG_GAMMA1_FINE_1           0xc7
#define JBT_REG_GAMMA1_FINE_2           0xc8
#define JBT_REG_GAMMA1_INCLINATION      0xc9
#define JBT_REG_GAMMA1_BLUE_OFFSET      0xca

#define JBT_REG_BLANK_CONTROL           0xcf
#define JBT_REG_BLANK_TH_TV             0xd0
#define JBT_REG_CKV_ON_OFF              0xd1
#define JBT_REG_CKV_1_2                 0xd2
#define JBT_REG_OEV_TIMING              0xd3
#define JBT_REG_ASW_TIMING_1            0xd4
#define JBT_REG_ASW_TIMING_2            0xd5

#define JBT_REG_HCLOCK_VGA              0xec
#define JBT_REG_HCLOCK_QVGA             0xed

#endif