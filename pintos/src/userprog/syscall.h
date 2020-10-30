#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);

/* User system call function. */
void halt();
void exit(status);
pid_t exec(const char*);
int wait(pid_t);
int read(int, void* unsigned);
int write(int, const void*, unsigned);
int fibonacci(int);
int max_of_four_int(int, int, int, int);

#endif /* userprog/syscall.h */
