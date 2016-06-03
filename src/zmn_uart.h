#ifndef ZMN_UART_H
#define ZMN_UART_H

#include <stdint.h>

/**
 * @brief  Enable UART with RXD and TXD on pin 1.6 and 1.7 respectively.
 */
void zmn_uart_init(void);

/**
 * @brief  Blocking function to receive character.
 *
 * @return  Character value read from UART.
 */
char zmn_uart_getc(void);

/**
 * @brief  Blocking function that will send a character.
 *
 * @param[in]  c  Character to put on UART.
 */
void zmn_uart_putc(const char c);
/**
 * @brief  Call zmn_uart_putc for each character in string.

 * @param[in]  str  String to send characters from.
 */
void zmn_uart_puts(const char *str);
/**
 * @brief  Print unsigned value with human readable characters.
 *
 * @param[in]  i  Unsigned integer to print
 */
void zmn_uart_putu(uint32_t i);
/**
 * @brief  Print signed value with human readable characters.
 *
 * @param[in]  i  Signed integer to print
 */
void zmn_uart_puti(int32_t i);

#endif
