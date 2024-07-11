#include "pq.h"
#include <stdio.h>
#include "huffman.h"
#define ASCII_RANGE 128

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

FILE* compress(FILE* fp, const char* name) {
    // 1. Analyze and count the character frequency.
    uint64_t* freq_table = analyze_frequency(fp);
    // 2. Build the tree based off the character frequency.
    Tree* huffman_tree = buildTree(freq_table);
    // 3. Create a textfile and map each letter of the file to its representation in 
    //    the huffman tree structure.
    FILE* new_file = fopen(name, "w");
    char line[1000];
    char new_line[1000];
    // start here!!!
    while (fgets(line, sizeof(line), fp)) {
        size_t n = strlen(line);
        for (size_t i = 0; i < n; i++) {
            
        }
    }
    return new_file;
}