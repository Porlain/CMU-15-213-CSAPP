/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-14 14:05:50
 */


// A.因为访问union中的元素不需要加偏移量，所以e1.p和e2.x作为e1和e2的第一个元素偏移量都是0
// 字段	偏移量
// e1.p	0
// e1.y	8
// e2.x	0
// e2.next	8

// B.这个结构总共需要多少个字节？
// union需要的字节等于它最大字段的大小，8+8=16

// #void proc(union ele up)
// #up in %rdi
// proc:
//     movq    8(%rdi), %rax  #偏移量为8，存的是up->e1.y或者是up->e2.next
//     movq    (%rax), %rdx   #用作内存引用(P121)，取出该地址中的值，所以上面是up->e2.next，
//     #取出*(up->e2.next)的偏移量为0的内容，也有两种情况： *(up->e2.next).e1.p或*(up->e2.next).e2.x)
    
//     movq    (%rdx), %rdx   #用作内存引用，所以上面是*(up->e2.next).e1.p，取出*( *(up->e2.next).e1.p )的内容，为long型
//     subq    8(%rax), %rdx  #取出*(up->e2.next)的偏移量为8的内容，因为要作为减数，所以减数是*(up->e2.next).e1.y
//     movq    %rdx, (%rdi)   #将减法之差存入，up->e2.x
//     ret
#include<stdio.h>
union ele{
	struct{
		long *p;
		long y;
	}e1;
	struct{
		long x;
        union ele *next;
	}e2;
};

void proc (union ele *up) {
    up->e2.x = *(*(up->e2.next).e1.p) - up->e2.next.e1.y;
}



