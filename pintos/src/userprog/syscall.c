#include "userprog/syscall.h"
#include <stdio.h>
#include <string.h>
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
  lock_init(&file_lock);
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
    case SYS_CREATE:
      addr_check(f->esp + 8);
      f->eax = sys_create((const char*)*(uint32_t*)(f->esp + 4), (unsigned)*(uint32_t*)(f->esp + 8));
      break;
    case SYS_REMOVE:
      f->eax = sys_remove((const char*)*(uint32_t*)(f->esp + 4));
      break;
    case SYS_OPEN:
      f->eax = sys_open((const char*)*(uint32_t*)(f->esp + 4));
      break;
    case SYS_FILESIZE:
      f->eax = sys_filesize(*(int*)(f->esp + 4));
      break;
    case SYS_SEEK:
      sys_seek(*(int*)(f->esp + 4), (unsigned)*(uint32_t*)(f->esp + 8));
      break;
    case SYS_TELL:
      f->eax = sys_tell(*(int*)(f->esp + 4));
      break;
    case SYS_CLOSE:
      sys_close(*(int*)(f->esp + 4));
      break;
  }
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
    struct thread* cur = thread_current();

    /* Close all files in current thread. */
    for(int i=3;i<128;i++){
        if(cur->file_desp[i] != NULL)
          sys_close(i);
    }

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
    struct thread* cur = thread_current();
    off_t result = -1;

    addr_check(buffer);

    /* Set read lock. */
    lock_acquire(&file_lock);

    if(fd == 0){ // STDIN
        for(i=0;i<(int)size;i++){
            *(uint8_t*)(buffer + i) = input_getc();
        }

        if(i != (int)size) result = -1; // Bad read.
        else result = size;
    }
    else if(fd>2){
        if(cur->file_desp[fd] == NULL) sys_exit(-1); // No file.

        result = file_read(cur->file_desp[fd], buffer, size);
    }

    /* Release read lock. */
    lock_release(&file_lock);
    return result;
}

int sys_write(int fd, const void* buffer, unsigned size){
    struct thread* cur = thread_current();
    off_t result = -1;
    
    addr_check(buffer);

    /* Set write lock. */
    lock_acquire(&file_lock);

    if(fd == 1){ // STDOUT
        putbuf(buffer, size);
        result = size;
    }
    else if(fd>2){
        if(cur->file_desp[fd] == NULL) sys_exit(-1); // No file.

        /* Wait until enable write. */
        if(cur->file_desp[fd]->deny_write)
          file_deny_write(cur->file_desp[fd]);

        result = file_write(cur->file_desp[fd], buffer, size);
    }
    
    /* Release write lock. */
    lock_release(&file_lock);
    return result;
}

int fibonacci(int n){
    int first = 0; int second = 1;
    int ans;

    if(n == 0) return 0;
    if(n == 1) return 1;

    for(int i=2;i<=n;i++){
        ans = first+ second;
        first = second;
        second = ans;
    }

    return ans;
}

int max_of_four_int(int a, int b, int c, int d){
    int max = a;

    if(max < b) max = b;
    if(max < c) max = c;
    if(max < d) max = d;

    return max;
}

bool sys_create(const char* file, unsigned initial_size){
    if(file == NULL) sys_exit(-1); // NULL exception
    return filesys_create(file, initial_size);
}

bool sys_remove(const char* file){
    if(file == NULL) sys_exit(-1); // NULL exception
    return filesys_remove(file);
}

int sys_open(const char* file){
    if(file == NULL) sys_exit(-1); // NULL exception

    /* Set open lock. */
    lock_acquire(&file_lock);

    struct file* f = filesys_open(file);
    struct thread* cur = thread_current(); 
    int result = -1;

    /* No file. */
    if(f == NULL){
        lock_release(&file_lock);
        return -1;
    }
    
    /* Find empty descriptor and set. */
    for(int i=3;i<128;i++){
        if(cur->file_desp[i] == NULL){
            cur->file_desp[i] = f;

            /* Set deny write. */
            if(!strcmp(file, cur->name))
              file_deny_write(cur->file_desp[i]);

            result = i;
            break;
        }
    }

    /* Release open lock. */
    lock_release(&file_lock);
    return result;
}

int sys_filesize(int fd){
    if(thread_current()->file_desp[fd] == NULL) 
      sys_exit(-1); // No file.

    return file_length(thread_current()->file_desp[fd]);
}

void sys_seek(int fd, unsigned position){
    if(thread_current()->file_desp[fd] == NULL) 
      sys_exit(-1); // No file.

    file_seek(thread_current()->file_desp[fd], position);
}

unsigned sys_tell(int fd){
    if(thread_current()->file_desp[fd] == NULL) 
      sys_exit(-1); // No file.

    return file_tell(thread_current()->file_desp[fd]);
}

void sys_close(int fd){
    struct thread* cur = thread_current();

    if(thread_current()->file_desp[fd] == NULL) 
      sys_exit(-1); // No file.

    file_close(cur->file_desp[fd]);
    cur->file_desp[fd] = NULL;
}
