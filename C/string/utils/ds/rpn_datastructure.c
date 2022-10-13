//
// Created by Anvei on 2022/10/12.
//

#include "rpn_datastructure.h"
#include <stdlib.h>

/**
 * 初始化一个字符串栈
 * @param pstack
 * @return
 */
bool rpn_stack_init(rpn_stack *pstack)
{
    String *pele = malloc(sizeof(String) * RPN_STACK_INITSIZE);
    if (!pele) return false;
    pstack->base = pele;
    pstack->top = pele;
    pstack->size = RPN_STACK_INITSIZE;
    return true;
}

/**
 * 销毁一个字符串栈
 * @param pstack
 */
void rpn_stack_destory(rpn_stack *pstack)
{
    free(pstack->base);
}

/**
 * 判断一个栈是否为空
 * @param pstack
 * @return
 */
bool rpn_stack_empty(const rpn_stack *pstack)
{
    return pstack->top == pstack->base;
}

/**
 * 将一个元素压入字符串栈
 * @param pstack
 * @param ele
 * @return
 */
bool rpn_stack_push(rpn_stack *pstack, String ele)
{
    if (pstack->top - pstack->base == pstack->size)     // 栈的容量已经满了，需要重新分配空间
    {
        String *temp = realloc(pstack->base, sizeof(String) * (pstack->size + RPN_STACK_INCREMENTSIZE));
        if (!temp) return false;
        pstack->base = temp;
        pstack->top = temp + pstack->size;
        pstack->size += RPN_STACK_INCREMENTSIZE;
    }
    *pstack->top = ele;
    pstack->top++;
    return true;
}

/**
 * 返回栈顶元素
 * @param pstack
 * @return
 */
String rpn_stack_peek(const rpn_stack *pstack)
{
    if (rpn_stack_empty(pstack)) exit(__LINE__);
    return *(pstack->top - 1);
}

/**
 * 返回当前栈顶元素，并将其从栈顶移除
 * @param pstack
 * @return
 */
String rpn_stack_pop(rpn_stack *pstack)
{
    if (rpn_stack_empty(pstack))
        exit(__LINE__);
    pstack->top--;
    return *pstack->top;
}

/**
 * 初始化一个字符串顺序表
 * @param plist
 * @return
 */
bool rpn_seqlist_init(rpn_seqlist *plist)
{
    String *pele = malloc(sizeof(String) * RPN_SEQLIST_INITSIZE);
    if (!pele) return false;
    plist->length = 0;
    plist->size = RPN_SEQLIST_INITSIZE;
    plist->data = pele;
    return true;
}

/**
 * 销毁一个字符串顺序表
 * @param plist
 */
void rpn_seqlist_destory(rpn_seqlist *plist)
{
    free(plist->data);
}

/**
 * 获取顺序表指定下标元素
 * @param list
 * @param index
 * @return
 */
String  rpn_seqlist_get(rpn_seqlist list, int index)
{
    return *(list.data + index);
}

/**
 * 向顺序表指定下标插入一个元素
 * @param plist
 * @param index
 * @param ele
 * @return
 */
bool rpn_seqlist_insert(rpn_seqlist *plist, int index, String ele)
{
    if (index > plist->length) return false;
    if (plist->length == plist->size)   // 如果顺序表容量已经满了，需要重新分配内存
    {
        String *temp = realloc(plist->data,
                               sizeof(String) * (plist->length + RPN_SEQLIST_INCREMENTSIZE));
        if (!temp) return false;
        plist->size += RPN_SEQLIST_INCREMENTSIZE;
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
 * 往顺序表尾部添加一个元素
 * @param plist
 * @param ele
 * @return
 */
bool rpn_seqlist_add(rpn_seqlist *plist, String ele)
{
    return rpn_seqlist_insert(plist, plist->length, ele);
}