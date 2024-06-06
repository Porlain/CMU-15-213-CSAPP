/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-13 16:11:15
 */

// 对于一个声明如下的数组：
// T D[R][C];
// 它的数组元素D[i][j]的内存地址为
//     &D[i][j]=x_D+L(C*i+j)	(式3.1)   
// L是数据类型T以字节为单位的大小。x_D是数组头起始地址，加上L(C*i)得到该行起始地址                                                                                                                              

// A[R][S][T]；
// &A[i][j][k] = x_A + L[S * T * i + T * j + k] // S*T*i是算A[i],T*j算A[i][j]，+k得到A[i][j][k]，推到不出来的可以画个图

// #long store_ele(long i,long j,long k,long*dest)
// #i in %rdi,j in %rsi,k in %rdx, dest in %rcx
// store_ele：
// 	1eaq	(%rsi,%rsi,2),%rax	        #%rax = j + 2j = 3j
// 	leaq	(%rsi,%rax,4),%rax	        #%rax = j + 4 * (%rax) = 13j
// 	movq	%rdi,%rsi			        #%rsi = i，即j = i
// 	salq 	$6,%rsi				        #%rsi = i << 6
// 	addq	%rsi,%rdi			        #%rdi = i + i << 6 = i * 65
// 	addq	%rax,%rdi			        #%rdi = 65i + 13j
// 	addq	%rdi,%rdx 			        #%rdx = k + (65i + 13j)
// 	movq	A(,%rdx,8),%rax		        #%rax = A + 8 * [k + (65i + 13j)]
// 	movq	%rax,(%rcx)			        #将dest存放的地址修改为A + 8 * [k + (65i + 13j)]，即L = 8(long为八字节),65 = ST,T = 13，S = 5
// 	movl	$3640,%eax			        #%rax = $3640,即sizeof(A)，R*S*T = 3640/8 = 455，得到R = 455/ST = 7
// 	ret 						

