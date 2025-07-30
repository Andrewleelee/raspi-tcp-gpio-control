#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x92997ed8, "_printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xf89f9719, "gpio_to_desc" },
	{ 0xc13c22af, "gpiod_unexport" },
	{ 0xfe990052, "gpio_free" },
	{ 0xec303bc6, "device_destroy" },
	{ 0x40a86756, "class_destroy" },
	{ 0x6815efd6, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x1cb6cfdf, "gpiod_export" },
	{ 0x4b528f8d, "gpiod_direction_output_raw" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x6603ec52, "cdev_init" },
	{ 0x6c7903e2, "cdev_add" },
	{ 0x9b753afb, "__class_create" },
	{ 0x51c10d8f, "device_create" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xf1c23c09, "gpiod_get_raw_value" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xbcb28a3d, "gpiod_set_raw_value" },
	{ 0x5f754e5a, "memset" },
	{ 0x91ade18, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "8FE7EE2D6AEAE3878A30393");
