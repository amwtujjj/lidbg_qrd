
#include "lidbg_def.h"

#include "lidbg_enter.h"


#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/memory.h>
#include <linux/memory_hotplug.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/notifier.h>
#include <linux/oom.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/sysfs.h>

static struct task_struct *test_task;

LIDBG_DEFINE;



int thread_test_xxx(void *data)
{
	u8 tmp,i,j,buff[2];
	i=0;
	j=0;
	tmp=0;
    while(1)
    {
        set_current_state(TASK_UNINTERRUPTIBLE);
        if(kthread_should_stop()) break;
        if(1)
        {

            while(1)
            {
            	buff[0]=0x63;
            	buff[1]=i&0xff;
				i++;
				j=128;
				while(j--)
					SOC_I2C_Send(1,0x88>>1, buff, 2);
				
				//SOC_I2C_Rec(1,0x88>>1, 0x63, &tmp,1);
				printk(".");
            	msleep(10);
				

            }
        }
        else
        {
            schedule_timeout(HZ);
        }
    }
    return 0;
}



int lidbg_test_init(void)
{
    DUMP_BUILD_TIME;
    LIDBG_GET;


    test_task = kthread_create(thread_test_xxx, NULL, "test_task");
    if(IS_ERR(test_task))
    {
        lidbg("Unable to start kernel thread.\n");

    }
    else wake_up_process(test_task);
    return 0;

}
void lidbg_test_deinit(void)
{


}



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Flyaudad Inc.");

module_init(lidbg_test_init);
module_exit(lidbg_test_deinit);



