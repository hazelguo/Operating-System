#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/spinlock.h>

#include "buffer.h"

extern spinlock_t lock;
extern char **buffer;
extern int head;
extern int tail;

static struct task_struct *task;

static int consumer(void *data)
{
	int count = 0;

	while (1) {
		// Producer needs time to run.
		if (kthread_should_stop())
			break;
	
		// Critical area.
		spin_lock(&lock);
		// Print all items in buffer.
		while (head != tail) {	
			printk(KERN_INFO "%s\n", buffer[head]);
			++count;
			head = (head + 1) % BUFFER_SIZE;
		}
		spin_unlock(&lock);

		printk(KERN_INFO "Consumer count=%d\n", count);
		// Sleep 1 sec. Do not use mdelay becase mdelay is busy-waiting.
		msleep_interruptible(1000);
	} 
	return 0;
}

static int consumer_init(void)
{
	printk(KERN_INFO "Consumer starts.\n");
	task = kthread_run(&consumer, NULL, "consumer");
	return 0;
}

static void consumer_exit(void)
{
	printk(KERN_INFO "Consumer ends.\n");
	kthread_stop(task);
}

module_init(consumer_init);
module_exit(consumer_exit);
