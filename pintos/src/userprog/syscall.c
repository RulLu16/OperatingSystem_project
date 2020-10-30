#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  switch(*(uint32_t*)f->esp){
    case SYS_HALT:
      halt();
      break;
    case SYS_EXIT:
      break;
    case SYS_EXEC:
      break;
    case SYS_WAIT:
      break;
    case SYS_READ:
      break;
    case SYS_WRITE:
      break;
    case SYS_FIBONACCI:
      break;
    case SYS_MAXOFFOURINT:
      break;
  }

  thread_exit ();
}

/* User system call function. */
void halt(){
}

void exit(int status){
}

pid_t exec(const char* cmd_line){
}

int wait(pid_t pid){
}

int read(int fd, void* buffer, unsigned size){
}

int write(int fd, const void* buffer, unsigned size){
}

int fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;

    return fibonacci(n-1) + fibonacci(n-2);
}

int max_of_four_int(int a, int b, int c, int d){
    int max = a;

    if(max < b) max = b;
    if(max < c) max = c;
    if(max < d) max = d;

    return max;
}
