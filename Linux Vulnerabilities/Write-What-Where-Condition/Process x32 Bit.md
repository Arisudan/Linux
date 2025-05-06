# Write-What-Where Condition in a Linux Kernel Module (Ubuntu 32-bit)

## Project Overview

This project demonstrates a **Write-What-Where Condition vulnerability (CWE-123)** in a Linux kernel module on Ubuntu. It shows how uncontrolled writes from userspace can overwrite kernel pointers, allowing arbitrary memory writes.

## Objectives

- Trigger a Write-What-Where condition in kernel memory
- Analyze the vulnerability using `dmesg` or GDB
- Apply a fix using proper validation and memory protection techniques

---
## Project Overflow

1. Creation of the Write-What-Where Condition:

   ![Capture 1](https://github.com/user-attachments/assets/aa281a95-ab83-4393-b68f-65cb0cb9d82d)

---
2. Load the Module and create the Character:

  ![Capture 2](https://github.com/user-attachments/assets/3b8c0bb4-d167-4d16-88ee-18368518e109)

---
3. Trigger the vulnerability and check the log:

  ![Capture 3](https://github.com/user-attachments/assets/a5aee2d6-5e19-42f0-9d80-596fcc7b4310)

---

4. View the performance of the kernel module before clearing out the vulnerability:
   
```bash
/usr/bin/time -v sudo perf stat -a -e cycles,instructions,cache-misses \
    bash -c "sudo insmod www_vuln.ko; sleep 2; sudo rmmod www_vuln"
```

![Capture 4](https://github.com/user-attachments/assets/4a5e7745-b977-4123-87c8-ca0ce0631f8a)
![Capture 5](https://github.com/user-attachments/assets/b2796d7d-3164-4c7e-bfce-a4f812ffc507)

---

5. After fixing the Vulnerability:

![Capture 6](https://github.com/user-attachments/assets/befc5d8d-1b82-4dfc-ac2b-9868d321f918)

![Capture 7](https://github.com/user-attachments/assets/154cdc97-4894-4f6c-b54b-f35d84903cf3)

---

6. View the performance of the kernel module after clearing out the vulnerability:
   
```bash
/usr/bin/time -v sudo perf stat -a -e cycles,instructions,cache-misses \
    bash -c "sudo insmod www_vuln.ko; sleep 2; sudo rmmod www_vuln"
```

![Capture 8](https://github.com/user-attachments/assets/2956e9ee-03e1-47db-87e6-48092ceadc8e)

![Capture 9](https://github.com/user-attachments/assets/576a3b5e-d1dd-46fa-86e8-8abecb2cb338)

---

## Write-What-Where Condition Vulnerability Performance Analysis

This section demonstrates the comparison of the performance **before** and **after** the vulnerability was fixed.

---

### 🧾 **System Performance Comparison Table (CWE-123 Vulnerability)**

| **Metric**                       | **Before Fix** | **After Fix** | **Change / Observation**                        |
| -------------------------------- | -------------- | ------------- | ----------------------------------------------- |
| **CPU Cycles**                   | Not Supported  | Not Supported | Not available (likely due to system limitation) |
| **Instructions**                 | Not Supported  | Not Supported | Not available                                   |
| **Cache Misses**                 | Not Supported  | Not Supported | Not available                                   |
| **Elapsed (Wall Clock) Time**    | 2.14 seconds   | 2.07 seconds  | ⬇ Slight improvement after fix                  |
| **User Time**                    | 0.04 seconds   | 0.04 seconds  | No change                                       |
| **System Time**                  | 0.04 seconds   | 0.04 seconds  | No change                                       |
| **Percent CPU Usage**            | 4%             | 4%            | No change                                       |
| **Max Resident Set Size**        | 5584 KB        | 5592 KB       | ⬆ Minor increase                                |
| **Voluntary Context Switches**   | 31             | 29            | ⬇ Slight improvement                            |
| **Involuntary Context Switches** | 51             | 43            | ⬇ Fewer forced switches after fix               |
| **Page Faults (Minor)**          | 1986           | 1985          | Almost identical                                |
| **Page Faults (Major)**          | 0              | 0             | No change                                       |
| **Swaps**                        | 0              | 0             | No change                                       |
| **Signals Delivered**            | 0              | 0             | No change                                       |
| **Exit Status**                  | 0              | 0             | No change                                       |

---

## Conclusion: 

After clearing the CWE-123 vulnerability, minor improvements were observed in **context switching** and **execution time**, indicating a slightly more efficient and stable system.

---
## 📁 Project Files

View and contribute to the project on GitHub:

**GitHub:** [https://github.com/Arisudan/Linux](https://github.com/Arisudan/Linux)

---

