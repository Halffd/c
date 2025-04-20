; Self-modifying assembly program demonstrating runtime code patching
; Calculates sum of numbers from N down to 1, with loop optimization at threshold

section .data
    iterations dd 10        ; Loop counter limit
    threshold dd 5          ; When to activate optimized jump
    output_msg db "Accumulator value: "
    output_len equ $-output_msg  ; Calculate string length at assemble time
    number_buffer db 16 dup(0)   ; Buffer for number-to-string conversion
    newline db 10                ; ASCII newline character
    newline_len equ $-newline    ; Length of newline string (1 byte)
    debug_patch db "Patching jump",10  ; Debug message
    debug_len equ $-debug_patch  ; Length of debug message

section .text
    global _start   ; Entry point for linker

_start:
    ; Initialize registers:
    mov ecx, [iterations]  ; Load loop counter
    mov eax, 0             ; Clear accumulator
    mov edx, 0             ; Patch flag (0 = not patched yet)

loop_start:
    ; Main computation loop
    add eax, ecx           ; Accumulate current counter value
    dec ecx                ; Decrement counter
    jz print_result        ; Exit loop when counter reaches zero

    ; Threshold check - only patch once when we reach threshold
    cmp ecx, [threshold]
    jne normal_continue    ; Skip if not at threshold
    cmp edx, 0             ; Check if we've already patched
    jne normal_continue    ; Skip if already patched

    ; ---- SELF-MODIFYING CODE SECTION ----
    ; This is where we rewrite the jump instruction at runtime
    mov edx, 1             ; Set patch flag (don't patch again)
    
    ; Replace 5-byte near jump with 2-byte short jump + NOPs
    mov byte [jmp_site], 0xEB    ; EB = short jump opcode
    mov byte [jmp_site+1], 0xF9  ; F9 = -7 offset (loop_start - (jmp_site + 2))
    ; Note: Remaining 3 bytes are already NOPs (0x90) from original padding

normal_continue:
jmp_site:
    ; This instruction gets modified at runtime:
    ; Original: E9 xx xx xx xx (5-byte near jump)
    ; Patched:  EB F9 90 90 90 (2-byte short jump + 3 NOPs)
    jmp loop_start  ; Will be overwritten when threshold reached
    nop             ; Padding to maintain 5-byte instruction size
    nop             ; (Important for correct code alignment)
    nop

print_result:
    ; Convert accumulated value to ASCII string
    mov edi, number_buffer  ; Point to output buffer
    call int_to_string      ; Convert EAX to string at EDI

    ; Print output message using Linux sys_write (syscall 4)
    mov eax, 4        ; sys_write
    mov ebx, 1        ; stdout
    mov ecx, output_msg
    mov edx, output_len
    int 0x80

    ; Print the converted number
    mov eax, 4
    mov ebx, 1
    mov ecx, number_buffer
    mov edx, 16       ; Maximum digits to print
    int 0x80

    ; Print newline
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, newline_len
    int 0x80

    ; Exit program (sys_exit)
    mov eax, 1        ; sys_exit
    mov ebx, 0        ; Return code 0
    int 0x80

; --------------------------------------------------
; Helper function: Convert integer in EAX to ASCII string
; Arguments:
;   EAX = number to convert
;   EDI = pointer to output buffer (must have 16+ bytes)
; Returns:
;   EDI points to null-terminated string
; Preserves: EBX, ECX
; --------------------------------------------------
int_to_string:
    push ebx          ; Save registers we'll modify
    push ecx
    mov ebx, 10       ; Base 10 conversion
    xor ecx, ecx      ; Digit counter (initialize to 0)
    
    .convert_loop:
        xor edx, edx    ; Clear upper 32 bits of dividend
        div ebx         ; Divide EDX:EAX by 10
        add dl, '0'     ; Convert remainder (0-9) to ASCII
        push edx        ; Store digit on stack (reverse order)
        inc ecx         ; Count digits
        test eax, eax   ; Check if quotient is zero
        jnz .convert_loop
    
    .store_loop:
        pop edx         ; Get digits back from stack
        mov [edi], dl   ; Store ASCII digit
        inc edi         ; Move to next buffer position
        dec ecx         ; Decrement digit counter
        jnz .store_loop
    
    mov byte [edi], 0   ; Null-terminate the string
    pop ecx             ; Restore registers
    pop ebx
    ret