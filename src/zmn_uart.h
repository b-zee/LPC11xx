#ifndef ZMN_UART_H
#define ZMN_UART_H

#include <stdint.h>

void zmn_uart_init(void);

char zmn_uart_getc(void);

void zmn_uart_putc(const char c);
void zmn_uart_puts(const char *str);
void zmn_uart_putu(uint32_t i);
void zmn_uart_puti(int32_t i);

#endif
