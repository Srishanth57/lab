#include <stdio.h>
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
