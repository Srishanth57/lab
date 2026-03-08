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
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(5001);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Connected to server!\n\n");

    int seq = 0;
    int total ; 
    printf("Enter the total no of frames to be sent: "); 
    scanf("%d" , &total) ; 

    for (int i = 0; i < total; i++) {
        char frame[50], ack[20];
        int is_last = (i == total - 1) ? 1 : 0;

            // Send frame as "seq:is_last"
            sprintf(frame, "%d:%d", seq, is_last);
            printf("Sending Frame %d (seq=%d)... ", i, seq);
            send(sockfd, frame, strlen(frame) + 1, 0);

            // Wait for ACK
            recv(sockfd, ack, sizeof(ack), 0);
            printf("Got: %s\n", ack);

        
            seq = 1 - seq;   // toggle and move on
                
    }

    printf("\nAll %d frames sent successfully!\n", total);
    close(sockfd);
    return 0;
}

/*
Output:
Connected to server!

Sending Frame 0 (seq=0)... Got: ACK:0
Sending Frame 1 (seq=1)... Got: ACK:1
Sending Frame 2 (seq=0)... Got: ACK:0
Sending Frame 3 (seq=1)... Got: ACK:1
Sending Frame 4 (seq=0)... Got: ACK:0

All 5 frames sent successfully!
*/
