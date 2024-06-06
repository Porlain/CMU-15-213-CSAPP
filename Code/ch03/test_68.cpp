/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-13 17:09:58
 */

// #void setVal(strl*p,str2*q)
// #p in %rdi,q in %rsi  
// setVal:
// 	movslq 	8(%rsi),%rax	#%rax=*(8 + q)，访问q->t，所以char array[B]占据8字节，因为需要考虑对齐原则，所以先得出 B <= 8
// 	addq	32(%rsi),%rax 	#%rax=%rax+*(32 + q)，计算v1+v2，通过+32访问q->u,32减去int占据的4得到short s[A]占据的，所以4 + A * 2 <= 32 - 8 <= 24得到A<=10
// 	movq	%rax,184(%rdi)	#*(184 + p)=%rax,+184访问p->y，由于对齐原则是保证8的倍数,所以176 < 4*A*B <= 184，得44 < A*B <=46
// 	#所以A*B = 45 或者A*B = 46，结合A, B各自的范围，只可能为A = 9, B = 5.
// ret
