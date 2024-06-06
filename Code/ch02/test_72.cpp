#include <iostream>
#include <assert.h>

using namespace std;

void copy_int(int val, void *buf, int maxbytes)
{   
    // sizeof返回size_t是unsigned类型，maxbytes - sizeof(val)返回unsigned，永远>=0
    // 将sizeof返回值设置为int或者直接比较即可
    if (maxbytes >= sizeof(val))
        memcpy(buf, (void *)&val, sizeof(val));
}

int main(int argc, char *argv[])
{
    int maxbytes = sizeof(int) * 10;
    void *buf = malloc(maxbytes);
    int val;

    val = 0x12345678;
    copy_int(val, buf, maxbytes);
    assert(*(int *)buf == val);

    val = 0xAABBCCDD;
    copy_int(val, buf, 0);
    assert(*(int *)buf != val);

    free(buf);
    return 0;
}