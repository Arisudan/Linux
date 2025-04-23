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

### 5. Run After Triggering Overflow
Trigger the overflow with crafted input:
```bash
time echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```
```bash
perf stat echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | sudo tee /dev/vuln > /dev/null
```

---

## Performance Table (Example)

| Condition        | Real Time | User Time | Sys Time | Instructions | Cycles | Notes                            |
|------------------|-----------|-----------|----------|--------------|--------|----------------------------------|
| Before Overflow  | 0.004s    | 0.001s    | 0.003s   | 10,200       | 3,800  | Normal execution                 |
| After Overflow   | 0.005s    | 0.001s    | 0.004s   | 12,000       | 4,000  | Return address may be corrupted |

---

## Conclusion

- 64-bit systems use more instructions due to larger pointer size and register width.
- Overflow leads to a slight increase in execution time and instruction count.
- Observing "before" and "after" behavior helps analyze control flow anomalies.

---

