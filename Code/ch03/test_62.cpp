/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-13 15:36:31
 */
/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-13 15:35:23
 */

// 首先看汇编代码：
// p1 in %rdi, p2 in %rsi, action in %edx，result in %rax

// .L8:								    MODE_E
// 	movl	$27,%eax	                %eax = 27
// 	ret

// .L3: 								MODE_A
// 	movq	(%rsi),%rax                 %rax = *p2，将%rsi中的内容当作地址寻址，p2寻址找到p2指向的值
// 	movq 	(%rdi),%rdx	                %rdx = *p1，和上面类似
// 	movq	 %rdx,(%rsi)                *p2 = %rdx，即*p2 = *p1
// 	ret

// .L5: 								MODE_B
// 	movq	(%rdi),%rax                 %rax = *p1
// 	addq	(%rsi),%rax                 %rax += *p2
// 	movq 	%rax,(%rdi)                 *p1 = %rax
// 	ret

// .L6:  								MODE_C
// 	movq 	$59,(%rdi)                  *p1=59
// 	movq	(%rsi),%rax                 %rax = *p2
// 	ret

// .L7:  								MODE_D
// 	movq	(%rsi),%rax                 %rax = *p2
// 	movq	 %rax,(%rdi)                *p1 = *p2
// 	mov1	$27,%eax	                %rax = 27
// 	ret

// .L9:  								default
// 	movl	$12,%eax	                rax=12
// 	ret

/* Enumerated type creates set of contants numbered 0 and upward */
#include <stdio.h>
typedef enum
{
    MODE_A,
    MODE_B,
    MODE_C,
    MODE_D,
    MODE_E
} mode_t;

long switch3(long *p1, long *p2, mode_t action)
{
    long result = 0;
    switch (action)
    {
    case MODE_A:
        result = *p2;
        *p2 = *p1;
        break;
    case MODE_B:
        *p1 = *p1 + *p2;
        result = *p1;
        break;
    case MODE_C:
        *p1 = 59;
        result = *p2;
        break;
    case MODE_D:
        *p1 = *p2;
        result = 27;
        break;
    case MODE_E:
        result = 27;
        break;
    default:
        result = 12;
        break;
    }
    return result;
}
