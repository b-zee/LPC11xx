#ifndef SYS_H
#define SYS_H

#include <stdint.h>


// Set pin from port to input or output direction
#define GPIO_IN(port, pin)   (port->DIR  &= ~(1 << pin))
#define GPIO_OUT(port, pin)  (port->DIR  |=  (1 << pin))
// Set pin from port to low or high logical state
#define GPIO_LO(port, pin)   (port->DATA &= ~(1 << pin))
#define GPIO_HI(port, pin)   (port->DATA |=  (1 << pin))
#define GPIO_GET(port, pin)  (port->DATA &   (1 << pin))


void     sys_init(void);
uint32_t sys_device_id(void);

#endif
