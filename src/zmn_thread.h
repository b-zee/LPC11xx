#ifndef ZMN_THREAD_H
#define ZMN_THREAD_H

void zmn_thread_init(void);
void zmn_thread_create(void (*f)(void));

#endif
