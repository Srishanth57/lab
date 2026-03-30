/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd, clientfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(5001);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sockfd, 1);

    printf("Server waiting...\n");
    clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);
    printf("Client connected!\n\n");

    int expected = 0;
    int i = 0 ;
    while (1) {
        char frame[50];
        int seq, is_last;

        // Receive frame
        recv(clientfd, frame, sizeof(frame), 0);
        sscanf(frame, "%d:%d", &seq, &is_last);
        printf("Received: Frame %d ", i++);
      
        char ack[10];
        if (seq == expected) {
            printf("-> Accepted. Sending ACK %d\n", seq);
            sprintf(ack, "ACK:%d", seq);
            expected = 1 - expected;   // toggle 0/1
        } else {
            printf("-> Wrong order! Sending NAK\n");
            sprintf(ack, "NAK:%d", expected);
        }

        send(clientfd, ack, strlen(ack) + 1, 0);

        if (is_last && seq == 1 - expected) {
            printf("\nAll frames received!\n");
            break;
        }
    }

    close(clientfd);
    close(sockfd);
    return 0;
}
*/
/*
Output:
Server waiting...
Client connected!

Received: Frame 0 -> Accepted. Sending ACK 0
Received: Frame 1 -> Accepted. Sending ACK 1
Received: Frame 0 -> Accepted. Sending ACK 0
Received: Frame 1 -> Accepted. Sending ACK 1
Received: Frame 0 -> Accepted. Sending ACK 0

All frames received!
*/




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int check(int a[], int n, int x) {
    for (int i = 0; i < n; i++)
        if (a[i] == x) return 1;
    return 0;
}

void del(int a[], int *n, int x) {
    for (int i = 0; i < *n; i++) {
        if (a[i] == x) {
            for (int j = i; j < *n - 1; j++)
                a[j] = a[j + 1];
            (*n)--;
            return;
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(5001);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Server waiting...\n\n");

    int total;
    printf("Enter total number of frames expected: ");
    scanf("%d", &total);

    int lost[50], l = 0;
    int timeout[50], t = 0;

    int nl, nt;

    printf("Enter number of lost frames: ");
    scanf("%d", &nl);

    if (nl > 0) {
        printf("Enter lost frame numbers: ");
        for (int i = 0; i < nl; i++)
            scanf("%d", &lost[l++]);
    }

    printf("Enter number of timeout frames: ");
    scanf("%d", &nt);

    if (nt > 0) {
        printf("Enter timeout frame numbers: ");
        for (int i = 0; i < nt; i++)
            scanf("%d", &timeout[t++]);
    }

    int next = 0;

    while (next < total) {
        char frame[20], ack[20];
        socklen_t len = sizeof(client_addr);

        recvfrom(sockfd, frame, sizeof(frame), 0,
                 (struct sockaddr *)&client_addr, &len);

        int f = atoi(frame);

        printf("[Server] Received Frame %d\n", f);

        if (check(lost, l, f)) {
            sprintf(ack, "%d", -1);
            sendto(sockfd, ack, strlen(ack), 0,
                   (struct sockaddr *)&client_addr, len);

            printf("[Server] Frame %d LOST -> NAK Sent\n\n", f);
            del(lost, &l, f);
        }
        else if (check(timeout, t, f)) {
            printf("[Server] Frame %d TIMEOUT -> No ACK\n\n", f);
            del(timeout, &t, f);
        }
        else {
            next = f + 1;
            sprintf(ack, "%d", next);

            sendto(sockfd, ack, strlen(ack), 0,
                   (struct sockaddr *)&client_addr, len);

            printf("[Server] Frame %d OK -> ACK Sent\n\n", f);
        }
    }

    printf("[Server] All frames received!\n");

    close(sockfd);
    return 0;
}
