#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5001);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected to server!\n\n");

    int seq = 0;
    int total;

    printf("Enter the total no of frames to be sent: ");
    scanf("%d", &total);

    int error_frame = total / 2; // simulate error at middle frame

    for (int i = 0; i < total; i++) {
        char frame[50], ack[20];

        int is_last = (i == total - 1) ? 1 : 0;
        int send_seq = (i == error_frame) ? (1 - seq) : seq; // flip seq for error

        sprintf(frame, "%d:%d", send_seq, is_last);

        printf("Sending Frame %d (seq=%d)... ", i, send_seq);

        send(sockfd, frame, strlen(frame) + 1, 0);

        recv(sockfd, ack, sizeof(ack), 0);
        printf("Got: %s\n", ack);

        if (strncmp(ack, "NAK", 3) == 0) {
            printf("[NAK received for frame %d]\n", i);
        }

        seq = 1 - seq; // toggle sequence
    }

    printf("\nAll %d frames sent!\n", total);
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
