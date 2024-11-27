#include <stdlib.h>
#include "rbt.h"

RBNode* createRBNode(int key){
  RBNode* newNode = malloc(sizeof(RBNode));
  newNode->parent = NULL;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->color = RED;
  newNode->key = key ;
  return newNode;
}

RBTree* createRBTree(){
  RBTree* rbTree = malloc(sizeof(RBTree));
  rbTree->root = NULL;
  return rbTree;
}

void insertRBT(RBTree *t, RBNode *z){
  RBNode* x = t->root;
  RBNode* y = NULL;

  while(x != NULL){
    y = x;
    if(z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }

  z->parent = y;

  if(y){
    if(z->key < y->key)
      y->left = z;
    else 
      y->right = z;
  }else{
    t->root = z;
  }
  //rbInsertFixUp(t, z);
}
