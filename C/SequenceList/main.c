#include <stdio.h>
#include "SequenceList.h"
#include <stdlib.h>
int main() {
    SqList list, *pList = &list;
    initList(pList);
    for(int i = 0; i < 10; i++)
    {
        listInsert(pList, i, i*2);
    }
    listDelete(pList, 9);
    printf("length of list: %d, size of lis: %d\n", listLength(*pList), pList->size);
    minList(pList);
    printf("length of list: %d, size of lis: %d\n", listLength(*pList), pList->size);
    destroyList(pList);
    return 0;
}
