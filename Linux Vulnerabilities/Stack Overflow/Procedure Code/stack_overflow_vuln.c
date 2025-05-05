#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "vuln"
#define BUF_LEN 32

static int major;
static char kernel_buffer[BUF_LEN];

ssize_t device_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    printk(KERN_INFO "[vuln] Writing %zu bytes (max: %d) to kernel buffer.\n", len, BUF_LEN);
    copy_from_user(kernel_buffer, buf, len);  // Vulnerability: no bounds checking
    return len;
}

static struct file_operations fops = {
    .write = device_write,
};

static int __init vuln_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    printk(KERN_INFO "[vuln] Module loaded. Major number: %d\n", major);
    return 0;
}

static void __exit vuln_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "[vuln] Module unloaded.\n");
}

module_init(vuln_init);
module_exit(vuln_exit);
MODULE_LICENSE("GPL");
