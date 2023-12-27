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
      if (strcmp(message, "Bye") == 0 || strcmp(inputBuffer, "Bye") == 0)
        break;
      printf("Client: %s\n", inputBuffer);
      printf("Server: ");
      scanf("%[^\n]", message);
      getchar();
      send(clientSockfd, message, sizeof(message), 0);
       
    }
    if (strcmp(message, "Bye") == 0 || strcmp(inputBuffer, "Bye") == 0)
      break;
  }
  return 0;
}