//
// Created by 35433 on 2022/7/19.
// Sequence List实现
//

#ifndef SEQUENCELIST_SEQUENCELIST_H
#define SEQUENCELIST_SEQUENCELIST_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define INITSIZE 30     // 初始化大小
#define LISTINCREMENT 10    // 每次递增的大小

/* 类型定义 */
typedef double ElemType;
typedef struct
{
    ElemType *elem;     // 一个ElemType数组
    int length;     // 当前元素的个数
    int size;     // 存储空间大小
}SqList;

/* 提供的接口 */
bool initList(SqList *pList);     // 顺序表的初始化

void destroyList(SqList *pList);    // 顺序表的销毁

void clearList(SqList *pList);      // 顺序表的清空

bool listEmpty(SqList list);      // 判断顺序表是否为空

int listLength(SqList list);        // 获取顺序表的长度

ElemType getElem(SqList list, int index);

int locateElem(SqList list, ElemType elem, bool (*compare)(ElemType, ElemType));

ElemType priorElem(SqList list, ElemType curElem);

ElemType nextElem(SqList list, ElemType curElem);

bool listInsert(SqList *pList, int index, ElemType elem);

ElemType listDelete(SqList *pList, int index);

void mergeList(SqList list1, SqList list2, SqList *pList);

bool minList(SqList *pList);

void listTraverse(SqList list, void (*visit)(ElemType elem));

#endif //SEQUENCELIST_SEQUENCELIST_H
