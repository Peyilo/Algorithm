//
// Created by 35433 on 2022/7/21.
//

#include "Stack.h"
#include <stdlib.h>
#include <stdbool.h>

/* 初始化一个空栈 */
bool initStack(Stack *pStack)
{
    pStack->base = (ElemType*)malloc(INITSIZE * sizeof(ElemType));
    if(!pStack->base) return false;
    pStack->top = pStack->base;
    pStack->stackSize = INITSIZE;
    return true;
}

/* 销毁一个栈 */
void destroyStack(Stack *pStack)
{
    pStack->top = pStack->base;
    pStack->stackSize = 0;
    free(pStack->base);
}

// 清空栈中的元素
void clearStack(Stack *pStack)
{
    pStack->top = pStack->base;
}

// 判断栈是否为空
bool stackIsEmpty(Stack stack)
{
    if(stack.base == stack.top) return true;
    return false;
}

bool stackIsFull(Stack stack)
{
    if(stackOfLength(stack) >= stack.stackSize) return true;
    return false;
}

/* 获取栈的长度 */
int stackOfLength(Stack stack)
{
    return (int)(stack.top - stack.base);
}

// 获取栈顶元素
ElemType getTop(Stack stack)
{
    if(stackIsEmpty(stack)) exit(-1);
    return *(stack.top - 1);
}

// 将指定元素压入栈顶
bool push(Stack *pStack, ElemType elem)
{
    if(stackIsFull(*pStack))
    {
        ElemType *temp = (ElemType*)realloc(pStack->base, (pStack->stackSize + INCREMENTSIZE) * sizeof(ElemType));
        if(!temp) return false;
        pStack->base = temp;
        pStack->top = pStack->base + pStack->stackSize;
        pStack->stackSize += INCREMENTSIZE;
    }
    *pStack->top = elem;
    pStack->top++;
    return true;
}

// 移除栈顶元素，并通过传递的指针返回删除的栈顶元素
ElemType pop(Stack *pStack)
{
    if(stackIsEmpty(*pStack)) exit(-1);
    pStack->top--;
    return *pStack->top;
}

bool stackTraverse(Stack stack, bool (*visit)(ElemType *))
{
    bool res = true;
    ElemType *pointer = stack.base;
    while(pointer != stack.top && res)
    {
        res = visit(pointer);
        pointer++;
    }
    return res;
}