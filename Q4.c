#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // f3.c
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>


void func(double st, double ed, double* result) {
  double r = 0.0;
  for (double i = st; i <= ed; i++) {
    r += (i - 1) / i;
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
  pipe(fd);
  pid = fork();  // fork a child process
  if (pid < 0) { // error occurred
    fprintf(stderr, "Fork Failed");
    return 1;
  } else if (pid == 0) { // child process
    close(fd[0]);
    func(1.0, 15.0, &value);
    printf("child result=%.9lf\n", value);
    write(fd[1], &value, sizeof(value));
    close(fd[1]);
  } else {      // parent process
    wait(NULL); // parent wait child complete
    read(fd[0], &value, sizeof(value));
    // printf("Child Complete\n");
    func(16.0, 40.0, &value);
    printf("parent result=%.9lf\n", value);
    close(fd[0]);
    clock_gettime(CLOCK_REALTIME, &et);
    printf("Total time of multiprocess: %.9lf s\n",
         (et.tv_sec - st.tv_sec)/1000000.0 + (et.tv_nsec - st.tv_nsec) / 1000000000.0);


    clock_gettime(CLOCK_REALTIME, &st);
    func(1.0, 15.0, &value);
    func(16.0, 40.0, &value);
    clock_gettime(CLOCK_REALTIME, &et);
    printf("Total time of singleprocess: %.9lf s\n",
         (et.tv_sec - st.tv_sec)/1000000.0 + (et.tv_nsec - st.tv_nsec) / 1000000000.0);
  }
  return 0;
}