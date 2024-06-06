#include <iostream>
typedef __int128 int128_t;
void store_prod(int128_t *dest, int64_t x, int64_t y)
{
    *dest = x * (int128_t)y;
}

// dest in %rdi, x in %rsi, y in %rdx
//  1 store_prod:
//  2     movq   %rdx, %rax   # %rax = y
//  3     cqto                # 转换q为16字节长,即4字符号拓展到8字,假如y的符号位为1,那么%rdx所有位都是1(此时值是-1),否则,%rdx全为0(此时值是0).%rdx = yh
//  4     movq   %rsi, %rcx   # %rcx = x
//  5     sarq   $63,  %rcx   # 将%rcx向右移63位,跟%rdx的含义一样,二进制位要么全是1,要么是0,%rcx = xh（右移63位，获得符号）
//  6     imulq  %rax, %rcx   # %rcx = y * xh
//  7     imulq  %rsi, %rdx   # %rdx = x * yh
//  8     addq   %rdx, %rcx   # %rcx = y * xh + x * yh,计算了第二项
//  9     mulq   %rsi         # 无符号计算 xl*yl,mulq命令会将xl*yl的128位结果的高64位放在%rdx,低位放在%rax,计算了第三项.
//  10    addq   %rcx, %rdx   # 将第二项计算结果加到%rdx
//  11    movq   %rax, (%rdi) # 将%rax的值放到dest的低位
//  12    movq   %rdx, 8(%rdi)# 将%rdx的值放到dest的高位
//  13    ret
