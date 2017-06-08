	.file	"kadai1_1.c"
	.section	.rodata
.LC0:
	.string	"w"
.LC1:
	.string	"hello\n"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$.LC0, %edx
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L2
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	perror
	movl	$1, %eax
	jmp	.L3
.L2:
	movl	$.LC1, %eax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rcx
	movl	$6, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fwrite
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose
	cmpl	$-1, %eax
	jne	.L4
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	perror
	movl	$1, %eax
	jmp	.L3
.L4:
	movl	$0, %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-17)"
	.section	.note.GNU-stack,"",@progbits
