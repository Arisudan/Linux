Here's a complete flow for how you can **build**, **run**, and **profile** your kernel module (`www_vuln.c`) using both `perf` and `/usr/bin/time`.

Since you’re dealing with a **kernel module**, we can't directly use `perf stat ./www_vuln` like with user-space apps, but we can still monitor **system-wide effects** when the module is loaded and unloaded.

---

## ✅ Full Workflow: Compile, Insert Module, Profile with `perf` and `time`

### 🔹 1. `Makefile` (for building kernel module)

Create this `Makefile` in the same directory as `www_vuln.c`:

```makefile
obj-m += www_vuln.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

---

### 🔹 2. Compile the Module

```bash
make
```

You should now have `www_vuln.ko`

---

### 🔹 3. Monitor System Performance While Inserting Module

```bash
/usr/bin/time -v sudo perf stat -a -e cycles,instructions,cache-misses \
    bash -c "sudo insmod www_vuln.ko; sleep 2; sudo rmmod www_vuln"
```

* `-a`: system-wide
* `sleep 2`: lets the module run for a short time
* `/usr/bin/time -v`: collects memory and time info
* `perf stat`: collects CPU and cache data

You can redirect output if you want:

```bash
/usr/bin/time -v sudo perf stat -a -e cycles,instructions,cache-misses \
    bash -c "sudo insmod www_vuln.ko; sleep 2; sudo rmmod www_vuln" \
    > perf_output.txt 2>&1
```

---

### 🔹 4. Clean Build

```bash
make clean
```

---

### 🧾 Sample Output (perf + time)

You’ll get combined metrics like:

* **CPU cycles**
* **Instructions executed**
* **Cache misses**
* **Elapsed time**
* **Max resident set size**
* **User/system time**

---

Would you like me to auto-generate a shell script (`profile_module.sh`) to wrap all this?
