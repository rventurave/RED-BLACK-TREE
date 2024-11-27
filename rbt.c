
#include <stdlib.h>
#include "rbt.h"

// Crear un nodo del Árbol Rojo-Negro
RBNode* createRBNode(int key) {
    RBNode* newNode = malloc(sizeof(RBNode));
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = RED;  // Los nuevos nodos siempre comienzan siendo rojos
    newNode->key = key;
    return newNode;
}

// Crear un Árbol Rojo-Negro
RBTree* createRBTree() {
    RBTree* rbTree = malloc(sizeof(RBTree));
    rbTree->nil = malloc(sizeof(RBNode)); // Nodo centinela
    rbTree->nil->color = BLACK;
    rbTree->nil->left = rbTree->nil->right = rbTree->nil->parent = NULL;
    rbTree->root = rbTree->nil; // Inicialmente el árbol está vacío
    return rbTree;
}

// Rotación a la izquierda
void rotateLeft(RBTree* t, RBNode* x) {
    RBNode* y = x->right;       // y es el hijo derecho de x
    x->right = y->left;         // Transfiere el subárbol izquierdo de y a ser el hijo derecho de x

    if (y->left != t->nil) {    // Si y tiene un hijo izquierdo, actualiza su padre
        y->left->parent = x;
    }

    y->parent = x->parent;      // Conecta el padre de x con y

    if (x->parent == t->nil) {  // Si x es la raíz del árbol
        t->root = y;
    } else if (x == x->parent->left) { // Si x es hijo izquierdo
        x->parent->left = y;
    } else {                    // Si x es hijo derecho
        x->parent->right = y;
    }

    y->left = x;                // Establece x como hijo izquierdo de y
    x->parent = y;              // Actualiza el padre de x
}

// Rotación a la derecha
void rotateRight(RBTree* t, RBNode* x) {
    RBNode* y = x->left;        // y es el hijo izquierdo de x
    x->left = y->right;         // Transfiere el subárbol derecho de y a ser el hijo izquierdo de x

    if (y->right != t->nil) {   // Si y tiene un hijo derecho, actualiza su padre
        y->right->parent = x;
    }

    y->parent = x->parent;      // Conecta el padre de x con y

    if (x->parent == t->nil) {  // Si x es la raíz del árbol
        t->root = y;
    } else if (x == x->parent->right) { // Si x es hijo derecho
        x->parent->right = y;
    } else {                    // Si x es hijo izquierdo
        x->parent->left = y;
    }

    y->right = x;               // Establece x como hijo derecho de y
    x->parent = y;              // Actualiza el padre de x
}

void rbInsertFixUp(RBTree* t, RBNode* z) {
    while (z->parent->color == RED) { // Mientras el padre de z sea rojo
        if (z->parent == z->parent->parent->left) { // Caso en que el padre de z es hijo izquierdo
            RBNode* y = z->parent->parent->right; // El tío de z

            if (y->color == RED) { // Caso 1: El tío de z también es rojo
                z->parent->color = BLACK; // El padre de z se vuelve negro
                y->color = BLACK;        // El tío de z se vuelve negro
                z->parent->parent->color = RED; // El abuelo de z se vuelve rojo
                z = z->parent->parent; // Avanza hacia el abuelo de z
            } else {
                if (z == z->parent->right) { // Caso 2: z es hijo derecho
                    z = z->parent;
                    rotateLeft(t, z); // Realiza una rotación a la izquierda
                }
                // Caso 3: z es hijo izquierdo
                z->parent->color = BLACK; // El padre de z se vuelve negro
                z->parent->parent->color = RED; // El abuelo de z se vuelve rojo
                rotateRight(t, z->parent->parent); // Realiza una rotación a la derecha
            }
        } else { // Caso en que el padre de z es hijo derecho (simétrico al anterior)
            RBNode* y = z->parent->parent->left; // El tío de z

            if (y->color == RED) { // Caso 1: El tío de z también es rojo
                z->parent->color = BLACK; // El padre de z se vuelve negro
                y->color = BLACK;        // El tío de z se vuelve negro
                z->parent->parent->color = RED; // El abuelo de z se vuelve rojo
                z = z->parent->parent; // Avanza hacia el abuelo de z
            } else {
                if (z == z->parent->left) { // Caso 2: z es hijo izquierdo
                    z = z->parent;
                    rotateRight(t, z); // Realiza una rotación a la derecha
                }
                // Caso 3: z es hijo derecho
                z->parent->color = BLACK; // El padre de z se vuelve negro
                z->parent->parent->color = RED; // El abuelo de z se vuelve rojo
                rotateLeft(t, z->parent->parent); // Realiza una rotación a la izquierda
            }
        }
    }
    t->root->color = BLACK; // Asegura que la raíz del árbol sea negra
}
// Insertar un nodo en el Árbol Rojo-Negro
void insertRBT(RBTree *t, RBNode *z) {
    RBNode* y = t->nil;         // Inicializa y como nodo nil
    RBNode* x = t->root;        // Comienza desde la raíz del árbol

    while (x != t->nil) {       // Encuentra la posición correcta para z
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == t->nil) {          // Si el árbol estaba vacío
        t->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = t->nil;
    z->right = t->nil;
    z->color = RED;             // Los nuevos nodos siempre son rojos al insertarse

    // Llamada a una función de corrección (no implementada aquí)
    rbInsertFixUp(t, z);
}

