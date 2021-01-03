#ifndef BSTlib_h
#define BSTlib_h

typedef struct node node_t;
void insertNode(void *element, node_t **root, int (*cp)(void *A, void *B));///插入一個節點進BST
node_t *deleteNode(void *target, node_t **root, int (*cp)(void *A, void *B), void(*print_node)(void*));///刪除BST
node_t *findMinNode(node_t *root);///找出BST中鍵值最小
node_t *findMaxNode(node_t *root);///找出BST中鍵值最大
node_t *findNode(void *target, node_t *root, int (*cp)(void *A, void *B));///找出BST符合鍵值的節點

void inOrder(node_t *root,  void(*print_node)(void*));///列印出BST根據中序追蹤法每個節點的內容

void treeCopy(node_t **new_tree, node_t *root, int struct_node_size);///複製BST

void treeEqual(node_t *tree1, node_t *tree2, int(*cp)(void *A, void *B), int *flag, void(*print_node)(void*));///比較兩個BST是否相同

#endif
