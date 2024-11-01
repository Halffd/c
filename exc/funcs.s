	.file	"funcs.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Hello world!\0"
.LC1:
	.ascii "Enter a value for 'a': \0"
.LC2:
	.ascii "Enter a value for 'b': \0"
.LC3:
	.ascii "%hhu\0"
.LC4:
	.ascii "Enter a value for 'g': \0"
.LC5:
	.ascii "Value of 'a': %c\12\0"
.LC6:
	.ascii "Value of 'b': %u\12\0"
.LC7:
	.ascii "Value of 'c': %ld\12\0"
.LC8:
	.ascii "Value of 'd': %lf\12\0"
.LC9:
	.ascii "Value of 'e': %hd\12\0"
.LC10:
	.ascii "Value of 'g': %c\12\0"
.LC11:
	.ascii "mem[%zu]: %u\12\0"
.LC12:
	.ascii "Value of s.x: %d\12\0"
.LC13:
	.ascii "Value of s.a: %d\12\0"
.LC15:
	.ascii "x = %d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$144, %rsp
	.seh_stackalloc	144
	.seh_endprologue
	call	__main
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$5, -12(%rbp)
	movl	$10, -16(%rbp)
	movl	$2, -20(%rbp)
	movl	$3, -56(%rbp)
	leaq	-56(%rbp), %rax
	movq	%rax, -32(%rbp)
	movl	$7, -64(%rbp)
	movl	$4, -60(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	$0, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rax, %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %r8
	movl	$32, %edx
	movq	%rax, %rcx
	call	fgets
	movzbl	-112(%rbp), %eax
	movb	%al, -72(%rbp)
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	$0, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rax, %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %r8
	movl	$32, %edx
	movq	%rax, %rcx
	call	fgets
	leaq	-72(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %r8
	leaq	.LC3(%rip), %rdx
	movq	%rax, %rcx
	call	sscanf
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	$0, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rax, %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %r8
	movl	$32, %edx
	movq	%rax, %rcx
	call	fgets
	movzbl	-112(%rbp), %eax
	movb	%al, -72(%rbp)
	movzbl	-72(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %edx
	leaq	.LC5(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movzbl	-72(%rbp), %eax
	movzbl	%al, %eax
	movl	%eax, %edx
	leaq	.LC6(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	-72(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC7(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movsd	-72(%rbp), %xmm0
	movapd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movq	%xmm1, %rax
	movapd	%xmm0, %xmm1
	movq	%rax, %rdx
	leaq	.LC8(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movzwl	-72(%rbp), %eax
	cwtl
	movl	%eax, %edx
	leaq	.LC9(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movzbl	-72(%rbp), %eax
	movsbl	%al, %eax
	movl	%eax, %edx
	leaq	.LC10(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	-72(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	$8, -48(%rbp)
	movq	$0, -8(%rbp)
	jmp	.L2
.L3:
	movq	-40(%rbp), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %edx
	movq	-8(%rbp), %rax
	movl	%edx, %r8d
	movq	%rax, %rdx
	leaq	.LC11(%rip), %rax
	movq	%rax, %rcx
	call	printf
	addq	$1, -8(%rbp)
.L2:
	movq	-8(%rbp), %rax
	cmpq	-48(%rbp), %rax
	jb	.L3
	movl	-64(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC12(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	-60(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC13(%rip), %rax
	movq	%rax, %rcx
	call	printf
	leaq	-56(%rbp), %rdx
	addl	$1, -16(%rbp)
	movl	-16(%rbp), %eax
	cltq
	imulq	%rdx, %rax
	pxor	%xmm1, %xmm1
	cvtsi2ssq	%rax, %xmm1
	movss	.LC14(%rip), %xmm0
	subss	%xmm1, %xmm0
	movl	-64(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -64(%rbp)
	movl	-64(%rbp), %eax
	pxor	%xmm1, %xmm1
	cvtsi2ssl	%eax, %xmm1
	subss	%xmm1, %xmm0
	cvttss2sil	%xmm0, %edx
	movl	-60(%rbp), %eax
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	movl	%eax, -52(%rbp)
	cmpl	$0, -12(%rbp)
	je	.L4
	movl	-52(%rbp), %eax
	jmp	.L5
.L4:
	movl	-20(%rbp), %eax
.L5:
	addl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC15(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	$0, %eax
	addq	$144, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	dumbcmp
	.def	dumbcmp;	.scl	2;	.type	32;	.endef
	.seh_proc	dumbcmp
dumbcmp:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	24(%rbp), %rax
	movq	(%rax), %rdx
	movq	16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	call	strcmp
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	compare
	.def	compare;	.scl	2;	.type	32;	.endef
	.seh_proc	compare
compare:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L10
	movl	$0, %eax
	jmp	.L11
.L10:
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jge	.L12
	movl	$-1, %eax
	jmp	.L11
.L12:
	movl	$1, %eax
.L11:
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC16:
	.ascii "%d\0"
.LC17:
	.ascii "2147483647\0"
.LC18:
	.ascii "No overflow\0"
.LC19:
	.ascii "%d\12\0"
.LC20:
	.ascii "Character code for %d: %c\12\0"
.LC21:
	.ascii "aids\0"
.LC22:
	.ascii "crud\0"
.LC23:
	.ascii "evil\0"
.LC24:
	.ascii "gall\0"
.LC25:
	.ascii "idiot\0"
.LC26:
	.ascii "kick\0"
.LC27:
	.ascii "moon\0"
.LC28:
	.ascii "oval\0"
.LC29:
	.ascii "quod\0"
.LC30:
	.ascii "sulk\0"
.LC31:
	.ascii "under\0"
.LC32:
	.ascii "west\0"
.LC33:
	.ascii "year\0"
	.text
	.globl	tmp
	.def	tmp;	.scl	2;	.type	32;	.endef
	.seh_proc	tmp
tmp:
	pushq	%rbp
	.seh_pushreg	%rbp
	subq	$272, %rsp
	.seh_stackalloc	272
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	movl	$1, 140(%rbp)
	jmp	.L14
.L18:
	movq	$0, -80(%rbp)
	movq	$0, -72(%rbp)
	movq	$0, -64(%rbp)
	movq	$0, -56(%rbp)
	movl	140(%rbp), %ecx
	movslq	%ecx, %rax
	imulq	$1431655766, %rax, %rax
	shrq	$32, %rax
	movq	%rax, %rdx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	testl	%edx, %edx
	jne	.L15
	leaq	-80(%rbp), %rax
	movq	%rax, %rcx
	call	strlen
	movq	%rax, %rdx
	leaq	-80(%rbp), %rax
	addq	%rdx, %rax
	movl	$2054842694, (%rax)
	movb	$0, 4(%rax)
.L15:
	movl	140(%rbp), %ecx
	movslq	%ecx, %rax
	imulq	$1717986919, %rax, %rax
	shrq	$32, %rax
	movl	%eax, %edx
	sarl	%edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	testl	%edx, %edx
	jne	.L16
	leaq	-80(%rbp), %rax
	movq	%rax, %rcx
	call	strlen
	movq	%rax, %rdx
	leaq	-80(%rbp), %rax
	addq	%rdx, %rax
	movl	$2054845762, (%rax)
	movb	$0, 4(%rax)
.L16:
	movzbl	-80(%rbp), %eax
	testb	%al, %al
	jne	.L17
	movl	140(%rbp), %edx
	leaq	-80(%rbp), %rax
	movl	%edx, %r8d
	leaq	.LC16(%rip), %rdx
	movq	%rax, %rcx
	call	sprintf
.L17:
	leaq	-80(%rbp), %rax
	movq	%rax, %rcx
	call	puts
	addl	$1, 140(%rbp)
.L14:
	cmpl	$100, 140(%rbp)
	jle	.L18
	leaq	.LC17(%rip), %rax
	movq	%rax, 120(%rbp)
	movq	120(%rbp), %rax
	movq	%rax, %rcx
	call	atoi
	movl	%eax, 116(%rbp)
	leaq	.LC18(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	116(%rbp), %eax
	addl	$1, %eax
	movl	%eax, %edx
	leaq	.LC19(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	$-1, 136(%rbp)
	jmp	.L19
.L20:
	movl	136(%rbp), %eax
	movsbl	%al, %edx
	movl	136(%rbp), %eax
	movl	%edx, %r8d
	movl	%eax, %edx
	leaq	.LC20(%rip), %rax
	movq	%rax, %rcx
	call	printf
	subl	$1, 136(%rbp)
.L19:
	cmpl	$-260, 136(%rbp)
	jge	.L20
	movl	$7, 80(%rbp)
	movl	$2, 84(%rbp)
	movl	$6, 88(%rbp)
	movl	$1, 92(%rbp)
	movl	$2, 96(%rbp)
	movl	$5, 100(%rbp)
	leaq	80(%rbp), %rax
	leaq	compare(%rip), %r9
	movl	$4, %r8d
	movl	$6, %edx
	movq	%rax, %rcx
	call	qsort
	movl	$0, 132(%rbp)
	jmp	.L21
.L22:
	movl	132(%rbp), %eax
	cltq
	movl	80(%rbp,%rax,4), %eax
	movl	%eax, %edx
	leaq	.LC19(%rip), %rax
	movq	%rax, %rcx
	call	printf
	addl	$1, 132(%rbp)
.L21:
	cmpl	$5, 132(%rbp)
	jle	.L22
	leaq	.LC21(%rip), %rax
	movq	%rax, -32(%rbp)
	leaq	.LC22(%rip), %rax
	movq	%rax, -24(%rbp)
	leaq	.LC23(%rip), %rax
	movq	%rax, -16(%rbp)
	leaq	.LC24(%rip), %rax
	movq	%rax, -8(%rbp)
	leaq	.LC25(%rip), %rax
	movq	%rax, 0(%rbp)
	leaq	.LC26(%rip), %rax
	movq	%rax, 8(%rbp)
	leaq	.LC27(%rip), %rax
	movq	%rax, 16(%rbp)
	leaq	.LC28(%rip), %rax
	movq	%rax, 24(%rbp)
	leaq	.LC29(%rip), %rax
	movq	%rax, 32(%rbp)
	leaq	.LC30(%rip), %rax
	movq	%rax, 40(%rbp)
	leaq	.LC31(%rip), %rax
	movq	%rax, 48(%rbp)
	leaq	.LC32(%rip), %rax
	movq	%rax, 56(%rbp)
	leaq	.LC33(%rip), %rax
	movq	%rax, 64(%rbp)
	leaq	.LC23(%rip), %rax
	movq	%rax, -40(%rbp)
	leaq	-32(%rbp), %rdx
	leaq	-40(%rbp), %rax
	leaq	dumbcmp(%rip), %rcx
	movq	%rcx, 32(%rsp)
	movl	$8, %r9d
	movl	$13, %r8d
	movq	%rax, %rcx
	call	bsearch
	testq	%rax, %rax
	setne	%al
	movzbl	%al, %eax
	movl	%eax, 112(%rbp)
	movl	112(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC19(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	$0, 128(%rbp)
	jmp	.L23
.L26:
	movl	108(%rbp), %eax
	movl	%eax, %ecx
	movq	__imp_isspace(%rip), %rax
	call	*%rax
	testl	%eax, %eax
	je	.L24
	addl	$1, 128(%rbp)
	jmp	.L25
.L24:
	movl	$0, 128(%rbp)
.L25:
	cmpl	$0, 128(%rbp)
	jle	.L23
	movl	128(%rbp), %eax
	movl	%eax, %ecx
	call	putchar
.L23:
	call	getchar
	movl	%eax, 108(%rbp)
	cmpl	$-1, 108(%rbp)
	jne	.L26
	nop
	nop
	addq	$272, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 4
.LC14:
	.long	1082130432
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev3, Built by MSYS2 project) 14.1.0"
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	fgets;	.scl	2;	.type	32;	.endef
	.def	sscanf;	.scl	2;	.type	32;	.endef
	.def	strcmp;	.scl	2;	.type	32;	.endef
	.def	strlen;	.scl	2;	.type	32;	.endef
	.def	sprintf;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	atoi;	.scl	2;	.type	32;	.endef
	.def	qsort;	.scl	2;	.type	32;	.endef
	.def	bsearch;	.scl	2;	.type	32;	.endef
	.def	putchar;	.scl	2;	.type	32;	.endef
	.def	getchar;	.scl	2;	.type	32;	.endef
