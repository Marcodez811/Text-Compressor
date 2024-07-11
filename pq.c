#include "pq.h"

#define INIT_CAPACITY 16
#define left(x) (x * 2 + 1)
#define right(x) (x * 2 + 2)
#define parent(x) ((x - 1) / 2)

PriorityQueue* initPQ() {
    PriorityQueue* pq = malloc(sizeof(PriorityQueue));
    pq->size = 0;
    pq->capacity = INIT_CAPACITY;
    pq->data = calloc(INIT_CAPACITY, sizeof(Tree*));
    return pq;
}

int cmp(Tree* a, Tree* b) {
    return a->root->key - b->root->key;
}

void resizePQ(PriorityQueue* pq) {
    pq->capacity *= 2;
    pq->data = realloc(pq->data, pq->capacity * sizeof(Tree*));
}

void insertPQ(PriorityQueue* pq, Tree* t) {
    if (pq->size == pq->capacity) {
        resizePQ(pq);
    }
    int cur = pq->size;
    pq->data[pq->size++] = t;
    while (cur > 0 && cmp(pq->data[cur], pq->data[parent(cur)]) < 0) {
        Tree* tmp = pq->data[cur];
        pq->data[cur] = pq->data[parent(cur)];
        pq->data[parent(cur)] = tmp;
        cur = parent(cur);
    }
}

void heapify(PriorityQueue* pq, size_t i) {
    size_t l = left(i);
    size_t r = right(i);
    size_t smallest = i;
    if (l < pq->size && cmp(pq->data[l], pq->data[smallest]) < 0) {
        smallest = l;
    }
    if (r < pq->size && cmp(pq->data[r], pq->data[smallest]) < 0) {
        smallest = r;
    }
    if (smallest != i) {
        Tree* tmp = pq->data[i];
        pq->data[i] = pq->data[smallest];
        pq->data[smallest] = tmp;
        heapify(pq, smallest);
    }
}

Tree* extractMin(PriorityQueue* pq) {
    if (pq->size <= 0) return NULL;
    if (pq->size == 1) {
        return pq->data[--pq->size];
    }
    Tree* root = pq->data[0];
    pq->data[0] = pq->data[--pq->size];
    heapify(pq, 0);
    return root;
}