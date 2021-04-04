	.text
	.file	"solution.c"
	.globl	my_barrier_wait         # -- Begin function my_barrier_wait
	.p2align	4, 0xcc
	.type	my_barrier_wait,@function
my_barrier_wait:                        # @my_barrier_wait
	.cfi_startproc
# %bb.0:
	movq	__retguard_52(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r11
	subq	$40, %rsp
	.cfi_offset %r11, -24
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdi
	callq	pthread_mutex_lock@PLT
	movq	-24(%rbp), %rdi
	movl	16(%rdi), %ecx
	addl	$1, %ecx
	movl	%ecx, 16(%rdi)
	movq	-24(%rbp), %rdi
	cmpl	20(%rdi), %ecx
	movl	%eax, -28(%rbp)         # 4-byte Spill
	jb	.LBB0_2
# %bb.1:
	movq	-24(%rbp), %rax
	movl	$0, 16(%rax)
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	callq	pthread_cond_broadcast@PLT
	movq	-24(%rbp), %rdi
	movl	%eax, -32(%rbp)         # 4-byte Spill
	callq	pthread_mutex_unlock@PLT
	movl	$-1, -12(%rbp)
	movl	%eax, -36(%rbp)         # 4-byte Spill
	jmp	.LBB0_3
.LBB0_2:
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movq	-24(%rbp), %rsi
	movq	%rax, %rdi
	callq	pthread_cond_wait@PLT
	movq	-24(%rbp), %rdi
	movl	%eax, -40(%rbp)         # 4-byte Spill
	callq	pthread_mutex_unlock@PLT
	movl	$0, -12(%rbp)
	movl	%eax, -44(%rbp)         # 4-byte Spill
.LBB0_3:
	movl	-12(%rbp), %eax
	addq	$40, %rsp
	popq	%r11
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_52(%rip), %r11
	je	.Ltmp0
	int3
	int3
.Ltmp1:
	.zero	15-((.Ltmp1-my_barrier_wait)&15),204
.Ltmp0:
	retq
.Lfunc_end0:
	.size	my_barrier_wait, .Lfunc_end0-my_barrier_wait
	.cfi_endproc
                                        # -- End function
	.globl	my_barrier_init         # -- Begin function my_barrier_init
	.p2align	4, 0xcc
	.type	my_barrier_init,@function
my_barrier_init:                        # @my_barrier_init
	.cfi_startproc
# %bb.0:
	movq	__retguard_2655(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movl	%edx, -28(%rbp)
	cmpq	$0, -24(%rbp)
	je	.LBB2_2
# %bb.1:
	movl	$91, -4(%rbp)
	jmp	.LBB2_7
.LBB2_2:
	cmpl	$0, -28(%rbp)
	jne	.LBB2_4
# %bb.3:
	movl	$22, -4(%rbp)
	jmp	.LBB2_7
.LBB2_4:
	cmpq	$0, -16(%rbp)
	jne	.LBB2_6
# %bb.5:
	movl	$22, -4(%rbp)
	jmp	.LBB2_7
.LBB2_6:
	movq	-16(%rbp), %rax
	movq	$0, (%rax)
	movq	-16(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-16(%rbp), %rax
	movl	$0, 16(%rax)
	movl	-28(%rbp), %ecx
	movq	-16(%rbp), %rax
	movl	%ecx, 20(%rax)
	movl	$0, -4(%rbp)
.LBB2_7:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_2655(%rip), %r11
	je	.Ltmp2
	int3
	int3
.Ltmp3:
	.zero	15-((.Ltmp3-my_barrier_init)&15),204
.Ltmp2:
	retq
.Lfunc_end1:
	.size	my_barrier_init, .Lfunc_end1-my_barrier_init
	.cfi_endproc
                                        # -- End function
	.globl	my_barrier_destroy      # -- Begin function my_barrier_destroy
	.p2align	4, 0xcc
	.type	my_barrier_destroy,@function
my_barrier_destroy:                     # @my_barrier_destroy
	.cfi_startproc
# %bb.0:
	movq	__retguard_2162(%rip), %r11
	xorq	(%rsp), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r11
	subq	$24, %rsp
	.cfi_offset %r11, -24
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rdi
	callq	pthread_mutex_lock@PLT
	movq	-24(%rbp), %rdi
	cmpl	$0, 16(%rdi)
	movl	%eax, -28(%rbp)         # 4-byte Spill
	jbe	.LBB3_2
# %bb.1:
	movq	-24(%rbp), %rdi
	callq	pthread_mutex_unlock@PLT
	movl	$16, -12(%rbp)
	movl	%eax, -32(%rbp)         # 4-byte Spill
	jmp	.LBB3_3
.LBB3_2:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	callq	free@PLT
	movl	$0, -12(%rbp)
.LBB3_3:
	movl	-12(%rbp), %eax
	addq	$24, %rsp
	popq	%r11
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	xorq	(%rsp), %r11
	cmpq	__retguard_2162(%rip), %r11
	je	.Ltmp4
	int3
	int3
.Ltmp5:
	.zero	15-((.Ltmp5-my_barrier_destroy)&15),204
.Ltmp4:
	retq
.Lfunc_end2:
	.size	my_barrier_destroy, .Lfunc_end2-my_barrier_destroy
	.cfi_endproc
                                        # -- End function
	.section	.text.__llvm_retpoline_r11,"axG",@progbits,__llvm_retpoline_r11,comdat
	.hidden	__llvm_retpoline_r11    # -- Begin function __llvm_retpoline_r11
	.weak	__llvm_retpoline_r11
	.p2align	4, 0xcc
	.type	__llvm_retpoline_r11,@function
__llvm_retpoline_r11:                   # @__llvm_retpoline_r11
# %bb.0:
	callq	.Ltmp6
.LBB1_2:                                # Block address taken
                                        # =>This Inner Loop Header: Depth=1
	pause
	lfence
	jmp	.LBB1_2
	.p2align	4, 0xcc
# %bb.3:                                # Block address taken
.Ltmp6:
	movq	%r11, (%rsp)
	retq
.Lfunc_end3:
	.size	__llvm_retpoline_r11, .Lfunc_end3-__llvm_retpoline_r11
                                        # -- End function
	.hidden	__retguard_52           # @__retguard_52
	.type	__retguard_52,@object
	.section	.openbsd.randomdata.retguard.52,"aGw",@progbits,__retguard_52,comdat
	.weak	__retguard_52
	.p2align	3
__retguard_52:
	.quad	0
	.size	__retguard_52, 8

	.hidden	__retguard_2655         # @__retguard_2655
	.type	__retguard_2655,@object
	.section	.openbsd.randomdata.retguard.2655,"aGw",@progbits,__retguard_2655,comdat
	.weak	__retguard_2655
	.p2align	3
__retguard_2655:
	.quad	0
	.size	__retguard_2655, 8

	.hidden	__retguard_2162         # @__retguard_2162
	.type	__retguard_2162,@object
	.section	.openbsd.randomdata.retguard.2162,"aGw",@progbits,__retguard_2162,comdat
	.weak	__retguard_2162
	.p2align	3
__retguard_2162:
	.quad	0
	.size	__retguard_2162, 8


	.addrsig
	.addrsig_sym pthread_mutex_lock
	.addrsig_sym pthread_cond_broadcast
	.addrsig_sym pthread_mutex_unlock
	.addrsig_sym pthread_cond_wait
	.addrsig_sym free
