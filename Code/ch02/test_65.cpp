/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-18 17:21:25
 */
#include <iostream>
#include <assert.h>

using namespace std;

// - 待右移数是unsigned，则“>>”是逻辑右移。
//
// - 待右移数是signed，则“>>”是算数右移。

// https://www.cnblogs.com/fudanxi/p/17035408.html

// 简单解释：x是unsigned,逻辑右移，右移在高位填0
// 以8位为例：设x = d7 d6 d5 d4 d3 d2 d1 d0
// x = x >> 4 -> x = 0000 d7 d6 d5 d4
// 异或运算：相同为0，不同为1，x ^= x >> 4 比较后4位，也就是 d4 ^ d0, d5 ^ d1, d6 ^ d2, d7 ^ d3
// 如果d4 ^ d0的结果为1，则d4和d0必有一个1，也就是两者一共有奇数个1
// 如果结果为0，则必有偶数个1，其他位的异或结果同理
// 结论：x ^= x >> L 结果的最后L位将具有与x的原始值的最后2*L位的奇偶性相同
// 继续推导：记之前异或的结果为e0-e4 x = x >> 2 -> x = 000000 e4 e3,，则e3 ^ e0, e4 ^ e1,结果的文字表示同21行
// 最终剩下的一位，表达的是x中有奇数还是偶数个1，剩0，则偶数个1，剩1，则奇数个1

// -------------------------------------------
// 继续推导：这种形式下，& | 都表示x中至少有一个1
// -------------------------------------------

int odd_ones(unsigned x)
{
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    x &= 0x1;
    return x;
}

int main(int argc, char *argv[])
{
    assert(odd_ones(0x10101011));
    assert(!odd_ones(0x01010101));

    return 0;
}