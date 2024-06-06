/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-14 14:37:23
 */

typedef enum { NEG, ZERO, POS, OTHER } range_t;

range_t find_range(float x){
    range_t result;
    if (x < 0){
        result = NEG;
    }else if (x == 0){
        result = ZERO;
    }else if (x > 0){
        result = POS;
    }else{
        result = OTHER;
    }
    return result;
}

// find_range:
//     vxorps %xmm1, %xmm1, %xmm1	#x设置为0
//     movq $0, %r8				#
//     movq $1, %r9				#
//     movq $2, %r10				#
//     movq $3, %rax				#默认为NaN
//     vucomiss %xmm1, %xmm0		#比较x:0,
//     cmovb %r8, %rax				#x<0,设置为0
//     cmove %r9, %rax				#x=0
//     cmova %r10, %rax			#x>0
//     ret

// linux反汇编生成代码如下：
// 0000000000000000 <_Z10find_rangef>:
//    0:   66 0f ef c9             pxor   %xmm1,%xmm1
//    4:   0f 2e c8                ucomiss %xmm0,%xmm1
//    7:   77 16                   ja     1f <_Z10find_rangef+0x1f>
//    9:   0f 2e c1                ucomiss %xmm1,%xmm0
//    c:   7a 02                   jp     10 <_Z10find_rangef+0x10>
//    e:   74 15                   je     25 <_Z10find_rangef+0x25>
//   10:   0f 2e 05 00 00 00 00    ucomiss 0x0(%rip),%xmm0        # 17 <_Z10find_rangef+0x17>
//   17:   76 12                   jbe    2b <_Z10find_rangef+0x2b>
//   19:   b8 02 00 00 00          mov    $0x2,%eax
//   1e:   c3                      retq   
//   1f:   b8 00 00 00 00          mov    $0x0,%eax
//   24:   c3                      retq   
//   25:   b8 01 00 00 00          mov    $0x1,%eax
//   2a:   c3                      retq   
//   2b:   b8 03 00 00 00          mov    $0x3,%eax
//   30:   c3                      retq   