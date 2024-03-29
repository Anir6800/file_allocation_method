#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 100
#define FILE_SIZE 1024 // Assuming each file has the same size for simplicity

struct File {
    int start;
    int size;
};

struct File files[MAX_FILES];

int allocateContiguous(int fileSize) {
    int i;
    for (i = 0; i < MAX_FILES; ++i) {
        if (files[i].size == 0) {
            int j, flag = 1;
            for (j = 0; j < MAX_FILES; ++j) {
                if (files[j].size != 0) {
                    if (files[j].start < (MAX_FILES - fileSize)) {
                        flag = 0;
                        break;
                    }
                }
            }
            if (flag) {
                files[i].start = MAX_FILES - fileSize;
                files[i].size = fileSize;
                return i;
            }
        }
    }
    return -1; // No space available
}

void deallocateContiguous(int fileIndex) {
    if (fileIndex >= 0 && fileIndex < MAX_FILES) {
        files[fileIndex].size = 0;
    } else {
        printf("Invalid file index\n");
    }
}

int main() {
    int fileIndex = allocateContiguous(FILE_SIZE);
    if (fileIndex != -1) {
        printf("File allocated at index %d\n", fileIndex);
        // Perform operations with the allocated file
        deallocateContiguous(fileIndex);
        printf("File deallocated\n");
    } else {
        printf("Failed to allocate file\n");
    }
    return 0;
}
