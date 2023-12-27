#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>  // Client – simplec.c
#include <stdlib.h> // gcc simplec.c -o simplec -lunp
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char message[2048], receiveMessage[2048]; // Send/receive a message to server;
  int sockfd = 0;                         // socket的建立
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Fail to create a socket.");
  }
  struct sockaddr_in info; // socket的連線
  bzero(&info, sizeof(info));
  info.sin_family = PF_INET;
  info.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost test
  info.sin_port = htons(8700);
  int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
  if (err == -1) {
    printf("Connection error");
  }
  while (1) {
    printf("Client: ");
    scanf("%[^\n]", message);
    getchar();
    send(sockfd, message, sizeof(message), 0);
    recv(sockfd, receiveMessage, sizeof(receiveMessage), 0);
    printf("Server: %s\n", receiveMessage);
    if (strcmp(message, "Bye") == 0 || strcmp(receiveMessage, "Bye") == 0)
      break;
  }
  printf("close Socket\n");
  close(sockfd);
  return 0;
}