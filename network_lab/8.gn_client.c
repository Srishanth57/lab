#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5001);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Connected to server!\n\n");

    int total, window;
    printf("Enter total number of frames to send: ");
    scanf("%d", &total);
    printf("Enter window size: ");
    scanf("%d", &window);

    int error_frame = total / 2;
    printf("\n[Error will be simulated at Frame %d]\n\n", error_frame);

    int next_to_send = 0;
    int error_done = 0;

    while (next_to_send < total) {

        int window_start = next_to_send;
        int window_end = next_to_send + window;
        if (window_end > total) window_end = total;

        printf("-- Sending window [%d to %d] --\n", window_start, window_end - 1);

        for (int i = window_start; i < window_end; i++) {

            char frame[50];
            int is_last = (i == total - 1) ? 1 : 0;

            int send_seq;
            if (i == error_frame && error_done == 0) {
                send_seq = -1;
                error_done = 1;
            } else {
                send_seq = i;
            }

            sprintf(frame, "%d:%d:%d", send_seq, is_last, total);

            if (i == error_frame && send_seq == -1)
                printf("Sending Frame %d (seq=%d) [SIMULATED ERROR]... \n", i, send_seq);
            else
                printf("Sending Frame %d (seq=%d)... \n", i, send_seq);

            sendto(sockfd, frame, strlen(frame) + 1, 0,
                   (struct sockaddr *)&server_addr, len);
        }

        int nak_at = -1;

        for (int i = window_start; i < window_end; i++) {

            char ack[20] = {0};

            recvfrom(sockfd, ack, sizeof(ack), 0,
                     (struct sockaddr *)&server_addr, &len);

            printf(" Got: %s\n", ack);

            if (strncmp(ack, "NAK", 3) == 0) {
                sscanf(ack, "NAK:%d", &nak_at);
                printf(" [NAK received! Going back to Frame %d]\n\n", nak_at);
                break;
            }
        }

        if (nak_at != -1)
            next_to_send = nak_at;
        else
            next_to_send = window_end;
    }

    printf("\nAll %d frames sent successfully!\n", total);

    close(sockfd);
    return 0;
}
