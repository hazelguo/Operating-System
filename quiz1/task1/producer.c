#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/spinlock.h>

#include "queue.h"
#define STR_SIZE 100

DEFINE_SPINLOCK(lock);
struct list_head *list; 

EXPORT_SYMBOL(lock);
EXPORT_SYMBOL(list);

static struct task_struct *task;

static int producer(void *data)
{
	// Random time to sleep.
	int sleep;
	int count = 0;
	struct node *new_item = NULL;
	char *str;
	
	// Initialization.
	list = kzalloc(sizeof (struct list_head), GFP_KERNEL);
	INIT_LIST_HEAD(list);
	
	while (1) {
		// Consumer needs time to run.
		if (kthread_should_stop())
			break;

		sleep = get_random_int() % 1024 + 1;
		++ count;
		str = (char *) kcalloc(STR_SIZE, sizeof(char), GFP_KERNEL);
		sprintf(str, "%s (%d): count=%d, random=%d", 
			__func__, __LINE__, count, sleep);
		new_item = new_node(str);

		// Critical area.
		spin_lock(&lock);
		add_node_tail(new_item, list);
		spin_unlock(&lock);
	
		msleep_interruptible(sleep);
	}
	return 0;
}

static int producer_init(void)
{
	printk(KERN_INFO "Producer starts.\n");
	task = kthread_run(&producer, NULL, "producer");
	return 0;
}

static void producer_exit(void)
{
	printk(KERN_INFO "Producer ends.\n");
	kthread_stop(task);
}

module_init(producer_init);
module_exit(producer_exit);
