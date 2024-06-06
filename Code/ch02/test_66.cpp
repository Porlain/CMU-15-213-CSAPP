#include <iostream>
#include <assert.h>

using namespace std;

// 参看链接：https://www.cnblogs.com/fudanxi/p/17035408.html

// 首先，生成一个掩码，使最左边的一位之后的所有位都是1。

// 例如，0xFF00 -> 0xFFFF，以及0x6000 -> 0x7FFF，如果x=0，就得到0
// 如何利用最左边的1将此1右边的所有位都填满1呢，通过 mask |= mask >> 2^n 的操作，每次填满 2 的幂次个 1，由 n = 0到 n = 4 即可填滿 32 位元。

// 例如：x=0100 0000 0000 0000 ...0，

// n=0=>x1=0110 0000 0000 0000 ...0，//最左边的1会往右移动2的0次方个位，

// n=1=>x2=0111 1000 0000 0000 ...0，//左边的两个1会往右移动2的1次方个位，

// n=2=>x3=0111 11111 1000 0000 ...0，//左边的4个1会往右移动2的2次方个位，

// n=3，n=4，左边的1会依次填满 2 的幂次个 1。直到右边全部为1。
// 右移一位(先加 1 有可能 overflow) 再+1，(mask >> 1) + 1，即0011 1111=>0001 1111再+1得到0010 0000。

// 考虑x可能为0，所以与自己做与运算，x & ((mask >> 1) + 1)

int leftmost_one(unsigned x)
{
    unsigned mask = x;
    mask |= x >> 1;
    mask |= x >> 2;
    mask |= x >> 4;
    mask |= x >> 8;
    mask |= x >> 16;
    return x & ((mask >> 1) + 1);
}

int main(int argc, char *argv[])
{
    printf("Left most bit of 0xff00 is 0x%x\n", leftmost_one(0xff00));
    printf("Left most bit of 0x6600 is 0x%x\n", leftmost_one(0x6600));
    printf("Left most bit of 0x0001 is 0x%x\n", leftmost_one(0x0001));
    printf("Left most bit of 0x0000 is 0x%x\n", leftmost_one(0x0000));

    return 0;
}