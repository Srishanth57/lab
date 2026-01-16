#include <stdio.h>
#include <stdlib.h>
#define DISK_SIZE 50
#define MAX_FILES 10

// Structure for Linked Allocation
struct LinkedNode {
    int block;
    struct LinkedNode* next;
};

// Function to initialize disk (0 = free, 1 = occupied)
void init_disk(int disk[], int size) {
    for (int i = 0; i < size; i++) disk[i] = 0;
}

// Sequential Allocation
void sequential_allocation(int disk[], int file_size, int file_id) {
    int start = -1;
    int count = 0;
    
    // Find contiguous free blocks
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == 0) {
            if (start == -1) start = i;
            count++;
            if (count == file_size) break;
        } else {
            start = -1;
            count = 0;
        }
    }
    
    if (count == file_size) {
        printf("\nSequential Allocation for File %d:\n", file_id);
        printf("Start Block: %d\nBlocks: ", start);
        for (int i = 0; i < file_size; i++) {
            disk[start + i] = 1;
            printf("%d ", start + i);
        }
        printf("\n");
    } else {
        printf("\nSequential Allocation for File %d: Not enough contiguous space\n", file_id);
    }
}

// Indexed Allocation
void indexed_allocation(int disk[], int file_size, int file_id) {
    int index_block = -1;
    int blocks[MAX_FILES];
    int free_count = 0;
    
    // Count free blocks
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == 0) free_count++;
    }
    
    if (free_count < file_size + 1) { // +1 for index block
        printf("\nIndexed Allocation for File %d: Not enough free blocks\n", file_id);
        return;
    }
    
    // Find index block
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == 0) {
            index_block = i;
            disk[i] = 1;
            break;
        }
    }
    
    // Allocate data blocks
    int allocated = 0;
    for (int i = 0; i < DISK_SIZE && allocated < file_size; i++) {
        if (disk[i] == 0) {
            blocks[allocated] = i;
            disk[i] = 1;
            allocated++;
        }
    }
    
    printf("\nIndexed Allocation for File %d:\n", file_id);
    printf("Index Block: %d\nData Blocks: ", index_block);
    for (int i = 0; i < file_size; i++) {
        printf("%d ", blocks[i]);
    }
    printf("\n");
}

// Linked Allocation
void linked_allocation(int disk[], int file_size, int file_id) {
    struct LinkedNode* head = NULL;
    struct LinkedNode* tail = NULL;
    int free_count = 0;
    
    // Count free blocks
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == 0) free_count++;
    }
    
    if (free_count < file_size) {
        printf("\nLinked Allocation for File %d: Not enough free blocks\n", file_id);
        return;
    }
    
    // Allocate blocks
    int allocated = 0;
    for (int i = 0; i < DISK_SIZE && allocated < file_size; i++) {
        if (disk[i] == 0) {
            struct LinkedNode* new_node = (struct LinkedNode*)malloc(sizeof(struct LinkedNode));
            new_node->block = i;
            new_node->next = NULL;
            
            if (head == NULL) {
                head = tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
            
            disk[i] = 1;
            allocated++;
        }
    }
    
    // Print allocation
    printf("\nLinked Allocation for File %d:\n", file_id);
    printf("Blocks: ");
    struct LinkedNode* current = head;
    while (current != NULL) {
        printf("%d", current->block);
        if (current->next != NULL) printf(" -> ");
        current = current->next;
    }
    printf("\n");
    
    // Free memory
    current = head;
    while (current != NULL) {
        struct LinkedNode* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int disk[DISK_SIZE];
    int num_files, file_sizes[MAX_FILES];
    
    init_disk(disk, DISK_SIZE);
    
    printf("Enter the number of files: ");
    scanf("%d", &num_files);
    if (num_files > MAX_FILES) {
        printf("Exceeds maximum files (%d)\n", MAX_FILES);
        return 1;
    }
    
    printf("Enter the size of each file:\n");
    for (int i = 0; i < num_files; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &file_sizes[i]);
        if (file_sizes[i] > DISK_SIZE) {
            printf("File size exceeds disk size (%d)\n", DISK_SIZE);
            return 1;
        }
    }
    
    // Simulate allocations for each file
    for (int i = 0; i < num_files; i++) {
        int temp_disk[DISK_SIZE];
        for (int j = 0; j < DISK_SIZE; j++) temp_disk[j] = disk[j];
        
        sequential_allocation(temp_disk, file_sizes[i], i + 1);
        
        for (int j = 0; j < DISK_SIZE; j++) temp_disk[j] = disk[j];
        indexed_allocation(temp_disk, file_sizes[i], i + 1);
        
        for (int j = 0; j < DISK_SIZE; j++) temp_disk[j] = disk[j];
        linked_allocation(temp_disk, file_sizes[i], i + 1);
    }
    
    return 0;
}