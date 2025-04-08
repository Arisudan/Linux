# Linux Command Reference Guide

This repository contains documentation for commonly used Linux commands. It is designed to help beginners and intermediate users understand what each command does, how to use it, and where it fits in daily Linux usage.

---

## Table of Contents

1. [Introduction](#1-introduction)  
2. [Command Reference](#2-command-reference)  
3. [Usage Examples and Explanations](#3-usage-examples-and-explanations)  
4. [Getting Started](#4-getting-started)  
5. [Repository Structure](#5-repository-structure)  
6. [Contributing](#6-contributing)  
7. [License](#7-license)

---

## 1. Introduction

Linux commands are essential tools used in system navigation, file manipulation, software management, debugging, and automation. This guide serves as a reference to help users understand and effectively use these commands.

---

## 2. Command Reference

| Command / Concept         | Description                                      |
|--------------------------|--------------------------------------------------|
| `chmod`                  | Change file or directory permissions             |
| `mkdir`                  | Create new directories                           |
| `gdb`                    | GNU Debugger for C/C++ code                      |
| `ln`                     | Create hard links                                |
| `ln -s`                  | Create symbolic (soft) links                     |
| `sudo apt update`        | Update package list (Debian-based systems)       |
| `gedit`                  | Open a graphical text editor                     |
| `vi` / `vim`             | Terminal-based text editor                       |
| `fork()`                 | System call to create a child process            |
| `copy-on-write`          | Memory optimization concept used with `fork()`   |
| `nl`                     | Add line numbers to file content                 |
| `man`, `tail`            | Manual page viewer and file output viewer        |
| `tree`                   | Display directory structure in tree format       |
| `ps -l`                  | Detailed process listing                         |
| `./`, `+x`               | Execute scripts, make them executable            |
| `rm`, `rm -r`            | Delete files and directories                     |
| `ELF`                    | Executable and Linkable Format for binaries      |
| `dialog`, `kdialog`      | Interactive dialog boxes in scripts              |
| `.,-3`, `.,+3`           | Line addressing in `vi`                          |
| `1,$d`                   | Delete all lines in a file using `vi` or `sed`   |

---

## 3. Usage Examples and Explanations

### `chmod` – Change Permissions

#### What it Does:
`chmod` is used to change the access permissions of files and directories. Every file in Linux has permissions for three types of users: the file **owner (user)**, the **group**, and **others**. These permissions can be read (`r`), write (`w`), and execute (`x`).

#### Permission Types:

| Permission | Symbol | Description                             |
|------------|--------|-----------------------------------------|
| Read       | `r`    | Allows viewing the contents              |
| Write      | `w`    | Allows modifying or deleting             |
| Execute    | `x`    | Allows running the file as a program     |

#### Categories of Users:

| Category | Symbol | Description                    |
|----------|--------|--------------------------------|
| User     | `u`    | The file owner                 |
| Group    | `g`    | Users who are in the file's group |
| Others   | `o`    | All other users                |
| All      | `a`    | Applies to user, group, and others |

#### Numeric (Octal) Permissions:

| Octal | Binary | Symbolic | Meaning       |
|-------|--------|----------|---------------|
| 7     | 111    | rwx      | Read, write, execute |
| 6     | 110    | rw-      | Read, write only    |
| 5     | 101    | r-x      | Read and execute    |
| 4     | 100    | r--      | Read only           |
| 0     | 000    | ---      | No permission       |

#### Examples:
```bash
chmod 755 script.sh       # rwxr-xr-x: owner can read/write/execute; others can read/execute
chmod 644 file.txt        # rw-r--r--: owner can read/write; others can only read
chmod 700 private.sh      # rwx------: only owner has full access
chmod u+x script.sh       # Add execute permission for the user
chmod go-rw file.txt      # Remove read/write from group and others
chmod a=r mydoc.txt       # Set read-only for all
chmod u=rw,g=r,o= file.txt  # Owner: rw, Group: r, Others: none
```

---

Let me know if you’d like this added as a separate Markdown file under `commands/` (like `commands/chmod.md`) too!

---

### `mkdir` – Make Directory

**Purpose:**  
Creates a new directory.

**Syntax:**
```bash
mkdir [directory_name]
mkdir -p parent/child     # Create nested directories
```

---

### `gdb` – GNU Debugger

**Purpose:**  
Used to debug C/C++ programs.

**Steps:**
1. Compile with debug info: `g++ file.cpp -g`
2. Start debugger: `gdb ./a.out`

---

### `ln` – Hard Link

**Purpose:**  
Creates a second name for a file, pointing to the same data.

**Syntax:**
```bash
ln original.txt hardlink.txt
```

---

### `ln -s` – Symbolic Link

**Purpose:**  
Creates a shortcut pointing to another file or directory.

**Syntax:**
```bash
ln -s /path/to/file symlink
```

---

### `sudo apt update` – Update Repositories

**Purpose:**  
Fetches latest package info. Run before install/upgrade.

**Syntax:**
```bash
sudo apt update
```

---

### `gedit` – Graphical Editor

**Purpose:**  
Opens a text file in the GNOME graphical editor.

**Syntax:**
```bash
gedit file.txt
```

---

### `vi` / `vim` – Terminal Text Editor

**Modes:**
- `i` – Insert
- `Esc` – Command
- `:w` – Save
- `:q` – Quit
- `:wq` – Save and quit

**Common Commands:**
```bash
dd     # Delete line
yy     # Copy line
p      # Paste
u      # Undo
/%     # Search
:%s/old/new/g   # Replace all
```

---

### `fork()` – Process Creation

**Purpose:**  
Creates a child process that runs in parallel.

**Syntax (C):**
```c
pid_t pid = fork();
```

---

### `copy-on-write` – Memory Optimization

**Concept:**  
Parent and child initially share memory pages. Actual copy happens only when write occurs.

---

### `nl` – Number Lines

**Purpose:**  
Displays file contents with numbered lines.

**Syntax:**
```bash
nl filename
```

---

### `man`, `tail` – Manual & Output Viewer

- `man`: View command manual
- `tail`: View last lines of a file

**Examples:**
```bash
man tail
tail -n 3 filename     # Last 3 lines
tail +2 filename       # From line 2 onward
```

---

### `tree` – Directory Tree Viewer

**Purpose:**  
Displays the file/folder hierarchy visually.

**Syntax:**
```bash
tree /path
```

---

### `ps -l` – Process Info

**Purpose:**  
Detailed listing of running processes.

**Syntax:**
```bash
ps -l
```

---

### `./`, `+x` – Executing Files

- `+x`: Add execute permission  
- `./file`: Run script in current directory

**Example:**
```bash
chmod +x myscript.sh
./myscript.sh
```

---

### `rm`, `rm -r` – Remove Files/Dirs

**Purpose:**  
- `rm`: Delete files  
- `rm -r`: Delete folders recursively

**Examples:**
```bash
rm file.txt
rm -r myfolder/
```

---

### `ELF` – Executable Format

**Explanation:**  
ELF = Executable and Linkable Format (used in Linux binaries)

**View Format:**
```bash
file a.out
```

---

### `dialog`, `kdialog` – Interactive Dialogs

**Purpose:**  
Used in shell scripts to show message boxes.

- `dialog`: Terminal UI
- `kdialog`: KDE GUI

**Examples:**
```bash
dialog --msgbox "Welcome" 10 30
kdialog --msgbox "Welcome"
```

---

### `.,-3`, `.,+3` – `vi` Line Ranges

**Use Case:**  
Apply action to lines relative to the current one.

**Examples:**
```vim
:.,+2d    # Delete current and next 2 lines
:.,-1d    # Delete current and previous 1 line
```

---

### `1,$d` – Delete All Lines

**In `vi`:**
```vim
:1,$d
```
---

## 4. Getting Started

If you're new to Linux:

1. Use a virtual machine or dual-boot setup with Ubuntu/Debian.
2. Open a terminal (`Ctrl+Alt+T`) and try basic commands.
3. Refer to this guide or use `man [command]` for details.

---

## 5. Repository Structure

```
Linux/
├── README.md
├── LICENSE
├── commands/                   # Markdown documentation per command
├── examples/                   # Code examples and scripts
├── assets/                     # Images or diagrams (optional)
```

---

## 6. Contributing

To contribute:

1. Fork this repository
2. Create a new branch
3. Add or update markdown files under `commands/` or `examples/`
4. Open a pull request with a clear description

---

## 7. License

This project is licensed under the [MIT License](LICENSE).

---
