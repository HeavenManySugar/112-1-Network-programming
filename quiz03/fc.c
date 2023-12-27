#include <stdio.h> // Client
#include <stdlib.h> // gcc fileClient.c
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        return 1;
    }

    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[256];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;

    /* Create a socket first */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket\n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2])); // port
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    /* Attempt a connection */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Error : Connect Failed\n");
        return 1;
    }

    /* Receive the filename */
    char filename[256];
    memset(filename, 0, sizeof(filename));
    if ((bytesReceived = read(sockfd, filename, sizeof(filename) - 1)) < 0) {
        printf("\n Error : Read Failed\n");
        return 1;
    }
    printf("Received filename: %s\n", filename);

    /* Create file where data will be stored */
    FILE *fp;
    fp = fopen(filename, "wb");
    if (NULL == fp) {
        printf("Error opening file");
        return 1;
    }

    /* Receive data in chunks of 256 bytes */
    while ((bytesReceived = read(sockfd, recvBuff, 256)) > 0) {
        // printf("Bytes received %d\n", bytesReceived);
        fwrite(recvBuff, 1, bytesReceived, fp);
    }

    if (bytesReceived < 0) {
        printf("\n Read Error\n");
    }

    return 0;
}