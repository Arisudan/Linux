# 📈 32-bit Buffer Overflow Performance Analysis

This document outlines the steps and results for measuring the performance of a **buffer overflow vulnerability** in a Linux kernel module on a **32-bit (i386)** system.

---

## Step-by-Step Guide

### 1. Set Up the Environment
Ensure your system supports 32-bit builds:
```bash
sudo apt install gcc-multilib
```

### 2. Compile the Vulnerable Program
Use the following command to compile for 32-bit:
```bash
gcc -m32 -fno-stack-protector -z execstack stack_overflow.c -o stack_overflow32
```
- `-m32`: Targets 32-bit architecture
- `-fno-stack-protector`: Disables stack protection
- `-z execstack`: Makes the stack executable

---

  ## Error for unable to acquire the dpkg frontend lock

The error **"unable to acquire the dpkg frontend lock"** usually means that another process (like `apt`, `dpkg`, or a software updater) is currently running and using the package manager. Here's how to fix it:

#### A. **Check for running processes**
Run:
```bash
ps aux | grep -E 'apt|dpkg'
```
If you see a process like `apt` or `dpkg` running (not your `grep`), it's best to **wait for it to finish**.

---

#### B. **If it’s stuck or you’re sure no update is running**

 Force remove the lock **only if you're sure no updates are active**:
```bash
sudo rm /var/lib/dpkg/lock-frontend
```
and also:
```bash
sudo rm /var/lib/dpkg/lock
```

Then reconfigure `dpkg` just in case:
```bash
sudo dpkg --configure -a
```

---

#### C. **Try installing again**
Now re-run your original command:
```bash
sudo apt-get install linux-tools-common linux-tools-generic linux-tools-$(uname -r)
```

---

### 3. Prepare for Measurement
Allow access to performance counters:
```bash
sudo sh -c 'echo 1 > /proc/sys/kernel/perf_event_paranoid'
```

---

### 4. Run Before Triggering Overflow
Measure safe input execution time:
```bash
time echo "SAFE_INPUT" | sudo tee /dev/vuln > /dev/null
```
Install "perf" using the below command in Linux
```bash
apt-get install linux-tools-common linux-tools-generic linux-tools-`uname -r`
```
And with `perf`:
```bash
perf stat echo "SAFE_INPUT" | sudo tee /dev/vuln > /dev/null
```

---

## Performance Comparison: Safe Input vs Overflow Payload (32-bit Ubuntu) - For a Stack Overflow Vulnerability

Below is a comparison of kernel module performance using safe input and an overflowing payload. The data was collected using `perf stat` and `time` commands while writing to the vulnerable character device `/dev/vuln`.

| **Metric**                 | **SAFE_INPUT**               | **Overflow Payload (A...A)**              |
|---------------------------|------------------------------|-------------------------------------------|
| `task-clock (msec)`       | 1.025309                     | 0.873880                                  |
| `% CPUs utilized`         | 0.283                        | 0.472                                     |
| `context-switches`        | 2                            | 0                                         |
| `cpu-migrations`          | 0                            | 0                                         |
| `page-faults`             | 47                           | 43                                        |
| `cycles`                  | *not supported*              | *not supported*                           |
| `instructions`            | *not supported*              | *not supported*                           |
| `branches`                | *not supported*              | *not supported*                           |
| `branch-misses`           | *not supported*              | *not supported*                           |
| `elapsed time (sec)`      | 0.003619159                  | 0.001850336                               |


### 🔍 Observations

- **CPU Utilization** increased under the overflow scenario, indicating more aggressive resource usage.
- **Context Switches** dropped to zero with the overflow input, possibly due to altered or skipped system-level handling.
- **Elapsed Execution Time** was shorter with the overflow input, which may indicate an abrupt return or early exit caused by buffer overflows.
- **Page Faults** decreased slightly, which might reflect differences in memory access patterns between safe and overflowing inputs.

---

### 5. Run After Triggering Overflow
Send overflow input:
```bash
time echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```
```bash
perf stat echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```
---

## 🛡️ Post-Fix Performance Comparison (32-bit Ubuntu) - After the Vulnerability is been fixed

This section presents the system performance metrics gathered using `perf stat` after fixing the stack overflow vulnerability in the `vuln_module`. Below are comparisons for both safe input and an input that previously triggered the vulnerability.

| Metric                | SAFE_INPUT             | Long 'A' Input                                |
|-----------------------|------------------------|-----------------------------------------------|
| **Task Clock (msec)** | 0.864282               | 0.908874                                      |
| **CPU Utilized**      | 0.447 CPUs             | 0.693 CPUs                                    |
| **Context Switches**  | 1                      | 0                                             |
| **CPU Migrations**    | 0                      | 0                                             |
| **Page Faults**       | 46                     | 43                                            |
| **Cycles**            | *Not Supported*        | *Not Supported*                               |
| **Instructions**      | *Not Supported*        | *Not Supported*                               |
| **Branches**          | *Not Supported*        | *Not Supported*                               |
| **Branch Misses**     | *Not Supported*        | *Not Supported*                               |
| **Elapsed Time (sec)**| 0.001934368            | 0.001311939                                   |


### Summary
- The vulnerability fix does not significantly impact performance.
- Slight variation in `task-clock` and `CPU utilization` is observed depending on the input length.

---

## 📊 Performance Table: Before and After Stack Overflow

| **Condition**      | **Real Time** | **User Time** | **Sys Time** | **Instructions** | **Cycles** | **Time Elapsed** | **Notes**                              |
|--------------------|---------------|---------------|--------------|------------------|------------|------------------|----------------------------------------|
| **Before Overflow** | 0.0036s       | 0.0016s       | 0.0020s      | Not Supported    | Not Supported  | 0.0036s          | Normal execution                       |
| **After Overflow**  | 0.0019s       | 0.0009s       | 0.0010s      | Not Supported    | Not Supported  | 0.0019s          | Abrupt return or early exit due to overflow |

---

## ✅ Conclusion

- Stack overflow can cause abrupt returns or bypass normal system handling, as seen in the reduced time and zero context switches.
- Performance impact is minimal, but behavioral anomalies indicate serious security risks.
- Fixing the vulnerability restores predictable execution even with long or malformed input.

---
