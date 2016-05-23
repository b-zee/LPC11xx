#ifndef ZMN_GPIO_H
#define ZMN_GPIO_H

#include <LPC11xx.h>

static inline void zmn_gpio_in(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	gpio->DIR &= ~(1 << pin);
}
static inline void zmn_gpio_out(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	gpio->DIR |= (1 << pin);
}

static inline void zmn_gpio_set(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	gpio->DATA |= (1 << pin);
}
static inline void zmn_gpio_clear(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	gpio->DATA &= ~(1 << pin);
}

static inline uint32_t zmn_gpio_get(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	return (gpio->DATA >> pin) & 1;
}

#endif
