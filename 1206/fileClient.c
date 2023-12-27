#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
int main(void){
    int listenfd = 0;
    int connfd = 0;
    int bytesReceived = 0;
    char recvBuff[256];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket retrieve success\n");

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);
    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(listen(listenfd, 10) == -1) {
        printf("Failed to listen\n");
        return -1;
    }

    while(1){
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);
        /* Create file where data will be stored */
        FILE *fp;
        fp = fopen("server.txt", "w");
        if(NULL == fp) {
            printf("Error opening file");
            return 1;
        }

        /* Receive data in chunks of 256 bytes */
        while((bytesReceived = read(connfd, recvBuff, 256)) > 0) {
            printf("Bytes received %d\n",bytesReceived);
            for (int i = 0; i < bytesReceived; i++) {
                recvBuff[i] -= 5;
            }
            fwrite(recvBuff, 1,bytesReceived,fp);
        }

        if(bytesReceived < 0) {
            printf("\n Read Error\n");
        }
        fclose(fp);
        close(connfd);
        sleep(1);
    }
    return 0;
}