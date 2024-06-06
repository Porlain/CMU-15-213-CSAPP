/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-18 14:18:41
 */
#include <iostream>
#include <assert.h>

using namespace std;

typedef unsigned char *byte_pointer;

int int_shifts_are_arithemetic()
{
    // 算数右移：右移时高位补现在的最高位，如001右移1位000,111右移1位，111
    // 逻辑右移：高位补0，低位舍弃
    // 异或：相同为0，不同为1,相同为算数右移，不同为逻辑右移
    // 题目要求，相同返回1，不同返回0，所以需要增加！
    int num = -1;
    return !num ^ (num >> 1);
}

int main(int argc, char *argv[])
{
    assert(int_shifts_are_arithemetic());

    return 0;
}