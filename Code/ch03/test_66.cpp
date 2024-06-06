// long sum_col(long n, long A[NR(n)][NC(n)], long j)
// #n in %rdi, A in %rsi, j in %rdx
// sum_col:
// 	leaq	1(,%rdi,4), %r8			 #%r8 = 1 + 4 * n
// 	leaq	(%rdi,%rdi,2), %rax		 #%rax = 3 * n
// 	movq	%rax, %rdi				 #%rdi = %rax = 3 * n
// 	testq	%rax, %rax				 #检验 %rax
// 	jle		.L4					     #if %rax <= 0, goto L4
// 	salq	$3, %r8				     #%r8 = %r8 << 3 ,即8 *(4n+1)
// 	leaq	(%rsi,%rdx,8), %rcx		 #%rcx = %rsi + 8 * %rdx = A + 8 * j，所以开始时%rcx = A[0][j]的地址（参考test_64.cpp）
// 	movl	$0, %eax			     #%rax = 0 ，因为result要返回，所以在%rax中，即result = 0
// 	movl	$0, %edx				 #%rdx = 0，即i = 0
// .L3:
// 	addq	(%rcx), %rax			 #%rax = %rax + *rcx,即result += A[i][j]
// 	addq	$1, %rdx				 #%rdx = %rdx + 1，即i++
// 	addq	%r8, %rcx				 #%rcx = %rcx + %r8，此时%rcx是A[i+1][j]地址，
// 	#所以位移量8 * %r8 = 8 * (4n+1) ==> L = 8,C = 4n + 1,每行有4n+1个，NR = 4n + 1
// 	cmpq	%rdi, %rdx				 #比较 %rdx - %rdi，比较i和3n，C代码中的判断 i < NR(n)，所以NR=3n
// 	jne		.L3					     #if %rdx - %rdi != 0，相等就结束循环
// 	rep; ret
// .L4:
// 	movl	$0, %eax				 #%	rax = 0
// ret
