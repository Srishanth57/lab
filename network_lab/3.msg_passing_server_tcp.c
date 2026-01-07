#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>



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
	char buffer[1024] = {0}; 
	if((recv(clientfd , buffer , sizeof(buffer), 0)) < 0) {
		perror("Error receiving content from client");
		exit(1);
		
		
	}
	
	printf("Msg received: %s\n", buffer);
	close(sockfd);
	close(clientfd);
	return 0;
}


/*
Output 

Client connection successfull
Msg received: Hello



*/
