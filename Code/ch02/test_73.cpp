#include <iostream>
#include <assert.h>

using namespace std;

int saturating_add(int x, int y)
{
    // 判断是否溢出：两个正数相加，结果<0,两个负数相加，结果>0
    // 不能使用if判断

    // 提取符号
    int x_sign_mask = x >> ((sizeof(int) << 3) - 1);
    int y_sign_mask = y >> ((sizeof(int) << 3) - 1);

    int sum = x + y;
    int sum_sign_mask = sum >> ((sizeof(int) << 3) - 1);

    // 正溢出,符号：x : 00000000 y : 00000000, sum : ffffffff
    int postive_flag = ~x_sign_mask & ~y_sign_mask & sum_sign_mask;

    // 负溢出,符号: x : ffffffff y : ffffffff, sum : 00000000
    int negativate_flag = x_sign_mask & y_sign_mask & ~sum_sign_mask;

    return sum = (INT_MAX & postive_flag) | (INT_MIN & negativate_flag) | (sum & ~(postive_flag | negativate_flag));
}

int main(int argc, char *argv[])
{

    return 0;
}