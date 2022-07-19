#include <stdio.h>
#include "SequenceList.h"
#include <stdlib.h>
int main() {
    SqList list;
    SqList *pList = &list;
    initList(pList);
    Status status;
    for(int i = 0; i < 10; i++)
    {
        status = listInsert(pList, i, i*2);
        if(!status) exit(-3);
    }
    ElemType elem;
    listDelete(pList, 16, &elem);
    printf("length of list: %d, size of lis: %d\n", listLength(*pList), pList->size);
    minList(pList);
    printf("length of list: %d, size of lis: %d\n", listLength(*pList), pList->size);
    destroyList(pList);
    return 0;
}
