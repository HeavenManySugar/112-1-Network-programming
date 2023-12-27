#include <netinet/in.h> //Server – simples.c, gcc simples.c -o simples -lunp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char inputBuffer[2048];
  char message[] = {"Sorry. I don't understand.\n"};
  int sockfd = 0, clientSockfd = 0; // socket的建立
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("Fail to create a socket.");
  }
  struct sockaddr_in serverInfo, clientInfo; // socket的連線
  int addrlen = sizeof(clientInfo);
  bzero(&serverInfo, sizeof(serverInfo));
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = INADDR_ANY;
  serverInfo.sin_port = htons(8700);
  bind(sockfd, (struct sockaddr *)&serverInfo, sizeof(serverInfo));
  listen(sockfd, 8);
  while (1) {
    clientSockfd = accept(sockfd, (struct sockaddr *)&clientInfo, &addrlen);
    while (1) {
      recv(clientSockfd, inputBuffer, sizeof(inputBuffer), 0);
      if (strcmp(inputBuffer, "Hello~") == 0)
        send(clientSockfd, "Hi~", sizeof(message), 0);
      else if (strcmp(inputBuffer, "Good!") == 0) {
        send(clientSockfd, "THANKS~", sizeof(message), 0);
        // break;
      }
      else if (strcmp(inputBuffer, "How are you?") == 0) {
        send(clientSockfd, "I am fine. How are you.", sizeof(message), 0);
      }else if (strcmp(inputBuffer, "How old are you?") == 0) {
        send(clientSockfd, "I am twenty years old.", sizeof(message), 0);
      } else
        send(clientSockfd, message, sizeof(message), 0);
      printf("Get:=>%s,%s\n", inputBuffer, message);
    }
  }
  return 0;
}