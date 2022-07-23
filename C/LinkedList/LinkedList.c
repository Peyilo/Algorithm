//
// Created by 35433 on 2022/7/19.
//

#include "LinkedList.h"


bool initList(LinkedList *pList)
{
    *pList = (LinkedList) malloc(sizeof(Node)); // 必须得使用动态内存分配
    if(!*pList) return false;
    (*pList)->next = NULL;
    return true;
}

int getLength(LinkedList list)
{
    int len = 0;
    list = list->next;
    while(list)
    {
        len++;
        list = list->next;
    }
    return len;
}

ElemType getElem(LinkedList list, int index)
{
    int count = 0;
    list = list->next;
    while(list && count < index) // 定位下标为index的元素
    {
        list = list->next;
        count++;
    }
    if(!list || index < 0)
    {
        printf("index out of range.\n");
        exit(-1);
    }
    return list->data;
}

// 链表的插入
// 因为没必要修改LinkedList本身的信息（头结点），所以没必要传入LinkedList的引用
bool listInsert(LinkedList list, int index, ElemType elem)
{
    int count = -1;
    while(list && count < index - 1) // 定位到下标为index-1的元素
    {
        list = list->next;
        count++;
    }
    if(!list || index < 0)
    {
        printf("Index error!\n");
        exit(-1);
    }
    LinkedList temp = (LinkedList)malloc(sizeof(Node));
    if(!temp) return false;
    temp->data = elem;
    temp->next = list->next; // 让新结点next指针指向index的结点
    list->next = temp; // 让新结点称为index - 1的下一个结点
    return true;
}

// 链表元素的删除
ElemType listDelete(LinkedList list, int index)
{
    int count = -1;
    while(list && count < index - 1) // 定位到下标为index-1的元素
    {
        list = list->next;
        count++;
    }
    // 如果下标index的元素不存在或者index<0就表示index错误
    if(!(list->next) || index < 0)
    {
        printf("Index error!\n");
        exit(-1);
    }
    LinkedList temp = list->next; // temp就是指向index的指针
    list->next = temp->next; // 让index-1的结点直接指向index+1结点
    ElemType elem = temp->data;
    free(temp); // 释放内存
    return elem;
}

void mergeList(LinkedList list1, LinkedList list2)
{
    LinkedList list = list1; // 选取list1的头结点作为两个链表合并之后的头结点
    LinkedList temp = list2; // 储存list2头结点的地址，用来在之后释放内存
    list1 = list1->next;
    list2 = list2->next;
    free(temp); // 释放list2的头结点
    while(list1 && list2)
    {
        if(list1->data < list2->data)
        {
            list->next = list1;
            list = list->next;
            list1 = list1->next;
        }
        else
        {
            list->next = list2;
            list = list->next;
            list2 = list2->next;
        }
    }
    list->next = list1 ? list1 : list2; // 因为剩余的都是有序的，直接接上就可以了
}

void destroyList(LinkedList list)
{
    LinkedList temp = NULL;
    while(list)
    {
        temp = list->next; // 保存下一个结点的地址
        free(list);
        list = temp;
    }
}