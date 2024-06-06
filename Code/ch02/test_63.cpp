/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-18 15:08:38
 */
#include <iostream>
#include <assert.h>

using namespace std;

typedef unsigned char *byte_pointer;

unsigned srl(unsigned x, int k)
{
    unsigned xsra = (int)x >> k;
    // 算数右移实现逻辑右移，不能使用右移或除法
    // 将高位全部置为0即可
    // 补码负数左移填0
    int w = sizeof(int) << 3;
    int mask = (int)-1 << (w - k);
    return xsra & ~mask;
}

int sra(int x, int k)
{
    int xsrl = (unsigned)x >> k;
    // 用逻辑右移实现算数右移，不能使用右移或除法
    // (补码)算数右移：右移时高位补现在的最高位，如001右移1位000,111右移1位，111
    // (补码)逻辑右移：高位补0，低位舍弃
    // 高位置为x的最高数值，低位为0 | xsrl即可
    int w = sizeof(int) << 3;
    int mask = (int)-1 << (w - k);

    // 当前最高位的数值
    int m = 1 << (w - 1);
    mask &= !(x & m) - 1;
    return xsrl | mask;
}

int main(int argc, char *argv[])
{
    unsigned test_unsigned = 0x12345678;
    int test_int = 0x12345678;

    assert(srl(test_unsigned, 4) == test_unsigned >> 4);
    assert(sra(test_int, 4) == test_int >> 4);

    test_unsigned = 0x87654321;
    test_int = 0x87654321;

    assert(srl(test_unsigned, 4) == test_unsigned >> 4);
    assert(sra(test_int, 4) == test_int >> 4);

    return 0;
}