#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd, clientfd;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(5002);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 1);
    printf("Waiting for client...\n");

    clientfd = accept(sockfd, (struct sockaddr *)&addr, &len);

    int expected = 0;

    while (1) {
        int seq, last;
        recv(clientfd, &seq,  sizeof(int), 0);
        recv(clientfd, &last, sizeof(int), 0);

        if (seq == expected) {
            printf("Received frame %d -> ACK\n", seq);
            send(clientfd, "ACK", 4, 0);
            expected++;
        } else {
            printf("Received frame %d (expected %d) -> NAK\n", seq, expected);
            send(clientfd, "NAK", 4, 0);
        }

        if (last && seq == expected - 1) break;
    }

    printf("All frames received.\n");
    close(clientfd);
    close(sockfd);
    return 0;
}

/*
Output:
Waiting for client...
Received frame 0 -> ACK
Received frame 1 -> ACK
Received frame 2 (expected 2) -> NAK
Received frame 2 -> ACK
Received frame 3 -> ACK
Received frame 4 -> ACK
Received frame 5 -> ACK
Received frame 6 -> ACK
Received frame 7 -> ACK
All frames received.
*/
