#include <stdio.h>
#include <stdlib.h>
#include "BSTlib.h"
#include <string.h>
struct node
{
    struct node *left;
    struct node *right;
};

node_t *findMinNode(node_t *root)///找出BST中鍵值最小
{
    node_t *cur = root;
    while( root != NULL)
    {
        cur = root;
        root = root->left;
    }
    return cur;
}

node_t *findMaxNode(node_t *root)///找出BST中鍵值最大
{
    node_t *cur = root;
    while( root != NULL)
    {
        cur = root;
        root = root->right;
    }
    return cur;
}
void insertNode(void *element, node_t **root, int (*cp)(void *A, void *B))//插入一個節點進BST
{
    if( (*root) == NULL)
    {
        (*root) = element;
    }
    else
    {
        node_t *temp = *root;
        while(1)
        {
            if( cp( ((void*)temp), element ) == 1 )
            {
                if( temp->left == NULL)
                {
                    temp->left = (node_t*)element;
                    return ;
                }
                else
                    temp = temp->left;
            }
            else
            {
                if( temp->right == NULL)
                {
                    temp->right = (node_t*)element;
                    return ;
                }
                else
                    temp = temp->right;
            }
        }
    }
}

node_t *deleteNode(void *target, node_t **root, int (*cp)(void *A, void *B))///刪除BST
{
    if(!(*root))
        return (*root);

    if( cp((void*)target, (void*)(*root)) == -1)///target value > root value
        (*root)->left = deleteNode(target, &((*root)->left), cp);

    else if(cp((void*)target, (void*)(*root)) == 1)///target value > root value
        (*root)->right = deleteNode(target, &((*root)->right), cp);

    else
    {
        ///with only one child or no child
        if(((*root)->left) == NULL )
        {
            node_t *tmp = (*root)->right;
            free(root);
            return tmp;
        }
        else if(((*root)->right) == NULL)
        {
            node_t *tmp = (*root)->left;
            free(root);
            return tmp;
        }

        ///node with two children
        node_t *tmp = findMinNode((*root)->right);
        if((*root)->left != NULL)
        {
            tmp->left = (*root)->left;
        }
        (*root) = tmp;
        (*root)->right = deleteNode(target, &((*root)->right), cp);
    }
    return (*root);
}

node_t *findNode(void *target, node_t *root, int (*cp)(void *A, void *B))///找出BST符合鍵值的節點
{
    node_t *curr = root;
    int judge = 1;
    while(curr != NULL && judge != 0)
    {
        judge = cp( (void*)curr, target) ;

        if(judge == 1)
            curr = curr->left;
        else if (judge == -1)
            curr = curr->right;
    }
    return curr;
}

void inOrder(node_t *root, void (*print_node)(void*))///列印出BST根據中序追蹤法每個節點的內容
{
    if( root )
    {
        inOrder(root->left, print_node);
        print_node((void*)root);
        inOrder(root->right, print_node);
    }
    return;
}

void treeCopy(node_t **new_tree, node_t *root, int struct_node_size)///複製BST
{
    if(!root)
        return;
    void *new_root = malloc(sizeof(char)*struct_node_size);
    memcpy(new_root, root, struct_node_size);
    *new_tree = (node_t*)new_root;
    treeCopy( &((*new_tree)->left), root->left, struct_node_size);
    treeCopy( &((*new_tree)->right), root->right, struct_node_size);
}

void treeEqual(node_t *tree1, node_t *tree2, int(*cp)(void *A, void *B), int *flag)///比較兩個BST是否相同
{
    if(tree1 == NULL && tree2 == NULL)
        return NULL;
    if( *flag == 0 )
        return;
    if( cp((void*)tree1, (void*)tree2) != 0 )
    {
        *flag = 0;
        return;
    }
    if( (tree1->left != NULL && tree2->left == NULL) || (tree1->left == NULL && tree2->left != NULL) )
    {
        *flag = 0;
        return;
    }
    if( (tree1->right != NULL && tree2->right == NULL) || (tree1->right == NULL && tree2->right != NULL))
    {
        *flag = 0;
        return;
    }
    treeEqual(tree1->left, tree2->left, cp, flag);
    treeEqual(tree1->right, tree2->right, cp, flag);

}
