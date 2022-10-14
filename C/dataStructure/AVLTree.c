//
// Created by Anvei on 2022/10/14.
//

#include "AVLTree.h"
#include "../utils/errorutils.h"
#include <malloc.h>
#include <stdio.h>

// 返回一个新结点的地址
static avl_node *new_avl_node(int data)
{
    avl_node *temp = malloc(sizeof(avl_node));
    anv_assert(temp != NULL);
    temp->data = data;
    temp->height = 1;
    temp->l_child = temp->r_child = NULL;
    return temp;
}

// 释放AVL树的内存
void avl_destory(AVLTree *ptree)
{
    anv_assert(ptree != NULL);
    if (*ptree != NULL)
    {
        avl_destory(&(*ptree)->l_child);
        avl_destory(&(*ptree)->r_child);
        (*ptree) = NULL;
        free(*ptree);
    }
}

// 获取树的高度，输入的树可以为NULL，如果为NULL，高度为0
static int avl_height(AVLTree tree)
{
    if (tree == NULL) return 0;
    return tree->height;
}

// 返回左子树的高度与右子树的高度的差，即平衡因子
static int avl_height_diff(AVLTree tree)
{
    return avl_height(tree->l_child) - avl_height(tree->r_child);
}

// 获取该树的最小结点的地址
avl_node *avl_find_min(AVLTree tree)
{
    anv_assert(tree != NULL);
    if (tree->l_child != NULL)
        return avl_find_min(tree->l_child);
    return tree;
}

// 获取该树的最大结点的地址
avl_node *avl_find_max(AVLTree tree)
{
    anv_assert(tree != NULL);
    if (tree->r_child != NULL)
        return avl_find_max(tree->r_child);
    return tree;
}

// 对LL型树右旋，返回右旋之后获得的树
static avl_node *avl_right_rotate(AVLTree tree)
{
    // 断言根节点、左节点不为NULL
    anv_assert(tree != NULL && tree->l_child != NULL);
    avl_node *left = tree->l_child;
    // 开始右旋
    avl_node *temp = left->r_child;
    left->r_child = tree;
    tree->l_child = temp;

    // 高度已经发生改变
    tree->height = avl_height(tree->l_child) > avl_height(tree->r_child) ?
           avl_height(tree->l_child) + 1 : avl_height(tree->r_child) + 1;
    left->height = avl_height(left->l_child) > avl_height(left->r_child) ?
                   avl_height(left->l_child) + 1 : avl_height(left->r_child) + 1;
    return left;
}

// 对RR型树左旋
static avl_node *avl_left_rotate(AVLTree tree)
{
    anv_assert(tree != NULL && tree->r_child != NULL);
    avl_node *right = tree->r_child;
    avl_node *temp = right->l_child;
    right->l_child = tree;
    tree->r_child = temp;

    tree->height = avl_height(tree->l_child) > avl_height(tree->r_child) ?
                   avl_height(tree->l_child) + 1 : avl_height(tree->r_child) + 1;
    right->height = avl_height(right->l_child) > avl_height(right->r_child) ?
                   avl_height(right->l_child) + 1 : avl_height(right->r_child) + 1;
    return right;
}

// 对RL型树右左旋
static avl_node *avl_right_left_rotate(AVLTree tree)
{
    tree->r_child = avl_right_rotate(tree->r_child);
    return avl_left_rotate(tree);
}

// 对LR型树左右旋
static avl_node *avl_left_right_rotate(AVLTree tree)
{
    tree->l_child = avl_left_rotate(tree->l_child);
    return avl_right_rotate(tree);
}

// 插入一个元素，每次插入元素之前，已经假设AVL树为严格平衡状态，并且插入元素之后该树依旧保持严格平衡状态
avl_node *avl_insert(AVLTree tree, int data)
{
    // 与BST相同的插入操作
    if (tree == NULL)
    {
        return new_avl_node(data);
    }
    if (tree->data > data)
    {
        tree->l_child = avl_insert(tree->l_child, data);
    }
    else if (tree->data < data)
    {
        tree->r_child = avl_insert(tree->r_child, data);
    }
    // 更新插入完成之后树的高度
    tree->height = avl_height(tree->l_child) > avl_height(tree->r_child) ?
                   avl_height(tree->l_child) + 1 : avl_height(tree->r_child) + 1;
    // 插入元素之后的平衡处理操作
    // 平衡因子balanced大于1表示是插入在左子树，小于-1则表示插入在右子树
    int balanced = avl_height_diff(tree);
    if (balanced > 1 && data < tree->l_child->data)     // LL型树
    {
        tree =  avl_right_rotate(tree);
    }
    else if (balanced < -1 && data > tree->r_child->data)    // RR型树
    {
        tree =  avl_left_rotate(tree);
    }
    else if (balanced > 1 && data > tree->l_child->data)        // LR型树
    {
        tree =  avl_left_right_rotate(tree);
    }
    else if (balanced < -1 && data < tree->r_child->data)       // RL型树S
    {
        tree = avl_right_left_rotate(tree);
    }
    // 如果平衡因子为-1、0、1就不做平衡处理
    return tree;
}

// 删除AVL树中指定元素，返回删除之后获得的新AVL树
avl_node *avl_delete(AVLTree tree, int data)
{
    if (tree == NULL) return NULL;
    if (data < tree->data)
        tree->l_child = avl_delete(tree->l_child, data);
    else if (data > tree->data)
        tree->r_child = avl_delete(tree->r_child, data);
    else
    {
        if (tree->r_child == NULL && tree->l_child == NULL)
        {
            free(tree);
            tree = NULL;
        }
        else if (tree->r_child == NULL)
        {
            avl_node *temp = tree;
            tree = tree->l_child;
            free(temp);
        }
        else if (tree->l_child == NULL)
        {
            avl_node *temp = tree;
            tree = tree->r_child;
            free(temp);
        }
        else
        {
            avl_node *temp = avl_find_max(tree->l_child);
            tree->data = temp->data;
            avl_delete(tree->l_child, temp->data);
        }
    }
    tree->height = avl_height(tree->l_child) > avl_height(tree->r_child) ?
                   avl_height(tree->l_child) + 1 : avl_height(tree->r_child) + 1;

    int balanced = avl_height_diff(tree);

    if (balanced > 1)
        tree = tree->l_child->data > data ? avl_right_rotate(tree) : avl_left_right_rotate(tree);
    else if (balanced < -1)
        tree = tree->r_child->data < data ? avl_left_rotate(tree) : avl_right_left_rotate(tree);
    return tree;
}

// 在AVL树内查找指定元素
avl_node *avl_find(AVLTree tree, int data)
{
    if (tree == NULL) return NULL;
    if (data < tree->data)
        return avl_find(tree->l_child, data);
    else if (data > tree->data)
        return avl_find(tree->r_child, data);
    else
        return tree;
}

// 采用中序遍历打印升序序列
void avl_print_inorder(AVLTree tree)
{
    if (tree != NULL)
    {
        avl_print_inorder(tree->l_child);
        printf("%d ", tree->data);
        avl_print_inorder(tree->r_child);
    }
}

// 采用前序遍历打印升序序列
void avl_print_preorder(AVLTree tree)
{
    if (tree != NULL)
    {
        printf("%d ", tree->data);
        avl_print_preorder(tree->l_child);
        avl_print_preorder(tree->r_child);
    }
}

// 采用后序遍历打印升序序列
void avl_print_postorder(AVLTree tree)
{
    if (tree != NULL)
    {
        avl_print_postorder(tree->l_child);
        avl_print_postorder(tree->r_child);
        printf("%d ", tree->data);
    }
}