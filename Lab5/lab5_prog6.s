	.file	"lab5_prog6.c"
	.text
	.globl	very_fast_function
	.type	very_fast_function, @function
very_fast_function:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	sall	$6, %eax
	addl	$1, %eax
	cmpl	$1024, %eax
	jle	.L2
	movl	8(%ebp), %eax
	addl	$1, 8(%ebp)
	jmp	.L3
.L2:
	movl	$0, %eax
.L3:
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	very_fast_function, .-very_fast_function
	.section	.rodata
	.align 4
.LC0:
	.string	"The function value of i is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	movl	$40, 28(%esp)
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	very_fast_function
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (SUSE Linux) 4.7.3"
	.section	.note.GNU-stack,"",@progbits
