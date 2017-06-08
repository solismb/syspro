#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char out_data[4096], *out_ptr;  // クリップボードから読んだ文字列を格納する
  char *head, *pos;             // 共有メモリにアクセスするポインタ
  int shmid;                    // 共有メモリのID番号
  key_t shmkey;                 // 共有メモリを作る際のID番号

  // 共有メモリを確保する
//  shmkey = ftok("mcut", 'a');
//  if ((shmid = shmget(shmkey, sizeof(out_data), 0)) < 0){
//    perror("shmget");
//    exit(EXIT_FAILURE);
//  }
//  printf("shared memory id = %d\n", shmid);

  // 手入力で共有メモリのID番号を指定する
  scanf("%d", &shmid);

  // 共有メモリを変数pos、headに対応付ける(アタッチする)
  if ((head = pos = shmat(shmid, 0, 0)) < 0){
    perror("shmat");
    exit(EXIT_FAILURE);
  }

  // 共有メモリの内容をout_dataにコピーする
  out_ptr = out_data;
  strncpy(out_ptr, pos, sizeof(out_data));
  printf("---- 読み込んだ内容 ----\n");
  printf("%s", out_data);
  printf("------------------------\n");

  // 共有メモリをデタッチする
  shmdt(head);
  return EXIT_SUCCESS;
}
