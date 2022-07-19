//
// Created by 35433 on 2022/7/19.
//

#include "SequenceList.h"
#include <stdlib.h>
Status initList(SqList *pList)
{
    pList->elem = (ElemType*)malloc(INITSIZE * sizeof(ElemType));
    if(!pList->elem) exit(OVERFLOW);
    pList->length = 0;
    pList->size = INITSIZE;
    return OK;
}

void destroyList(SqList *pList)
{
    if(pList->elem) free(pList->elem);
    pList->length = 0;
    pList->size = 0;
}

void clearList(SqList *pList)
{
    pList->length = 0;
}

Status listEmpty(SqList list)
{
    return list.length == 0 ? TRUE : FALSE;
}

int listLength(SqList list)
{
    return list.length;
}

Status getElem(SqList list, int index, ElemType *pElem)
{
    if(index > list.length - 1 || index < 0) return ERROR;
    *pElem = list.elem[index];
    return OK;
}

int locateElem(SqList list, ElemType elem, Status (*compare)(ElemType, ElemType))
{
    int index = -1;
    for(int i = 0; i < list.length; i++)
    {
        if(compare(list.elem[i], elem))
        {
            index = i;
            break;
        }
    }
    return index;
}

Status equal(ElemType elem1, ElemType elem2)
{
    if(elem1 == elem2) return TRUE;
    return FALSE;
}

Status priorElem(SqList list, ElemType curElem, ElemType *pPreElem)
{
    int index = locateElem(list, curElem, equal);
    if(index < 1) return ERROR;
    getElem(list, index - 1, pPreElem);
    return OK;
}

Status nextElem(SqList list, ElemType curElem, ElemType *pNextElem)
{
    int index = locateElem(list, curElem, equal);
    if(index < 0 || index == list.length - 1) return ERROR;
    getElem(list, index + 1, pNextElem);
    return OK;
}

Status listInsert(SqList *pList, int index, ElemType elem)
{
    // 处理下标越界问题
    if(index < 0 || index > pList->length) return ERROR;
    // 处理顺序表容量不够问题
    if(pList->length >= pList->size)
    {
        ElemType *temp = (ElemType*)realloc(pList->elem, (pList->size + LISTINCREMENT) * sizeof(ElemType));
        if(!temp) exit(OVERFLOW);
        pList->elem = temp;
        pList->size += LISTINCREMENT;
    }
    // 移动部分元素
    for(int i = pList->length - 1; i >= index; i--)
    {
        pList->elem[i + 1] = pList->elem[i];
    }
    // 插入目标元素
    pList->elem[index] = elem;
    pList->length++; // 表长增加1
    return OK;
}

void mergeList(SqList list1, SqList list2, SqList *pList)
{
    if(!pList) initList(pList);
    int index1 = 0, index2 = 0, index = 0;
    int len1 = list1.length, len2 = list2.length;
    while(index1 < len1 && index2 < len2)
    {
        if(list1.elem[index1] < list2.elem[index2])
        {
            listInsert(pList, index++, list1.elem[index1++]);
        }
        else
        {
            listInsert(pList, index++, list2.elem[index2++]);
        }
    }
    while(index1 < len1)
    {
        listInsert(pList, index++, list1.elem[index1++]);
    }
    while(index2 < len2)
    {
        listInsert(pList, index++, list2.elem[index2++]);
    }
}

// 删除顺序线性表中下标为index的元素，并使用pElem返回删除的值
Status listDelete(SqList *pList, int index, ElemType *pElem)
{
    if(index < 0 || index > pList->length - 1) return ERROR;
    getElem(*pList, index, pElem);
    for(int i = index + 1; i < pList->length; i++)
    {
        pList->elem[i - 1] = pList->elem[i];
    }
    pList->length--;
    return OK;
}

Status listTraverse(SqList list, Status (*visit)(ElemType elem))
{
    int i = 0;
    while(i < list.length && visit(list.elem[i]))
    {
        i++;
    }
    return i == list.length ? OK : ERROR;
}

void minList(SqList *pList)
{
    ElemType *temp = (ElemType*)malloc(pList->length * sizeof(ElemType));
    if(!temp) exit(OVERFLOW);
    for(int i = 0; i < pList->length; i++)
    {
        temp[i] = pList->elem[i];
    }
    free(pList->elem);
    pList->elem = temp;
    pList->size = pList->length;
}