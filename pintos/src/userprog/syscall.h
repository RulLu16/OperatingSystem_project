#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);

/* User system call function. */
void halt();
void exit();
void exec();
void wait();
void write();
void read();
int fibonacci(int);
int max_of_four_int(int, int, int, int);

#endif /* userprog/syscall.h */
