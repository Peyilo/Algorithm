//
// Created by Anvei on 2022/10/13.
//
#include "../../BSTree.h"
#include <stdio.h>

int main(void)
{
    BSTree tree = new_bst_node(50);
    for (int i = 0; i < 100; i++)
    {
        bst_add(tree, i);
    }
    bst_print(tree);
    putchar('\n');
    printf("height = %d\n", bst_height(tree));
    free_BSTress(tree);
    return 0;
}