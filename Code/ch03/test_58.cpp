#include <iostream>
// x、y和z通过寄存器%rdi、%rsi和%rdx,代码将返回值存放在寄存器%rax中。
// x in %rdi, y in %rsi, z in %rdx

// 1 decode2：
// 2	subq	%rdx，%rsi      y = y - z
// 3	imulq	%rsi，%rdi      x = x * y
// 4	movq	%rsi，%rax      res = y
// 5	salq	$63，%rax       res<<=63
// 6	sarq	$63，%rax       res>>=63
// 7	xorq	%rdi，%rax      res=res^x
// 8	ret

long decode2(long x, long y, long z)
{
    long res = y - z;
    return (res * x) ^ (res << 63 >> 63);
}

int main()
{
    std::cout << decode2(4, 5, 6) << std::endl;
    return 0;
}
