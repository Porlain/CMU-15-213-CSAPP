/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-19 13:59:31
 */
#include <iostream>
#include <assert.h>

using namespace std;

int fits_bits(int x, int n)
{
    int w = sizeof(int) << 3;
    int offset = w - n;
    return (x << offset >> offset) == x;
}

int main(int argc, char *argv[])
{
    assert(!fits_bits(0xFF, 8));
    assert(!fits_bits(~0xFF, 8));

    assert(fits_bits(0b0010, 3));
    assert(!fits_bits(0b1010, 3));
    assert(!fits_bits(0b0110, 3));

    assert(fits_bits(~0b11, 3));
    assert(!fits_bits(~0b01000011, 3));
    assert(!fits_bits(~0b111, 3));
    return 0;
}