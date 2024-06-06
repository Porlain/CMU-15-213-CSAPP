/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-19 16:46:46
 */
#include <iostream>
#include <assert.h>

using namespace std;

int divide_power2(int x, int k)
{
    // (x<0?x+(1<<k)-1:x)>>k
    int is_neg = x & INT_MIN;
    (is_neg && (x = x + (1 << k) - 1)); // 替代x<0? (x+((1<<k)-1))/(1<<k) ，如果is_neg=0，非负数，就不会给x增加偏执
    return x >> k;
}

int mul3div4(int x)
{
    int res = (x << 1) + x;
    res = divide_power2(res, 2);
    return res;
}

int main(int argc, char *argv[])
{
    int x = 0x87654321;
    assert(mul3div4(x) == x * 3 / 4);
    return 0;
}