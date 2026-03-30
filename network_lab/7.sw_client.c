/*#include <stdio.h>
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
*/
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




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(5001);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Timeout setup
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int total;
    printf("Enter total number of frames: ");
    scanf("%d", &total);

    printf("\n[Client] Sending %d frames...\n\n", total);

    int next = 0;

    while (next < total) {
        char frame[20], ack[20];

        sprintf(frame, "%d", next);

        printf("[Client] Sending Frame %d...\n", next);
        sendto(sockfd, frame, strlen(frame), 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr));

        socklen_t len = sizeof(server_addr);

        int r = recvfrom(sockfd, ack, sizeof(ack), 0,
                         (struct sockaddr *)&server_addr, &len);

        if (r < 0) {
            printf("[Client] TIMEOUT -> Resending Frame %d\n\n", next);
            continue;
        }

        ack[r] = '\0';
        int a = atoi(ack);

        printf("[Client] Received ACK: %d\n", a);

        if (a == -1) {
            printf("[Client] NAK -> Resending Frame %d\n\n", next);
            continue;
        }

        if (a == next + 1) {
            printf("[Client] Frame %d Acknowledged\n\n", next);
            next++;
        } else {
            printf("[Client] Wrong ACK -> Resend\n\n");
        }
    }

    printf("[Client] All frames sent successfully!\n");

    close(sockfd);
    return 0;
}
