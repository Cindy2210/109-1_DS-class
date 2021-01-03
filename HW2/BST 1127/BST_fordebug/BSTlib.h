#ifndef BSTlib_h
#define BSTlib_h

typedef struct node node_t;
void insertNode(void *element, node_t **root, int (*cp)(void *A, void *B));///���J�@�Ӹ`�I�iBST
node_t *deleteNode(void *target, node_t **root, int (*cp)(void *A, void *B), void(*print_node)(void*));///�R��BST
node_t *findMinNode(node_t *root);///��XBST����ȳ̤p
node_t *findMaxNode(node_t *root);///��XBST����ȳ̤j
node_t *findNode(void *target, node_t *root, int (*cp)(void *A, void *B));///��XBST�ŦX��Ȫ��`�I

void inOrder(node_t *root,  void(*print_node)(void*));///�C�L�XBST�ھڤ��ǰl�ܪk�C�Ӹ`�I�����e

void treeCopy(node_t **new_tree, node_t *root, int struct_node_size);///�ƻsBST

void treeEqual(node_t *tree1, node_t *tree2, int(*cp)(void *A, void *B), int *flag, void(*print_node)(void*));///������BST�O�_�ۦP

#endif
