// gcc daytime.c -o daytime -lunp
// ./daytime
#include <stdio.h>
#include <time.h>
#define MAXLINE 2048
int main(int argc, char **argv) {
  char buff[MAXLINE];
  time_t ticks;
  ticks = time(NULL);
  printf("%ld\n", ticks);
  snprintf(buff, sizeof(buff), "%s\n", ctime(&ticks));
  printf("%.24s\n", buff); // Output 24 char
}