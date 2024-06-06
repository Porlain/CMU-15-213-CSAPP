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

int main(int argc, char *argv[])
{
    int x = 0x80000007;
    assert(divide_power2(x, 1) == x / 2);
    assert(divide_power2(x, 2) == x / 4);
    return 0;
}