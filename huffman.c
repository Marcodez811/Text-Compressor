#include "pq.h"
#include <stdio.h>
#include "huffman.h"
#define ASCII_RANGE 128
char* mapping_table[ASCII_RANGE];

// Analyzes the character frequency of the given file.
uint64_t* analyze_frequency(FILE* fp) {
    if (!fp) {
        fprintf(stderr, "Error: Invalid file pointer.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }
    uint64_t* table = calloc(ASCII_RANGE, sizeof(uint64_t));
    if (!table) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
        return NULL;
    }
    char line[1000];
    while (fgets(line, sizeof(line), fp)) {
        size_t n = strlen(line);
        for (size_t i = 0; i < n; i++) {
            table[line[i]]++;
        }
    }
    return table;
}

// Builds the huffman tree based off the given data
Tree* buildTree(uint64_t* data) {
    PriorityQueue* pq = initPQ();
    for (size_t i = 0; i < ASCII_RANGE; i++) {
        if (data[i] > 0) {
            insertPQ(pq, createTree(createNode(data[i], i, NULL, NULL)));
        }
    }
    while (pq->size > 1) {
        Tree* a = extractMin(pq);
        Tree* b = extractMin(pq);
        insertPQ(pq, mergeTree(a, b));
    }
    return extractMin(pq);
}

bool search(Node* root, int depth, char c, char* path) {
    if (isLeaf(root)) {
        if (root->val == c) {
            path[depth] = '\0';
            return true;
        }
        return false;
    }
    // search left subtree
    path[depth] = '0';
    if (search(root->left, depth + 1, c, path)) {
        return true;
    }
    path[depth] = '1';
    if (search(root->right, depth + 1, c, path)) {
        return true;
    }
    return false;
}

// Maps the character to its binary string
char* huffman_mapping(Tree* t, char c) {
    if (mapping_table[c] != NULL) {
        return mapping_table[c];
    }
    char* path = calloc(ASCII_RANGE, sizeof(char));
    if (!search(t->root, 0, c, path)) {
        fprintf(stderr, "Error: Character not found within tree.\n");
        exit(EXIT_FAILURE);
    }
    mapping_table[c] = path;
    return path;
}

// Compresses a file
FILE* compress(FILE* fp, const char* name) {
    // 1. Analyze and count the character frequency.
    uint64_t* freq_table = analyze_frequency(fp);
    // 2. Build the tree based on the character frequency.
    Tree* huffman_tree = buildTree(freq_table);
    // 3. Map each letter of the file to its representation in the tree structure.
    FILE* new_file = fopen(name, "wb");
    if (!new_file) {
        fprintf(stderr, "Error: Could not open file for writing.\n");
        exit(EXIT_FAILURE);
    }
    // Initialize mapping table
    for (size_t i = 0; i < ASCII_RANGE; i++) {
        mapping_table[i] = NULL;
    }
    // Reset the file pointer
    rewind(fp);
    // Create a buffer for packing bits
    unsigned char buffer = 0;
    int buffer_index = 0;    
    char c;
    while ((c = fgetc(fp)) != EOF) {
        char* bin_str = huffman_mapping(huffman_tree, c);
        size_t len = strlen(bin_str);
        // Write bits into buffer
        for (size_t i = 0; i < len; i++) {
            if (bin_str[i] == '1') {
                buffer |= (1 << (7 - buffer_index));
            }
            buffer_index++;
            if (buffer_index == 8) {
                fwrite(&buffer, 1, 1, new_file);
                buffer = 0;
                buffer_index = 0;
            }
        }
    }
    if (buffer_index > 0) {
        fwrite(&buffer, 1, 1, new_file);
    }
    fclose(new_file);
    free(freq_table);
    return new_file;
}
