//
// Created by Anvei on 2022/10/8.
//

#include <stdio.h>
#include "../../LinkedList.h"

void lklist_print(LinkedList list)
{
    int len = lklist_length(list);
    for (int i = 0; i < len; i++)
    {
        printf("%2d ", lklist_get(list, i));
        if ((i + 1) % 10 == 0) putchar('\n');
    }
}

int main(void)
{
    LinkedList list;
    if (!lklist_init(&list))
        printf("初始化失败!\n");
    for (int i = 0; i < 100; i++)
    {
        lklist_insert(list, i, i);
    }
    printf("开始打印\n");
    lklist_print(list);
    printf("结束打印\n");

    lklist_delete(list, 0);
    lklist_delete(list, 23);
    lklist_print(list);

    lklist_destory(list);
    return 0;
}