#include "huffman.h"

int main(int argc, char* argv[]) {
    const char* filename = argv[1];
    FILE* fp = fopen(filename, "r");
    compress(fp, "compressed.txt");
    return 0;
}