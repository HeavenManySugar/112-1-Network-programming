// shm1.c - server
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 50
void replaceSubstring(char *str, const char *substr) {
  int len = strlen(substr);
  char *ptr = strstr(str, substr);
  while (ptr != NULL) {
    memset(ptr, '*', len);
    ptr = strstr(ptr + len, substr);
  }
}

int main() {
  char c;
  int shm_id;
  key_t key;
  char *shm, *s;

  char str[100];
  char substr[100];

  printf("Enter the main string: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = '\0';

  printf("Enter the substring to replace: ");
  fgets(substr, sizeof(substr), stdin);
  substr[strcspn(substr, "\n")] = '\0';

  replaceSubstring(str, substr);

  // 命名共享記憶體(shared memory segment) "567".
  key = 567;
  // Create the segment.
  shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
  if (shm_id < 0) {
    perror("shmget");
    printf("creat fail");
    exit(1);
  }
  // attach 共享記憶體到本 process的變數
  if ((shm = shmat(shm_id, NULL, 0)) == (char *)-1) {
    perror("shmat");
    printf("attach fail");
    exit(1);
  }
  // 寫入資料到共用記憶體,等待其他 process 讀取
  s = shm;
  // 第一個字元表示要寫入資料 byte 個數
  *s++ = strlen(str);

  for (int i=0;i<strlen(str);i++) {
    *s++ = str[i];
  }
  // 等待其他 process 修改記憶體第一個字元 '*',
  //  表示已經讀取本 process 寫入資料
  while (*shm != '*') {
    sleep(1);
  }
  return 0;
}