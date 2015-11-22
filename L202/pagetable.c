/*  
 *  hello-2.c - Demonstrating the module_init() and module_exit() macros.
 *  This is preferred over using init_module() and cleanup_module().
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */
#include <linux/mm.h>
#include <linux/sched.h>

static int __init page_table_init(void)
{
	printk(KERN_INFO "~~ Hello, I'm finding page frame structs.\n");
	
	struct mm_struct *mm = current->mm;
	if (mm == NULL)
		mm = current->active_mm;
	printk(KERN_INFO "~~ mm is %p", mm);
	struct mm_walk walker = {
		.mm = mm,
		.private = mm->mmap,
	};
	printk(KERN_INFO "~~ %ld, %ld", mm->mmap->vm_start, mm->mmap->vm_end);
	return walk_page_range(mm->mmap->vm_start, mm->mmap->vm_end, &walker);
}

static void __exit page_table_exit(void)
{
	printk(KERN_INFO "Goodbye, page frame struct.\n");
}

module_init(page_table_init);
module_exit(page_table_exit);
