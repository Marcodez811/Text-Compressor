#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct node {
    u_int64_t key;
    char val;
    struct node* left;
    struct node* right;
} Node;

typedef struct tree {
    Node* root;
} Tree;

/**
    Analyzes the character usage of this file.
    Then creates and returns a usage table.
*/
u_int64_t* analyze_frequency(FILE* fp) {
    u_int64_t* table = calloc(256, sizeof(u_int64_t));
    char line[1000];
    
    return table;
}

/**
    Compress the text file into a new file 
*/
FILE* compress(FILE* fp, const char* name) {
    // 1. Analyze and count the character frequency.

}