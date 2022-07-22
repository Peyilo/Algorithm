//
// Created by 35433 on 2022/7/21.
// 顺序栈的实现
//

#ifndef STACK_STACK_H
#define STACK_STACK_H
#include <stdbool.h>
#define INITSIZE 20     // 栈的初始容量大小
#define INCREMENTSIZE 10        // 当容量不够时，每次栈增加的容量大小

// 通用定义
typedef char ElemType;
typedef struct {
    ElemType *base; // 栈底指针
    ElemType *top;  // 栈顶指针
    int stackSize;  // 当前栈的最大容量
}Stack;

// 初始化一个空栈
bool initStack(Stack *pStack);

// 销毁一个栈
void destroyStack(Stack *pStack);

// 清空一个栈
void clearStack(Stack *pStack);

// 判断栈是否为空
bool stackIsEmpty(Stack stack);

// 判断栈是否已满
bool stackIsFull(Stack stack);

// 获取栈的长度
int stackOfLength(Stack stack);

// 获取栈顶元素
ElemType getTop(Stack stack);

// 将指定元素压入栈顶
bool push(Stack *stack, ElemType elem);

// 移除当前栈顶元素，并返回栈顶元素
ElemType pop(Stack *pStack);

// 对栈中的每一个元素都进行一次指定操作
bool stackTraverse(Stack stack, bool (*visit)(ElemType *));

#endif //STACK_STACK_H
