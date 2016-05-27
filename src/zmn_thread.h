#ifndef ZMN_THREAD_H
#define ZMN_THREAD_H

#include <stddef.h>

_Noreturn void zmn_thread_init(void (*f)(void), size_t s);
//void zmn_thread_create(void (*f)(void));

#endif
