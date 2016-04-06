// Set pin from port to input or output direction
#define GPIO_IN(port, pin)   (port->DIR  &= ~(1 << pin))
#define GPIO_OUT(port, pin)  (port->DIR  |=  (1 << pin))
// Set pin from port to low or high logical state
#define GPIO_LO(port, pin)   (port->DATA &= ~(1 << pin))
#define GPIO_HI(port, pin)   (port->DATA |=  (1 << pin))
#define GPIO_GET(port, pin)  (port->DATA & (1 << pin))


#define IRC_FREQ          12000000UL
#define SYSAHBCLKDIV_int  0x01
#define   UARTCLKDIV_int  0x01

#define BAUD_RATE     19200
#define UART_DIVISOR  (IRC_FREQ / SYSAHBCLKDIV_int / UARTCLKDIV_int / BAUD_RATE / 16)
