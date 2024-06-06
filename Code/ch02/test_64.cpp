/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-18 15:19:29
 */
#include <iostream>
#include <assert.h>

using namespace std;

int any_odd_one(unsigned x)
{   
    // 返回1或者0，直接返回的话是10进制的值，可能是0-INT_MAX之间的任意数字
    return !!(0xAAAAAAAA & x);
}

int main(int argc, char *argv[])
{
    int test = 0xAA11;
    printf("%d", any_odd_one(test));

    return 0;
}