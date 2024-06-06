#include <iostream>
#include <assert.h>

using namespace std;

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]); // line:data:show_bytes_printf
    printf("\n");
}

void show_int(int x)
{
    show_bytes((byte_pointer)&x, sizeof(int)); // line:data:show_bytes_amp1
}

int A(int x)
{
    // 不能使用if，使用C语言的逻辑运算，取非，在取反，与原数保持一致，如果x!=0则返回1，否则返回0
    return !~x;
}

int B(int x)
{
    // 直接取反，如果x==0（!x == 1）则返回1，否则返回0
    return !x;
}

int C(int x)
{
    // A为1的条件：任何位都为1，C的条件：低位为1，使用A的方法判断时需要将高位置为1，避免高位不全为1时对C判断的影响
    return A(x | ~0xff);
}

int D(int x)
{
    // B的条件：任何位都为0，D的条件，最高有效位为0
    // 直接使用B函数，由于x & 0xff保留了低位，如果低位不全为0，则判断会出现错误，所以需要删除低位，或者将低位全置为0
    return B(x >> ((sizeof(int) - 1) << 3) & 0xff);
}

void test()
{
    int all_bit_one = ~0;
    int all_bit_zero = 0;

    assert(A(all_bit_one));
    assert(!B(all_bit_one));
    assert(C(all_bit_one));
    assert(!D(all_bit_one));

    assert(!A(all_bit_zero));
    assert(B(all_bit_zero));
    assert(!C(all_bit_zero));
    assert(D(all_bit_zero));

    // test magic number 0x1234ff
    assert(!A(0x1234ff));
    assert(!B(0x1234ff));
    assert(C(0x1234ff));
    assert(D(0x1234ff));

    // test magic number 0x1234
    assert(!A(0x1234));
    assert(!B(0x1234));
    assert(!C(0x1234));
    assert(D(0x1234));
}

int main(int argc, char *argv[])
{
    int x = 12345;
    //=============
    //  规则与逻辑测试，结果如下：
    //  39 30 00 00
    //  00 ff ff ff
    //  39 00 00 00
    //  00 30 00 00
    //  ff 30 00 00
    //  39 ff ff ff
    //=============
    // show_int(x);
    // show_int(~0xff);
    // // 低位保留，高位置为0
    // show_int(x & 0xff);
    // // 高位保留，低位置为0
    // show_int(x & ~0xff);
    // // 高位保留，低位置为1
    // show_int(x | 0xff);
    // // 低位保留，高位置为1
    // show_int(x | ~0xff);

    // 判断答案是否正确
    test();

    return 0;
}