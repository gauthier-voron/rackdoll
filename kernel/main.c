#include <idt.h>                            /* see there for interrupt names */
#include <memory.h>                               /* physical page allocator */
#include <printk.h>                      /* provides printk() and snprintk() */
#include <string.h>                                     /* provides memset() */
#include <syscall.h>                         /* setup system calls for tasks */
#include <task.h>                             /* load the task from mb2 info */
#include <types.h>              /* provides stdint and general purpose types */
#include <vga.h>                                         /* provides clear() */
#include <x86.h>                                    /* access to cr3 and cr2 */

/*
 * Memory model for Rackdoll OS
 *
 * +----------------------+ 0xffffffffffffffff
 * | Higher half          |
 * | (unused)             |
 * +----------------------+ 0xffff800000000000
 * | (impossible address) |
 * +----------------------+ 0x00007fffffffffff
 * | User                 |
 * | (text + data + heap) |
 * +----------------------+ 0x2000000000
 * | User                 |
 * | (stack)              |
 * +----------------------+ 0x40000000
 * | Kernel               |
 * | (valloc)             |
 * +----------------------+ 0x200000
 * | Kernel               |
 * | (text + data)        |
 * +----------------------+ 0x100000
 * | Kernel               |
 * | (BIOS + VGA)         |
 * +----------------------+ 0x0
 *
 * This is the memory model for Rackdoll OS: the kernel is located in low
 * addresses. The first 2 MiB are identity mapped and not cached.
 * Between 2 MiB and 1 GiB, there are kernel addresses which are not mapped
 * with an identity table.
 * Between 1 GiB and 128 GiB is the stack addresses for user processes growing
 * down from 128 GiB.
 * The user processes expect these addresses are always available and that
 * there is no need to map them exmplicitely.
 * Between 128 GiB and 128 TiB is the heap addresses for user processes.
 * The user processes have to explicitely map them in order to use them.
 */


void print_mapping(struct task *ctx)
{
	/* TODO */
	if (ctx) {}
}

void map_page(struct task *ctx, vaddr_t vaddr, paddr_t paddr)
{
	/* TODO */
	if (ctx && vaddr && paddr) {}
}

/*
 * Load a new task in memory.
 *   - Create a new page table and fill it so ctx->load_vaddr is mapped on
 *     ctx->load_paddr up to ctx->load_end_paddr.
 *   - Fill ctx->pgt with the physical address of this page table.
 */
void load_task(struct task *ctx)
{
	/* TODO */
	if (ctx) {}
}

/*
 * Set the new current task memory mapping.
 */
void set_task(struct task *ctx)
{
	/* TODO */
	if (ctx) {}
}

/*
 * Allocate a new physical page and map vaddr on it for the task with the given
 * ctx context.
 * If vaddr is already mapped, unmap it before to proceed.
 */
void mmap(struct task *ctx, vaddr_t vaddr)
{
	/* TODO */
	if (ctx && vaddr) {}
}

/*
 * Unmap the given vaddr and free the associated physical page for the task
 * with the given ctx context.
 */
void munmap(struct task *ctx, vaddr_t vaddr)
{
	/* TODO */
	if (ctx && vaddr) {}
}


__attribute__((noreturn))
void die(void)
{
	/* Stop fetching instructions and go low power mode */
	asm volatile ("hlt");

	/* This while loop is dead code, but it makes gcc happy */
	while (1)
		;
}

__attribute__((noreturn))
void main_multiboot2(void *mb2)
{
	clear();                                     /* clear the VGA screen */
	printk("Rackdoll OS\n-----------\n\n");                 /* greetings */

	setup_interrupts();                           /* setup a 64-bits IDT */
	setup_tss();                                  /* setup a 64-bits TSS */

	disable_pic();                         /* disable anoying legacy PIC */
	sti();                                          /* enable interrupts */

	load_tasks(mb2);                         /* load the tasks in memory */
	run_tasks();                                 /* run the loaded tasks */

	printk("\nGoodbye!\n");                                 /* fairewell */
	die();                        /* the work is done, we can die now... */
}
