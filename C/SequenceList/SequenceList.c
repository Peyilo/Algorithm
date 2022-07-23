//
// Created by 35433 on 2022/7/19.
//

#include "SequenceList.h"

bool initList(SqList *pList)
{
    pList->elem = (ElemType*)malloc(INITSIZE * sizeof(ElemType));
    if(!pList->elem) return false;
    pList->length = 0;
    pList->size = INITSIZE;
    return true;
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

bool listEmpty(SqList list)
{
    return list.length == 0 ? true : false;
}

int listLength(SqList list)
{
    return list.length;
}

ElemType getElem(SqList list, int index)
{
    if(index > list.length - 1 || index < 0)
    {
        printf("Index error!\n");
        exit(-1);
    }
    return list.elem[index];
}

int locateElem(SqList list, ElemType elem, bool (*compare)(ElemType, ElemType))
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

bool equal(ElemType elem1, ElemType elem2)
{
    if(elem1 == elem2) return true;
    return false;
}

ElemType priorElem(SqList list, ElemType curElem)
{
    int index = locateElem(list, curElem, equal);
    if(index < 1)
    {
        printf("Index error!\n");
        exit(-1);
    }
    return getElem(list, index - 1);
}

ElemType nextElem(SqList list, ElemType curElem)
{
    int index = locateElem(list, curElem, equal);
    if(index < 0 || index == list.length - 1)
    {
        printf("Index error!\n");
        exit(-1);
    }
    return getElem(list, index + 1);
}

bool listInsert(SqList *pList, int index, ElemType elem)
{
    // 处理下标越界问题
    if(index < 0 || index > pList->length) return false;
    // 处理顺序表容量不够问题
    if(pList->length >= pList->size)
    {
        ElemType *temp = (ElemType*)realloc(pList->elem, (pList->size + LISTINCREMENT) * sizeof(ElemType));
        if(!temp) return false;
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
    return true;
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
ElemType listDelete(SqList *pList, int index)
{
    if(index < 0 || index > pList->length - 1)
    {
        printf("Index error!\n");
        exit(-1);
    }
    ElemType temp = getElem(*pList, index);
    for(int i = index + 1; i < pList->length; i++)
    {
        pList->elem[i - 1] = pList->elem[i];
    }
    pList->length--;
    return temp;
}

void listTraverse(SqList list, void (*visit)(ElemType elem))
{
    int i = 0;
    while(i < list.length)
    {
        visit(getElem(list, i));
        i++;
    }
}

bool minList(SqList *pList)
{
    ElemType *temp = (ElemType*)malloc(pList->length * sizeof(ElemType));
    if(!temp) return false;
    for(int i = 0; i < pList->length; i++)
    {
        temp[i] = pList->elem[i];
    }
    free(pList->elem);
    pList->elem = temp;
    pList->size = pList->length;
    return true;
}