#ifndef ZMN_THREAD_H
#define ZMN_THREAD_H

#include <stddef.h>

/**
 * @brief  Setup system for multi-tasking.
 */
_Noreturn void zmn_thread_init(void (*f)(void));

/**
 * @brief  Add a thread that starts executing the function given.
 */
//void zmn_thread_create(void (*f)(void));

#endif
