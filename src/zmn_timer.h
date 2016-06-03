#ifndef ZMN_TIMER_H
#define ZMN_TIMER_H

#include <stdint.h>

/**
 * @brief  Start 32 bit timer doing 1 tick per millisecond.
 */
void zmn_timer_init(void);

/**
 * @brief  Retreive tick count, resets when overflow.
 *
 * @return  Timer value
 */
uint32_t zmn_timer_get(void);

#endif
