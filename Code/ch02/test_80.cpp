#include <iostream>
#include <assert.h>

using namespace std;

int divide_power2(int x, int k, int is_neg)
{
    // (x<0?x+(1<<k)-1:x)>>k
    (is_neg && (x = x + (1 << k) - 1)); // 替代x<0? (x+((1<<k)-1))/(1<<k) ，如果is_neg=0，非负数，就不会给x增加偏执
    return x >> k;
}

int threeforths(int x)
{
    // 代码不能溢出，可以将x拆分为高位和低位进行计算
    int is_neg = x & INT_MIN;
    int f = x & ~0x3; // 高位
    int l = x & 0x3;  // 低位

    int fd4 = f >> 2;
    int fd4m3 = (fd4 << 1) + fd4;

    int lm3 = (l << 1) + l;
    int ld4m3 = divide_power2(lm3, 2, is_neg);
    return fd4m3 + ld4m3;
}

int main(int argc, char *argv[])
{
    assert(threeforths(8) == 6);
    assert(threeforths(9) == 6);
    assert(threeforths(10) == 7);
    assert(threeforths(11) == 8);
    assert(threeforths(12) == 9);

    assert(threeforths(-8) == -6);
    assert(threeforths(-9) == -6);
    assert(threeforths(-10) == -7);
    assert(threeforths(-11) == -8);
    assert(threeforths(-12) == -9);

    return 0;
}