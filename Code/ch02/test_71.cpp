/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-19 14:35:42
 */
/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-19 14:08:20
 */
#include <iostream>
#include <assert.h>

using namespace std;

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum)
{
    // word 是unsigned 类型，使用逻辑运算，左右移都填0
    // word >> (bytenum << 3) & 0xff不能提取负数，0xAABBCCDD, 1会变为0x000000CC,正确为0xFFFFFFCC
    // 变成算数右移就可以了,unsigned -> int
    // 只能使用左右移位和减法
    int size = sizeof(unsigned);
    int left_size = (size - bytenum  - 1)<< 3;
    int right_size = (size - 1) << 3;
    return (int)word << left_size >> right_size;
}

int main(int argc, char *argv[])
{
    // 补码运算，算数右移，右移填1，左移填0
    assert(xbyte(0x00112233, 2) == 0x11);
    assert(xbyte(0x00112233, 0) == 0x33);
    assert(xbyte(0x00112233, 1) == 0x22);
    assert(xbyte(0x00112233, 3) == 0x00);

    assert(xbyte(0xAABBCCDD, 0) == 0xFFFFFFDD);
    assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
    assert(xbyte(0xAABBCCDD, 2) == 0xFFFFFFBB);
    assert(xbyte(0xAABBCCDD, 3) == 0xFFFFFFAA);

    return 0;
}