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

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5001);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sockfd, 1);

    printf("Server waiting...\n");

    clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);
    printf("Client connected!\n\n");

    int expected = 0;
    int frame_count = 0;
    int i = 0;

    while (1) {
        char frame[50];
        int seq, is_last;

        recv(clientfd, frame, sizeof(frame), 0);
        sscanf(frame, "%d:%d", &seq, &is_last);

        printf("Received: Frame %d ", i++);

        char ack[10];

        if (seq == expected) {
            frame_count++;
            sprintf(ack, "ACK:%d", frame_count);
            printf("-> Accepted\n");
            expected = 1 - expected; // toggle expected seq
        } else {
            sprintf(ack, "NAK"); // wrong sequence
            printf("-> Wrong order\n");
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


/* Output 
Connected to server!

Enter the total no of frames to be sent: 10
Sending Frame 0 (seq=0)... Got: ACK:1
Sending Frame 1 (seq=1)... Got: ACK:2
Sending Frame 2 (seq=0)... Got: ACK:3
Sending Frame 3 (seq=1)... Got: ACK:4
Sending Frame 4 (seq=0)... Got: ACK:5
Sending Frame 5 (seq=0)... Got: NAK
[NAK received for frame 5]
Sending Frame 6 (seq=0)... Got: NAK
[NAK received for frame 6]
Sending Frame 7 (seq=1)... Got: ACK:6
Sending Frame 8 (seq=0)... Got: ACK:7
Sending Frame 9 (seq=1)... Got: ACK:8

All 10 frames sent!


*/
