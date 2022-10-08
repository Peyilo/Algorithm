//
// Created by Anvei on 2022/10/7.
//

#include "LinkedList.h"
#include <stdlib.h>

/**
 * 对链表进行初始化
 * @param plist
 * @return
 */
bool lklist_init(LinkedList *plist)
{
    lklist_node *pNode = malloc(sizeof(lklist_node));
    if (!pNode) return false;
    pNode->next = NULL;
    *plist = pNode;
    return true;                // 链表的值为头结点的地址，头结点不储存数据
}

/**
 * 释放链表的内存
 * @param pList
 */
void lklist_destory(LinkedList list)
{
    LinkedList temp = NULL;
    while (list)        // list != NULL
    {
        temp = list->next;
        free(list);
        list = temp;
    }
}

/**
 * 链表指定下标插入元素
 * @param list
 * @param index
 * @param ele
 * @return
 */
bool lklist_insert(LinkedList list, int index, lklist_ele ele)
{
    int count = -1;
    while (list && count < index - 1)   // 循环开始时，count和list都对应于-1号位元素(头结点)
    {                                   // 每次循环，count、list都移动一次
        count++;                        // 最终以count = index - 1结束
        list = list->next;
    }
    if (!list || index < 0) return false;   // 如果index - 1号元素都不存在，显然index是错误的插入
    LinkedList temp = malloc(sizeof(lklist_node));
    if (!temp) return false;
    temp->next = list->next;            // 让插入的元素执行先前的index号元素（即插入后的index+1)号元素
    temp->ele = ele;
    list->next = temp;                  // 让index-1号元素指向插入的元素
    return true;
}

/**
 * 获取链表指定下标的元素
 * @param list
 * @param index
 * @return
 */
lklist_ele lklist_get(LinkedList list, int index)
{
    int count = -1;
    while (list && count < index)       // 定位index号元素
    {
        count++;
        list = list->next;
    }
    if (!list || index < 0)             // 处理错误情形
        exit(-110829);
    return list->ele;
}

/**
 * 删除链表指定下标的元素
 * @param pList
 * @param index
 */
void lklist_delete(LinkedList list, int index)
{
    int count = -1;
    while (list && count < index - 1)
    {
        list = list->next;
        count++;
    }
    if (!list || index < 0)
        exit(-110829);
    LinkedList temp = list->next;
    list->next= temp->next;
    free(temp);
}

/**
 * 获取链表的长度
 * @param list
 * @return
 */
int lklist_length(LinkedList list)
{
    int count = -1;
    while (list)
    {
        count++;
        list = list->next;
    }
    return count;
}