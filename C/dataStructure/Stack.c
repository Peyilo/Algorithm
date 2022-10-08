//
// Created by Anvei on 2022/10/7.
//

#include "Stack.h"
#include <stdlib.h>

#define INITSIZE 20
#define INCREMENTSIZE 10

/**
 * 初始化一个栈
 * @param pstack
 * @return
 */
bool stack_init(Stack *pstack)
{
    stack_ele *pEle = malloc(sizeof(stack_ele) * INITSIZE);
    if (!pEle) return false;
    pstack->base = pEle;
    pstack->top = pEle;
    pstack->size = INITSIZE;
    return true;
}

/**
 * 释放栈的内存
 * @param pstack
 */
void stack_destory(Stack *pstack)
{
    free(pstack->base);
}

/**
 * 判断栈是否为空
 * @param pstack
 * @return
 */
bool stack_empty(const Stack *pstack)
{
    return pstack->top == pstack->base;
}

/**
 * 将指定元素压入栈顶
 * @param pstack
 * @param ele
 * @return
 */
bool stack_push(Stack *pstack, stack_ele ele)
{
    if (pstack->top - pstack->base == pstack->size)     // 栈的容量已经满了，需要重新分配空间
    {
        stack_ele *temp = realloc(pstack->base, sizeof(stack_ele) * (pstack->size + INCREMENTSIZE));
        if (!temp) return false;
        pstack->base = temp;
        pstack->top = temp + pstack->size;
        pstack->size += INCREMENTSIZE;
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
stack_ele stack_peek(const Stack *pstack)
{
    if (stack_empty(pstack)) exit(-1);
    return *(pstack->top - 1);
}

/**
 * 返回栈顶元素的同时，移除栈顶元素
 * @param pstack
 * @return
 */
stack_ele stack_pop(Stack *pstack)
{
    if (stack_empty(pstack)) exit(-1);
    pstack->top--;
    return *pstack->top;
}