//
// Created by Anvei on 2022/10/7.
//

#include "SequenceList.h"
#include <stdlib.h>

#define SEQLIST_INITSIZE 20
#define SEQLIST_INCREMENTSIZE 10

/**
 * 顺序表的初始化
 * @param plist
 * @return 初始化成功则返回true，反之则返回false
 */
bool seqlist_init(SequenceList *plist)
{
    seqlist_ele *pele = malloc(sizeof(seqlist_ele) * SEQLIST_INITSIZE);
    if (!pele) return false;
    plist->length = 0;
    plist->size = SEQLIST_INITSIZE;
    plist->data = pele;
    return true;
}

/**
 * 释放顺序表的内存
 * @param plist
 */
void seqlist_destory(SequenceList *plist)
{
    free(plist->data);
}

/**
 * 获取顺序表指定下标的元素
 * @param list
 * @param index
 * @return
 */
seqlist_ele  seqlist_get(SequenceList list, int index)
{
    return *(list.data + index);
}

/**
 * 对顺序表指定下标进行插入元素
 * @param plist
 * @param index
 * @param ele
 * @return 成功插入则返回true，否则返回false
 */
bool seqlist_insert(SequenceList *plist, int index, seqlist_ele ele)
{
    if (index > plist->length) return false;
    if (plist->length == plist->size)   // 如果顺序表容量已经满了，需要重新分配内存
    {
        seqlist_ele *temp = realloc(plist->data,
                                    sizeof(seqlist_ele) * (plist->length + SEQLIST_INCREMENTSIZE));
        if (!temp) return false;
        plist->size += SEQLIST_INCREMENTSIZE;
        plist->data = temp;
    }
    for (int i = index; i < plist->length; i++) // 将下标index开始的元素向后移一位
    {
        plist->data[i + 1] = plist->data[i];
    }
    plist->data[index] = ele;
    plist->length++;
    return true;
}

/**
 * 删除顺序表指定下标的元素
 * @param plist
 * @param index
 */
void seqlist_delete(SequenceList *plist, int index)
{
    for (int i = index; i < plist->length - 1; i++)     // 前移一位
    {
        plist->data[index] = plist->data[index + 1];
    }
    plist->length--;
}

/**
 * 清空顺序表
 * @param plist
 */
void seqlist_clear(SequenceList *plist)
{
    plist->length = 0;
}

/**
 * 判断顺序表是否为空
 * @param list
 * @return
 */
bool seqlist_empty(SequenceList list)
{
    return list.length == 0;
}