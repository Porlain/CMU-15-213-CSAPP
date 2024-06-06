#include <iostream>
#include <assert.h>

using namespace std;

// 有符号数的x*y高32位结果
int signed_high_prod(int x, int y)
{
    int64_t mul = x * y;
    return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
    int sig_x = x >> 31; // 获取x的符号，0或者1
    int sig_y = y >> 31; // 获取y的符号

    return signed_high_prod(x, y) + x * sig_y + y * sig_x;
}

/* 通过64位计算来验证a theorically correct version to test unsigned_high_prod func */
unsigned another_unsigned_high_prod(unsigned x, unsigned y)
{
    uint64_t mul = (uint64_t)x * y; // 通过64得到2w位的乘积结果
    return mul >> 32;
}

int main(int argc, char *argv[])
{
    unsigned x = 0x12345678;
    unsigned y = 0xFFFFFFFF;
    // 比较结果
    assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));
    return 0;
}