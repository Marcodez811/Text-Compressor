#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/**
    Analyzes the character usage of this file.
    Then creates and returns a usage table.
*/
uint64_t* analyze_frequency(FILE* fp);
/**
    Compress the text file into a new file using 'HUFFMAN CODING'
*/
FILE* compress(FILE* fp, const char* name);