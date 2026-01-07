#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>



int main() {

	struct sockaddr_in server_addr; 
	int sockfd ; 
	
	if((sockfd = socket(AF_INET , SOCK_STREAM , 0 )) < 0) {
		perror("Socket connection failed!\n");
		exit(1);
	
	}
	
	memset(&server_addr , 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET ; 
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	socklen_t server_addr_len = sizeof(server_addr);
	if((connect(sockfd , (struct sockaddr *) &server_addr  , server_addr_len) ) < 0) {
		printf("Error connecting server");
		exit(1);
	}
	
	printf("Server connection successfull\n");
	char msg_buffer[1024];
	printf("Enter msg: ");
	fgets(msg_buffer , sizeof(msg_buffer), stdin);
	if((send(sockfd , msg_buffer , sizeof(msg_buffer) , 0)) < 0) {
		perror("Error while sending message\n");
		exit(1);
	}
	printf("Msg sent successfull\n");
	close(sockfd);
	return 0 ;
}



/*
Output 

Server connection successfull
Enter msg: Hello
Msg sent successfull




*/
