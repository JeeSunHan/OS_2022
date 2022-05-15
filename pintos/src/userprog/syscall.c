#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);
void halt (void);
void exit (int);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  uint32_t *esp;
  esp = f->esp;
  int syscall = *esp;
  
  switch(syscall){
    case SYS_HALT:
      halt();
      break;

    case SYS_EXIT:
      exit(*(esp+1));
      break;

    case SYS_EXEC:
      //not implemented
      /*exec(*(esp+1))*/
      break;

    case SYS_WAIT:
      //not implemented
      break;

    case SYS_CREATE:
      //not implemented
      break;

    case SYS_REMOVE:
      //not implemented
      break;

    case SYS_OPEN:
      //not implemented
      break;

    case SYS_FILESIZE:
      //not implemented
      break;

    case SYS_READ:
      //not implemented
      break;

    case SYS_WRITE:
      //not implemented
      break;

    case SYS_SEEK:
      //not implemented
      break;

    case SYS_TELL:
      //not implemented
      break;

    case SYS_CLOSE:
      //not implemented
      break;

    default:
      printf("syscall!");
      thread_exit();
      break;
  }
  printf ("system call!\n");
  thread_exit ();
}

void halt(void){
	shutdown_power_off();
}

void exit(int s){
	struct thread *t = thread_current();
	printf("%s: exit(%d)\n", t->name, s);
	thread_exit();
}
