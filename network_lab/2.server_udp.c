#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

  struct sockaddr_in server_addr ;
  int sockfd ; 
  
  
  if((sockfd = socket(AF_INET , SOCK_DGRAM , 0) ) < 0) {
  
    perror("Socket connection failed!\n"); 
    exit(1);
    
  }
  memset(&server_addr, '\0' , sizeof(server_addr));
  server_addr.sin_family = AF_INET ;
  server_addr.sin_port  = htons(5001);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  socklen_t server_addr_len = sizeof(server_addr);
  if((bind(sockfd , (struct sockaddr * )& server_addr , server_addr_len)) < 0) {
    perror("Error binding connection!\n");
    exit(1);
    
  }
  
  char buffer[1024] = {0};
  if((recvfrom(sockfd , buffer , sizeof(buffer) -1, 0 , (struct sockaddr *)& server_addr , &server_addr_len)) < 0) {
    perror("Error receiving content/data from client!\n");
    exit(1);
  }
  
  printf("[+] Client data received: %s\n", buffer);
  
    char *msg = "Message from server";
  if((sendto(sockfd , msg , strlen(msg) , 0 , (struct sockaddr *)& server_addr , server_addr_len)) < 0) {
    perror("Error sending content/data to client!\n");
    exit(1);
  }
  
  printf("[+] Server data sent\n");
  


  
  return 0; 
}


/* 
Output 

[+] Client data received: Message from client
[+] Server data sent

*/
