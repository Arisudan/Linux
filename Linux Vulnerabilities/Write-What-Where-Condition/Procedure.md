# Write-What-Where Condition in a Linux Kernel Module

## Project Goal

This project demonstrates a **Write-What-Where Condition** vulnerability in a custom Linux kernel module. It allows direct user input into kernel memory, showing how unsafe memory handling can lead to critical security flaws. The project also includes a fix and best practices.

---

## Tools Required

- Ubuntu (recommended)
- Terminal with `sudo` privileges
- Installed packages:
  - `build-essential`
  - `linux-headers-$(uname -r)`

---

## Setup and Execution

### Step 1: Install Required Packages

```bash
sudo apt update
```
```bash
sudo apt install build-essential linux-headers-$(uname -r)
```
---

### Step 2: Create Project Directory

```bash
mkdir -p ~/write-what-where-lab/vuln_module
```
```bash
cd ~/write-what-where-lab/vuln_module
```

---

### Step 3: Create Vulnerable Kernel Module

```bash
nano www_vuln.c
```

Paste the following vulnerable code:

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "www_vuln"

struct linked_node {
    struct linked_node *next;
    struct linked_node *prev;
};

static int major;
static struct linked_node node;

ssize_t device_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    printk(KERN_INFO "[www_vuln] Received %zu bytes from user.\n", len);

    // Vulnerability: direct write into kernel structure
    if (len > 0 && len <= sizeof(struct linked_node)) {
        copy_from_user(&node, buf, len);  // Write-What-Where condition
    }

    return len;
}

static struct file_operations fops = {
    .write = device_write,
};

static int __init www_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    printk(KERN_INFO "[www_vuln] Module loaded. Major number: %d\n", major);
    return 0;
}

static void __exit www_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "[www_vuln] Module unloaded.\n");
}

module_init(www_init);
module_exit(www_exit);
MODULE_LICENSE("GPL");
```

---

### Step 4: Create Makefile

```bash
nano Makefile
```

Paste this content:

```make
obj-m += www_vuln.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

---

### Step 5: Compile the Module

```bash
make
```

---

### Step 6: Load the Module

```bash
sudo insmod www_vuln.ko
```

Check if loaded:

```bash
sudo dmesg | grep www_vuln
```

---

### Step 7: Create Character Device Node

```bash
sudo mknod /dev/www_vuln c <MAJOR_NUMBER> 0
```
```bash
sudo chmod 666 /dev/www_vuln
```

Replace `<MAJOR_NUMBER>` with the number from `dmesg`.

---

### Step 8: Trigger the Vulnerability

```bash
python3 -c 'import os; os.write(os.open("/dev/www_vuln", os.O_WRONLY), b"A"*16)'
```

Check logs:

```bash
sudo dmesg | grep www_vuln
```

---

### Step 9: View the Performance of the system before clearing the vulnerability

```bash
sudo perf stat -a -e cycles,instructions,cache-misses sleep 5 > vuln_perf.txt
```
---

### Step 10: Fix the Vulnerability

Edit `www_vuln.c`:

```bash
nano www_vuln.c
```

Replace this vulnerable code:

```c
copy_from_user(&node, buf, len);
```

With this safe version:

```c
printk(KERN_INFO "[www_vuln] Unsafe memory write prevented.\n");
// No direct write to structure from user-space
```

Copy and Paste the Following Safe Code:

```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "www_vuln"

struct linked_node {
    struct linked_node *next;
    struct linked_node *prev;
};

static int major;
static struct linked_node node;

ssize_t device_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    printk(KERN_INFO "[www_vuln] Received %zu bytes from user.\n", len);

    // Vulnerability: direct write into kernel structure
    if (len > 0 && len <= sizeof(struct linked_node)) {
        printk(KERN_INFO "[www_vuln] Unsafe memory write prevented.\n");  // Write-What-Where condition eradicated
    }

    return len;
}

static struct file_operations fops = {
    .write = device_write,
};

static int __init www_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    printk(KERN_INFO "[www_vuln] Module loaded. Major number: %d\n", major);
    return 0;
}

static void __exit www_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "[www_vuln] Module unloaded.\n");
}

module_init(www_init);
module_exit(www_exit);
MODULE_LICENSE("GPL");

```
---

### Step 11: Rebuild and Reload

```bash
make clean
make
sudo rmmod www_vuln
sudo insmod www_vuln.ko
```

---

### Step 12: Test After Fix

Try the same payload:

```bash
python3 -c 'import os; os.write(os.open("/dev/www_vuln", os.O_WRONLY), b"A"*16)'
```

You should see the safe message in `dmesg`:

```bash
sudo dmesg | grep www_vuln
```
---

### Step 13: View the Performance of the system after clearing the vulnerability

```bash
sudo perf stat -a -e cycles,instructions,cache-misses sleep 5 > vuln_perf.txt
sudo perf stat -e cycles,instructions,cache-misses ./www_vuln > vuln_perf.txt

```
---

## Troubleshooting

| Issue                  | Solution                                                             |
| ---------------------- | -------------------------------------------------------------------- |
| Cannot create device   | Use correct major number from `dmesg`                                |
| No module output       | Check if module is loaded using `lsmod` and `dmesg`                  |
| `copy_from_user` fails | Ensure user buffer length is valid and device is writable            |
| Segfault or crash      | Reboot if kernel memory is corrupted; use virtual machine for safety |

---

## Conclusion

This project demonstrates:

* A typical **Write-What-Where Condition** in kernel-space
* How unvalidated user-space input leads to memory corruption
* Safe practices for kernel module development

---

## Project Files

All project files can be cloned or downloaded from:

**GitHub**: [https://github.com/Arisudan/Linux](https://github.com/Arisudan/Linux)

```

---
