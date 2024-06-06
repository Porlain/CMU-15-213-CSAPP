/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-19 11:20:43
 */
#include <iostream>
#include <assert.h>

using namespace std;

typedef unsigned char *byte_pointer;

int lower_one_mask(int n)
{
    int w = sizeof(int) << 3;
    return (unsigned)-1 >> (w - n);
}

int main(int argc, char *argv[])
{
    assert(lower_one_mask(6) == 0x3F);
    assert(lower_one_mask(17) == 0x1FFFF);
    assert(lower_one_mask(32) == 0xFFFFFFFF);
    return 0;
}