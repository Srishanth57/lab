#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TOTAL  8
#define WINDOW 4

void send_frame(int sockfd, int seq, int last) {
    send(sockfd, &seq,  sizeof(int), 0);
    send(sockfd, &last, sizeof(int), 0);
}

int main() {
    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(5002);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    int base = 0, next = 0;

    while (base < TOTAL) {
        // Send window
        while (next < base + WINDOW && next < TOTAL) {
            int last = (next == TOTAL - 1);

            // Simulate frame 2 lost on first pass
            if (next == 2 && base == 0) {
                printf("Sending frame %d (lost)\n", next);
                send_frame(sockfd, 99, last);   // wrong seq triggers NAK
            } else {
                printf("Sending frame %d\n", next);
                send_frame(sockfd, next, last);
            }
            next++;
        }

        // Get one response
        char reply[4];
        recv(sockfd, reply, sizeof(reply), 0);

        if (strcmp(reply, "ACK") == 0) {
            printf("ACK received -> base moves to %d\n\n", base + 1);
            base++;
        } else {
            printf("NAK received -> retransmitting from frame %d\n\n", base);
            next = base;   // go back
        }
    }

    printf("All frames sent.\n");
    close(sockfd);
    return 0;
}

/*
Output:
Sending frame 0
Sending frame 1
Sending frame 2 (lost)
Sending frame 3
ACK received -> base moves to 1

ACK received -> base moves to 2

NAK received -> retransmitting from frame 2

Sending frame 2
Sending frame 3
Sending frame 4
Sending frame 5
ACK received -> base moves to 3

ACK received -> base moves to 4

ACK received -> base moves to 5

ACK received -> base moves to 6

Sending frame 6
Sending frame 7
ACK received -> base moves to 7

ACK received -> base moves to 8

All frames sent.
*/
