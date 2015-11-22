#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/mm.h>
#include <linux/kallsyms.h>

int (*_walk_page_range)(unsigned long start, unsigned long end,	struct mm_walk *walk);
static int print(pte_t *pte, unsigned long addr,
		unsigned long next, struct mm_walk *walk)
{
	printk(KERN_INFO "page frame struct is @ %d\n", pte->pte);
	return 0;
}

MODULE_LICENSE("GPL");
static int pid = 0;
module_param(pid, int, 0644);

static int __init hello_init(void)
{
	int uu = 0;
	printk(KERN_INFO "walk module installed");
	_walk_page_range = kallsyms_lookup_name("walk_page_range");
	struct task_struct *tsk = pid_task(find_vpid(pid), PIDTYPE_PID);	
	struct mm_struct *mm = tsk->mm;
	struct vm_area_struct *vma;
	down_read(&mm->mmap_sem);
	//for (vma = mm->mmap; vma; vma = vma->vm_next) {
		vma = mm->mmap;
		printk(KERN_INFO "vma %d \n", uu++);
		struct mm_walk my_walk = {
			.pte_entry = print,

				.mm = mm,
				.private = vma,
		};

		_walk_page_range(vma->vm_start, vma->vm_end,
				&my_walk);
	//}
	up_read(&mm->mmap_sem);
	return 0;
}


static void __exit hello_exit(void)
{
}

module_init(hello_init);
module_exit(hello_exit);
