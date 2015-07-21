# llama Readme
##Codebase Structure
- cross system root located at sysroot
- libc
    - Each standard function is a file with the same name as the function inside a directory with the name of the header.
         - eg. strlen from string.h is in `libc/string/strlen.c`
    - The standard headers use a BSD-like scheme where sys/cdefs.h declares a bunch of useful preprocessor macros meant for internal use by the standard library. 
         - eg. all the function prototypes are wrapped in `extern "C" {` and `}` such that C++ code can correctly link against libc (as libc doesn't use C++ linkage). Note also how the compiler provides the internal keyword `__restrict` unconditionally (even in C89) mode, which is useful for adding the restrict keyword to function prototypes even when compiling code in pre-C99 mode.
    - The special `__is_llama_libc` macro lets the source code detect whether it is part of the libc.

### Full list of headers
(output of find . -name *.h)
```
libc/include/string.h
libc/include/stdio.h
libc/include/stdlib.h
libc/include/sys/cdefs.h
kernel/include/kernel/vga.h
kernel/include/kernel/tty.h
````
## Runtime Order
- The kernel implements the correct way of invoking global constructors (useful for C++ code and C code using `__attribute__((constructor))`). The kernel initialization is done in three steps:
    1. First the `kernel_early()` function is called which sets up the essential kernel features (such as the kernel log). 
    2. The bootstrap assembly then proceeds to call `_init` (which invokes all the global constructors)
    3. `kernel_main()`

## Notes
- packages necessary
    - grub-pc
    - cross-compiler targeting i686-elf
    - qemu
