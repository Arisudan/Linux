# 📈 64-bit Buffer Overflow Performance Analysis

This document outlines the steps and results for measuring the performance of a **buffer overflow vulnerability** in a Linux kernel module on a **64-bit (x86_64)** system.

---

## Step-by-Step Guide

### 1. Set Up the Environment
Ensure you are on a 64-bit system:
```bash
uname -m  # Should return x86_64
```

### 2. Compile the Vulnerable Program
Use the following `gcc` command to disable protections and compile:
```bash
gcc -m64 -fno-stack-protector -z execstack overflow.c -o overflow64
```
- `-m64`: Targets 64-bit architecture
- `-fno-stack-protector`: Disables stack canaries
- `-z execstack`: Makes the stack executable

### 3. Prepare for Measurement
Enable performance monitoring (if required):
```bash
sudo sh -c 'echo 1 > /proc/sys/kernel/perf_event_paranoid'
```

### 4. Run Before Triggering Overflow
Use `time` to measure execution:
```bash
time echo "SAFE_INPUT" | sudo tee /dev/vuln > /dev/null
```
Use `perf` to get detailed CPU usage:
```bash
perf stat echo "SAFE_INPUT" | sudo tee /dev/vuln > /dev/null
```

---

## Performance Comparison: Safe Input vs Overflow Payload (64-bit Ubuntu) - For a Stack Overflow Vulnerability

Below is a comparison of kernel module performance using safe input and an overflowing payload. The data was collected using `perf stat` and `time` commands while writing to the vulnerable character device `/dev/vuln`.


| **Metric**                 | **SAFE_INPUT**               | **Overflow Payload (A...A)**              |
|---------------------------|------------------------------|-------------------------------------------|
| `task-clock (msec)`       | 0.510                        | 0.873880                                  |
| `% CPUs utilized`         | 0.428                        | 0.472                                     |
| `context-switches`        | 0                            | 0                                         |
| `cpu-migrations`          | 0                            | 0                                         |
| `page-faults`             | 69                           | 43                                        |
| `cycles`                  | 1,641,356                    | *not supported*                           |
| `instructions`            | 1,329,532                    | *not supported*                           |
| `branches`                | 242,112                      | *not supported*                           |
| `branch-misses`           | 8,490                        | *not supported*                           |
| `elapsed time (sec)`      | 0.001179516                  | 0.001850336                               |


## 🔍 Observations

- **Safe input** results in measurable instruction execution and branch data.
- **Overflow input** on 64-bit takes longer to execute, suggesting non-trivial control flow alterations.
- **Page faults** reduce during overflow, possibly due to premature exit or bypassed logic.
- **CPU utilization** is slightly higher during overflow, potentially from exception handling or abnormal memory access patterns.

---

### 5. Run After Triggering Overflow
Trigger the overflow with crafted input:
```bash
time echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```
```bash
perf stat echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```
---

## 🛡️ Post-Fix Performance Comparison (64-bit Ubuntu) - After the Vulnerability Has Been Fixed

This section presents the system performance metrics gathered using `perf stat` on a 64-bit system **after fixing the stack overflow vulnerability** in the `vuln_module`. The comparisons are based on both safe input and a long sequence of `'A'` characters that previously triggered the vulnerability.


| **Metric**              | **SAFE_INPUT** | **Overflowing 'A' Input**              |
|-------------------------|----------------|----------------------------------------|
| **Task Clock (msec)**   | -              | 0.420                                  |
| **CPU Utilized**        | -              | 0.523 CPUs                             |
| **Context Switches**    | -              | 0                                      |
| **CPU Migrations**      | -              | 0                                      |
| **Page Faults**         | -              | 68                                     |
| **Cycles**              | -              | 1,500,775                              |
| **Instructions**        | -              | 1,311,208                              |
| **Branches**            | -              | 238,589                                |
| **Branch Misses**       | -              | 8,118                                  |
| **Elapsed Time (sec)**  | 0.011          | 0.000811037                            |
| **User Time (sec)**     | 0.003          | 0.000858000                            |
| **Sys Time (sec)**      | 0.007          | 0.000000000                            |

### Summary
- The fixed kernel module on 64-bit architecture executed efficiently with no faults or crashes.
- All metrics were successfully recorded for the overflow input, indicating stable behavior.
- Minor differences in page faults and CPU usage are acceptable, given improved security and system integrity.

---

## Overall Performance Table (64-bit System)

This table compares performance metrics before and after the stack overflow occurred, highlighting the impact of the overflow on system behavior and efficiency.

| **Condition**     | **Real Time** | **User Time** | **Sys Time** | **Instructions** | **Cycles** | **Branch Misses** | **Notes**                            |
|------------------|---------------|---------------|--------------|------------------|------------|--------------------|--------------------------------------|
| Before Overflow  | 0.011s        | 0.003s        | 0.007s       | Not Captured     | Not Captured | Not Captured      | Normal echo command execution        |
| After Overflow   | 0.0008s       | 0.00085s      | 0.0000s      | 1,311,208        | 1,500,775   | 8,118              | Handled long input securely post-fix |

### Summary
- **Before Overflow:** Echo command ran with regular input, system utilized more real and system time.
- **After Overflow:** Performance counters show stable behavior with secure handling of potentially malicious input.
- Fix implementation greatly improves execution efficiency while capturing detailed low-level stats.
- 
---

## Conclusion

- 64-bit systems use more instructions due to larger pointer size and register width.
- Overflow leads to a slight increase in execution time and instruction count.
- Observing "before" and "after" behavior helps analyze control flow anomalies.

---

### Author: ARISUDAN TH
GitHub: https://github.com/Arisudan

