#include <stdio.h> // 0701.c
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define SHM_SIZE 50
#define KEY 567
typedef unsigned char byte;
byte *getBytes(double *pValue) {
    byte *p = (byte *)(pValue);
    return p;
}
void writeSHM(double magic, int loc) {
    int shm_id;
    char *shm, *s;
    byte *p;
    double k = magic;
    // 共享記憶體(shared memory segment) "567".
    if ((shm_id = shmget(KEY, SHM_SIZE, 0666)) < 0) {
        printf("get fail");
        exit(1);
    }
    // attach 共享記憶體到本 process的變數
    if ((shm = shmat(shm_id, NULL, 0)) == (char *)-1) {
        printf("attach fail");
        exit(1);
    }

    // 寫入資料到共享記憶體,等待其他 process 讀取
    p = getBytes(&k);
    s = shm + loc * 8;
    // 寫入double到共享記憶體,等待parent process 讀取
    // printf("\n %lf \n", magic);
    for (int i = 0; i < 8; i++) {
        *s++ = p[i];
        // printf("%x", p[i]);
    }
}
void getResult() {
    int shm_id;
    char *shm, *s;
    byte *p;
    double value;
    double a, b, c;
    // get the segment named "567", created by the server.
    if ((shm_id = shmget(KEY, SHM_SIZE, 0666)) < 0) {
        printf("get fail");
        exit(1);
    }
    // attach the segment to our data space.
    if ((shm = shmat(shm_id, NULL, 0)) == (char *)-1) {
        printf("attach fail");
        exit(1);
    }
    // read what the server put in the memory.
    s = shm;
    p = (byte *)malloc(8);
    for (int i = 0; i < 8; i++) {
        p[i] = s[i];
        // printf("%x-", p[i]);
    }
    // printf("\n==>value = %lf\n", *((double *)p));
    a = *((double *)p);
    for (int i = 0; i < 8; i++) {
        p[i] = s[i + 8];
        // printf("%x-", p[i]);
    }
    // printf("\n==>value = %lf\n", *((double *)p));
    b = *((double *)p);
    for (int i = 0; i < 8; i++) {
        p[i] = s[i + 16];
        // printf("%x-", p[i]);
    }
    // printf("\n==>value = %lf\n", *((double *)p));
    c = *((double *)p);
    printf("==>value = %lf\n", a+b+c);
}

double compute(int loc) {
    double r = 0.0;
    int sign = 1;
    for (double i = 4 * loc; i < 4 * (loc + 1); i++) {
        r += sign * 4 / (i * 2 + 1);
        sign *= -1;
    }
    return r;
}

int main() {
    // struct timespec st = {0, 0};
    // struct timespec et = {0, 0};
    // clock_gettime(CLOCK_REALTIME, &st);
    // printf("%lf\n", compute(0)+compute(1)+compute(2));
    // clock_gettime(CLOCK_REALTIME, &et);
    // printf("%ld ms\n", (et.tv_sec - st.tv_sec) * 1000 +
    //                                              (et.tv_nsec - st.tv_nsec) / 1000000);
    int shm_id;
    double r = 0;
    pid_t wpid;
    pid_t child[3] = {-1, -1, -1}, self = getpid();
    struct timespec st = {0, 0};
    struct timespec et = {0, 0};
    clock_gettime(CLOCK_REALTIME, &st);
    if ((shm_id = shmget(KEY, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        printf("creat fail");
        exit(1);
    }
    child[0] = fork();
    if (child[0] > 0)
        child[1] = fork();
    if (child[1] > 0)
        child[2] = fork();
    if (child[0] > 0 && child[1] > 0 && child[2] > 0) {
        // printf("===>%.16f\n", compute(1));
        // printf("parent pid =%d\n", self);
        // printf("Parent process, wait for child...\n");
        while ((wpid = wait(NULL)) > 0)
            ; // 等待child程序
        getResult();
        r = compute(3); //
        // printf("\nParent process, wait for child end.\n");
        clock_gettime(CLOCK_REALTIME, &et);
        printf("%ld ms\n", (et.tv_sec - st.tv_sec) * 1000 +
                                                     (et.tv_nsec - st.tv_nsec) / 1000000);
    } else {
        // sleep(1);
        if (child[0] == 0) {
            r = 1;
            r = compute(0);
            writeSHM(r, 0);
            // printf("\n0:child process pid =%d\n", getpid());
        } else if (child[1] == 0) {
            r = 1;
            r = compute(1);
            writeSHM(r, 1);
            // printf("\n1:child process pid =%d\n", getpid());
        } else if (child[2] == 0) {
            r = 1;
            r = compute(2);
            writeSHM(r, 2);
            // printf("\n2:child process pid =%d\n", getpid());
        }
    }
    return 0;
}