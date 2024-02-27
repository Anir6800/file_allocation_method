#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 100
#define MAX_BLOCKS 10

struct IndexBlock {
    int blocks[MAX_BLOCKS];
};

struct File {
    struct IndexBlock indexBlock;
    int size;
};

struct File files[MAX_FILES];

int allocateIndexed(int fileSize) {
    int i;
    for (i = 0; i < MAX_FILES; ++i) {
        if (files[i].size == 0) {
            int j, count = 0;
            for (j = 0; j < MAX_FILES; ++j) {
                if (files[j].size != 0) {
                    ++count;
                }
            }
            if (count + fileSize <= MAX_BLOCKS) {
                int k;
                for (k = 0; k < fileSize; ++k) {
                    files[i].indexBlock.blocks[k] = count + k;
                }
                files[i].size = fileSize;
                return i;
            }
        }
    }
    return -1; // No space available
}

void deallocateIndexed(int fileIndex) {
    if (fileIndex >= 0 && fileIndex < MAX_FILES) {
        files[fileIndex].size = 0;
    } else {
        printf("Invalid file index\n");
    }
}

int main() {
    int fileIndex = allocateIndexed(3); // Example: Allocate a file of 3 blocks
    if (fileIndex != -1) {
        printf("File allocated at index %d\n", fileIndex);
        // Perform operations with the allocated file
        deallocateIndexed(fileIndex);
        printf("File deallocated\n");
    } else {
        printf("Failed to allocate file\n");
    }
    return 0;
}
