#ifndef RBT_H
#define RBT_H
typedef enum {RED, BLACK} Color;
typedef struct sRBNode{
  struct sRBNode* parent;
  struct sRBNode* left;
  struct sRBNode* right;
  Color color;
  int key;
} RBNode;

RBNode* createRBNode(int key);

typedef struct{ RBNode* root;} RBTree;

RBTree* createRBTree();

void insertRBT(RBTree *rbtree, RBNode* z);

void rotateLeft(RBNode t, RBNode* x);
void rotateRight(RBNode t, RBNode* x);

#endif
