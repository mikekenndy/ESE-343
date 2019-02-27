#include <linux/module.h>	/* must have */
#include <linux/kernel.h>	/* why is this needed?? */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mike Kennedy");
//TRY modinfo
MODULE_DESCRIPTION("A simple Hello World LKM!");
MODULE_VERSION("0.005");

static int __init hello_world(void)
{
	printk(KERN_DEBUG "Hello world!\n");
	return 0;
}

static void __exit bye_world(void)
{
	printk(KERN_DEBUG "Bye world!\n");
}

module_init(hello_world);
module_exit(bye_world);
