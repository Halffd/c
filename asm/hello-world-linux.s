.section .data
hello:
    .asciz "Hello, World!\n"

.section .text
.global _start

_start:
    # Write 'Hello, World!' to stdout
    mov $1, %rax          # syscall: write
    mov $1, %rdi          # file descriptor: stdout
    lea hello(%rip), %rsi # message to write
    mov $14, %rdx         # message length
    syscall                # invoke operating system to do the write

    # Exit
    mov $60, %rax         # syscall: exit
    xor %rdi, %rdi        # exit code: 0
    syscall                # invoke operating system to exit
