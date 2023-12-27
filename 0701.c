#include <stdio.h> // f2.c
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid;
  int status, i;
  if (fork() == 0) {
    printf("child process pid =%d\n", getpid());
    exit((4/9.0-4/11.0+4/13.0-4/15.0)*1000);
  } else {
    sleep(1);
    int j = (4-4/3.0+4/5.0-4/7.0)*1000;
    printf("Parent process, wait for child...\n");
    pid = wait(&status); // 回傳等待的child程序的pid, 回傳值
    i = WEXITSTATUS(status);
    printf("child's pid =%d . exit status=%d\n", pid, i);
    printf("Result = %lf\n", (i+j)/1000.0);
  }
  return 0;
}