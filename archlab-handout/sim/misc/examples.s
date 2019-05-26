	.file	"examples.c"
	.text
.globl sum_list
	.type	sum_list, @function
sum_list:
.LFB2:
	movl	$0, %eax
	testq	%rdi, %rdi
	je	.L6
.L4:
	addl	(%rdi), %eax
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	jne	.L4
.L6:
	rep ; ret
.LFE2:
	.size	sum_list, .-sum_list
.globl rsum_list
	.type	rsum_list, @function
rsum_list:
.LFB3:
	pushq	%rbx
.LCFI0:
	movl	$0, %eax
	testq	%rdi, %rdi
	je	.L7
	movl	(%rdi), %ebx
	movq	8(%rdi), %rdi
	call	rsum_list
	leal	(%rbx,%rax), %eax
.L7:
	popq	%rbx
	ret
.LFE3:
	.size	rsum_list, .-rsum_list
.globl copy_block
	.type	copy_block, @function
copy_block:
.LFB4:
	movl	$0, %ecx
	testl	%edx, %edx
	jle	.L15
.L13:
	movl	(%rdi), %eax
	addq	$4, %rdi
	movl	%eax, (%rsi)
	addq	$4, %rsi
	xorl	%eax, %ecx
	decl	%edx
	testl	%edx, %edx
	jg	.L13
.L15:
	movl	%ecx, %eax
	ret
.LFE4:
	.size	copy_block, .-copy_block
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.byte	0x4
	.long	.LCFI0-.LFB3
	.byte	0xe
	.uleb128 0x10
	.byte	0x83
	.uleb128 0x2
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.quad	.LFB4
	.quad	.LFE4-.LFB4
	.align 8
.LEFDE5:
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.4.6 (Ubuntu 3.4.6-6ubuntu5)"
