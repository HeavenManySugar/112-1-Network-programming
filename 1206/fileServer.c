#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
int main(void){
    int sockfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1024];
    int numrv;

    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0) {
        printf("\n Error : Could not create socket\n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
        printf("\n Error : Connect Failed\n");
        return 1;
    }

    // while(1) {
        FILE *fp1;
        fp1 = fopen("client.txt", "w");
        if(NULL == fp1) {
            printf("Error opening file");
            return 1;
        }

        char tmp[1024];
        scanf("%[^\n]", tmp);
        for (int i = 0; i < strlen(tmp); i++) {
            tmp[i] += 5;
        }
        fwrite(tmp, 1,strlen(tmp),fp1);
        fclose(fp1);

        /* Open the file that we wish to transfer */
        FILE *fp = fopen("client.txt","rb");
        if(fp==NULL) {
            printf("File opern error");
            return 1;
        }
        /* Read data from file and send it */
        while(1) {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int nread = fread(buff,1,256,fp);
            printf("Bytes read %d \n", nread);

            /* If read was success, send data. */
            if(nread > 0) {
                printf("Sending \n");
                write(sockfd, buff, nread);
            }
            /* There is something tricky going on with read ..
            * Either there was error, or we reached end of file. */
            if (nread < 256) {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
        }
        // close(sockfd);
        // sleep(1);
    // }
    return 0;
}