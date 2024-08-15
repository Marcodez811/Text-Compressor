#include "tree.h"
#include <stdio.h>
#include <string.h>

Node* createNode(uint64_t key, char val, Node* left, Node* right) {
    Node* n = malloc(sizeof(Node));
    n->key = key;
    n->val = val;
    n->left = left;
    n->right = right;
    return n;
}

Tree* createTree(Node* root) {
    Tree* t = malloc(sizeof(Tree));
    t->root = root;
    return t;
}

Tree* mergeTree(Tree* left, Tree* right) {
    Tree* newTree = malloc(sizeof(Tree));
    uint64_t newWeight = left->root->key + right->root->key;
    newTree->root = createNode(newWeight, '\0', left->root, right->root);
    return newTree; 
}

bool isLeaf(Node* root) {
    return !root->left && !root->right; 
}

void preorderHelper(Node* root, char* path) {
    if (isLeaf(root)) {
        if (root->val == '\n') {
            printf("\\n: %s\n", path);
        } else {
            printf("%c: %s\n", root->val, path);
        }
        return;
    }
    char* l_path = calloc(10, sizeof(char));
    char* r_path = calloc(10, sizeof(char));
    strcpy(l_path, path), strcpy(r_path, path);
    preorderHelper(root->left, strcat(l_path, "0"));
    preorderHelper(root->right, strcat(r_path, "1"));
}

void preorder(Tree* t) {
    char* path = calloc(10, sizeof(char));
    preorderHelper(t->root, path);
}

void freeHelper(Node* n) {
    if (!n) return;
    freeHelper(n->left);
    freeHelper(n->right);
    free(n);
}

void freeTree(Tree *t) {
    if (!t) return;
    freeHelper(t->root);
    free(t);
}