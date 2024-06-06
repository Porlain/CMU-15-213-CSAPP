/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-13 14:58:50
 */
/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-13 14:57:49
 */
#include <iostream>

long loop(long x, int n)
{
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = mask << n)
    {
        result |= mask & x;
    }
    return result;
}

// 首先看汇编代码，对汇编代码进行注释

// x in %rdi, n in %esi,result in %rax

// loop:
// 	movl	%esi,%ecx       把n放入%ecx(n是int,用movl)
// 	movl	$1,%edx         把1放入%edx
//  mov1	$0,%eax         把0放入%eax
// 	jmp	.L26                跳转到标号.L2

// .L3:
// 	movq	%rdi,%r8        把x放入%r8(x是long,用movq)
//  andq	%rdx,%r8        %r8 = %r8 & %rdx，即 & %edx 中的1，相当于判断x最低位是1还是0（%r8 = x & mask）
//  orq		%r8,%rax        %rax = %rax | %r8，即 %eax 中的 0 与 %r8 或运算,若x最低位是1得1，否则0 (result |= %r8)
// 	salq	%c1,%rdx        %rdx << = %rcx的字节（%c1为%rcx最低8位，即n的低8位）

// .L2:
// 	testq	%rdx,%rdx       检验%rdx & %rdx（mask in %rdx）
// 	jne	.L3                 jne即不等/ZF非零时跳转，即%rdx非零就跳转到标号L3
//  rep; ret
