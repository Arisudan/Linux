# 🧠 Stack Buffer Overflow in a Linux Kernel Module (Ubuntu 32-bit)

## 📌 Project Overview

This project demonstrates a **stack buffer overflow vulnerability (CWE-121)** using a custom Linux kernel module on a **32-bit Ubuntu system**. It shows how unsafe memory copying from user space can corrupt kernel stack memory, and how to fix the issue using proper bounds checking.

The project is especially valuable for learning low-level security and kernel module development on a simplified 32-bit memory architecture.

---

## 🎯 Objectives

- Create a vulnerable Linux kernel module
- Trigger a stack buffer overflow using `/dev/vuln`
- View the behavior in `dmesg`
- Apply a safe fix and verify the vulnerability is resolved

---

## 🧰 Requirements

- **OS**: Ubuntu 32-bit
- **Packages**:
  ```bash
  sudo apt update
  sudo apt install build-essential linux-headers-$(uname -r)
  ```

---

## 📁 Project Structure

```
stack-overflow-lab/
└── vuln_module/
    ├── stack_overflow.c      # Kernel module source
    ├── Makefile              # Build configuration
└── test_input.sh             # Script to simulate overflow
```

---

## ⚙️ Setup Instructions

### 1. Clone or Create Project

```bash
mkdir -p ~/stack-overflow-lab/vuln_module
cd ~/stack-overflow-lab/vuln_module
```

### 2. Write the Vulnerable Module

Paste this in `stack_overflow.c`:
> Vulnerable version uses `copy_from_user()` without bounds checking.

### 3. Create the Makefile

Paste this in `Makefile`:
```make
obj-m += stack_overflow.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

### 4. Compile

```bash
make
```

---

## 🧪 Execution Steps

### 5. Insert the Module

```bash
sudo insmod stack_overflow.ko
sudo dmesg | grep vuln
```

Copy the **major number** printed in `dmesg`.

---

### 6. Create Device Node

Replace `236` with the actual major number:

```bash
sudo rm -f /dev/vuln
sudo mknod /dev/vuln c 236 0
sudo chmod 666 /dev/vuln
```

---

### 7. Trigger the Vulnerability

```bash
echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln
```

Check kernel logs:

```bash
sudo dmesg | grep vuln
```

Expected:
```
[vuln] Writing 58 bytes (max: 32) to kernel buffer.
```

---

## 🔒 Fixing the Vulnerability

### Edit `stack_overflow.c`:

Replace:
```c
copy_from_user(kernel_buffer, buf, len);
```

With:
```c
size_t safe_len = len > BUF_LEN ? BUF_LEN : len;
if (copy_from_user(kernel_buffer, buf, safe_len)) {
    printk(KERN_WARNING "[vuln] copy_from_user failed\n");
}
```

### Rebuild & Reload:

```bash
make clean
make
sudo rmmod stack_overflow
sudo insmod stack_overflow.ko
```

---

## ✅ After the Fix

Re-run:
```bash
echo "OVERFLOW TEST" | sudo tee /dev/vuln
sudo dmesg | grep vuln
```

The message will show the correct length being handled, **without overflow**.

---

## 🧠 Why 32-bit?

- Simpler memory addressing (`0xbfXXXXXX`)
- Easier to understand stack layouts
- Great for learning **low-level exploitation**
- Common in older embedded systems

---

## 🛠 Troubleshooting

| Problem                             | Solution                                           |
|-------------------------------------|----------------------------------------------------|
| `/dev/vuln` is a regular file       | Use `mknod` with correct major number              |
| No output in `dmesg`                | Use `sudo dmesg | grep vuln`                      |
| Module changes not reflected        | Run `make clean && make` before reload             |
| Permissions error on `/dev/vuln`   | Run `sudo chmod 666 /dev/vuln`                    |

---

## 🧩 Learn More

- CWE-121: [MITRE CWE Entry](https://cwe.mitre.org/data/definitions/121.html)
- Linux Device Drivers: [LDD3 Book (free)](https://lwn.net/Kernel/LDD3/)

---

## 📂 Repository

This project is available on GitHub:  
🔗 [https://github.com/Arisudan/Linux](https://github.com/Arisudan/Linux)

---

## 👨‍💻 Author

Arisudan | Linux Kernel Security Enthusiast  
Ubuntu 32-bit Kernel Lab | 2024

```

---

Let me know if you want this exported as a `README.md` file or turned into a PDF!
