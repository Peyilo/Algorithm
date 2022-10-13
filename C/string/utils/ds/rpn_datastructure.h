//
// Created by Anvei on 2022/10/12.
//

#ifndef ALGORITHM_RPN_DATASTRUCTURE_H
#define ALGORITHM_RPN_DATASTRUCTURE_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include "../../../dataStructure/String.h"

#define RPN_STACK_INITSIZE 20
#define RPN_STACK_INCREMENTSIZE 10
#define RPN_SEQLIST_INITSIZE 20
#define RPN_SEQLIST_INCREMENTSIZE 10

// 字符串栈
typedef struct {
    String *base;
    String *top;
    int size;
} rpn_stack;

bool rpn_stack_init(rpn_stack *pstack);
void rpn_stack_destory(rpn_stack *pstack);
bool rpn_stack_empty(const rpn_stack *pstack);
bool rpn_stack_push(rpn_stack *pstack, String ele);
String rpn_stack_peek(const rpn_stack *pstack);
String rpn_stack_pop(rpn_stack *pstack);


// 字符串顺序表
typedef struct {
    String *data;
    int length;
    int size;
} rpn_seqlist;

bool rpn_seqlist_init(rpn_seqlist *plist);
void rpn_seqlist_destory(rpn_seqlist *plist);
String  rpn_seqlist_get(rpn_seqlist list, int index);
bool rpn_seqlist_insert(rpn_seqlist *plist, int index, String ele);
bool rpn_seqlist_add(rpn_seqlist *plist, String ele);

#ifdef __cplusplus
}
#endif
#endif //ALGORITHM_RPN_DATASTRUCTURE_H
