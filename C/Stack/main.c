#include <stdio.h>
#include "Stack.h"
#define ARRSIZE 20
//void test();
//void printStack(Stack *pStack);
//void conversion(int num);
//void test2();
double eval(char *expression);

// 测试
int main()
{
    /*
    test();
    conversion(12);
    test2();*/

    return 0;
}

/*
void test()
{
    Stack stack;
    Stack *pStack = &stack;
    if(initStack(pStack))
    {
        printf(stackIsEmpty(stack) ? "The stack is empty.\n" : "The stack is not empty.\n");
        printf("The stack length = %d, and the size = %d\n", stackOfLength(stack), stack.stackSize);
        for(int i = 0; i < 101; i++)
        {
            push(pStack, i * 1.0);
        }
        printf(stackIsEmpty(stack) ? "The stack is empty.\n" : "The stack is not empty.\n");
        printf("The stack length = %d, and the size = %d\n", stackOfLength(stack), stack.stackSize);
        printStack(pStack);
        destroyStack(pStack);
    }
    else
        printf("Initialize error!\n");
}

// 打印栈中的全部元素
void printStack(Stack *pStack)
{
    int count = 0;
    while(!stackIsEmpty(*pStack))
    {
        printf("No.%d: %.2f\n", ++count, pop(pStack));
    }
}

// 将十进制正整数转换为八进制
void conversion(int num)
{
    Stack stack;
    Stack *pStack = &stack;
    initStack(pStack);
    while(num)
    {
        push(pStack, num % 8);
        num = num / 8;
    }
    while(!stackIsEmpty(stack))
    {
        printf("%d", (int)pop(pStack));
    }
    printf("\n");
    destroyStack(pStack);
} */

/*
void test2()
{
    Stack stack, *pStack = &stack;
    initStack(pStack);
    char str[ARRSIZE];
    printf("Enter a string:");
    scanf("%s", str);
    for(int i = 0; i < ARRSIZE && str[i] != '\0'; i++)
    {
        char ch;
        switch(ch = str[i])
        {
            case '(':
            case '[':
            case '{':
                push(pStack, ch);
                break;
            case ')':
                if(getTop(stack) == '(')
                {
                    printf("()\t");
                    pop(pStack);
                }
                else
                {
                    printf("\nError!\n");
                }
                break;
            case ']':
                if(getTop(stack) == '[')
                {
                    printf("[]\t");
                    pop(pStack);
                }
                else
                {
                    printf("\nError!\n");
                }
                break;
            case '}':
                if(getTop(stack) == '{')
                {
                    printf("{}\t");
                    pop(pStack);
                }
                else
                {
                    printf("\nError!\n");
                }
                break;
            default:
                break;
        }
    }
    if(!stackIsEmpty(stack)) printf("\nError!\n");
    destroyStack(pStack);
}
 */