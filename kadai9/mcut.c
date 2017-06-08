//
// gcc -o mcut mcut.c でコンパイルすること。
//  ∵実行時に「mcut」というファイルが必要になるため。
//
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char in_data[4096], *in_ptr;  // ユーザの入力した文字列を格納する
  char *head, *pos;             // 共有メモリにアクセスするポインタ
  int shmid;                    // 共有メモリのID番号
  key_t shmkey;                 // 共有メモリを作る際のID番号
  int i, in_tmp;

  // 共有メモリを確保する
  shmkey = ftok("mcut", 'a');
  printf("%lx\n", shmkey);
  if ((shmid = shmget(shmkey, sizeof(in_data), IPC_CREAT|0666)) < 0){
    perror("shmget");
    exit(EXIT_FAILURE);
  }
  printf("shared memory id = %d\n", shmid);

  // 共有メモリを変数pos、headに対応付ける(アタッチする)
  if ((head = pos = shmat(shmid, 0, 0)) < 0){
    perror("shmat");
    exit(EXIT_FAILURE);
  }

  // 4095文字まで叉はCtrl+dするまで文字を読んでin_dataに入れる
  in_ptr = in_data;
  for (i = 0; i < sizeof(in_data) - 1; i++){
    if ((in_tmp = getchar()) == EOF){
      break;
    }
    *in_ptr = in_tmp;
    in_ptr++;
  }
  *in_ptr = '\0';

  // 入力文字列を共有メモリにコピーする
  in_ptr = in_data;
  strncpy(pos, in_ptr, sizeof(in_data));

  // 共有メモリをデタッチする
  shmdt(head);
  return EXIT_SUCCESS;
}
