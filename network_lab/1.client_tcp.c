#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr 

int main() {
  struct sockaddr_in server_addr; 
  
  int sockfd ;
  
  if((sockfd = socket(AF_INET , SOCK_STREAM , 0) ) < 0) {
    perror("Error creating socket!\n");
    exit(1);
    
  }
  
  server_addr.sin_family = AF_INET ; 
  server_addr.sin_port = htons(5000); // host to network short used to convert the 16bit unsigned integer to network byte order 
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  socklen_t server_addr_len = sizeof(server_addr);
  if((connect(sockfd , (struct sockaddr * )& server_addr , server_addr_len)) < 0 ) {
    perror("Error connecting to server!\n");
    exit(1);
    
  }
    printf("Server connection success\n");


  //Send a message to the server 
  char *msg = "Hello from client"; 
  if((send(sockfd , msg , strlen(msg), 0)) < 0) {
    perror("Error while sending message!\n");
    exit(1);
  }
  
  printf("Message sent\n");
  
  
    //Receive data from server ; 
  char buffer[1024] ; 
  if((recv(sockfd, buffer , sizeof(buffer) -1 , 0)) < 0) {
    perror("Error while receiving data !\n");
    exit(1);
  }
  
  printf("Message from server: %s\n", buffer);

  return 0; 
}
