#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"

static void syscall_handler (struct intr_frame *);

static void halt(void);
static void write(struct intr_frame*);
static void exit(struct intr_frame*);
/*
static void wait();
static void create();
static void remove();
static void open();
static void filesize();
static void read();
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
	
	switch(n){
		case SYS_HALT:
			halt();
			break;
		case SYS_EXIT:
			exit(f);
			break;
			/*
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
			*/
		case SYS_WRITE:
			write(f);
			break;
			/*
		case SYS_SEEK:
			seek();
			break;
		case SYS_TELL:
			tell();
			break;
		case SYS_CLOSE:
			close();
			break;
			*/
	}

  //thread_exit ();
}

static void halt(void){
	shutdown_power_off();
	NOT_REACHED();
}

static void write(struct intr_frame* f){
  int fd;
	unsigned size;
	void* buffer;
	char* esp = (char*)f->esp;
	uint32_t n = 0; // return to eax

	// find arguments; int fd, void* buffer, unsigned size;
	//printf("%p\n", esp);
	//hex_dump((uintptr_t)esp, esp, 8 * 127, false);
	esp += sizeof(int);  // pass interupt number
	fd = *(int*)esp;
	esp += sizeof(int);
	buffer = (const char*)*(void**)esp;
	esp += sizeof(void*);
	size = *(unsigned*)esp;
	

	// only console
	while(n <= size){
		if(size - n < 16){
			putbuf(buffer, size - n);
			n = size;
			break;
		}
		else{
			putbuf(buffer, 128);
			n += 128;
		}
	}
	// not console

	// return
	f->eax = n;
}

static void exit(struct intr_frame* f){
	thread_exit();
}
