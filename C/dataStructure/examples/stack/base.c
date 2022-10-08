//
// Created by Anvei on 2022/10/7.
//
#include "../../Stack.h"
#include <stdio.h>

void stack_print(Stack *pStack)
{
    for (int i = 0; i < 13; i++)
    {
        printf("%3d ", stack_pop(pStack));
        if ((i + 1) % 10 == 0)
            putchar('\n');
    }
}

int main(void)
{
    Stack stack;
    stack_init(&stack);
    for (int i = 0; i < 100; i++)
    {
        stack_push(&stack, (char)(i + 1));
    }

    stack_print(&stack);
    printf("End.\n");
    for (int i = 0; i < 43; i++)
    {
        stack_pop(&stack);
    }
    stack_print(&stack);
    printf("End.\n");
    stack_destory(&stack);
    return 0;
}
