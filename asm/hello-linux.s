.section .data
filename:
    .asciz "hello.s"           # File name with null terminator
flags = 0x00000001                 # O_RDONLY
buf:                                # Buffer for read data
    .space 1024                    # Allocate 1024 bytes
bufsize = 1024                     # Size of the buffer

    .section .text
    .global _start

_start:
    # Open the file
    movl $5, %eax                   # syscall number for open
    movl $filename, %ebx           # file path
    movl $flags, %ecx              # flags (O_RDONLY)
    xorl %edx, %edx                 # mode (not needed for read)
    int $0x80                       # invoke system call
    movl %eax, %ebx                 # store file descriptor in ebx

    # Read from the file
    movl $3, %eax                   # syscall number for read
    movl %ebx, %ebx                 # file descriptor
    movl $buf, %ecx                 # buffer address
    movl $bufsize, %edx             # buffer size
    int $0x80                       # invoke system call

    # Close the file
    movl $6, %eax                   # syscall number for close
    int $0x80                       # invoke system call

    # Exit the program
    movl $1, %eax                   # syscall number for exit
    xorl %ebx, %ebx                 # return 0
    int $0x80                       # invoke system call
