#include <linux/module.h>  
#include <linux/kernel.h>   
#include <linux/init.h>      
#include <linux/sched.h>
#include <linux/cred.h>


MODULE_LICENSE("GPL");

struct pid *structPID;
struct task_struct *task;
int param_num = 0;
module_param(param_num, int, S_IRUGO);

static int __init hello_init(void){
    structPID = find_get_pid(param_num);
    task = get_pid_task(structPID, PIDTYPE_PID);
    if (task) {
        printk(KERN_INFO "Process command path: %s\n",task->comm);
        printk(KERN_INFO "Process pid: %d\n",task->pid);
        printk(KERN_INFO "Process group id: %d\n",task->tgid);
        printk(KERN_INFO "Process user_id: %d\n", __kuid_val(task->cred->uid));
    }
    put_pid(structPID);
    return 0;    
}

static void __exit hello_cleanup(void){
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);