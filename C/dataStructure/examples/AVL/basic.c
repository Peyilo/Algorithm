//
// Created by Anvei on 2022/10/14.
//
#include "../../AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    AVLTree avl_tree = NULL;
    for (int i = 0; i < 6; i++)
    {
        int num = i;
        avl_tree = avl_insert(avl_tree, num);
    }
    avl_print_inorder(avl_tree);
    putchar('\n');
    avl_tree = avl_delete(avl_tree, 2);
    avl_tree = avl_delete(avl_tree, 12);

    avl_print_levelorder(avl_tree);

    avl_destory(&avl_tree);
    return 0;
}
