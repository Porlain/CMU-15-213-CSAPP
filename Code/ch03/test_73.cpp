/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-14 14:30:20
 */
// 图3-51 (a)
// typedef enum { NEG, ZERO, POS, OTHER } range_t;

// range_t find_range(float x){
//     range_t result;
//     if (x < 0){
//         result = NEG;
//     }else if (x == 0){
//         result = ZERO;
//     }else if (x > 0){
//         result = POS;
//     }else{
//         result = OTHER;
//     }
//     return result;
// }

// 图3-51 (b)
// #range_t find_range(float x)
// #x in %xmm0
// find_range: 
// 	vxorps	%xmm1,%xmm1,%xmm1	#Set % xmm1=0
// 	vucomiss	%xmm0,%xmm1		#Compare 0:x 比较%xmm1-%xmm0,即0-x
// 	ja	.L5						#If>, goto neg 
// 	vucomiss	%xmm1,% xmm0 	#Compare x:0,比较x-0
// 	jp	.L8						#If NaN, goto posornan 
// 	movl	$1,%eax				#result=ZERO 
// 	je	.L3						#If=, goto done
// .L8: 						#posornan: 
// 	vucomiss	.LC0(%rip),%xmm0 #Compare x:0
// 	setbe %al					#Set result=NaN?1:0
// 	movzbl	%al,%eax			#Zero-extend 
// 	add1	$2,%eax				#result+=2(POS for>0, OTHER for NaN)
// 	ret							#Return
// .L5: 						#neg:
// 	movl	$0,%eax				#result=NEG
// .L3: 						#done:
// 	rep;ret						#Return

// 修改汇编代码如下：
// vxorps %xmm1, %xmm1, %xmm1	#Set % xmm1=0
// vucomiss %xmm0, %xmm1		#Compare 0:x 比较%xmm1-%xmm0,即0-x
// ja .LA						#0>x
// je .LB						#0=x
// jb .LC						#0<x
// jp .LD						#NaN
// .LA:						#
//     movl $0, %eax			#
//     jmp .LE					#
// .LB:						#
//     movl $1, %eax			#
//     jmp .LE					#
// .LC:						#
//     movl $2, %eax			#
//     jmp .LE					#
// .LD:						#
//     movl $3, %eax			#
// .LE:						#

#include <stdio.h>
#include <limits.h>

typedef enum { NEG, ZERO, POS, OTHER } range_t;

range_t find_range_origin(float x){
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

range_t find_range(float x){
    //不能使用ret
    asm(
        "vxorps %xmm1, %xmm1, %xmm1\n\t"	
        "vucomiss %xmm0, %xmm1\n\t"
        "ja .LA\n\t"
        "je .LB\n\t"
        "jb .LC\n\t"
        "jp .LD\n\t"
        ".LA:\n\t"
            "movl $0, %eax\n\t"
            "jmp .LE\n\t"
        ".LB:\n\t"
            "movl $1, %eax\n\t"
            "jmp .LE\n\t"
        ".LC:\n\t"
            "movl $2, %eax\n\t"
            "jmp .LE\n\t"
        ".LD:\n\t"
            "movl $3, %eax\n\t"
        ".LE:\n\t"
    );
}

void test(){
    bool flag = true;
    int cnt = 0;
    for (short i = SHRT_MIN; i < SHRT_MAX; i++){
        if (find_range_origin(i) != find_range(i)){
            printf("Wrong result for %d!\n", i);
            flag = false;
            break;
        }
    }

    if (flag){
        printf("Passed the test!\n");
    }
}

int main(){
    test();
    return 0;
}

