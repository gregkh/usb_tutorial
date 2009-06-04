#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int __init gotemp_init(void)
{
	printk(KERN_INFO "Hello from the kernel!\n");
	return 0;
}

static void __exit gotemp_exit(void)
{
}

module_init(gotemp_init);
module_exit(gotemp_exit);

MODULE_AUTHOR("My name here");
MODULE_DESCRIPTION("Simple driver");
MODULE_LICENSE("GPL");
