#include <stdio.h>

#define TOTAL_MEMORY 100
#define MAX_FILES 100

int memory[TOTAL_MEMORY];
int startAddress[MAX_FILES];
int endAddress[MAX_FILES];
int numFiles = 0;

void allocateContiguous(int size) {
    if(numFiles == MAX_FILES) {
        printf("No more files can be allocated\n");
        return;
    }
    int i;
    for(i = 0; i < TOTAL_MEMORY - size + 1; i++) {
        if(memory[i] == 0) {
            int j;
            for(j = i; j < i + size; j++) {
                memory[j] = 1;
            }
            startAddress[numFiles] = i;
            endAddress[numFiles] = i + size - 1;
            numFiles++;
            printf("File allocated successfully\n");
            return;
        }
    }
    printf("No contiguous space found\n");
}

void deallocateContiguous(int index) {
    if(index >= numFiles) {
        printf("Invalid file index\n");
        return;
    }
    int i;
    for(i = startAddress[index]; i <= endAddress[index]; i++) {
        memory[i] = 0;
    }
    numFiles--;
}

int main() {
    int i;
    for(i = 0; i < TOTAL_MEMORY; i++) {
        memory[i] = 0;
    }
    allocateContiguous(10);
    allocateContiguous(20);
    allocateContiguous(30);
    deallocateContiguous(0);
    allocateContiguous(40);
    return 0;
}