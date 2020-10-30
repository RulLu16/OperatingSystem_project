#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include "lib/user/syscall.h"
#include "devices/shutdown.h"
#include "devices/input.h"

void syscall_init (void);

/* User system call function. */
void sys_halt(void);
void sys_exit(int);
pid_t sys_exec(const char*);
int sys_wait(pid_t);
int sys_read(int, void*, unsigned);
int sys_write(int, const void*, unsigned);
int fibonacci(int);
int max_of_four_int(int, int, int, int);

#endif /* userprog/syscall.h */
