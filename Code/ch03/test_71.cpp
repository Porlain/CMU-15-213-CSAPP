/*
 * @Create: Created by Porlain on 2024
 * @Author: Porlain szbj2023@163.com
 * @LastEditTime: 2024-05-14 14:18:32
 */

// 这道题主要需要了解fgets函数 char * fgets ( char * str, int num, FILE * stream );。下面将fgets函数的api文档进行翻译。

// Get string from stream#
// 从流中读取字符，并将其作为一个C语言字符串存储到str中，直到读完(num-1)个字符或达到换行符或文件结束，以先发生者为准。
// 换行符使fgets停止读取，但它被函数认为是一个有效的字符，并包括在拷贝到str的字符串中。
// 一个结束性的空字符会自动附加在复制到str的字符之后。
// 请注意，fgets与gets完全不同：fgets不仅接受一个流参数，而且允许指定str的最大尺寸，并在字符串中包括任何结束的换行字符。

// Return Value#
// 成功时，该函数返回str。
// 如果在试图读取一个字符时遇到了文件结束，则设置eof指示器（ffe）。如果在可以读取任何字符之前发生这种情况，返回的指针是一个空指针（而str的内容保持不变）。
// 如果发生读取错误，错误指示器（ferror）被设置，同时返回一个空指针（但str所指向的内容可能已经改变）。

#include <stdio.h>
#include <assert.h>

#define BUF_SIZE 2

void good_echo()
{
    char buf[BUF_SIZE];
    while (1)
    {
        char *p = fgets(buf, BUF_SIZE, stdin);
        // 可以使用int ferror ( FILE * stream );来判断（stdin的类型是FILE *），当读取出错时，调用ferror函数返回非0值
        if (p == NULL)
        { // 修改为if ( (p == NULL) & (ferror(stdin) != 0) )
            break;
        }
        printf("%s", p);
    }
    return;
}

int main()
{
    good_echo();
}