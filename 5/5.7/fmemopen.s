	.text
	.file	"fmemopen.c"
	.globl	fmemopen                # -- Begin function fmemopen
	.p2align	4, 0xcc
	.type	fmemopen,@function
fmemopen:                               # @fmemopen
	.cfi_startproc
# %bb.0:
	movq	__retguard_2710(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r11
	subq	$56, %rsp
	.cfi_offset %r11, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-40(%rbp), %rdi
	callq	convmode
	movl	%eax, -56(%rbp)
	movq	-24(%rbp), %rdi
	movq	-32(%rbp), %rsi
	movl	-56(%rbp), %edx
	callq	malloc_memfile
	movq	%rax, -48(%rbp)
	cmpq	$0, %rax
	jne	.LBB0_2
# %bb.1:
	movq	$0, -16(%rbp)
	jmp	.LBB0_5
.LBB0_2:
	movq	-48(%rbp), %rdi
	leaq	readfn(%rip), %rsi
	leaq	writefn(%rip), %rdx
	leaq	seekfn(%rip), %rcx
	leaq	closefn(%rip), %r8
	callq	funopen@PLT
	movq	%rax, -64(%rbp)
	cmpq	$0, %rax
	jne	.LBB0_4
# %bb.3:
	movq	$0, -16(%rbp)
	jmp	.LBB0_5
.LBB0_4:
	movq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
.LBB0_5:
	movq	-16(%rbp), %rax
	addq	$56, %rsp
	popq	%r11
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_2710(%rip), %r11
	je	.Ltmp0
	int3
	int3
.Ltmp1:
	.zero	15-((.Ltmp1-fmemopen)&15),204
.Ltmp0:
	retq
.Lfunc_end0:
	.size	fmemopen, .Lfunc_end0-fmemopen
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0xcc         # -- Begin function convmode
	.type	convmode,@function
convmode:                               # @convmode
	.cfi_startproc
# %bb.0:
	movq	__retguard_1504(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movl	.L__const.convmode.flags(%rip), %eax
	movl	%eax, -8(%rbp)
.LBB2_1:                                # =>This Inner Loop Header: Depth=1
	xorl	%eax, %eax
	movb	%al, %cl
	movq	-16(%rbp), %rdx
	movsbl	(%rdx), %eax
	cmpl	$0, %eax
	movb	%cl, -17(%rbp)          # 1-byte Spill
	je	.LBB2_3
# %bb.2:                                #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	shrb	$5, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	sete	%al
	movb	%al, -17(%rbp)          # 1-byte Spill
.LBB2_3:                                #   in Loop: Header=BB2_1 Depth=1
	movb	-17(%rbp), %al          # 1-byte Reload
	testb	$1, %al
	jne	.LBB2_4
	jmp	.LBB2_22
.LBB2_4:                                #   in Loop: Header=BB2_1 Depth=1
	movq	-16(%rbp), %rax
	movsbl	(%rax), %ecx
	xchgq	%rcx, %rdx
	movl	%edx, %ecx
	xchgq	%rcx, %rdx
	subl	$43, %edx
	movl	%ecx, -24(%rbp)         # 4-byte Spill
	movl	%edx, -28(%rbp)         # 4-byte Spill
	je	.LBB2_18
	jmp	.LBB2_28
.LBB2_28:                               #   in Loop: Header=BB2_1 Depth=1
	movl	-24(%rbp), %eax         # 4-byte Reload
	subl	$97, %eax
	movl	%eax, -32(%rbp)         # 4-byte Spill
	je	.LBB2_13
	jmp	.LBB2_29
.LBB2_29:                               #   in Loop: Header=BB2_1 Depth=1
	movl	-24(%rbp), %eax         # 4-byte Reload
	subl	$98, %eax
	movl	%eax, -36(%rbp)         # 4-byte Spill
	je	.LBB2_17
	jmp	.LBB2_30
.LBB2_30:                               #   in Loop: Header=BB2_1 Depth=1
	movl	-24(%rbp), %eax         # 4-byte Reload
	subl	$114, %eax
	movl	%eax, -40(%rbp)         # 4-byte Spill
	je	.LBB2_5
	jmp	.LBB2_31
.LBB2_31:                               #   in Loop: Header=BB2_1 Depth=1
	movl	-24(%rbp), %eax         # 4-byte Reload
	subl	$119, %eax
	movl	%eax, -44(%rbp)         # 4-byte Spill
	je	.LBB2_9
	jmp	.LBB2_19
.LBB2_5:                                #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	andb	$-2, %al
	orb	$1, %al
	movb	%al, -8(%rbp)
	movb	-8(%rbp), %al
	shrb	$1, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	jne	.LBB2_7
# %bb.6:                                #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	shrb	$2, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	je	.LBB2_8
.LBB2_7:                                #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	andb	$-33, %al
	orb	$32, %al
	movb	%al, -8(%rbp)
.LBB2_8:                                #   in Loop: Header=BB2_1 Depth=1
	jmp	.LBB2_20
.LBB2_9:                                #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	andb	$-3, %al
	orb	$2, %al
	movb	%al, -8(%rbp)
	movb	-8(%rbp), %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	jne	.LBB2_11
# %bb.10:                               #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	shrb	$2, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	je	.LBB2_12
.LBB2_11:                               #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	andb	$-33, %al
	orb	$32, %al
	movb	%al, -8(%rbp)
.LBB2_12:                               #   in Loop: Header=BB2_1 Depth=1
	jmp	.LBB2_20
.LBB2_13:                               #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	andb	$-5, %al
	orb	$4, %al
	movb	%al, -8(%rbp)
	movb	-8(%rbp), %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	jne	.LBB2_15
# %bb.14:                               #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	shrb	$1, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	je	.LBB2_16
.LBB2_15:                               #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	andb	$-33, %al
	orb	$32, %al
	movb	%al, -8(%rbp)
.LBB2_16:                               #   in Loop: Header=BB2_1 Depth=1
	jmp	.LBB2_20
.LBB2_17:                               #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	andb	$-17, %al
	orb	$16, %al
	movb	%al, -8(%rbp)
	jmp	.LBB2_20
.LBB2_18:                               #   in Loop: Header=BB2_1 Depth=1
	movb	-8(%rbp), %al
	andb	$-9, %al
	orb	$8, %al
	movb	%al, -8(%rbp)
	jmp	.LBB2_20
.LBB2_19:
	movb	-8(%rbp), %al
	andb	$-33, %al
	orb	$32, %al
	movb	%al, -8(%rbp)
	jmp	.LBB2_27
.LBB2_20:                               #   in Loop: Header=BB2_1 Depth=1
	jmp	.LBB2_21
.LBB2_21:                               #   in Loop: Header=BB2_1 Depth=1
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -16(%rbp)
	jmp	.LBB2_1
.LBB2_22:
	movb	-8(%rbp), %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	jne	.LBB2_26
# %bb.23:
	movb	-8(%rbp), %al
	shrb	$1, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	jne	.LBB2_26
# %bb.24:
	movb	-8(%rbp), %al
	shrb	$2, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	jne	.LBB2_26
# %bb.25:
	movb	-8(%rbp), %al
	andb	$-33, %al
	orb	$32, %al
	movb	%al, -8(%rbp)
.LBB2_26:
	jmp	.LBB2_27
.LBB2_27:
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_1504(%rip), %r11
	je	.Ltmp2
	int3
	int3
.Ltmp3:
	.zero	15-((.Ltmp3-convmode)&15),204
.Ltmp2:
	retq
.Lfunc_end1:
	.size	convmode, .Lfunc_end1-convmode
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0xcc         # -- Begin function malloc_memfile
	.type	malloc_memfile,@function
malloc_memfile:                         # @malloc_memfile
	.cfi_startproc
# %bb.0:
	movq	__retguard_1052(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r11
	subq	$40, %rsp
	.cfi_offset %r11, -24
	movl	%edx, -24(%rbp)
	movq	%rdi, -32(%rbp)
	movq	%rsi, -40(%rbp)
	movl	$40, %edi
	callq	malloc@PLT
	movq	%rax, -48(%rbp)
	cmpq	$0, %rax
	jne	.LBB3_2
# %bb.1:
	jmp	.LBB3_13
.LBB3_2:
	cmpq	$0, -40(%rbp)
	je	.LBB3_4
# %bb.3:
	movb	-24(%rbp), %al
	shrb	$5, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	je	.LBB3_5
.LBB3_4:
	jmp	.LBB3_12
.LBB3_5:
	cmpq	$0, -32(%rbp)
	jne	.LBB3_11
# %bb.6:
	movb	-24(%rbp), %al
	shrb	$3, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	jne	.LBB3_8
# %bb.7:
	jmp	.LBB3_12
.LBB3_8:
	movq	-40(%rbp), %rdi
	callq	malloc@PLT
	movq	%rax, -32(%rbp)
	cmpq	$0, %rax
	jne	.LBB3_10
# %bb.9:
	jmp	.LBB3_13
.LBB3_10:
	movb	-24(%rbp), %al
	andb	$-65, %al
	orb	$64, %al
	movb	%al, -24(%rbp)
.LBB3_11:
	movq	-32(%rbp), %rax
	movq	-48(%rbp), %rcx
	movq	%rax, (%rcx)
	movq	-40(%rbp), %rax
	movq	-48(%rbp), %rcx
	movq	%rax, 8(%rcx)
	movq	-48(%rbp), %rax
	movl	-24(%rbp), %edx
	movl	%edx, 32(%rax)
	movq	-40(%rbp), %rax
	movq	-48(%rbp), %rcx
	movq	%rax, 16(%rcx)
	movq	-48(%rbp), %rdi
	callq	initmemfilepos
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	jmp	.LBB3_16
.LBB3_12:
	callq	__errno@PLT
	movl	$22, (%rax)
.LBB3_13:
	movb	-24(%rbp), %al
	shrb	$6, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	je	.LBB3_15
# %bb.14:
	movq	-32(%rbp), %rdi
	callq	free@PLT
.LBB3_15:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	callq	free@PLT
	movq	$0, -16(%rbp)
.LBB3_16:
	movq	-16(%rbp), %rax
	addq	$40, %rsp
	popq	%r11
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_1052(%rip), %r11
	je	.Ltmp4
	int3
	int3
.Ltmp5:
	.zero	15-((.Ltmp5-malloc_memfile)&15),204
.Ltmp4:
	retq
.Lfunc_end2:
	.size	malloc_memfile, .Lfunc_end2-malloc_memfile
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0xcc         # -- Begin function readfn
	.type	readfn,@function
readfn:                                 # @readfn
	.cfi_startproc
# %bb.0:
	movq	__retguard_1421(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r11
	subq	$72, %rsp
	.cfi_offset %r11, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movq	-24(%rbp), %rsi
	movq	%rsi, -48(%rbp)
	cmpl	$0, -36(%rbp)
	jl	.LBB4_3
# %bb.1:
	movq	-48(%rbp), %rax
	movb	32(%rax), %cl
	andb	$1, %cl
	movzbl	%cl, %edx
	cmpl	$0, %edx
	jne	.LBB4_4
# %bb.2:
	movq	-48(%rbp), %rax
	movb	32(%rax), %cl
	shrb	$3, %cl
	andb	$1, %cl
	movzbl	%cl, %edx
	cmpl	$0, %edx
	jne	.LBB4_4
.LBB4_3:
	jmp	.LBB4_8
.LBB4_4:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	-48(%rbp), %rcx
	subq	24(%rcx), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %ecx
	cmpq	%rcx, %rax
	jae	.LBB4_6
# %bb.5:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	-48(%rbp), %rcx
	subq	24(%rcx), %rax
	movq	%rax, -64(%rbp)         # 8-byte Spill
	jmp	.LBB4_7
.LBB4_6:
	movslq	-36(%rbp), %rax
	movq	%rax, -64(%rbp)         # 8-byte Spill
.LBB4_7:
	movq	-64(%rbp), %rax         # 8-byte Reload
	movl	%eax, %ecx
	movl	%ecx, -52(%rbp)
	movq	-32(%rbp), %rdi
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	-48(%rbp), %rdx
	addq	24(%rdx), %rax
	movslq	-52(%rbp), %rdx
	movq	%rax, %rsi
	callq	memcpy@PLT
	movslq	-52(%rbp), %rdx
	movq	-48(%rbp), %rsi
	addq	24(%rsi), %rdx
	movq	%rdx, 24(%rsi)
	movl	-52(%rbp), %ecx
	movl	%ecx, -12(%rbp)
	movq	%rax, -72(%rbp)         # 8-byte Spill
	jmp	.LBB4_9
.LBB4_8:
	callq	__errno@PLT
	movl	$22, (%rax)
	movl	$-1, -12(%rbp)
.LBB4_9:
	movl	-12(%rbp), %eax
	addq	$72, %rsp
	popq	%r11
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_1421(%rip), %r11
	je	.Ltmp6
	int3
	int3
.Ltmp7:
	.zero	15-((.Ltmp7-readfn)&15),204
.Ltmp6:
	retq
.Lfunc_end3:
	.size	readfn, .Lfunc_end3-readfn
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0xcc         # -- Begin function writefn
	.type	writefn,@function
writefn:                                # @writefn
	.cfi_startproc
# %bb.0:
	movq	__retguard_4(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r11
	subq	$72, %rsp
	.cfi_offset %r11, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movq	-24(%rbp), %rsi
	movq	%rsi, -48(%rbp)
	cmpl	$0, -36(%rbp)
	jl	.LBB5_2
# %bb.1:
	movq	-48(%rbp), %rax
	movl	32(%rax), %edi
	callq	writable
	cmpl	$0, %eax
	jne	.LBB5_3
.LBB5_2:
	jmp	.LBB5_11
.LBB5_3:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	-48(%rbp), %rcx
	subq	24(%rcx), %rax
	movl	-36(%rbp), %edx
	movl	%edx, %ecx
	cmpq	%rcx, %rax
	jae	.LBB5_5
# %bb.4:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	-48(%rbp), %rcx
	subq	24(%rcx), %rax
	movq	%rax, -64(%rbp)         # 8-byte Spill
	jmp	.LBB5_6
.LBB5_5:
	movslq	-36(%rbp), %rax
	movq	%rax, -64(%rbp)         # 8-byte Spill
.LBB5_6:
	movq	-64(%rbp), %rax         # 8-byte Reload
	movl	%eax, %ecx
	movl	%ecx, -52(%rbp)
	movq	-48(%rbp), %rax
	movb	32(%rax), %dl
	shrb	$2, %dl
	andb	$1, %dl
	xchgq	%rcx, %rdx
	movzbl	%cl, %edx
	xchgq	%rcx, %rdx
	cmpl	$0, %ecx
	je	.LBB5_8
# %bb.7:
	movq	-48(%rbp), %rax
	movq	16(%rax), %rax
	movq	-48(%rbp), %rcx
	movq	%rax, 24(%rcx)
.LBB5_8:
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	-48(%rbp), %rcx
	addq	24(%rcx), %rax
	movq	-32(%rbp), %rsi
	movslq	-52(%rbp), %rdx
	movq	%rax, %rdi
	callq	memcpy@PLT
	movslq	-52(%rbp), %rcx
	movq	-48(%rbp), %rdx
	addq	24(%rdx), %rcx
	movq	%rcx, 24(%rdx)
	movslq	-52(%rbp), %rcx
	movq	-48(%rbp), %rdx
	addq	16(%rdx), %rcx
	movq	%rcx, 16(%rdx)
	movq	-48(%rbp), %rcx
	movb	32(%rcx), %r8b
	shrb	$2, %r8b
	andb	$1, %r8b
	movzbl	%r8b, %r9d
	cmpl	$0, %r9d
	movq	%rax, -72(%rbp)         # 8-byte Spill
	je	.LBB5_10
# %bb.9:
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movq	-48(%rbp), %rcx
	movq	16(%rcx), %rcx
	movb	$0, (%rax,%rcx)
.LBB5_10:
	movl	-52(%rbp), %eax
	movl	%eax, -12(%rbp)
	jmp	.LBB5_12
.LBB5_11:
	callq	__errno@PLT
	movl	$22, (%rax)
	movl	$-1, -12(%rbp)
.LBB5_12:
	movl	-12(%rbp), %eax
	addq	$72, %rsp
	popq	%r11
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_4(%rip), %r11
	je	.Ltmp8
	int3
	int3
.Ltmp9:
	.zero	15-((.Ltmp9-writefn)&15),204
.Ltmp8:
	retq
.Lfunc_end4:
	.size	writefn, .Lfunc_end4-writefn
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0xcc         # -- Begin function seekfn
	.type	seekfn,@function
seekfn:                                 # @seekfn
	.cfi_startproc
# %bb.0:
	movq	__retguard_2880(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r11
	subq	$56, %rsp
	.cfi_offset %r11, -24
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movq	$-1, -40(%rbp)
	movq	-16(%rbp), %rsi
	movq	%rsi, -48(%rbp)
	movl	-28(%rbp), %edx
	testl	%edx, %edx
	movl	%edx, -52(%rbp)         # 4-byte Spill
	je	.LBB6_1
	jmp	.LBB6_6
.LBB6_6:
	movl	-52(%rbp), %eax         # 4-byte Reload
	subl	$1, %eax
	movl	%eax, -56(%rbp)         # 4-byte Spill
	je	.LBB6_2
	jmp	.LBB6_7
.LBB6_7:
	movl	-52(%rbp), %eax         # 4-byte Reload
	subl	$2, %eax
	movl	%eax, -60(%rbp)         # 4-byte Spill
	je	.LBB6_3
	jmp	.LBB6_4
.LBB6_1:
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rcx
	movq	%rax, 24(%rcx)
	movq	%rax, -40(%rbp)
	jmp	.LBB6_5
.LBB6_2:
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rcx
	addq	24(%rcx), %rax
	movq	%rax, 24(%rcx)
	movq	%rax, -40(%rbp)
	jmp	.LBB6_5
.LBB6_3:
	movq	-48(%rbp), %rax
	movq	16(%rax), %rax
	subq	-24(%rbp), %rax
	movq	-48(%rbp), %rcx
	movq	%rax, 24(%rcx)
	movq	%rax, -40(%rbp)
	jmp	.LBB6_5
.LBB6_4:
	callq	__errno@PLT
	movl	$22, (%rax)
.LBB6_5:
	movq	-40(%rbp), %rax
	addq	$56, %rsp
	popq	%r11
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_2880(%rip), %r11
	je	.Ltmp10
	int3
	int3
.Ltmp11:
	.zero	15-((.Ltmp11-seekfn)&15),204
.Ltmp10:
	retq
.Lfunc_end5:
	.size	seekfn, .Lfunc_end5-seekfn
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0xcc         # -- Begin function closefn
	.type	closefn,@function
closefn:                                # @closefn
	.cfi_startproc
# %bb.0:
	movq	__retguard_2127(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r11
	subq	$24, %rsp
	.cfi_offset %r11, -24
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rdi
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdi
	movb	32(%rdi), %al
	shrb	$6, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	je	.LBB7_2
# %bb.1:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdi
	callq	free@PLT
	jmp	.LBB7_5
.LBB7_2:
	movq	-24(%rbp), %rax
	movl	32(%rax), %edi
	callq	writable
	cmpl	$0, %eax
	je	.LBB7_4
# %bb.3:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	-24(%rbp), %rcx
	movq	16(%rcx), %rcx
	movb	$0, (%rax,%rcx)
.LBB7_4:
	jmp	.LBB7_5
.LBB7_5:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	callq	free@PLT
	xorl	%eax, %eax
	addq	$24, %rsp
	popq	%r11
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_2127(%rip), %r11
	je	.Ltmp12
	int3
	int3
.Ltmp13:
	.zero	15-((.Ltmp13-closefn)&15),204
.Ltmp12:
	retq
.Lfunc_end6:
	.size	closefn, .Lfunc_end6-closefn
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0xcc         # -- Begin function initmemfilepos
	.type	initmemfilepos,@function
initmemfilepos:                         # @initmemfilepos
	.cfi_startproc
# %bb.0:
	movq	__retguard_1891(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	movb	32(%rdi), %al
	shrb	$6, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	jne	.LBB8_3
# %bb.1:
	movq	-8(%rbp), %rax
	movb	32(%rax), %cl
	andb	$1, %cl
	movzbl	%cl, %edx
	cmpl	$0, %edx
	jne	.LBB8_3
# %bb.2:
	movq	-8(%rbp), %rax
	movb	32(%rax), %cl
	shrb	$1, %cl
	andb	$1, %cl
	movzbl	%cl, %edx
	cmpl	$0, %edx
	je	.LBB8_4
.LBB8_3:
	movq	-8(%rbp), %rax
	movq	$0, 24(%rax)
	jmp	.LBB8_11
.LBB8_4:
	movq	$0, -16(%rbp)
.LBB8_5:                                # =>This Inner Loop Header: Depth=1
	xorl	%eax, %eax
	movb	%al, %cl
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rdx
	movq	-16(%rbp), %rsi
	movzbl	(%rdx,%rsi), %eax
	cmpl	$0, %eax
	movb	%cl, -17(%rbp)          # 1-byte Spill
	je	.LBB8_7
# %bb.6:                                #   in Loop: Header=BB8_5 Depth=1
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	cmpq	8(%rcx), %rax
	xchgq	%rax, %rdx
	setbe	%al
	xchgq	%rax, %rdx
	movb	%dl, -17(%rbp)          # 1-byte Spill
.LBB8_7:                                #   in Loop: Header=BB8_5 Depth=1
	movb	-17(%rbp), %al          # 1-byte Reload
	testb	$1, %al
	jne	.LBB8_8
	jmp	.LBB8_10
.LBB8_8:                                #   in Loop: Header=BB8_5 Depth=1
	jmp	.LBB8_9
.LBB8_9:                                #   in Loop: Header=BB8_5 Depth=1
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -16(%rbp)
	jmp	.LBB8_5
.LBB8_10:
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	%rax, 24(%rcx)
.LBB8_11:
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_1891(%rip), %r11
	je	.Ltmp14
	int3
	int3
.Ltmp15:
	.zero	15-((.Ltmp15-initmemfilepos)&15),204
.Ltmp14:
	retq
.Lfunc_end7:
	.size	initmemfilepos, .Lfunc_end7-initmemfilepos
	.cfi_endproc
                                        # -- End function
	.p2align	4, 0xcc         # -- Begin function writable
	.type	writable,@function
writable:                               # @writable
	.cfi_startproc
# %bb.0:
	movq	__retguard_3596(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -8(%rbp)
	movb	-8(%rbp), %al
	shrb	$1, %al
	andb	$1, %al
	movzbl	%al, %edi
	cmpl	$0, %edi
	movb	$1, %al
	movb	%al, -9(%rbp)           # 1-byte Spill
	jne	.LBB9_3
# %bb.1:
	movb	-8(%rbp), %al
	shrb	$2, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	movb	$1, %al
	movb	%al, -9(%rbp)           # 1-byte Spill
	jne	.LBB9_3
# %bb.2:
	movb	-8(%rbp), %al
	shrb	$3, %al
	andb	$1, %al
	movzbl	%al, %ecx
	cmpl	$0, %ecx
	setne	%al
	movb	%al, -9(%rbp)           # 1-byte Spill
.LBB9_3:
	movb	-9(%rbp), %al           # 1-byte Reload
	andb	$1, %al
	movzbl	%al, %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_3596(%rip), %r11
	je	.Ltmp16
	int3
	int3
.Ltmp17:
	.zero	15-((.Ltmp17-writable)&15),204
.Ltmp16:
	retq
.Lfunc_end8:
	.size	writable, .Lfunc_end8-writable
	.cfi_endproc
                                        # -- End function
	.section	.text.__llvm_retpoline_r11,"axG",@progbits,__llvm_retpoline_r11,comdat
	.hidden	__llvm_retpoline_r11    # -- Begin function __llvm_retpoline_r11
	.weak	__llvm_retpoline_r11
	.p2align	4, 0xcc
	.type	__llvm_retpoline_r11,@function
__llvm_retpoline_r11:                   # @__llvm_retpoline_r11
# %bb.0:
	callq	.Ltmp18
.LBB1_2:                                # Block address taken
                                        # =>This Inner Loop Header: Depth=1
	pause
	lfence
	jmp	.LBB1_2
	.p2align	4, 0xcc
# %bb.3:                                # Block address taken
.Ltmp18:
	movq	%r11, (%rsp)
	retq
.Lfunc_end9:
	.size	__llvm_retpoline_r11, .Lfunc_end9-__llvm_retpoline_r11
                                        # -- End function
	.type	.L__const.convmode.flags,@object # @__const.convmode.flags
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.L__const.convmode.flags:
	.byte	0                       # 0x0
	.zero	3
	.size	.L__const.convmode.flags, 4

	.hidden	__retguard_2710         # @__retguard_2710
	.type	__retguard_2710,@object
	.section	.openbsd.randomdata.retguard.2710,"aGw",@progbits,__retguard_2710,comdat
	.weak	__retguard_2710
	.p2align	3
__retguard_2710:
	.quad	0
	.size	__retguard_2710, 8

	.hidden	__retguard_1504         # @__retguard_1504
	.type	__retguard_1504,@object
	.section	.openbsd.randomdata.retguard.1504,"aGw",@progbits,__retguard_1504,comdat
	.weak	__retguard_1504
	.p2align	3
__retguard_1504:
	.quad	0
	.size	__retguard_1504, 8

	.hidden	__retguard_1052         # @__retguard_1052
	.type	__retguard_1052,@object
	.section	.openbsd.randomdata.retguard.1052,"aGw",@progbits,__retguard_1052,comdat
	.weak	__retguard_1052
	.p2align	3
__retguard_1052:
	.quad	0
	.size	__retguard_1052, 8

	.hidden	__retguard_1421         # @__retguard_1421
	.type	__retguard_1421,@object
	.section	.openbsd.randomdata.retguard.1421,"aGw",@progbits,__retguard_1421,comdat
	.weak	__retguard_1421
	.p2align	3
__retguard_1421:
	.quad	0
	.size	__retguard_1421, 8

	.hidden	__retguard_4            # @__retguard_4
	.type	__retguard_4,@object
	.section	.openbsd.randomdata.retguard.4,"aGw",@progbits,__retguard_4,comdat
	.weak	__retguard_4
	.p2align	3
__retguard_4:
	.quad	0
	.size	__retguard_4, 8

	.hidden	__retguard_2880         # @__retguard_2880
	.type	__retguard_2880,@object
	.section	.openbsd.randomdata.retguard.2880,"aGw",@progbits,__retguard_2880,comdat
	.weak	__retguard_2880
	.p2align	3
__retguard_2880:
	.quad	0
	.size	__retguard_2880, 8

	.hidden	__retguard_2127         # @__retguard_2127
	.type	__retguard_2127,@object
	.section	.openbsd.randomdata.retguard.2127,"aGw",@progbits,__retguard_2127,comdat
	.weak	__retguard_2127
	.p2align	3
__retguard_2127:
	.quad	0
	.size	__retguard_2127, 8

	.hidden	__retguard_1891         # @__retguard_1891
	.type	__retguard_1891,@object
	.section	.openbsd.randomdata.retguard.1891,"aGw",@progbits,__retguard_1891,comdat
	.weak	__retguard_1891
	.p2align	3
__retguard_1891:
	.quad	0
	.size	__retguard_1891, 8

	.hidden	__retguard_3596         # @__retguard_3596
	.type	__retguard_3596,@object
	.section	.openbsd.randomdata.retguard.3596,"aGw",@progbits,__retguard_3596,comdat
	.weak	__retguard_3596
	.p2align	3
__retguard_3596:
	.quad	0
	.size	__retguard_3596, 8


	.addrsig
	.addrsig_sym convmode
	.addrsig_sym malloc_memfile
	.addrsig_sym funopen
	.addrsig_sym readfn
	.addrsig_sym writefn
	.addrsig_sym seekfn
	.addrsig_sym closefn
	.addrsig_sym malloc
	.addrsig_sym initmemfilepos
	.addrsig_sym __errno
	.addrsig_sym free
	.addrsig_sym writable
