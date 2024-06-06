/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-13 16:27:51
 */


// 事实上，不假设自己画图理解更方便,自己画几个方框，对各个寄存器进行标注，然后按照顺序解析即可，下面的答案比较繁琐了
// 假设%rcx: t1, %rdx: t2, %rsi: t3, %rax: t4, %rdi: t5，
// #对应内循环 for(j = 0; j < i; j++)
// #			 long t = A[i][j];
// #            A[i][j] = A[j][i] ;
// #            A[j][i] = t;

// .L6:
// 	movq		(%rdx), %rcx			#t1 = *t2，
// 	movq		(%rax), %rsi			#t3 = *t4,
// 	movq		%rsi, (%rdx)			#*t2 = t3，
// 	movq		%rcx, (%rax)			#*t4 = t1,此行和前面完成了对角线元素值的交换
// 	#*t2的值修改为*t4，*t4的值修改为*t2，即指针t2和t4指向的值进行交换，
// 	#所以A[i][j]为t2在%rdx中，A[j][i]为t4，在%rax中，t在%rcx中
// 	addq		$8, %rdx				#t2 += 8,因为是long，所以L=8，+8即指针t2右移一位（A[i][j] -> A[i][j+1]）
// 	addq		$120, %rax				#t4 += 120,指针t4（A[j][i]）移动120/8=15位（ A[j][i] -> A[j+1][i]），所以M=15
// 	cmpq		%rdi, %rax				#比较A[j][i]和边界，即%rdi指向A[M][M]
// 	jne			.L6						#if A[j][i] != A[M][M]
