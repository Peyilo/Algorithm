//
// Created by Anvei on 2022/10/14.
//

#ifndef ALGORITHM_AVLTREE_H
#define ALGORITHM_AVLTREE_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct avl_node {
    int data;
    int height;
    struct avl_node *l_child;
    struct avl_node *r_child;
} avl_node, *AVLTree;

void avl_destory(AVLTree *ptree);

avl_node *avl_insert(AVLTree tree, int data);

avl_node *avl_delete(AVLTree tree, int data);

avl_node *avl_find(AVLTree tree, int data);

avl_node *avl_find_min(AVLTree tree);

avl_node *avl_find_max(AVLTree tree);

void avl_print_inorder(AVLTree tree);

void avl_print_preorder(AVLTree tree);

void avl_print_postorder(AVLTree tree);

void avl_print_levelorder(AVLTree tree);

#ifdef __cplusplus
}
#endif
#endif //ALGORITHM_AVLTREE_H
