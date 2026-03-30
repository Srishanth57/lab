#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5001);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Server waiting...\n");

    int expected = 0;
    int received = 0;
    int total = -1;

    while (1) {

        char frame[50] = {0};
        int seq, is_last, frame_total;

        recvfrom(sockfd, frame, sizeof(frame), 0,
                 (struct sockaddr *)&client_addr, &len);

        sscanf(frame, "%d:%d:%d", &seq, &is_last, &frame_total);

        if (total == -1) total = frame_total;

        printf("Received: Frame %d ", seq);

        char ack[20];

        if (seq == expected) {

            received++;
            expected++;

            printf("-> Accepted. Sending ACK %d\n", expected);
            sprintf(ack, "ACK:%d", expected);

        } else {

            printf("-> Wrong order! Sending NAK\n");
            sprintf(ack, "NAK:%d", expected);
        }

        sendto(sockfd, ack, strlen(ack) + 1, 0,
               (struct sockaddr *)&client_addr, len);

        if (received == total) {
            printf("\nAll %d frames received!\n", total);
            break;
        }
    }

    close(sockfd);
    return 0;
}
