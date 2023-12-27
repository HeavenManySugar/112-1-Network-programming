#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // f3.c
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void func(double st, double ed, double *result) {
    double r = 0.0;
    int sign = 1;
    for (double i = st; i <= ed; i++) {
        r += sign * 4 / (i * 2 + 1);
        sign *= -1;
    }
    *result = r;
}

int main() {
    struct timespec st = {0, 0};
    struct timespec et = {0, 0};
    clock_gettime(CLOCK_REALTIME, &st);

    double value = 0.0, result[2];
    pid_t pid;
    int fd[2];
    int N = 4; // Number of child processes (modify N value here)
    pipe(fd);

    int precision;
    printf("Enter the number of decimal places for the result: ");
    scanf("%d", &precision);

    for (int i = 0; i < N; i++) {
        pid = fork(); // fork a child process
        if (pid < 0) { // error occurred
            fprintf(stderr, "Fork Failed");
            return 1;
        } else if (pid == 0) { // child process
            close(fd[0]);
            func(1.0 + i * 10, 10.0 + i * 10, &value); // modify the range of values for each child process
            printf("origin child %d result=%.9lf\n", i, value);
            write(fd[1], &value, sizeof(value));
            close(fd[1]);
            return 0;
        }
    }

    // parent process
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        wait(NULL); // parent wait child complete
        read(fd[0], &value, sizeof(value));
        printf("parent received value from child %d: %.*lf\n", i, precision, value);
        sum += value;
    }

    printf("Sum of child results: %.*lf\n", precision, sum);

    close(fd[0]);
    clock_gettime(CLOCK_REALTIME, &et);
    printf("Total time of multiprocess: %.9lf s\n",
                 (et.tv_sec - st.tv_sec) / 1000000.0 +
                         (et.tv_nsec - st.tv_nsec) / 1000000000.0);

    clock_gettime(CLOCK_REALTIME, &st);
    func(1.0, 40.0, &value);
    clock_gettime(CLOCK_REALTIME, &et);
    printf("Total time of singleprocess: %.9lf s\n",
                 (et.tv_sec - st.tv_sec) / 1000000.0 +
                         (et.tv_nsec - st.tv_nsec) / 1000000000.0);

    return 0;
}