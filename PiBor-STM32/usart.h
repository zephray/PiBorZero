#ifndef __USART_H__
#define __USART_H__

#include "main.h"

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART1_Config(void);
void USART1_PutChar(u8 ch);
u8 USART1_GetChar();

#define USART1_WaitData() while((USART1->SR & USART_FLAG_RXNE) == (uint16_t)RESET)

#endif
