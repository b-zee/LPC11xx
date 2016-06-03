/**
 * @brief   Pin interface
 * @author  Benno Zeeman <bzeeman@live.nl>
 */
//  Copyright (C) 2016 Benno Zeeman
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ZMN_GPIO_H
#define ZMN_GPIO_H

#include <LPC11xx.h>

/**
 * @brief  Configure a pin for input.
 *
 * @param  gpio GPIO port
 * @param  pin  GPIO pin
 */
static inline void zmn_gpio_in(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	gpio->DIR &= ~(1 << pin);
}

/**
 * @brief  Configure a pin for output.
 *
 * @param  gpio GPIO port
 * @param  pin  GPIO pin
 */
static inline void zmn_gpio_out(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	gpio->DIR |= (1 << pin);
}

/**
 * @brief  Change the logic state of a pin to HIGH.
 *
 * @param  gpio GPIO port
 * @param  pin  GPIO pin
 */
static inline void zmn_gpio_set(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	gpio->DATA |= (1 << pin);
}
/**
 * @brief  Change the logic state of a pin to LOW.
 *
 * @param  gpio GPIO port
 * @param  pin  GPIO pin
 */
static inline void zmn_gpio_clear(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	gpio->DATA &= ~(1 << pin);
}

/**
 * @brief  Retreive the current logic state of a PIN
 *
 * @param  gpio GPIO port
 * @param  pin  GPIO pin
 *
 * @retval  0  Logic state is LOW
 * @retval  1  Logic state is HIGH
 */
static inline uint32_t zmn_gpio_get(LPC_GPIO_TypeDef *gpio, uint32_t pin)
{
	return (gpio->DATA >> pin) & 1;
}

#endif
