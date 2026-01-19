# Compile and Run Bare-Metal Code on Xilinx Zynq-7000

---

## (A) Compile Code

### Command
```bash
arm-none-eabi-gcc -mcpu=cortex-a9 -marm -nostdlib -nostartfiles -T link.ld -o hello.elf startup.S hello.c
```

### Description
Assemble `startup.S` and compile `hello.c`, then link them together into `hello.elf` according to `link.ld`.

---

### 1. `arm-none-eabi-gcc`
**Purpose:** Compiler + assembler + linker driver for ARM bare-metal systems.

- **arm** → target architecture  
- **none** → no operating system (bare-metal)  
- **eabi** → uses the *Embedded Application Binary Interface* (calling conventions, data layout, etc.)

---

### 2. `-mcpu=cortex-a9`
Specifies the target CPU core.

- Generates instructions optimized for **ARM Cortex-A9** (used in **Zynq-7000**).  
- Ensures correct instruction set, registers, and optimizations.

---

### 3. `-marm`
Forces compilation in **ARM mode** (32-bit ARM instructions), instead of **Thumb mode** (16-bit compressed instructions).

- Cortex-A9 supports both.
- ARM mode is preferred for early startup simplicity.

---

### 4. `-nostdlib`
Prevents linking against the standard C libraries (`libc`, `libm`, `libgcc`, etc.).

- Suitable for **bare-metal firmware**, since there’s no OS or runtime environment (no `printf`, `malloc`, etc.).

---

### 5. `-nostartfiles`
Disables default startup files (`crt0.o`, etc.) that GCC normally includes.

- We provide our own startup code: `startup.S`.  
- Without this flag, GCC would try to include system startup files not available in bare-metal projects.

---

### 6. `-T link.ld`
Specifies a custom **linker script** (`link.ld`).

Defines:
- **Memory regions** (e.g., Flash, RAM)  
- **Section placements** (`.text`, `.data`, `.bss`, etc.)  
- **Symbols** like `_stack_top`

---

## (B) Run QEMU

### Command
```bash
qemu-system-arm -M xilinx-zynq-a9 -serial mon:stdio -nographic -kernel hello.elf
```

### Description

| Option | Explanation |
|---------|--------------|
| `-M xilinx-zynq-a9` | Emulates a Xilinx Zynq-7000 ARM SoC. |
| `-serial mon:stdio` | Redirects serial port I/O to the QEMU monitor and terminal (stdio), allowing communication via terminal. |
| `-nographic` | Disables graphical output and redirects all output to the terminal (useful for headless or console-only apps). |
| `-kernel hello.elf` | Loads the specified ELF file (`hello.elf`) as the kernel or bare-metal application to run. |

---

## (C) Next Goal

> Develop a **complete Linux BSP** for the **Xilinx Zynq-7000** board in a custom way — as close to real-world as possible.

---
