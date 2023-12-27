#include "unp.h"
#include <time.h>
int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(1);
  }
  
  int listenfd, connfd;
  struct sockaddr_in servaddr;
  char buff[MAXLINE]; // 訊息緩衝區長度
  time_t ticks;
  
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(atoi(argv[1])); /* daytime server port*/
  
  Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  listen(listenfd, LISTENQ);
  
  for (;;) {
    connfd = accept(listenfd, (SA *)NULL, NULL);
    ticks = time(NULL);
    printf("Send To Client: %.4d/%.2d/%.2d\r\n", localtime(&ticks)->tm_year + 1900, localtime(&ticks)->tm_mon + 1, localtime(&ticks)->tm_mday);
    snprintf(buff, sizeof(buff), "%.4d/%.2d/%.2d\r\n", localtime(&ticks)->tm_year + 1900, localtime(&ticks)->tm_mon + 1, localtime(&ticks)->tm_mday);
    write(connfd, buff, strlen(buff));
    close(connfd);
  }
}