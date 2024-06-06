/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-13 15:22:56
 */
#include <iostream>

// 事实上，在最新的gcc版本上编译，两者貌似没什么区别

// 编译与反汇编命令：
// gcc -Og -fno-stack-protector -c test.cpp
// objdump -d test.o

// 生成结果：
// 0000000000000000 <_Z9cread_altPl>:
//    0:   48 85 ff                test   %rdi,%rdi
//    3:   74 04                   je     9 <_Z9cread_altPl+0x9>
//    5:   48 8b 07                mov    (%rdi),%rax
//    8:   c3                      retq   
//    9:   b8 00 00 00 00          mov    $0x0,%eax
//    e:   c3                      retq   

// 000000000000000f <_Z5creadPl>:
//    f:   48 85 ff                test   %rdi,%rdi
//   12:   74 04                   je     18 <_Z5creadPl+0x9>
//   14:   48 8b 07                mov    (%rdi),%rax
//   17:   c3                      retq   
//   18:   b8 00 00 00 00          mov    $0x0,%eax
//   1d:   c3                      retq   

// 以下是原回答与解题
// 条件表达式
// v=then-expr;
// ve=else-expr;
// t=test-expr;
// if(!t)
//     v=ve;

// create 汇编
// long cread(long *xp){
// 	return(xp ? *xp : 0);
// }

// xp in %rdi

// cread:
//   movq (%rdi), %rax	#v=then-expr，即使判断条件为false此行还是间接引用了空指针
//   testq %rdi, %rdi	#检验t
//   movl $0, %edx		#ve=0
//   cmove %rdx, %rax	#若t==0,进行传送操作，v=ve
//   ret				#return v

// 规避对空指针的计算，判断条件改为!xp
long cread_alt(long *xp) {
  return (!xp ? 0 : *xp);
}

// # long cread_alt(long* xp)
// # xp in %rdi
// cread_alt:
//   movl $0, %eax		#v=then-expr
//   testq %rdi, %rdi	#检验!t
//   cmovne (%rdi), %rax#若!t==0,即t不为空指针，进行传送操作，v=ve，得到*xp



