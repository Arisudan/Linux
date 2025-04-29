# Stack Buffer Overflow in a Linux Kernel Module (Ubuntu 32-bit)

## Project Overview

This project demonstrates a **stack buffer overflow vulnerability (CWE-121)** using a custom Linux kernel module on a **32-bit Ubuntu system**. It shows how unsafe memory copying from user space can corrupt kernel stack memory, and how to fix the issue using proper bounds checking.

The project is especially valuable for learning low-level security and kernel module development on a simplified 32-bit memory architecture.

---

## Objectives

- Create a vulnerable Linux kernel module
- Trigger a stack buffer overflow using `/dev/vuln`
- View the behavior in `dmesg`
- Apply a safe fix and verify the vulnerability is resolved

---

## Project Overflow

![Capture 1](https://github.com/user-attachments/assets/c63383dc-ee93-41e9-886f-766ebca2ec9a)
![Capture 2](https://github.com/user-attachments/assets/7b460a5c-ab51-477c-8385-41375f2098b7)
![Capture 3](https://github.com/user-attachments/assets/fae0da0e-150e-481c-8c37-5ae8172c8ec6)
![Capture 4](https://github.com/user-attachments/assets/91b8a096-9037-4f60-b39e-c088623294b9)
![Capture 5](https://github.com/user-attachments/assets/36fc25e4-5f29-4cbf-b038-ca669946015e)
![Capture 6](https://github.com/user-attachments/assets/d29c5412-f98b-4aaf-a9be-061db1721dae)
![Capture 7](https://github.com/user-attachments/assets/b6ae890b-95b2-48a5-b5e3-32b935a54b95)

---

## 🧠 Why 32-bit?

- Simpler memory addressing (`0xbfXXXXXX`)
- Easier to understand stack layouts
- Great for learning **low-level exploitation**
- Common in older embedded systems

---

## 📂 Repository

This project is available on GitHub:  
🔗 [https://github.com/Arisudan/Linux](https://github.com/Arisudan/Linux)

---

## 👨‍💻 Author

Arisudan TH 
Ubuntu 32-bit Kernel Lab | 2025

---
