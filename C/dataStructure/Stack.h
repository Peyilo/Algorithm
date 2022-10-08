//
// Created by Anvei on 2022/10/7.
//

#ifndef ALGORITHM_STACK_H
#define ALGORITHM_STACK_H
#include <stdbool.h>

typedef char stack_ele;
typedef struct {
    stack_ele *top;      // 栈顶指针，即下次压入栈中的元素所处的位置
    stack_ele *base;     // 栈底指针
    int size;       // 栈的大小
} Stack;

bool stack_init(Stack *pstack);
void stack_destory(Stack *pstack);
bool stack_empty(const Stack *pstack);
bool stack_push(Stack *pstack, stack_ele ele);
stack_ele stack_peek(const Stack *pstack);
stack_ele stack_pop(Stack *pstack);

#endif //ALGORITHM_STACK_H
