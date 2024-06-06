#include <iostream>
#include <assert.h>

using namespace std;

// A:
//   这个问题的关键是找到y，k 和数字n的关系
//   我们假设这个数字是n
//   那么n = 0.yyyyyyyy... 这个时候是无法得出结果的，并没有用到k
//   那么要想用到k，我们把n左移k为 n << k = y.yyyyyyyy...(反正y是不断重复的)
//   因为y是k位序列，y.yyyyyyyyy... = y+0.yyyyy...=Y + n
//   因此得出 n << k = Y + n === > n << k - n = Y == > n = Y/(2^k - 1)


// B：
//     (a).
//     y = 101, Y = 5, k = 3
//     n = 5/7

//     (b).
//     y = 0110, Y = 6, k = 4
//     n = 2/5

//     (c).
//     y = 010011, Y = 19, k = 6
//     n = 19/63