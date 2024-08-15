#include "lib/huffman.h"

int main(int argc, char* argv[]) {
    const char* filename = argv[1];
    FILE* fp = fopen(filename, "r");
    compress(fp, "output/compressed");
    return 0;
}