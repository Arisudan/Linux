
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
   
![1](https://github.com/user-attachments/assets/47f448bc-7034-438b-972f-3b30f211da9c)

---

2. Run and Trigger overflow in GDB:

![2](https://github.com/user-attachments/assets/7342a3bf-cd56-4ef3-9bb3-d0c96fddbdb1)

![3](https://github.com/user-attachments/assets/19c528fd-d20c-4628-9929-e4bbed6210a7)

bt - shows the backtrace, helping you locate the crashing line in the code.

---

3. Using Valgrind for Deeper Memory Checks

```bash
valgrind ./int_overflow
```
![4](https://github.com/user-attachments/assets/f34110f9-0bbf-4271-b440-eafc0bf7dad9)
![5](https://github.com/user-attachments/assets/2d1d1966-30d5-4357-b402-8c2bb03fe02d)

---

4. After fixing the Vulnerability:

 Enter number of integers to allocate: 
```bash
1073741825
```

![6](https://github.com/user-attachments/assets/4bf0ffc2-929a-45b5-b68e-56c9d65820b1)

---

5. View the performance of the kernel module before clearing out the vulnerability:
   
```bash
time ./int_overflow_safe
```
Enter number of integers to allocate: 
```bash
1073741825
```
![8](https://github.com/user-attachments/assets/77d87851-20a0-468a-af39-2378a3b3c4ef)

---

6. View the performance of the kernel module after clearing out the vulnerability:
   
```bash
time ./int_overflow_safe
```
![7](https://github.com/user-attachments/assets/8ba438a7-33a1-4e78-8b31-883af212e158)

---

## Performance 
## 📁 Project Files

View and contribute to the project on GitHub:

**GitHub:** [https://github.com/Arisudan/Linux](https://github.com/Arisudan/Linux)

---
