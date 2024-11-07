extern GetStdHandle
extern WriteFile
extern ExitProcess

section .text
global main

main:
    sub     rsp, 40             ; Reserve shadow space and align stack by 16

    mov     rcx, -11            
    call    GetStdHandle

    ; Print three variations of Lorem Ipsum
    printString(lorem1)
    printString(lorem2)
    printString(lorem3)

    xor     ecx, ecx
    call    ExitProcess

; Macro to print a string
%macro printString 1
    lea     rdx, [%1]           ; Load address of the string
    mov     r8d, %1.len         ; Load the length of the string
    lea     r9, [rsp+48]        ; lpNumberOfBytesWritten
    mov     qword [rsp + 32], 0 ; lpOverlapped = NULL
    call    WriteFile           ; WriteFile(handle, string, length, &numberOfBytesWritten, NULL)
%endmacro

section .data         ; or section .rdata to put it in a read-only page
    lorem1:  db "Lorem ipsum dolor sit amet, consectetur adipiscing elit.", 13, 10
    lorem2:  db "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.", 13, 10
    lorem3:  db "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi.", 13, 10

    lorem1.len equ $ - lorem1  ; Calculate the length of the first string
    lorem2.len equ $ - lorem2  ; Calculate the length of the second string
    lorem3.len equ $ - lorem3  ; Calculate the length of the third string