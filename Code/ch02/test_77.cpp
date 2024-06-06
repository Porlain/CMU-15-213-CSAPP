#include <iostream>
#include <assert.h>

using namespace std;

int A(int x)
{
    return (x << 4) + x;
}

int B(int x)
{
    return x - (x << 3);
}

int C(int x)
{
    return (x << 6) - (x << 2);
}
int D(int x)
{
    return (x << 4) - (x << 7);
}

int main(int argc, char *argv[])
{
    int x = 0x12345678;

    assert(A(x) == x * 17);
    assert(B(x) == x * -7);
    assert(C(x) == x * 60);
    assert(D(x) == x * -112);

    printf("Passed.\n");
    return 0;
}