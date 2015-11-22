#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <asm/setup.h>

MODULE_AUTHOR("Zihan Guo");
MODULE_LICENSE("GPL");

static int L5_print_hex_dump_init_module(void)
{
	char* boot_command_line = (char *)0xffffffff81dcf900;
	char** saved_command_line = (char *)0xffffffff81e75008;
	print_hex_dump(KERN_INFO, "L5_boot_command_line", DUMP_PREFIX_NONE, 16, 1, boot_command_line, COMMAND_LINE_SIZE, true);
	print_hex_dump(KERN_INFO, "L5_saved_command_line", DUMP_PREFIX_NONE, 16, 1, *saved_command_line, COMMAND_LINE_SIZE, true);

	return 0;
}

static void L5_print_hex_dump_cleanup_module(void)
{
	printk(KERN_INFO "goodbye L5 boot_command_line");
}

module_init(L5_print_hex_dump_init_module);
module_exit(L5_print_hex_dump_cleanup_module);
