//
// Created by Anvei on 2022/10/7.
// 本文件提供了顺序表的基本操作

#ifndef ALGORITHM_SEQUENCELIST_H
#define ALGORITHM_SEQUENCELIST_H

#include <stdbool.h>

typedef int seqlist_ele;
typedef struct {
    seqlist_ele *data;
    int length;
    int size;
} SequenceList;

bool seqlist_init(SequenceList *plist);
void seqlist_destory(SequenceList *plist);
seqlist_ele  seqlist_get(SequenceList list, int index);
bool seqlist_insert(SequenceList *plist, int index, seqlist_ele ele);
void seqlist_delete(SequenceList *plist, int index);
void seqlist_clear(SequenceList *plist);
bool seqlist_empty(SequenceList list);
#endif //ALGORITHM_SEQUENCELIST_H