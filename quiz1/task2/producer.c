#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/spinlock.h>

#include "buffer.h"
#define STR_SIZE 100

DEFINE_SPINLOCK(lock);
char **buffer;
int head = 0; // Point to an available position.
int tail = 0; // Point to an unavailable position.
EXPORT_SYMBOL(lock);
EXPORT_SYMBOL(buffer);
EXPORT_SYMBOL(head);
EXPORT_SYMBOL(tail);

static struct task_struct* task;

static int producer(void *data)
{
	// Random time to sleep.
	int i;
	int sleep;
	int count = 0;
	
	// Initialization.
	head = 0;
	tail = 0;
	buffer = kzalloc(sizeof (char *) * BUFFER_SIZE, GFP_KERNEL);
	for (i = 0; i < BUFFER_SIZE; ++i)
		buffer[i] = kzalloc(sizeof (char) * STR_SIZE, GFP_KERNEL);

	while (1) {
		// Consumer needs time to run.
		if (kthread_should_stop())
			break;

		sleep = get_random_int() % 1024 + 1;
		
		// Wastes a position to avoid overflow.
		if ((tail + 1) % BUFFER_SIZE != head) {
			++ count;
			// Critical area.	
			spin_lock(&lock);
			sprintf(buffer[tail], "%s (%d): count=%d, random=%d", 
				__func__, __LINE__, count, sleep);
			tail = (tail + 1) % BUFFER_SIZE;
			spin_unlock(&lock);
		}
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
