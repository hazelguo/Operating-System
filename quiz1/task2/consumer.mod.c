#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5612d940, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x5420b4e4, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xae1d350c, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x250f555c, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x408be03f, __VMLINUX_SYMBOL_STR(buffer) },
	{ 0xcc5005fe, __VMLINUX_SYMBOL_STR(msleep_interruptible) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xda3e43d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock) },
	{ 0xf6cb4273, __VMLINUX_SYMBOL_STR(tail) },
	{ 0x1a737417, __VMLINUX_SYMBOL_STR(head) },
	{ 0xd52bf1ce, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x50af7971, __VMLINUX_SYMBOL_STR(lock) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=producer";


MODULE_INFO(srcversion, "23532B02A413503E1EE7DEC");
