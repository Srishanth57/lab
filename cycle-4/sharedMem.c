#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#define SHM_SIZE 1024
int main()
{
    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    char *shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Child process failed");
    }
    else if (pid == 0)
    {
        printf("Reading from the shared memory\n");
        sleep(2);
        printf("Message %s\n", shmaddr);
    }
    else
    {
        printf("Parent process writing  message to shared memory\n");
        strcpy(shmaddr, "Hello data in shared memory");
        wait(NULL);
    }

    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}



// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SHM_KEY 1234

int main() {
    int shmid;
    char *shared_memory;

    // Create shared memory
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Write to shared memory
    char *message = "Hello from writer!";
    strncpy(shared_memory, message, SHM_SIZE);
    printf("Writer wrote: %s\n", shared_memory);

    // Wait for reader (manual termination in this case)
    printf("Press Enter after reader finishes...\n");
    getchar();

    // Detach shared memory
    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    // Remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl failed");
        exit(1);
    }

    printf("Writer finished.\n");
    return 0;
}









//Interprocess communication using two files







// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SHM_KEY 1234

int main() {
    int shmid;
    char *shared_memory;

    // Access existing shared memory
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Read from shared memory
    printf("Reader read: %s\n", shared_memory);

    // Detach shared memory
    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
        exit(1);
    }

    printf("Reader finished.\n");
    return 0;
}








