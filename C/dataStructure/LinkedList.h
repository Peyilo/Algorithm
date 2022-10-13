//
// Created by Anvei on 2022/10/7.
//
// 提供链表的基本实现

#ifndef ALGORITHM_LINKEDLIST_H
#define ALGORITHM_LINKEDLIST_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef int lklist_ele;
typedef struct lklist_node {
    lklist_ele ele;                 // 结点所保存的数据
    struct lklist_node *next;       // 每个结点都保存了指向下一个结点的指针
} lklist_node, *LinkedList;         // LinkedList指向头结点

bool lklist_init(LinkedList *plist);

void lklist_destory(LinkedList list);

bool lklist_insert(LinkedList list, int index, lklist_ele ele);

lklist_ele lklist_get(LinkedList list, int index);

void lklist_delete(LinkedList list, int index);

int lklist_length(LinkedList list);

#ifdef __cplusplus
}
#endif
#endif //ALGORITHM_LINKEDLIST_H
