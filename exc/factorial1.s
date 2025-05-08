	.file	"factorial.c"
	.text
	.globl	memo
	.bss
	.align 8
	.type	memo, @object
	.size	memo, 8
memo:
	.zero	8
	.text
	.globl	fibonacci_memo
	.type	fibonacci_memo, @function
fibonacci_memo:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	movq	memo(%rip), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	cmpl	$-1, %eax
	je	.L2
	movq	memo(%rip), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	jmp	.L3
.L2:
	cmpl	$1, -20(%rbp)
	jg	.L4
	movq	memo(%rip), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	movl	-20(%rbp), %eax
	movl	%eax, (%rdx)
	movl	-20(%rbp), %eax
	jmp	.L3
.L4:
	movl	-20(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	fibonacci_memo
	movl	%eax, %ebx
	movl	-20(%rbp), %eax
	subl	$2, %eax
	movl	%eax, %edi
	call	fibonacci_memo
	movq	memo(%rip), %rdx
	movl	-20(%rbp), %ecx
	movslq	%ecx, %rcx
	salq	$2, %rcx
	addq	%rcx, %rdx
	addl	%ebx, %eax
	movl	%eax, (%rdx)
	movq	memo(%rip), %rax
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
.L3:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	fibonacci_memo, .-fibonacci_memo
	.globl	fibonacci
	.type	fibonacci, @function
fibonacci:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, memo(%rip)
	movl	$0, -8(%rbp)
	jmp	.L6
.L7:
	movq	memo(%rip), %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	$-1, (%rax)
	addl	$1, -8(%rbp)
.L6:
	movl	-8(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jle	.L7
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	fibonacci_memo
	movl	%eax, -4(%rbp)
	movq	memo(%rip), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	fibonacci, .-fibonacci
	.globl	factorial_tail
	.type	factorial_tail, @function
factorial_tail:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jg	.L10
	movl	-8(%rbp), %eax
	jmp	.L11
.L10:
	movl	-4(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	-4(%rbp), %edx
	subl	$1, %edx
	movl	%eax, %esi
	movl	%edx, %edi
	call	factorial_tail
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	factorial_tail, .-factorial_tail
	.globl	factorial_optimized
	.type	factorial_optimized, @function
factorial_optimized:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	$1, %esi
	movl	%eax, %edi
	call	factorial_tail
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	factorial_optimized, .-factorial_optimized
	.section	.rodata
.LC0:
	.string	"Tail factorial %d: %d\n"
.LC1:
	.string	"Fibonaci %d: %d\n"
	.align 8
.LC2:
	.string	"\n=== ALGORITHM DEMONSTRATION ==="
.LC3:
	.string	"1. Factorial (Iterative)"
.LC4:
	.string	"2. Factorial (Recursive)"
.LC5:
	.string	"3. Fibonacci (Iterative)"
.LC6:
	.string	"4. Fibonacci (Recursive)"
.LC7:
	.string	"Enter your choice (1-4): "
.LC8:
	.string	"%d"
.LC9:
	.string	"Enter a number: "
	.align 8
.LC10:
	.string	"\nFactorial of %d (iterative): %d\n"
	.align 8
.LC11:
	.string	"\nFactorial of %d (recursive): %d\n"
	.align 8
.LC12:
	.string	"\nFibonacci sequence (iterative) up to %d terms:\n"
.LC13:
	.string	"%d "
	.align 8
.LC14:
	.string	"\nFibonacci sequence (recursive) up to %d terms:\n"
.LC15:
	.string	"\nInvalid choice!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$30, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	factorial_optimized
	movl	%eax, -16(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	fibonacci
	movl	%eax, -12(%rbp)
	movl	-16(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-12(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-36(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-36(%rbp), %eax
	cmpl	$4, %eax
	je	.L15
	cmpl	$4, %eax
	jg	.L16
	cmpl	$3, %eax
	je	.L17
	cmpl	$3, %eax
	jg	.L16
	cmpl	$1, %eax
	je	.L18
	cmpl	$2, %eax
	je	.L19
	jmp	.L16
.L18:
	movl	-32(%rbp), %eax
	movl	%eax, %edi
	call	factorial_iterative
	movl	%eax, %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L20
.L19:
	movl	-32(%rbp), %eax
	movl	%eax, %edi
	call	factorial_recursive
	movl	%eax, %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L20
.L17:
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, -28(%rbp)
	jmp	.L21
.L22:
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	fibonacci_iterative
	movl	%eax, %esi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -28(%rbp)
.L21:
	movl	-32(%rbp), %eax
	cmpl	%eax, -28(%rbp)
	jle	.L22
	movl	$10, %edi
	call	putchar@PLT
	jmp	.L20
.L15:
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, -24(%rbp)
	jmp	.L23
.L24:
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	fibonacci_recursive
	movl	%eax, %esi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -24(%rbp)
.L23:
	movl	-32(%rbp), %eax
	cmpl	%eax, -24(%rbp)
	jle	.L24
	movl	$10, %edi
	call	putchar@PLT
	jmp	.L20
.L16:
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L20:
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L26
	call	__stack_chk_fail@PLT
.L26:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	main, .-main
	.globl	factorial_iterative
	.type	factorial_iterative, @function
factorial_iterative:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L28
.L29:
	movl	-4(%rbp), %eax
	imull	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
	subl	$1, -20(%rbp)
.L28:
	cmpl	$1, -20(%rbp)
	jg	.L29
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	factorial_iterative, .-factorial_iterative
	.globl	factorial_recursive
	.type	factorial_recursive, @function
factorial_recursive:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	cmpl	$1, -4(%rbp)
	jg	.L32
	movl	$1, %eax
	jmp	.L33
.L32:
	movl	-4(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	factorial_recursive
	imull	-4(%rbp), %eax
.L33:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	factorial_recursive, .-factorial_recursive
	.globl	fibonacci_iterative
	.type	fibonacci_iterative, @function
fibonacci_iterative:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	cmpl	$0, -20(%rbp)
	jg	.L35
	movl	$0, %eax
	jmp	.L36
.L35:
	cmpl	$1, -20(%rbp)
	jne	.L37
	movl	$1, %eax
	jmp	.L36
.L37:
	movl	$0, -16(%rbp)
	movl	$1, -12(%rbp)
	movl	$0, -8(%rbp)
	movl	$2, -4(%rbp)
	jmp	.L38
.L39:
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -8(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, -12(%rbp)
	addl	$1, -4(%rbp)
.L38:
	movl	-4(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jle	.L39
	movl	-8(%rbp), %eax
.L36:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	fibonacci_iterative, .-fibonacci_iterative
	.globl	fibonacci_recursive
	.type	fibonacci_recursive, @function
fibonacci_recursive:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	cmpl	$0, -20(%rbp)
	jg	.L41
	movl	$0, %eax
	jmp	.L42
.L41:
	cmpl	$1, -20(%rbp)
	je	.L43
	cmpl	$2, -20(%rbp)
	jne	.L44
.L43:
	movl	$1, %eax
	jmp	.L42
.L44:
	movl	-20(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	fibonacci_recursive
	movl	%eax, %ebx
	movl	-20(%rbp), %eax
	subl	$2, %eax
	movl	%eax, %edi
	call	fibonacci_recursive
	addl	%ebx, %eax
.L42:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	fibonacci_recursive, .-fibonacci_recursive
	.ident	"GCC: (GNU) 14.2.1 20250207"
	.section	.note.GNU-stack,"",@progbits
