#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "userprog/process.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  if(*(int*)f->esp != SYS_HALT)
    addr_check(f->esp + 4);
  
  switch(*(int*)f->esp){
    case SYS_HALT:
      sys_halt();
      break;
    case SYS_EXIT:
      sys_exit(*(int*)(f->esp + 4));
      break;
    case SYS_EXEC:
      f->eax = sys_exec((const char*)*(uint32_t*)(f->esp + 4));
      break;
    case SYS_WAIT:
      f->eax = sys_wait(*(pid_t*)(f->esp + 4));
      break;
    case SYS_READ:
      addr_check(f->esp + 8);
      addr_check(f->esp + 12);
      f->eax = sys_read(*(uint32_t*)(f->esp + 4), (void*)*(uint32_t*)(f->esp + 8), \
                     (unsigned)*(uint32_t*)(f->esp + 12));
      break;
    case SYS_WRITE:
      addr_check(f->esp + 8);
      addr_check(f->esp + 12);
      f->eax = sys_write(*(uint32_t*)(f->esp + 4), (void*)*(uint32_t*)(f->esp + 8), \
                     (unsigned)*(uint32_t*)(f->esp + 12));
      break;
    case SYS_FIBONACCI:
      f->eax = fibonacci(*(int*)(f->esp + 4));
      break;
    case SYS_MAXOFFOURINT:
      addr_check(f->esp + 8);
      addr_check(f->esp + 12);
      addr_check(f->esp + 16);
      f->eax = max_of_four_int(*(int*)(f->esp + 4), *(int*)(f->esp + 8), \
                     *(int*)(f->esp + 12), *(int*)(f->esp + 16));
      break;
  }

  //thread_exit ();
}

/* Check if addr is in user address space. */
void addr_check(const void* addr){
    if(addr == NULL || is_kernel_vaddr(addr))
      sys_exit(-1);
}

/* User system call function. */
void sys_halt(void){
    shutdown_power_off();
}

void sys_exit(int status){
    printf("%s: exit(%d)\n", thread_name(), status);
    thread_current()->exit_status = status;
    thread_exit();
}

pid_t sys_exec(const char* cmd_line){
    return process_execute(cmd_line);
}

int sys_wait(pid_t pid){
    return process_wait(pid);
}

int sys_read(int fd, void* buffer, unsigned size){
    int i;

    if(fd == 0){
        for(i=0;i<(int)size;i++){
            *(uint8_t*)(buffer + i) = input_getc();
        }

        if(i != (int)size) return -1; // Bad read.
        else return size;
    }

    return -1;
}

int sys_write(int fd, const void* buffer, unsigned size){
    if(fd == 1){
        putbuf(buffer, size);
        return size;
    }
    else return -1;
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
