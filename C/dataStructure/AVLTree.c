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

static int avl_update_height(AVLTree tree)
{
    anv_assert(tree != NULL);
    int l_height = avl_height(tree->l_child);
    int r_height = avl_height(tree->r_child);
    return l_height > r_height ? l_height + 1 : r_height + 1;
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
    tree->height = avl_update_height(tree);
    left->height = avl_update_height(left);
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

    tree->height = avl_update_height(tree);
    right->height = avl_update_height(right);
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
// 输入：一个平衡二叉树，输出：插入指定元素后的平衡二叉树
avl_node *avl_insert(AVLTree tree, int data)
{
    // 与BST相同的插入操作
    if (tree == NULL)
        return new_avl_node(data);
    if (tree->data > data)
        tree->l_child = avl_insert(tree->l_child, data);
    else if (tree->data < data)
        tree->r_child = avl_insert(tree->r_child, data);
    // 更新插入完成之后树的高度
    tree->height = avl_update_height(tree);
    // 插入元素之后的平衡处理操作
    // 平衡因子balanced大于1表示是插入在左子树，小于-1则表示插入在右子树
    int balanced = avl_height_diff(tree);

    if (balanced > 1)
        tree = tree->l_child->data > data ? avl_right_rotate(tree) : avl_left_right_rotate(tree);
    else if (balanced < -1)
        tree = tree->r_child->data < data ? avl_left_rotate(tree) : avl_right_left_rotate(tree);
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
            return NULL;        // 无需继续平衡处理
        }
        else if (tree->r_child == NULL)
        {
            avl_node *temp = tree->l_child;
            free(tree);         // AVL树的性质：所有子树也是一个AVL树
            return temp;        // 所以无需继续平衡处理
        }
        else if (tree->l_child == NULL)
        {
            avl_node *temp = tree->r_child;
            free(tree);
            return temp;        // 无需继续平衡处理
        }
        else
        {
            avl_node *temp = avl_find_max(tree->l_child);
            tree->data = temp->data;
            tree->l_child = avl_delete(tree->l_child, temp->data);
        }
    }
    tree->height = avl_update_height(tree);

    // 因为是删除，如果大于1表示删除的是右子树的一个元素，如果是小于-1则表示删除的是左子树的一个元素
    int balanced = avl_height_diff(tree);

    if (balanced > 1)
        tree = avl_height_diff(tree->l_child) >= 0 ? avl_right_rotate(tree) : avl_left_right_rotate(tree);
    else if (balanced < -1)
        tree = avl_height_diff(tree->r_child) <= 0 ? avl_left_rotate(tree) : avl_right_left_rotate(tree);
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

#define AVL_QUEUE_SIZE 21           // 队列中最多允许20个元素
// 层次遍历打印
void avl_print_levelorder(AVLTree tree)
{
    avl_node *pnodes[AVL_QUEUE_SIZE] = {0};
    int front = 0, rear = 0;
    rear = (rear + 1) % AVL_QUEUE_SIZE;
    pnodes[rear] = tree;
    while (rear != front)
    {
        front = (front + 1) % AVL_QUEUE_SIZE;
        avl_node *pnode = pnodes[front];
        printf("%d ", pnode->data);
        if (pnode->l_child != NULL)
        {
            rear = (rear + 1) % AVL_QUEUE_SIZE;
            pnodes[rear] = pnode->l_child;
        }
        if (pnode->r_child != NULL)
        {
            rear = (rear + 1) % AVL_QUEUE_SIZE;
            pnodes[rear] = pnode->r_child;
        }
    }
}
