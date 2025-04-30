# 🧨 Integer Overflow Vulnerability on a Linux System

## 🎯 Project Goal

This project demonstrates an **Integer Overflow vulnerability** using a C program on a Linux system. It shows how unsafe memory calculations can cause memory corruption and how to detect and fix such overflows properly.

---

## 🛠 Tools Required

- A 64-bit/32-Bit Linux system (Ubuntu preferred)
- GCC compiler
- Terminal access

---

## ⚙️ Setup and Execution

### Step 1: Create Project Directory

```bash
mkdir -p ~/int-overflow-lab/vuln_code
cd ~/int-overflow-lab/vuln_code
```

---

### Step 2: Create Vulnerable Source Code

```bash
nano int_overflow.c
```

Paste the following code:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned int num_elements;
    printf("Enter number of integers to allocate: ");
    scanf("%u", &num_elements);

    unsigned int total_size = num_elements * sizeof(int);  // Vulnerable: no overflow check
    printf("Allocating %u bytes\n", total_size);

    int *array = (int *)malloc(total_size);
    if (!array) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (unsigned int i = 0; i < num_elements; i++) {
        array[i] = i;
    }

    printf("Memory write completed\n");
    free(array);
    return 0;
}
```

---

### Step 3: Compile the Code

```bash
gcc -o int_overflow int_overflow.c -fno-stack-protector -no-pie
```

---

## 🔥 Integer Overflow Explanation

Let’s say you enter:

```
1073741825
```

The program calculates:

```
total_size = 1073741825 * 4 = 4294967300
```

### 🧠 But what’s wrong?

- `UINT_MAX` for a 32-bit unsigned int = `4294967295`
- `4294967300` exceeds this limit

In **32-bit arithmetic**, it wraps around using modulo `2^32`:

```
4294967300 % 4294967296 = 4
```

So the system allocates only **4 bytes** instead of the needed **4294967300**.

### 🚨 Consequence

You're writing over **1 billion integers** into memory allocated for **just 1**, causing a **segmentation fault**.

---

### Step 4: Run and Trigger Overflow

```bash
./int_overflow
```

Enter:

```
1073741825
```

Expected output:

```
Allocating 4 bytes
Segmentation fault (core dumped)
```

---

### Step 5: Debug with GDB (Optional)

```bash
gdb ./int_overflow
run
```

After it crashes, type:

```bash
bt
```

To see the backtrace and locate the cause.

---

### Step 6: Fix the Vulnerability

Edit the code:

```bash
nano int_overflow.c
```

Apply the fix:

```c
#include <limits.h>  // Required for UINT_MAX

if (num_elements > UINT_MAX / sizeof(int)) {
    printf("Integer overflow detected! Allocation aborted.\n");
    return 1;
}

unsigned int total_size = num_elements * sizeof(int);
```

---

### Step 7: Rebuild and Retest

```bash
gcc -o int_overflow_safe int_overflow.c
./int_overflow_safe
```

Input:

```
1073741825
```

Expected output:

```
Integer overflow detected! Allocation aborted.
```

---

## 🧰 Troubleshooting and Best Practices

| Issue | Solution |
|-------|----------|
| Segmentation fault | Use GDB to locate the crash |
| Overflow check doesn't work | Use `UINT_MAX / sizeof(type)` properly |
| Still overflows | Check your variable data types |
| No warning from compiler | Use flags like `-Wall -Wextra -Wconversion` |

---

## ✅ Conclusion

This project showed how:

- Integer Overflow can occur during size computations
- You can crash a program by allocating incorrect memory sizes
- Proper overflow checks can prevent security issues
- GDB can help diagnose and debug such memory issues

---

## 📁 Project Files

You can find and contribute to this project at:

**GitHub**: [https://github.com/Arisudan/Linux](https://github.com/Arisudan/Linux)

---
