#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUFLEN 255
#define PORT 8885

void die(char *s) {
    perror(s);
    exit(1);
}

int main(void) {
    struct sockaddr_in si_other;
    int s, slen = sizeof(si_other), recv_len = 0;
    unsigned long flen = 0;
    char buf[BUFLEN], fname[20];
    FILE *fp;

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }

    memset((char *)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    if (inet_aton("SERVER_IP_ADDRESS", &si_other.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    if (connect(s, (struct sockaddr *)&si_other, sizeof(si_other)) == -1) {
        die("connect");
    }

    recv_len = recv(s, buf, sizeof(buf), 0);
    printf("%s\n", buf);

    strcpy(fname, "received.png");
    fp = fopen(fname, "wb");

    memset(buf, 0, BUFLEN);
    recv_len = recv(s, buf, sizeof(buf), 0);
    flen = atoi(buf);
    printf("%ld\n", flen);

    memset(buf, 0, BUFLEN);
    int numChunks = flen / BUFLEN + 1;
    for (int i = 0; i < numChunks; i++) {
        if ((recv_len = recv(s, buf, sizeof(buf), 0)) == -1) {
            die("recv()");
        }
        fwrite(buf, recv_len, 1, fp);
        memset(buf, 0, BUFLEN);
    }

    fclose(fp);
    close(s);
    return 0;
}