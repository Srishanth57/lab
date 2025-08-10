#include <stdio.h>

#include <stdlib.h>

 

// Structure for Sequential Allocation

typedef struct {

    char name[10];

    int start;

    int length;

} SequentialFile;

 

// Structure for Indexed Allocation

typedef struct {

    char name[10];

    int index_block;

    int blocks[20];

    int block_count;

} IndexedFile;

 

// Structure for Linked Allocation

typedef struct {

    char name[10];

    int blocks[20];

    int block_count;

} LinkedFile;

 

// Function to simulate Sequential Allocation

void sequential_allocation() {

    int num_files;

    printf("\n=== SEQUENTIAL ALLOCATION ===\n");

    printf("Enter the number of files: ");

    scanf("%d", &num_files);

    

    SequentialFile files[num_files];

    

    // Input file details

    for (int i = 0; i < num_files; i++) {

        printf("Enter file name, starting block, and length: ");

        scanf("%s %d %d", files[i].name, &files[i].start, &files[i].length);

    }

    

    // Output

    printf("\nFile Name Starting Block Length Blocks Allocated\n");

    

    for (int i = 0; i < num_files; i++) {

        printf("%s %d %d ", files[i].name, files[i].start, files[i].length);

        

        // Print allocated blocks

        for (int j = 0; j < files[i].length; j++) {

            printf("%d", files[i].start + j);

            if (j < files[i].length - 1) printf(" → ");

        }

        printf("\n");

    }

}

 

// Function to simulate Indexed Allocation

void indexed_allocation() {

    int num_files;

    printf("\n=== INDEXED ALLOCATION ===\n");

    printf("Enter the number of files: ");

    scanf("%d", &num_files);

    

    IndexedFile files[num_files];

    

    // Input file details

    for (int i = 0; i < num_files; i++) {

        printf("Enter file name and index block: ");

        scanf("%s %d", files[i].name, &files[i].index_block);

        

        printf("Enter number of data blocks: ");

        scanf("%d", &files[i].block_count);

        

        printf("Enter data blocks: ");

        for (int j = 0; j < files[i].block_count; j++) {

            scanf("%d", &files[i].blocks[j]);

        }

    }

    

    // Output

    printf("\nFile Name Index Block Blocks Allocated\n");

    

    for (int i = 0; i < num_files; i++) {

        printf("%s %d ", files[i].name, files[i].index_block);

        for (int j = 0; j < files[i].block_count; j++) {

            printf("%d", files[i].blocks[j]);

            if (j < files[i].block_count - 1) printf(", ");

        }

        printf("\n");

    }

}

 

// Function to simulate Linked Allocation

void linked_allocation() {

    int num_files;

    printf("\n=== LINKED ALLOCATION ===\n");

    printf("Enter the number of files: ");

    scanf("%d", &num_files);

    

    LinkedFile files[num_files];

    

    // Input file details

    for (int i = 0; i < num_files; i++) {

        printf("Enter file name: ");

        scanf("%s", files[i].name);

        

        printf("Enter number of blocks: ");

        scanf("%d", &files[i].block_count);

        

        printf("Enter blocks: ");

        for (int j = 0; j < files[i].block_count; j++) {

            scanf("%d", &files[i].blocks[j]);

        }

    }

    

    // Output

    printf("\nFile Name Blocks Allocated (linked)\n");

    

    for (int i = 0; i < num_files; i++) {

        printf("%s ", files[i].name);

        for (int j = 0; j < files[i].block_count; j++) {

            printf("%d", files[i].blocks[j]);

            if (j < files[i].block_count - 1) printf(" → ");

        }

        printf("\n");

    }

}

 

int main() {

    int choice;

    

    printf("File Allocation Strategy Simulator\n");

  

    printf("1. Sequential Allocation\n");

    printf("2. Indexed Allocation\n");

    printf("3. Linked Allocation\n");

    printf("Enter your choice: ");

    scanf("%d", &choice);

    

    switch(choice) {

        case 1:

            sequential_allocation();

            break;

        case 2:

            indexed_allocation();

            break;

        case 3:

            linked_allocation();

            break;

        default:

            printf("Invalid choice!\n");

    }

    

    return 0;

}

