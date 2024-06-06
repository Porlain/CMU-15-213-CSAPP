#include <iostream>
#include <assert.h>
#include <string.h>

using namespace std;

void *another_calloc(size_t nmemb, size_t size)
{
    if (nmemb == 0 || size == 0)
        return NULL;
    // 所需要的内存
    size_t buff_size = nmemb * size;
    // 计算溢出
    if (buff_size / size == nmemb)
    {
        void *ptr = malloc(buff_size);
        memset(ptr, 0, buff_size);
        return ptr;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    void *p;
    p = another_calloc(0x1234, 1);
    assert(p != NULL);
    free(p);

    p = another_calloc(SIZE_MAX, 2);
    assert(p == NULL);
    free(p);

    return 0;
}