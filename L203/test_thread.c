#include <linux/kthread.h>

static int kthread_func(void *data) {
	printf("lalalalalalal\n");
}

int main()
{
	struct task_struct *tsk = kthread_run(kthread_func, NULL, "lalala");
	return 0;
}
