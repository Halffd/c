section .data
    iterations dd 10
    threshold dd 5
    output_msg db "Accumulator value: %d", 10, 0  ; Format string with newline

section .bss
    ; Reserve space for any variables if needed

section .text
    global main      ; Changed from _start to main
    extern printf
    extern exit

main:               ; Changed from _start to main
    mov ecx, [iterations]  ; loop counter
    mov eax, 0             ; accumulator

loop_start:
    add eax, ecx
    dec ecx
    cmp ecx, 0
    je print_result

    ; Check if threshold is reached
    cmp ecx, [threshold]
    je patch_jump

normal_continue:
    ; This jmp will be modified
jmp_site:
    jmp loop_start  ; Initially a near jump (E9 ...)

    ; --- Self-modification takes place here ---
patch_jump:
    ; Change the jmp at jmp_site to a short jump (EB FE for jmp loop_start)
    mov byte [jmp_site], 0xEB  ; EB is short jump opcode
    mov byte [jmp_site + 1], 0xFE  ; FE is the offset (-2)
    jmp loop_start

print_result:
    push eax
    push eax
    push output_msg
    call printf
    add esp, 8
    pop eax

    push 0
    call exit