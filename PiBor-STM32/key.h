#ifndef __KEY_H__
#define	__KEY_H__

#include "main.h"

#define KEY_UP_GPIO     GPIOA
#define KEY_DOWN_GPIO   GPIOA
#define KEY_LEFT_GPIO   GPIOA
#define KEY_RIGHT_GPIO  GPIOA
#define KEY_X_GPIO      GPIOB
#define KEY_Y_GPIO      GPIOB
#define KEY_A_GPIO      GPIOB
#define KEY_B_GPIO      GPIOB
#define KEY_L_GPIO      GPIOB
#define KEY_R_GPIO      GPIOB
#define KEY_SEL_GPIO    GPIOB
#define KEY_START_GPIO  GPIOB
#define KEY_HOLD_GPIO   GPIOB

#define KEY_UP_PIN      GPIO_Pin_3
#define KEY_DOWN_PIN    GPIO_Pin_1
#define KEY_LEFT_PIN    GPIO_Pin_2
#define KEY_RIGHT_PIN   GPIO_Pin_0
#define KEY_X_PIN       GPIO_Pin_12
#define KEY_Y_PIN       GPIO_Pin_13
#define KEY_A_PIN       GPIO_Pin_14
#define KEY_B_PIN       GPIO_Pin_15
#define KEY_L_PIN       GPIO_Pin_5
#define KEY_R_PIN       GPIO_Pin_6
#define KEY_SEL_PIN     GPIO_Pin_3
#define KEY_START_PIN   GPIO_Pin_4
#define KEY_HOLD_PIN    GPIO_Pin_7

#define KEY_UP_SCANCODE     0x52
#define KEY_DOWN_SCANCODE   0x51
#define KEY_LEFT_SCANCODE   0x50
#define KEY_RIGHT_SCANCODE  0x4F
#define KEY_X_SCANCODE      0x1B
#define KEY_Y_SCANCODE      0x1C
#define KEY_A_SCANCODE      0x04
#define KEY_B_SCANCODE      0x05
#define KEY_L_SCANCODE      0x0F
#define KEY_R_SCANCODE      0x15
#define KEY_SEL_SCANCODE    0x29
#define KEY_START_SCANCODE  0x28


#define KEY_ON	1
#define KEY_OFF	0

void Key_GPIO_Config(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif /* __LED_H */

