#ifndef ZMN_ROUTINES_H
#define ZMN_ROUTINES_H

#include <stdint.h>

/**
 * @brief  Use process stack and set SP registers.
 *
 * @param[in]  psp  Address to point PSP to
 * @param[in]  msp  Address to point MSP to
 */
void zmn_switch_to_psp(uint32_t *psp, uint32_t *msp);

#endif
