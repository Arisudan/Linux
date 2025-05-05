
# Integer Overflow in a Userspace C Program (Ubuntu 32-bit)

## Project Overview

This project demonstrates an **Integer Overflow vulnerability (CWE-190)** in a C program on Ubuntu. It shows how unchecked memory allocation can lead to **heap buffer overflows**, causing crashes or security risks.

---

## Objectives

- Trigger an integer overflow in memory allocation
- Analyze the crash using GDB/Valgrind
- Apply a fix with proper bounds checking


---
## Project Overflow

1. Creation of the Integer Overflow Vulnerability:
   
   ![Capture 1](https://github.com/user-attachments/assets/0df43932-1811-42c1-bbce-fc66762d7742)

---

2. View the performance of the kernel module before clearing out the vulnerability:

```bash
time ./int_overflow_safe
```
Enter number of integers to allocate: 
```bash
1073741825
```
   ![Capture 2](https://github.com/user-attachments/assets/d847d8a6-5b0d-47a6-b585-f965d76a9528)

---

3. Run and Trigger overflow in GDB:

![Capture 3](https://github.com/user-attachments/assets/41a6cdad-5d66-4d66-8b85-7a70e2a718f1)

bt - shows the backtrace, helping you locate the crashing line in the code.

---

4. Using Valgrind for Deeper Memory Checks

```bash
valgrind ./int_overflow
```
![Capture 4](https://github.com/user-attachments/assets/2f96d9e0-ab98-41b6-8e51-88df8e4cd6d9)
![Capture 5](https://github.com/user-attachments/assets/e0080638-f35f-425a-a9b2-2dd02f00dc0d)

---

5. After fixing the Vulnerability:

 Enter number of integers to allocate: 
```bash
1073741825
```

![Capture 6](https://github.com/user-attachments/assets/3f2488f3-0d34-4667-8390-e3a26e5ee4a2)

---

6. View the performance of the kernel module after clearing out the vulnerability:
   
```bash
time ./int_overflow_safe
```
Enter number of integers to allocate: 
```bash
1073741825
```

![Capture 7](https://github.com/user-attachments/assets/b04852f0-142d-41e6-a640-7694e8ffbd64)

---

## Performance 
## 📁 Project Files

View and contribute to the project on GitHub:

**GitHub:** [https://github.com/Arisudan/Linux](https://github.com/Arisudan/Linux)

---
