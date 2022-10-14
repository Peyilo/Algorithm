//
// Created by Anvei on 2022/10/14.
//
#include "../../AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_rand_num()
{
    srand(time(NULL));
    return rand() % 1000;
}

int main(void)
{
    AVLTree avl_tree = NULL;
    for (int i = 0; i < 20; i++)
    {
        int num = get_rand_num();
        avl_tree = avl_insert(avl_tree, num);
    }
    avl_print_inorder(avl_tree);
    avl_destory(&avl_tree);
    return 0;
}
