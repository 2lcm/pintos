#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);
/*
static void halt();
static void exit(struct intr_frame *f, int status);
static void wait();
static void create();
static void remove();
static void open();
static void filesize();
static void read();
static void write(void);
static void seek();
static void tell();
static void close();
*/
void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
	int n;
  n = *(int*)f->esp;
	/*
	switch(n){
		case SYS_HALT:
			halt();
			break;
		case SYS_EXIT:
			exit(f, 0);
			break;
		case SYS_EXEC:
			exec();
			break;
		case SYS_WAIT:
			wait();
			break;
		case SYS_CREATE:
			create();
			break;
		case SYS_REMOVE:
			remove();
			break;
		case SYS_OPEN:
			open();
			break;
		case SYS_FILESIZE:
			filesize();
			break;
		case SYS_READ:
			read();
			break;
		case SYS_WRITE:
			write();
			break;
		case SYS_SEEK:
			seek();
			break;
		case SYS_TELL:
			tell();
			break;
		case SYS_CLOSE:
			close();
			break;
			
	}
	*/
  thread_exit ();
}
/*
static void halt(){
}

static void exit(struct intr_frame *f, int status){
	printf("%s: exit(%d)\n", thread_current()->name, status);
	return;
}

static void exec(){
}


static void write(){
	return;
}
*/
