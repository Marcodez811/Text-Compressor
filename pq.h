#include "huffman.h"
#include "tree.h"

typedef struct heap {
    size_t size;
    size_t capacity;
    Tree** data;
} PriorityQueue;

PriorityQueue* initPQ();
Tree* extractMin(PriorityQueue* pq);
void insertPQ(PriorityQueue* pq, Tree* t);