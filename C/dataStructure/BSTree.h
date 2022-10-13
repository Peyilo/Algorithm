//
// Created by Anvei on 2022/10/13.
//
// 提供了二叉搜索树（BST）的实现

#ifndef ALGORITHM_BSTREE_H
#define ALGORITHM_BSTREE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct bst_node {
    int data;
    struct bst_node *l_child;
    struct bst_node *r_child;
} bst_node, *BSTree;

bst_node *new_bst_node(int data);
void free_BSTress(BSTree tree);
bst_node *bst_add(BSTree tree, int num);
bst_node *bst_max(BSTree tree);
bst_node *bst_min(BSTree tree);
bst_node *bst_delete(BSTree tree, int num);
void bst_print(BSTree tree);
int bst_height(BSTree tree);
bool bst_find(BSTree tree, int num);

#ifdef __cplusplus
}
#endif
#endif //ALGORITHM_BSTREE_H
