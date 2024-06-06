/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-04-19 15:19:07
 */
#include <iostream>
#include <assert.h>

using namespace std;

int tsub_ok(int x, int y)
{
    if (y == INT_MIN)
        return 0;
    int neg_y = -y;
    int sum = x + neg_y;
    int postivate_flag = x > 0 && neg_y > 0 && sum < 0;
    int negtivate_flag = x < 0 && neg_y < 0 && sum >= 0;
    return !(postivate_flag || negtivate_flag);
}

int main(int argc, char *argv[])
{
    assert(!tsub_ok(0x00, INT_MIN));
    assert(tsub_ok(0x00, 0x00));
    return 0;
}