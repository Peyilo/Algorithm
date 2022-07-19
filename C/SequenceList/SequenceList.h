//
// Created by 35433 on 2022/7/19.
// Sequence List实现
//

#ifndef SEQUENCELIST_SEQUENCELIST_H
#define SEQUENCELIST_SEQUENCELIST_H

#define INITSIZE 30     // 初始化大小
#define LISTINCREMENT 10    // 每次递增的大小
/* 状态代码Status */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

/* 类型定义 */
typedef int Status;
typedef double ElemType;
typedef struct
{
    ElemType *elem;     // 一个ElemType数组
    int length;     // 当前元素的个数
    int size;     // 存储空间大小
}SqList;

/* 提供的接口 */
Status initList(SqList *pList);     // 顺序表的初始化
void destroyList(SqList *pList);    // 顺序表的销毁
void clearList(SqList *pList);      // 顺序表的清空
Status listEmpty(SqList list);      // 判断顺序表是否为空
int listLength(SqList list);        // 获取顺序表的长度
Status getElem(SqList list, int index, ElemType *pElem);
int locateElem(SqList list, ElemType elem, Status (*compare)(ElemType, ElemType));
Status priorElem(SqList list, ElemType curElem, ElemType *pPreElem);
Status nextElem(SqList list, ElemType curElem, ElemType *pNextElem);
Status listInsert(SqList *pList, int index, ElemType elem);
Status listDelete(SqList *pList, int index, ElemType *pElem);
void mergeList(SqList list1, SqList list2, SqList *pList);
void minList(SqList *pList);
Status listTraverse(SqList list, Status (*visit)(ElemType elem));
#endif //SEQUENCELIST_SEQUENCELIST_H
