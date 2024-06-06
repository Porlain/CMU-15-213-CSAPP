/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-17 10:59:19
 */
#include <stdio.h>
#include <assert.h>

int main()
{
    size_t mask = 0xff;
    size_t x = 0x89ABCDEF;
    size_t y = 0x76543210;

    size_t res = (x & mask) | (y & ~mask);

    assert(res == 0x765432EF);
    return 0;
}