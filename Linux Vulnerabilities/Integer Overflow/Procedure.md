# Integer Overflow Vulnerability on a Linux System

## 🎯 Project Goal

This project demonstrates an **Integer Overflow vulnerability** using a C program on a Linux system. It shows how unsafe memory calculations can lead to memory corruption and how to **detect, debug, and fix** such overflows using tools like GDB.

---

## 🛠 Tools Required

- A 64-bit or 32-bit Linux system (Ubuntu preferred)
- GCC compiler (`sudo apt install gcc`)
- GDB debugger (`sudo apt install gdb`)
- Terminal access
- Optional: Valgrind (`sudo apt install valgrind`) for detailed memory diagnostics

---

## ⚙️ Setup and Execution

### ✅ Step 1: Create Project Directory

```bash
mkdir -p ~/int-overflow-lab/vuln_code
```
```bash
cd ~/int-overflow-lab/vuln_code
```

---

### ✅ Step 2: Create Vulnerable Source Code

```bash
nano int_overflow.c
```

Paste the following **vulnerable C code**:

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

    // Force memory write to trigger crash on overflow
    for (unsigned int i = 0; i < num_elements; i++) {
        array[i] = i;
        if (i % 100000000 == 0)
            printf("Wrote %u elements...\n", i);
    }

    printf("Memory write completed\n");
    free(array);
    return 0;
}
```

---

### ✅ Step 3: Compile the Vulnerable Code (with Debug Symbols)

```bash
gcc -g -fno-stack-protector -no-pie -o int_overflow int_overflow.c
```

- `-g` enables debugging symbols for GDB.
- `-fno-stack-protector` disables stack protection to expose vulnerabilities.
- `-no-pie` makes memory layout more predictable.

---

## 🔥 Integer Overflow Vulnerability Explained

### 🧪 Example Input:

```
1073741825
```

### 🧠 What Happens:

```c
total_size = 1073741825 * 4 = 4294967300
```

- `UINT_MAX` for 32-bit `unsigned int` is `4294967295`
- So `4294967300` **overflows** and wraps to:

```
4294967300 % 2^32 = 4
```

### 🚨 Consequence:

- `malloc(4)` allocates only **4 bytes**.
- Loop tries to write **>1 billion integers**, far beyond allocated space.
- This causes a **segmentation fault** due to heap buffer overflow.

---

### ✅ Step 4: Run and Trigger Overflow

```bash
./int_overflow
```

Input:

```
1073741825
```

Expected output:

```
Allocating 4 bytes
Wrote 0 elements...
Wrote 100000000 elements...
...
Segmentation fault (core dumped)
```

---

### 🐞 Step 5: Debug with GDB

```bash
gdb ./int_overflow
```

At the GDB prompt:

```bash
run
```
Enter number of integers to allocate: 

```bash
1073741825
```

After the crash:

```bash
bt
```

This will show the **backtrace**, helping you locate the crashing line in the code.

---

### 🧪 Step 6: Use Valgrind for Deeper Memory Checks

```bash
valgrind ./int_overflow
```

Expected output includes:

```
Invalid write of size 4
Address 0x4 is not stack'd, malloc'd or (recently) free'd
...
```

---

## 🛡️ Step 7: Fix the Vulnerability

Edit the source:

```bash
nano int_overflow.c
```

Apply this fix before the allocation:

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For UINT_MAX

int main() {
    unsigned int num_elements;
    printf("Enter number of integers to allocate: ");
    scanf("%u", &num_elements);

    // Check for integer overflow during size calculation
    if (num_elements > UINT_MAX / sizeof(int)) {
        printf("Integer overflow detected! Allocation aborted.\n");
        return 1;
    }

    unsigned int total_size = num_elements * sizeof(int);
    printf("Allocating %u bytes\n", total_size);

    int *array = (int *)malloc(total_size);  // malloc is now declared via stdlib.h
    if (!array) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Write to the allocated memory
    for (unsigned int i = 0; i < num_elements; i++) {
        array[i] = i;
        if (i % 100000000 == 0)
            printf("Wrote %u elements...\n", i);
    }

    printf("Memory write completed\n");
    free(array);
    return 0;
}
```

```
This ensures that multiplication won’t wrap around and cause misallocated memory.
```
---

## 🔁 Step 8: Rebuild and Test Safe Version

```bash
gcc -g -o int_overflow_safe int_overflow.c
```
```bash
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

✅ No crash — vulnerability mitigated!

---

## Step 9: To view kernel system performance

```bash
time ./int_overflow_safe
```

Input:

```
1073741825
```
---

## 🧰 Troubleshooting and Best Practices

| Issue                       | Solution                                                                 |
|----------------------------|--------------------------------------------------------------------------|
| Segmentation fault          | Use GDB or Valgrind to locate the exact crashing memory access           |
| Overflow check doesn’t work| Ensure you're using `UINT_MAX / sizeof(type)` for comparisons            |
| Still crashes               | Check if loop or memory write exceeds allocated space                    |
| No warning from compiler    | Use `-Wall -Wextra -Wconversion` flags for better diagnostics            |

---

## ✅ Conclusion

In this project, you learned how:

- Integer overflows can silently corrupt memory allocations
- Heap overflows can cause segmentation faults
- Proper validation prevents dangerous behavior
- GDB and Valgrind help find and fix memory bugs

---

## 📁 Project Files

View and contribute to the project on GitHub:

**GitHub:** [https://github.com/Arisudan/Linux](https://github.com/Arisudan/Linux)

---
