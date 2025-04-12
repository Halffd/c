section .data
    iterations dd 10
    threshold dd 5
    output_msg db "Accumulator value: ", 0
    number_buffer db 16 dup(0)  ; Buffer to store the number string
    newline db 10, 0

section .bss
    ; No variables needed for this version

section .text
    global _start  ; Changed back to _start since we're not using libc

_start:
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
    ; Convert number to string
    mov edi, number_buffer
    call int_to_string
    
    ; Print "Accumulator value: "
    mov eax, 4        ; sys_write
    mov ebx, 1        ; stdout
    mov ecx, output_msg
    mov edx, 18       ; length of string
    int 0x80
    
    ; Print the number
    mov eax, 4        ; sys_write
    mov ebx, 1        ; stdout
    mov ecx, number_buffer
    mov edx, 16       ; maximum length
    int 0x80
    
    ; Print newline
    mov eax, 4        ; sys_write
    mov ebx, 1        ; stdout
    mov ecx, newline
    mov edx, 1        ; length of newline
    int 0x80
    
    ; Exit the program
    mov eax, 1        ; sys_exit
    mov ebx, 0        ; exit code
    int 0x80

; Helper function to convert integer to string
; Input: EAX = number, EDI = buffer
; Output: EDI points to string, EDX = length
int_to_string:
    push ebx
    push ecx
    mov ebx, 10       ; base 10
    xor ecx, ecx      ; digit counter
    
    .convert_loop:
        xor edx, edx
        div ebx        ; divide eax by 10
        add dl, '0'    ; convert remainder to ASCII
        push edx        ; store digit
        inc ecx         ; increment digit count
        test eax, eax
        jnz .convert_loop
    
    .store_loop:
        pop edx
        mov [edi], dl
        inc edi
        dec ecx
        jnz .store_loop
    
    mov byte [edi], 0  ; null terminator
    pop ecx
    pop ebx
    ret