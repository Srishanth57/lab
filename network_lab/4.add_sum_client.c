#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void)
{
    struct sockaddr_in server_addr;
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket connection failed!\n");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5001);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t server_addr_len = sizeof(server_addr);

    char msg_buffer[1024];

    /* Get numbers from user */
    printf("Enter numbers: ");
    fgets(msg_buffer, sizeof(msg_buffer), stdin);

    if (sendto(sockfd,
               msg_buffer,
               strlen(msg_buffer),
               0,
               (struct sockaddr *)&server_addr,
               server_addr_len) < 0)
    {
        perror("Error sending content/data to server!\n");
        exit(1);
    }

    printf("[+] Client data sent\n");

    char buffer[1024] = {0};

    if (recvfrom(sockfd,
                 buffer,
                 sizeof(buffer) - 1,
                 0,
                 (struct sockaddr *)&server_addr,
                 &server_addr_len) < 0)
    {
        perror("Error receiving content/data from server!\n");
        exit(1);
    }

    printf("[+] Server data received: %s\n", buffer);

    return 0;
}

/*
Output

Enter numbers: 10 10
[+] Client data sent
[+] Server data received: 20
*/

