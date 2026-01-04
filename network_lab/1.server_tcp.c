#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> // htons , htonl ,ntohs, ntohl


int main() {
  struct sockaddr_in server_addr, client_addr; 
  
  int sockfd , clientfd;
  
  if((sockfd = socket(AF_INET , SOCK_STREAM , 0) ) < 0) {
    perror("Error creating socket!\n");
    exit(1);
    
  }
  
  server_addr.sin_family = AF_INET ; 
  server_addr.sin_port = htons(5000); // host to network short used to convert the 16bit unsigned integer to network byte order 
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  socklen_t server_addr_len = sizeof(server_addr);
  if((bind(sockfd , (struct sockaddr *)& server_addr , server_addr_len)) < 0) {
    perror("Error binding!\n");
    exit(1);
  }
  
  int backlogs = 4 ; // maximum no of connection the kernel should queue for this socket  
  if((listen(sockfd , backlogs)) < 0 ) {
     perror("Error listening!\n");
    exit(1);
  }
  
  // Client connection accept 
  socklen_t client_addr_len = sizeof(client_addr);
  clientfd = accept(sockfd , (struct sockaddr *)&client_addr , &client_addr_len);
  if(clientfd < 0) {
    perror("Error while accept!\n");
    exit(1);
  }
    printf("Client connection success\n");
  //Receive data from client ; 
  char buffer[1024] ; 
  if((recv(clientfd, buffer , sizeof(buffer) -1 , 0)) < 0) {
    perror("Error while receiving data !\n");
    exit(1);
  }
  
  printf("Message from client: %s\n", buffer);
  
  
  // Send a response to the client
    char *response = "Hello from the server!";
    if (send(clientfd, response, strlen(response), 0) < 0) {
        perror("Error sending response to client");
    } 
    printf("Sent response to client\n");
    

    // Close the connections
    close(clientfd);
    close(sockfd);

  return 0; 
}




/*
Output 



Client connection success
Message from client: Hello from client
Sent response to client


*/
