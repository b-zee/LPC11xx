#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(void);
void uart_putc(const char c);
void uart_puts(const char *str);
void uart_putu(uint32_t i);
void uart_puti(int32_t i);

#endif/*UART_H*/
