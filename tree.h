#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef TREE_H
#define TREE_H

typedef struct node {
    uint64_t key;
    char val;
    struct node* left;
    struct node* right;
} Node;

typedef struct tree {
    Node* root;
} Tree;

Node* createNode(uint64_t key, char val, Node* left, Node* right);
Tree* createTree(Node* root);
Tree* mergeTree(Tree* left, Tree* right);
bool isLeaf(Node* root);
void preorder(Tree* t);
#endif // TREE_H
