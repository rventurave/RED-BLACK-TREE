#ifndef RBT_H
#define RBT_H
typedef enum {RED, BLACK} Color;

typedef struct sRBNode {
    struct sRBNode* parent;
    struct sRBNode* left;
    struct sRBNode* right;
    Color color;
    int key;
} RBNode;

RBNode* createRBNode(int key);

typedef struct {
    RBNode* root;
    RBNode* nil; // Nodo centinela
} RBTree;

RBTree* createRBTree();
void insertRBT(RBTree *rbtree, RBNode* z);

void rotateLeft(RBTree* T, RBNode* x);
void rotateRight(RBTree* T, RBNode* x);
void rbInsertFixUp(RBTree* T, RBNode* z);

#endif

