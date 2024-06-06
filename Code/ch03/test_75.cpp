/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-14 14:37:54
 */


// double c_imag(double complex x)
// c_imag:
// 	movapd	%xmm1, %xmm0		#r0 = r1
// 	ret                 		#return r0
	
// double c_real (double complex x)
// c_real:
// 	rep; ret             		#return r0
	
// double complex c_sub(double complex x, double complex y)
// c_sub:
// 	subsd	%xmm2, %xmm0		#t0 -= t2实部相减
// 	subsd	%xmm3, %xmm1		#t1 -= t3虚部相减
// 	ret																

// A.如何向函数传递复数参数？

// %xmm0存储实部，%xmm1存储虚部。

// B. 如何从函数返回复数值？

// 返回%xmm0,%xmm1。