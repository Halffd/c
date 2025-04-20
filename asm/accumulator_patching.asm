section .data
    iterations dd 10
    threshold dd 5
    output_msg db "Accumulator value: "
    output_len equ $-output_msg
    number_buffer db 16 dup(0)
    newline db 10
    newline_len equ $-newline
    debug_patch db "Patching jump",10
    debug_len equ $-debug_patch

section .text
    global _start

_start:
    mov ecx, [iterations]
    mov eax, 0

loop_start:
    add eax, ecx
    dec ecx
    jz print_result

    cmp ecx, [threshold]
    je patch_jump

normal_continue:
jmp_site:
    jmp loop_start      ; Original 5-byte near jump
    nop                 ; Pad remaining 3 bytes
    nop
    nop

patch_jump:
    ; Debug message
    mov eax, 4
    mov ebx, 1
    mov ecx, debug_patch
    mov edx, debug_len
    int 0x80

    ; Overwrite ENTIRE 5-byte jmp with short jump + NOPs
    mov byte [jmp_site], 0xEB    ; Short jump opcode
    mov byte [jmp_site+1], 0xF3  ; -13 offset (calculated below)
    mov byte [jmp_site+2], 0x90  ; NOP
    mov byte [jmp_site+3], 0x90  ; NOP
    mov byte [jmp_site+4], 0x90  ; NOP

    jmp loop_start

print_result:
    ; ... (rest of code remains same)