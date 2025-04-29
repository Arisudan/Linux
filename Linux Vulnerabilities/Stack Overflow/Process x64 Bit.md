# Stack Buffer Overflow in a Linux Kernel Module (Ubuntu 64-bit)

## Project Overview

This project demonstrates a **stack buffer overflow vulnerability (CWE-121)** using a custom Linux kernel module on a **64-bit Ubuntu system**. It shows how unsafe memory copying from user space can corrupt kernel stack memory, and how to fix the issue using proper bounds checking.

The project is especially valuable for learning low-level security and kernel module development on a simplified 32-bit memory architecture.

---

## Objectives

- Create a vulnerable Linux kernel module
- Trigger a stack buffer overflow using `/dev/vuln`
- View the behavior in `dmesg`
- Apply a safe fix and verify the vulnerability is resolved

---

## Project Overflow

1. Creation of the  Stack Overflow Vulnerability:
   
![New1](https://github.com/user-attachments/assets/01b0e8ce-d8ac-4e10-a3d1-8ccf2ab6a2d7)

---

2. By using the following commands we get the Performance of the 64 Bit in a Stack Overflow Vulnerability:
   
A. Use time to measure execution:

```bash
time echo "SAFE_INPUT" | sudo tee /dev/vuln > /dev/null
```
  Use perf to get detailed CPU usage:

```bash
perf stat echo "SAFE_INPUT" | sudo tee /dev/vuln > /dev/null
```
![New 2](https://github.com/user-attachments/assets/09b20e11-a2cf-4adb-b0aa-027361cc97c8)

---

B. Trigger the overflow with crafted input:

```bash
time echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```
  Use perf to get detailed CPU usage:

```bash
perf stat echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```

![New 7](https://github.com/user-attachments/assets/c94c8d72-5134-441e-b63d-e8978c51fddf)

---

3. After clearing out the Stack Overflow Vulnerability:

![New 3](https://github.com/user-attachments/assets/5518aaef-7b81-4fa3-8ca7-9ba48a49ef28)
![New 4](https://github.com/user-attachments/assets/a10b856b-a765-4c7e-bcda-ff405fdb0d01)

---

4. By using the following commands we get the Performance of the 64 Bit after clearing out the Stack Overflow Vulnerability:

A. Use time to measure execution:

```bash
time echo "SAFE_INPUT" | sudo tee /dev/vuln > /dev/null
```
  Use perf to get detailed CPU usage:

```bash
perf stat echo "SAFE_INPUT" | sudo tee /dev/vuln > /dev/null
```
![New 5](https://github.com/user-attachments/assets/5fbcbfa0-89ef-4697-ba2d-6a3a27603585)

---

B. Trigger the overflow with crafted input:

```bash
time echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```
  Use perf to get detailed CPU usage:

```bash
perf stat echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```

![New 6](https://github.com/user-attachments/assets/2c7c727a-574a-4b9c-97db-22abe2aa2535)

---

## 🧠 Why 64-bit?

- Larger addressable memory space (0x00007FFFFFFFFFFF)
    - Can access up to 16 exabytes of virtual memory (compared to 4 GB in 32-bit).

- More general-purpose registers
    - x86-64 provides 16 general-purpose registers (vs 8 in 32-bit), making code more efficient.

- Standard for modern operating systems
    - Most OSes (Linux, Windows, macOS) default to 64-bit, making it more relevant today.

- Supports modern software and toolchains
    - Many newer libraries, applications, and exploits assume 64-bit architecture.

- Better performance for large computations
    - 64-bit CPUs can handle larger integers and memory operations natively.

- Richer calling conventions (System V / Microsoft x64)
    - Parameters are passed through registers, making function calls faster and stack layouts more interesting for exploitation.

- ASLR and other mitigations are more complex
    - Great for learning advanced exploitation techniques.
---

## 📂 Repository

This project is available on GitHub:  
🔗 [https://github.com/Arisudan/Linux](https://github.com/Arisudan/Linux)

---

## 👨‍💻 Author

### Arisudan TH 
Ubuntu 64-bit Kernel Lab | 2025

---
