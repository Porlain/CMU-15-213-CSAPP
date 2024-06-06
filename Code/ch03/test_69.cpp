/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-14 13:59:02
 */


// #void test(long i, b_struct *bp)
// #i in %rdi, bp in %rsi:
// 000000000000000 <test>:
// 	0:	8b 8e 20 01 00 00	mov	0x120(%rsi),%ecx   		#%rcx=*(bp+288),访问bp->last（因为first和a[CNT]都不会＋288），由于对齐原则是保证8的倍数，所以8+CNT*sizeof(a_struct)=288
// 	6:	03 0e            	add	(%rsi),%ecx		   		#%rcx+=*bp=>*(bp+288)+*bp，即bp->first+bp->last，可知%rcx存的n
// 	8:	48 8d 04 bf      	lea	(%rdi,%rdi,4), %rax	 	#%rax=5*i
// 	c:	48 8d 04 c6      	lea	(%rsi,%rax,8), %rax   	#%rax=bp+8*%rax=bp+40*i
  
// 	10:	48 8b 50 08 		mov	0x8(%rax),%rdx       	#%rdx=*(%rax+8)，即bp+40*i+8，
// 	# ap = &bp->a[i] = bp+8+i*40, +8意味着从bp开始的第1个八字节里面只有int（first占8），且a_struct大小必为8字节或更大，若为4字节，就不是+8而是+4了（不然4+4可以直接跟8对齐不需要将4填补4字节来对齐）
// 	# 因为是i*40，所以a_struct大小为40字节，因为first占8个字节，所以cnt=(288-8)/40=7
// 	# 此句很明显取出了一个数，再结合倒数第二条指令mov %rcx, 0x10(%rax,%rdx,8)，所以%rdx为ap->idx，
// 	# 而且在结构体a_struct中，第一个成员为整数类型的idx
	
// 	14:	48 63 c9         	movslq %ecx,%rcx			#%rcx = %ecx (带符号拓展)
// 	17:	48 89 4c d0 10   	mov	%rcx,0x10(%rax,%rdx,8)	#*(%rax+8*%rdx+16)=%rcx，即ap->x[ap->idx]=n，
// 	# 先看0x10(%rax,)部分，是bp+16+i*40，比ap多了8字节，这里是a_struct数组成员的开始地址，也说明了idx大小为8字节
//  # 再看(,%rdx,8)部分，是idx*8，所以说明了a_struct数组成员的大小为8字节
//  # 合起来看就是bp+8+i*40+8 +idx*8，第二个+8跳过了a_struct的整数成员idx
 	
// 	# a_struct大小为40字节，第一个成员idx为long，8字节，还剩32字节
//  # 第二个成员是long型数组，按照剩余字节，数组大小为4	
// 	1c:	c3               	retq

typedef struct {
	long idx;
	long x[4];
} a_struct;

