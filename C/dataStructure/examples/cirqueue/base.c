//
// Created by Anvei on 2022/10/10.
//

#include "../../CircularQueue.h"
#include <stdio.h>

int main(void)
{
    CircularQueue queue;
    cirqueue_init(&queue, 30);
    for (int i = 0; i < 25; i++)
    {
        cirqueue_ele ele;
        switch (i % 4) {
            case 0:
                ele = "Anvei0";
                break;
            case 1:
                ele = "Anvei1";
                break;
            case 2:
                ele = "Anvei2";
                break;
            default:
                ele = "Anvei3";
                break;
        }
        cirqueue_enqueue(&queue, ele);
    }
    for (int i = 0; i < 14; i++)
    {
        printf("%s\n", cirqueue_dequeue(&queue));
    }
    cirqueue_destory(queue);
    return false;
}