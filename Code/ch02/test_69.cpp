/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-19 11:25:09
 */
#include <iostream>
#include <assert.h>

using namespace std;

typedef unsigned char *byte_pointer;

// x是unsigned，左移或者右移都是逻辑移位，填0
unsigned rotate_left(unsigned x, int n)
{
    int w = sizeof(int) << 3;
    /* pay attention when n == 0 */
    return x << n | x >> (w - n - 1) >> 1;
}

int main(int argc, char *argv[])
{
    assert(rotate_left(0x12345678, 4) == 0x23456781);
    assert(rotate_left(0x12345678, 20) == 0x67812345);
    return 0;
}