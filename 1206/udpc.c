#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

#define SERVER "127.0.0.1"
#define BUFLEN 255
#define PORT 8885

void die(char *s) {
    perror(s);
    exit(1);
}

unsigned long fsize(char* file) {
    FILE * f = fopen(file, "r");
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
}

int main(void) {
    struct sockaddr_in si_other;

    char message[BUFLEN], fname[20], str[10];
    FILE *f;
    int s, i;
    unsigned long size;

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == -1) {
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER , &si_other.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    scanf("%s", fname);
    // strcpy(fname, "server.txt");
    printf("%s\n", fname);
    sendto(s, fname, sizeof(fname), 0, (struct sockaddr *) &si_other, sizeof(si_other));
    memset(message, 0, BUFLEN);
    size = fsize(fname);
    printf("%ld", (size % BUFLEN));
    sprintf(str, "%ld", size);
    sendto(s, str, sizeof(str), 0 , (struct sockaddr *) &si_other, sizeof(si_other));
    f = fopen(fname, "rb");
    memset(message, 0, sizeof(message));

    unsigned long numChunks = (size / BUFLEN) + 1;
    for (unsigned long chunk = 0; chunk < numChunks; chunk++) {
        fread(message, BUFLEN, 1, f);
        printf("%s\n", message);
        if (sendto(s, message, BUFLEN, 0 , (struct sockaddr *) &si_other, sizeof(si_other)) == -1) {
            die("sendto()");
        }
        memset(message, 0, BUFLEN);
    }

    fclose(f);
    close(s);
    return 0;
}