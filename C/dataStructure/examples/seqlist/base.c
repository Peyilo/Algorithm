//
// Created by Anvei on 2022/10/7.
//
/**
 * 顺序表是一种下标取值时间复杂度为O(1)、插入和删除时间复杂度O(n)的顺序存储结构
 */
#include <stdio.h>
#include "../../SequenceList.h"

void seqlist_print(SequenceList list)
{
    for (int i = 0; i < list.length; i++)
    {
        printf("%2d ", seqlist_get(list, i));
        if ((i + 1) % 10 == 0)
            putchar('\n');
    }
}

int main(void)
{
    SequenceList seqlist;
    seqlist_init(&seqlist);
    for (int i = 0; i < 100; i++)
    {
        seqlist_insert(&seqlist, i, i);
    }
    seqlist_print(seqlist);
    seqlist_destory(&seqlist);      // 记得释放内存
    return 0;
}