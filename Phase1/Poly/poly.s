	.file	"poly.c"
	.text
	.globl	multiply
	.type	multiply, @function
multiply:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movq	%rdx, -56(%rbp)
	movl	%ecx, -48(%rbp)
	movq	%r8, -64(%rbp)
	movl	-44(%rbp), %edx
	movl	-48(%rbp), %eax
	addl	%edx, %eax
	leal	1(%rax), %edx
	movq	-64(%rbp), %rax
	movl	%edx, (%rax)
	movq	-64(%rbp), %rax
	movl	(%rax), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L2
.L3:
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, (%rax)
	addl	$1, -20(%rbp)
.L2:
	movq	-64(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jle	.L3
	movl	$0, -16(%rbp)
	jmp	.L4
.L7:
	movl	$0, -12(%rbp)
	jmp	.L5
.L6:
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rsi
	movq	-56(%rbp), %rax
	addq	%rsi, %rax
	movl	(%rax), %eax
	imull	%eax, %edx
	movl	-16(%rbp), %esi
	movl	-12(%rbp), %eax
	addl	%esi, %eax
	cltq
	leaq	0(,%rax,4), %rsi
	movq	-8(%rbp), %rax
	addq	%rsi, %rax
	addl	%ecx, %edx
	movl	%edx, (%rax)
	addl	$1, -12(%rbp)
.L5:
	movl	-12(%rbp), %eax
	cmpl	-48(%rbp), %eax
	jle	.L6
	addl	$1, -16(%rbp)
.L4:
	movl	-16(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jle	.L7
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	multiply, .-multiply
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"+%dx^%d"
.LC2:
	.string	"%dx^%d"
.LC3:
	.string	"+%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-64(%rbp), %eax
	addl	$1, %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -32(%rbp)
	movl	$0, -52(%rbp)
	jmp	.L10
.L11:
	movl	-64(%rbp), %eax
	subl	-52(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	addl	$1, -52(%rbp)
.L10:
	movl	-64(%rbp), %eax
	cmpl	%eax, -52(%rbp)
	jle	.L11
	leaq	-60(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-60(%rbp), %eax
	addl	$1, %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	movl	$0, -48(%rbp)
	jmp	.L12
.L13:
	movl	-60(%rbp), %eax
	subl	-48(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	addl	$1, -48(%rbp)
.L12:
	movl	-60(%rbp), %eax
	cmpl	%eax, -48(%rbp)
	jle	.L13
	movl	-60(%rbp), %ecx
	movl	-64(%rbp), %esi
	leaq	-56(%rbp), %rdi
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdi, %r8
	movq	%rax, %rdi
	call	multiply
	movq	%rax, -16(%rbp)
	movl	-64(%rbp), %edx
	movl	-60(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -40(%rbp)
	movl	-56(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -44(%rbp)
	jmp	.L14
.L17:
	movl	-56(%rbp), %eax
	subl	$1, %eax
	subl	-44(%rbp), %eax
	movl	%eax, -36(%rbp)
	movl	-44(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jle	.L15
	movl	-40(%rbp), %eax
	subl	-36(%rbp), %eax
	movl	%eax, %edx
	movl	-44(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L16
.L15:
	movl	-40(%rbp), %eax
	subl	-36(%rbp), %eax
	movl	%eax, %edx
	movl	-44(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L16:
	subl	$1, -44(%rbp)
.L14:
	cmpl	$0, -44(%rbp)
	jg	.L17
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jle	.L18
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L19
.L18:
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L19:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L21
	call	__stack_chk_fail@PLT
.L21:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
