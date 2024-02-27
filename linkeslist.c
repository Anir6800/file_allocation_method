#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 100

struct Node {
    int blockNumber;
    struct Node* next;
};

struct File {
    struct Node* head;
    int size;
};

struct File files[MAX_FILES];

int allocateLinked(int fileSize) {
    int i;
    for (i = 0; i < MAX_FILES; ++i) {
        if (files[i].size == 0) {
            int j, count = 0;
            struct Node* temp = NULL;
            for (j = 0; j < MAX_FILES; ++j) {
                if (files[j].size != 0) {
                    ++count;
                    temp = files[j].head;
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                }
            }
            if (count + fileSize <= MAX_FILES) {
                files[i].head = malloc(sizeof(struct Node));
                struct Node* currentNode = files[i].head;
                int k;
                for (k = 0; k < fileSize - 1; ++k) {
                    currentNode->blockNumber = count + k;
                    currentNode->next = malloc(sizeof(struct Node));
                    currentNode = currentNode->next;
                }
                currentNode->blockNumber = count + k;
                currentNode->next = NULL;
                files[i].size = fileSize;
                return i;
            }
        }
    }
    return -1; // No space available
}

void deallocateLinked(int fileIndex) {
    if (fileIndex >= 0 && fileIndex < MAX_FILES) {
        free(files[fileIndex].head);
        files[fileIndex].size = 0;
    } else {
        printf("Invalid file index\n");
    }
}

int main() {
    int fileIndex = allocateLinked(3); // Example: Allocate a file of 3 blocks
    if (fileIndex != -1) {
        printf("File allocated at index %d\n", fileIndex);
        // Perform operations with the allocated file
        deallocateLinked(fileIndex);
        printf("File deallocated\n");
    } else {
        printf("Failed to allocate file\n");
    }
    return 0;
}
