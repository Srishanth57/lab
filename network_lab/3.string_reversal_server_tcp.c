#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

void revString(char *str) {
    int i = 0, j = 0;
    char temp;

    // Find length of string
    j = strlen(str); 
    j--; // last character index

    // Swap characters from both ends
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int main() {

	struct sockaddr_in server_addr, client_addr; 
	int sockfd, clientfd ; 
	
	if((sockfd = socket(AF_INET , SOCK_STREAM , 0 )) < 0) {
		perror("Socket connection failed!\n");
		exit(1);
	
	}
	
	memset(&server_addr , 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET ; 
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	socklen_t server_addr_len = sizeof(server_addr);
	if((bind(sockfd , (struct sockaddr * ) &server_addr , server_addr_len )) < 0 ) {
		perror("Bind connection failed!\n");
		exit(1);
	}
	
	if ((listen(sockfd , 4 )) < 0) {
		perror("Listen failed!\n");
		exit(1);
	}
	
	socklen_t client_addr_len = sizeof(client_addr);
	if((clientfd = accept(sockfd , (struct sockaddr * ) &client_addr  , &client_addr_len)) < 0) {
		perror("Accept failed!\n");
		exit(1);
	} 
	
	printf("Client connection successfull\n");
	char buffer[1024] = {'\0'}; 
	if((recv(clientfd , buffer , sizeof(buffer), 0)) < 0) {
		perror("Error receiving content from client");
		exit(1);
		
		
	}
	printf("Received string: %s\n", buffer);
	revString(buffer);

	if((send(clientfd , buffer , strlen(buffer) , 0)) < 0) {
		perror("Error while sending message\n");
		exit(1);
	}
	
	
	close(sockfd);
	close(clientfd);
	return 0;
}


/*
Output 

Client connection successfull
Received string: hola





*/
