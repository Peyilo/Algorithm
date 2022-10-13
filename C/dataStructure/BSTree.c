//
// Created by Anvei on 2022/10/13.
//

#include "BSTree.h"
#include "../utils/errorutils.h"
#include <stdlib.h>
#include <stdio.h>

// 创建一个新node
bst_node *new_bst_node(int data)
{
    bst_node *temp = malloc(sizeof(bst_node));
    anv_assert(temp != NULL);          // 断言不为null
    temp->data = data;
    temp->l_child = temp->r_child = NULL;
    return temp;
}

// 采用后序遍历，双方该树全部结点内存
void free_BSTress(BSTree tree)
{
    if (tree != NULL)
    {
        free_BSTress(tree->l_child);
        free_BSTress(tree->r_child);
        free(tree);
    }
}

/**
 * 向二叉搜索树添加一个元素，返回值为插入该元素后的获得的新树
 * @param tree
 * @param num
 * @return
 */
bst_node *bst_add(BSTree tree, int num)
{
    if (tree == NULL)       // 为null时，表示该位置就是插入元素的正确位置，创建一个新结点，并将其返回
    {
        tree = new_bst_node(num);
    }
    if (num < tree->data)
        tree->l_child = bst_add(tree->l_child, num);
    else if (num > tree->data)
        tree->r_child = bst_add(tree->r_child, num);
    return tree;
}

// 获取二叉搜索树最大元素
bst_node *bst_max(BSTree tree)
{
    anv_assert(tree != NULL);
    if (tree->r_child != NULL) return bst_max(tree->r_child);
    return tree;
}

// 获取二叉搜索树最小元素
bst_node *bst_min(BSTree tree)
{
    anv_assert(tree != NULL);
    if (tree->l_child != NULL) return bst_min(tree->l_child);
    return tree;
}

// 删除一个元素，返回值为删除该元素后所获得的新树
bst_node *bst_delete(BSTree tree, int num)
{
    if (tree == NULL)       // 在删除一个空树删除一个元素，返回值自然还是NULL
        return tree;
    if (num < tree->data)
        tree->l_child = bst_delete(tree->l_child, num);
    else if (num > tree->data)
        tree->r_child = bst_delete(tree->r_child, num);
    else
    {
        if (tree->l_child == NULL && tree->r_child == NULL)
        {
            free(tree);
            tree = NULL;
        }
        else if (tree->l_child == NULL)
        {
            bst_node *temp = tree->r_child;
            free(tree);
            tree = temp;
        }
        else if (tree->r_child == NULL)
        {
            bst_node *temp = tree->l_child;
            free(tree);
            tree = temp;
        }
        else        // 左右子树都不为0
        {           // 获取右子树的最小值、或者左子树的最大值都行
            bst_node *temp = bst_min(tree->r_child);
            tree->data = temp->data;
            tree->r_child = bst_delete(tree->r_child, temp->data);
        }
    }
    return tree;
}

/**
 * 在二叉树中进行查找指定元素
 * @param tree
 * @return
 */
bool bst_find(BSTree tree, int num)
{
    if (tree == NULL) return false;
    if (tree->data == num)
        return true;
    else if (tree->data < num)
        return bst_find(tree->r_child, num);
    else
        return bst_find(tree->l_child, num);
}

// 采用中序遍历打印，实现了从小到大进行输出
void bst_print(BSTree tree)
{
    if (tree != NULL)
    {
        bst_print(tree->l_child);
        printf("%d ", tree->data);
        bst_print(tree->r_child);
    }
}

/**
 * 计算搜索树的高度
 * @param tree
 * @return
 */
int bst_height(BSTree tree)
{
    if (tree == NULL) return 0;
    int l_height = bst_height(tree->l_child);
    int r_height = bst_height(tree->r_child);
    return l_height > r_height ? l_height + 1 : r_height + 1;
}
