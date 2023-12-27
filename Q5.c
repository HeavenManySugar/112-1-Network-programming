#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

double func(int st, int ed){
    double result = 0.0;
  int sign = 1;
  for (int i = st; i <= ed; i++) {
    if (i%2 == 0) {
        sign = -1;
    }else {
        sign = 1;
    }
    result += sign * (1.0/i);
  }
  return result;
}

void *compute(int loc) {
    int st, ed;
    if(loc==0){
        st = 1; ed = 10;
    }else if(loc==1){
        st = 11; ed = 25;
    }else{
        st = 26; ed = 40;
    }
    double *result = malloc(sizeof(double) * 1);
    result[0] = func(st, ed);
  pthread_exit((void *)result);
}

int main(int argc, char *argv[]) {
  struct timespec st = {0, 0};
  struct timespec et = {0, 0};
  clock_gettime(CLOCK_REALTIME, &st);

  int i;
  int t1, t2, t3;
  double result = 0.0;
  void *ret; // 子執行緒傳回值
  pthread_t thread1, thread2, thread3;
  t1 = pthread_create(&thread1, NULL, (void *)compute, 0);
  if (t1) {
    fprintf(stderr, "Error creating thread(compute), return code: %d\n", t1);
    exit(EXIT_FAILURE);
  }
  t2 = pthread_create(&thread2, NULL, (void *)compute, 1);
  if (t2) {
    fprintf(stderr, "Error creating thread(compute), return code: %d\n", t2);
    exit(EXIT_FAILURE);
  }
  t3 = pthread_create(&thread3, NULL, (void *)compute, 2);
  if (t3) {
    fprintf(stderr, "Error creating thread(compute), return code: %d\n", t3);
    exit(EXIT_FAILURE);
  }
  pthread_join(thread1, &ret);
  result += *(double *)ret;
  pthread_join(thread2, &ret);
  result += *(double *)ret;
  pthread_join(thread3, &ret);
  result += *(double *)ret;
  printf("Result: %.9lf\n", result);
  clock_gettime(CLOCK_REALTIME, &et);
    printf("Total time of multiprocess: %.9lf s\n",
         (et.tv_sec - st.tv_sec)/1000000.0 + (et.tv_nsec - st.tv_nsec) / 1000000000.0);


    clock_gettime(CLOCK_REALTIME, &st);
    func(1, 40);
    clock_gettime(CLOCK_REALTIME, &et);
    printf("Total time of singleprocess: %.9lf s\n",
         (et.tv_sec - st.tv_sec)/1000000.0 + (et.tv_nsec - st.tv_nsec) / 1000000000.0);

  exit(EXIT_SUCCESS);
}