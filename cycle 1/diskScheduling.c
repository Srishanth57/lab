#include <stdio.h>
#include <stdlib.h>
#define MAX_REQUESTS 20

// Function to calculate absolute difference
int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}
 
// FCFS Disk Scheduling
void fcfs(int requests[], int n, int head) {
    int total_movement = 0;
    printf("\nFCFS Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);
    
    for (int i = 0; i < n; i++) {
        total_movement += abs_diff(head, requests[i]);
        head = requests[i];
        printf(" -> %d", head);
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
}

// SCAN Disk Scheduling
void scan(int requests[], int n, int head, int disk_size, int direction) {
    int total_movement = 0;
    int sorted[MAX_REQUESTS];
    for (int i = 0; i < n; i++) sorted[i] = requests[i];
    
    // Sort the requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("\nSCAN Disk Scheduling (Direction: %s):\n", direction ? "Right" : "Left");
    printf("Head Movement Sequence: %d", head);
    
    if (direction == 1) { // Right direction
        int i;
        for (i = 0; i < n; i++) {
            if (sorted[i] >= head) break;
        }
        // Move right to max
        for (; i < n; i++) {
            total_movement += abs_diff(head, sorted[i]);
            head = sorted[i];
            printf(" -> %d", head);
        }
        if (head != disk_size - 1) {
            total_movement += abs_diff(head, disk_size - 1);
            head = disk_size - 1;
            printf(" -> %d", head);
        }
        // Move left to remaining
        for (i = i - 2; i >= 0; i--) {
            total_movement += abs_diff(head, sorted[i]);
            head = sorted[i];
            printf(" -> %d", head);
        }
    } else { // Left direction
        int i;
        for (i = n - 1; i >= 0; i--) {
            if (sorted[i] <= head) break;
        }
        // Move left to 0
        for (; i >= 0; i--) {
            total_movement += abs_diff(head, sorted[i]);
            head = sorted[i];
            printf(" -> %d", head);
        }
        if (head != 0) {
            total_movement += abs_diff(head, 0);
            head = 0;
            printf(" -> %d", head);
        }
        // Move right to remaining
        for (i = i + 2; i < n; i++) {
            total_movement += abs_diff(head, sorted[i]);
            head = sorted[i];
            printf(" -> %d", head);
        }
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
}

// C-SCAN Disk Scheduling
void c_scan(int requests[], int n, int head, int disk_size) {
    int total_movement = 0;
    int sorted[MAX_REQUESTS];
    for (int i = 0; i < n; i++) sorted[i] = requests[i];  
    
    // Sort the requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    
    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);
    
    int start_idx;
    for (start_idx = 0; start_idx < n; start_idx++) {
        if (sorted[start_idx] >= head) break;
    }
    
    // Move right to end
    for (int i = start_idx; i < n; i++) {
        total_movement += abs_diff(head, sorted[i]);
        head = sorted[i];
        printf(" -> %d", head);
    }
    if (head != disk_size - 1) {
        total_movement += abs_diff(head, disk_size - 1);
        head = disk_size - 1;
        printf(" -> %d", head);
    }
    // Jump to 0
    total_movement += abs_diff(head, 0);
    head = 0;
    printf(" -> %d", head);
    // Move right to remaining
    for (int i = 0; i < start_idx; i++) {
        total_movement += abs_diff(head, sorted[i]);
        head = sorted[i];
        printf(" -> %d", head);
    }
    
    printf("\nTotal Head Movement: %d\n", total_movement);
}

int main() {
    int requests[MAX_REQUESTS], n, head, disk_size, direction;
    
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);
    
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);

    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
   
    
    printf("Enter direction for SCAN (0 for left, 1 for right): ");
    scanf("%d", &direction);
    
    // Simulate all three algorithms
    fcfs(requests, n, head);
    scan(requests, n, head, disk_size, direction);
    c_scan(requests, n, head, disk_size);
    
    return 0;
}