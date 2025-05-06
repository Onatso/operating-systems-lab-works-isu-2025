# 🖥️ Operating Systems Lab Works — ISU 2025

> 💡 This repository contains lab work for the course **“Operating Systems”** at ISU in 2025.

> ⚠️ **NOTE**:  
> I formatted the report in **English** because it looks **much nicer and more professional** that way!  
> (Отчёт на английском, потому что **это крайне концептуально**.)



---

## 📚 Table of Contents

- [📘 Lab Work №1: Compilation, Assembly & IPC](#-lab-work-1-compilation-assembly--ipc)
  - [🧪 Step 1: GCC, Assembly & System Interaction](#-step-1-gcc-assembly--system-interaction)
    - [🧪 GCC, Assembly, and Optimization](#-gcc-assembly-and-optimization)
    - [🧾 Source Code (C++)](#-source-code-c)
    - [⚙️ Compilation (Assembly Generation)](#-compilation-assembly-generation)
    - [🔍 Unoptimized Assembly Analysis (`-O0`)](#-unoptimized-assembly-analysis-o0)
    - [🔍 Key Features of Unoptimized Code](#-key-features-of-unoptimized-code)
    - [📦 Modular Conversion & Makefile](#-modular-conversion--makefile)
    - [📁 Project Structure](#-project-structure)
    - [🔄 Key Improvements](#-key-improvements)
  - [🧪 Step 2: Parallelism with `fork`, Shared Memory, and Semaphores](#-step-2-parallelism-with-fork-shared-memory-and-semaphores)
    - [⚙️ Key Improvements](#-key-improvements-1)
    - [🗂️ New Project Structure](#-new-project-structure)
    - [📦 Project Structure (Final)](#-project-structure-final)

- [📘 Lab Work №2: Installing Linux](#-lab-work-2-installing-linux)
  - [🛠️ Installation Process](#-installation-process)
  - [🌀 Going Further](#-going-further)
  - [🔐 SSH Setup](#-ssh-setup)
  - [🌐 Router Configuration](#-router-configuration)
  - [✅ Summary](#-summary)

---

## 📘 Lab Work №1: Compilation, Assembly & IPC
[![Arch Linux](https://img.shields.io/badge/Linux-Arch-blue?logo=arch-linux&logoColor=white)](https://archlinux.org/)  
[![GCC](https://img.shields.io/badge/Compiler-GCC-orange?logo=gnu&logoColor=white)](https://gcc.gnu.org/)  
[![POSIX](https://img.shields.io/badge/IPC-POSIX%20Semaphores-blueviolet?logo=linux&logoColor=white)](#)  
[![Build - Make](https://img.shields.io/badge/Build-Make-informational?logo=gnubash&logoColor=white)](#)

---


### 🧪 Step 1: GCC, Assembly & System Interaction

In this step, I explored the **GCC compiler**, **assembly language**, and how a program interacts with the **operating system**. I also worked with **Makefile** and **Git**.

> 🧵 **Task**:  
> Write a program in **C**, **C++**, **Pascal/FPC**, or other compiled languages, and translate it into **assembly** using different optimization options.

I chose to calculate the **factorial** in **C++**.

---

### 🧪 GCC, Assembly, and Optimization

I chose to implement a simple **recursive factorial** in C++:

---

### 🧾 Source Code (C++)

I wrote the following code:

```cpp
#include <iostream>

int factorial(int n) {
	if (n <= 1) return 1;
	return n * factorial(n - 1);
}

int main() {
	std::cout << factorial(5);
	return 0;
}
```

---

### ⚙️ Compilation (Assembly Generation)

I compiled the program with the following command:

```bash
g++ -S -O0 -masm=intel factorial.cpp -o factorial_O0.s
```
-S — generate assembler code.

-O0 — disable optimizations.

-masm=intel — Intel syntax (default AT&T).

### 🔍 Unoptimized Assembly Analysis (`-O0`)

```nasm
.file   "factorial.cpp"
.intel_syntax noprefix
.text

# ==================== FACTORIAL FUNCTION ====================
.globl  _Z9factoriali
.def    _Z9factoriali; .scl 2; .type 32; .endef
.seh_proc   _Z9factoriali
_Z9factoriali:
.LFB1573:
    # Function prologue
    push    rbp
    .seh_pushreg    rbp
    mov     rbp, rsp            # Setup new stack frame
    sub     rsp, 32             # Allocate 32 bytes stack space
    .seh_stackalloc 32
    .seh_endprologue

    mov     DWORD PTR 16[rbp], ecx  # Store parameter 'n'
    
    # Base case check: if (n <= 1)
    cmp     DWORD PTR 16[rbp], 1
    jg      .L2                 # Jump if n > 1
    
    mov     eax, 1              # Return 1
    jmp     .L3                 # Exit function

.L2:
    # Recursive case preparation
    mov     eax, DWORD PTR 16[rbp]  # eax = n
    sub     eax, 1              # eax = n-1
    mov     ecx, eax             # Set argument for call
    call    _Z9factoriali        # Recursive call
    
    imul    eax, DWORD PTR 16[rbp] # Multiply result by n

.L3:
    # Function epilogue
    add     rsp, 32
    pop     rbp
    ret
.seh_endproc

# ==================== MAIN FUNCTION ====================
.def    __main; .scl 2; .type 32; .endef
.globl  main
.def    main; .scl 2; .type 32; .endef
.seh_proc   main
main:
.LFB1574:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 32             # Stack alignment
    
    call    __main              # Runtime initialization
    
    # Call factorial(5)
    mov     ecx, 5              # Set argument n = 5
    call    _Z9factoriali       # Function call
    
    # Output result via cout
    mov     edx, eax            # Store result
    mov     rcx, QWORD PTR .refptr._ZSt4cout[rip]
    call    _ZNSolsEi           # Call output operator
    
    mov     eax, 0              # Return 0
    add     rsp, 32
    pop     rbp
    ret
.seh_endproc

# The rest of the code is utility sections for initializing the C++ environment
# (static initialization of cout and destructors)
	.def	__tcf_0;	.scl	3;	.type	32;	.endef
	.seh_proc	__tcf_0
__tcf_0:
.LFB2056:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	lea	rcx, _ZStL8__ioinit[rip]
	call	_ZNSt8ios_base4InitD1Ev
	nop
	add	rsp, 32
	pop	rbp
	ret
	.seh_endproc
	.def	_Z41__static_initialization_and_destruction_0ii;	.scl	3;	.type	32;	.endef
	.seh_proc	_Z41__static_initialization_and_destruction_0ii
_Z41__static_initialization_and_destruction_0ii:
.LFB2055:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	mov	DWORD PTR 16[rbp], ecx
	mov	DWORD PTR 24[rbp], edx
	cmp	DWORD PTR 16[rbp], 1
	jne	.L9
	cmp	DWORD PTR 24[rbp], 65535
	jne	.L9
	lea	rcx, _ZStL8__ioinit[rip]
	call	_ZNSt8ios_base4InitC1Ev
	lea	rcx, __tcf_0[rip]
	call	atexit
.L9:
	nop
	add	rsp, 32
	pop	rbp
	ret
	.seh_endproc
	.def	_GLOBAL__sub_I__Z9factoriali;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I__Z9factoriali
_GLOBAL__sub_I__Z9factoriali:
.LFB2057:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	mov	edx, 65535
	mov	ecx, 1
	call	_Z41__static_initialization_and_destruction_0ii
	nop
	add	rsp, 32
	pop	rbp
	ret
	.seh_endproc
	.section	.ctors,"w"
	.align 8
	.quad	_GLOBAL__sub_I__Z9factoriali
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	_ZNSolsEi;	.scl	2;	.type	32;	.endef
	.def	_ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
	.def	_ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	atexit;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr._ZSt4cout, "dr"
	.globl	.refptr._ZSt4cout
	.linkonce	discard
.refptr._ZSt4cout:
	.quad	_ZSt4cout
```
---
### 🔍 Key Features of Unoptimized Code

1) **Recursion instead of loop**  
No tail recursion optimization → each call creates new stack frame

2) **Variable handling**  
Parameter `n` constantly saved/read from stack (`DWORD PTR 16[rbp]`), though could stay in register

3) **Redundant operations**  
Extra `sub rsp, 32`/`add rsp, 32` even when local variables not used

---

### 📦 Modular Conversion & Makefile
Converted program into modular structure and developed Makefile

---

### 📁 Project Structure
I came up with this file organization:

```
project/
├── src/
│   ├── main.cpp     # Main program
│   ├── factorial.h  # Function header
│   └── factorial.cpp# Implementation of factorial
├── Makefile         # Build script
└── bin/             # (Will be created after build)
```

`main.cpp`

```cpp
#include <iostream>
#include "factorial.h"

int main() {
    std::cout << factorial(5);
    return 0;
}
```

`factorial.h`

```cpp
#ifndef FACTORIAL_H
#define FACTORIAL_H

int factorial(int n);

#endif
```

`factorial.cpp`

```cpp
#include "factorial.h"

int factorial(int n) {
	if (n <= 1) return 1;
	return n * factorial(n - 1);
}
```

`Makefile`

```makefile
# Compiler and flags
CXX      = g++
CXXFLAGS = -Wall -Wextra -I./src -std=c++17
LDFLAGS  = 
TARGET   = bin/program

# Source files and objects
SRC_DIR = src
SRC     = $(wildcard $(SRC_DIR)/*.cpp)
OBJ     = $(patsubst $(SRC_DIR)/%.cpp,obj/%.o,$(SRC))

# Main purpose of the build
all: create_dirs $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Rule for object files
obj/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories bin/ and obj/
create_dirs:
	mkdir -p bin obj

# Cleaning up the project
clean:
	rm -rf bin obj

# Rebuild
rebuild: clean all

# Starting the program
run: all
	./$(TARGET)

.PHONY: all clean rebuild run
```

---

### 🧪 Step 2: Parallelism with `fork`, Shared Memory, and Semaphores

After successfully building the project on my **Linux laptop** using the `make` command, I went further and **improved the program** by introducing **parallel processing** using **Linux system calls**.

> 🎯 **Goal**:  
> Implement **synchronized access** to a shared resource using **multiple processes**.

---

### ⚙️ Key Improvements

I implemented **parallel access** to a **shared variable** using the following mechanisms:

- 🧬 `fork()` — creates a new process (child).
- 🔒 `sem_t`, `sem_init`, `sem_wait`, `sem_post` — **POSIX semaphores** for safe access.
- 🧠 `mmap()` — **shared memory** between processes.

---

### 🗂️ New Project Structure

I created a new project, structurally similar to the previous one, but with support for interprocess communication:

`main.cpp`

```cpp
#include <iostream>
#include <unistd.h>     // fork
#include <sys/mman.h>   // mmap
#include <semaphore.h>  // sem_t, sem_init, etc.
#include <sys/wait.h>   // wait
#include "factorial.h"  // factorial function

int main() {
    // Create shared memory for the result
    int* result = static_cast<int*>(mmap(nullptr, sizeof(int),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    if (result == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Create a semaphore in shared memory
    sem_t* sem = static_cast<sem_t*>(mmap(nullptr, sizeof(sem_t),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    if (sem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    sem_init(sem, 1, 0); // 1 - for interprocess use, 0 - initial value

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process: calculates factorial and writes to shared memory
        *result = factorial(5);

        // We signal that the result is ready
        sem_post(sem);

        // Exiting a child process
        return 0;
    }
    else {
        // Parent process: waiting for signal from semaphore
        sem_wait(sem);

        // Reads the result
        std::cout << "Factorial calculated in child process: " << *result << std::endl;

        // Waits for the child process to complete
        wait(nullptr);

        // Resource Cleanup
        sem_destroy(sem);
        munmap(result, sizeof(int));
        munmap(sem, sizeof(sem_t));

        return 0;
    }
}
```

`Makefile`:
Added -pthread to CXXFLAGS and LDFLAGS.

---

Using the `make` command on my **linux laptop** I built the project.

## 📘 Lab Work №2: Installing Linux

[![Arch Linux](https://img.shields.io/badge/Linux-Arch-blue?logo=arch-linux&logoColor=white)](https://archlinux.org/)
[![Gentoo](https://img.shields.io/badge/Linux-Gentoo-purple?logo=gentoo&logoColor=white)](https://www.gentoo.org/)
[![SSH Enabled](https://img.shields.io/badge/SSH-enabled-green?logo=openssh&logoColor=white)](#)

I decided it would be more engaging to install a new Linux distribution on my personal laptop rather than inside a virtual machine (it was previously running Ubuntu). Installation was done via a bootable USB flash drive.

---

### 🛠️ Installation Process

Using the resources from the [Arch Wiki (EN)](https://wiki.archlinux.org/) and [Arch Wiki (RU)](https://wiki.archlinux.org/title/Main_page_(Русский)), and with guidance from a colleague, I successfully installed **Arch Linux**.

> 📹 **Installation video**:  
> [![Watch on YouTube](https://img.shields.io/badge/Watch%20Video-%F0%9F%93%BA-red?logo=youtube&logoColor=white)](https://youtu.be/i5FqydpN3-E)

To solidify my understanding, I repeated the installation process **two more times**.

---

### 🌀 Going Further

Later, I attempted to install **Gentoo Linux**.  
As of now, the process is ongoing — Gentoo requires a significantly deeper level of configuration and understanding.

---

### 🔐 SSH Setup

After successfully installing Arch, I configured the **SSHD server** to enable remote access via SSH.

> 📹 **SSHD configuration video**:  
> [![Watch on YouTube](https://img.shields.io/badge/Watch%20Video-%F0%9F%93%BA-red?logo=youtube&logoColor=white)](https://youtu.be/S8vru6sC-OA)

---

### 🌐 Router Configuration

I began setting up **port forwarding** on my home router to allow external SSH access.

<details>
<summary>📋 Router Configuration Story</summary>

- I didn’t have access to the router's admin interface initially.
- Contacted **Rostelecom** support — a technician tried to forward ports remotely, but failed.
- Eventually received admin credentials and set everything up manually.
- Despite correct configuration, my colleague still saw the error:  
  ❌ `"Connection refused"`

> 📹 **Router troubleshooting video**:  
> [![Watch on YouTube](https://img.shields.io/badge/Watch%20Video-%F0%9F%93%BA-red?logo=youtube&logoColor=white)](https://youtu.be/J5QIRlPyFA4)

</details>

---

## ✅ Summary

| Task                            | Status    |
|---------------------------------|-----------|
| Arch Linux installation         | ✅ Done (3×) |
| SSHD server configuration       | ✅ Done     |
| Router port forwarding          | ⚠️ Partially done |
| Gentoo installation             | 🔄 In Progress |

---

## 📎 Additional Notes

- All installation steps were done without a graphical installer.
- Arch Linux was installed using manual partitioning, base system setup, and post-install configurations.
- SSH access setup included creating a user, enabling the `sshd` service, and setting up firewall rules (if any).

---

