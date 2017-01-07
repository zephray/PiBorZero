#ifndef __BEEP_PWM_H__
#define	__BEEP_PWM_H__

#include "stm32f10x.h"

void TIM1_PWM_Init(void);
#define TIM1_PWM_Duty(x) TIM1->CCR1=x

#endif

