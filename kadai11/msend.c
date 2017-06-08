//
// gcc -o msend msend.c でコンパイルすること
// 　∵実行時に「msend」というファイルが必要になるため
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  struct msgbuf {
    long mtype;
    char mtext[256];
  };
  char line[256];
  int msgid;
  key_t msgkey;
  struct msgbuf msgdata, *p;

  // キーボードで送信文字列を入力する
  p = &msgdata;
  printf("Enter message: ");
  fflush(stdout);
  fgets(line, sizeof(line), stdin);
  if (sscanf(line, "%[^\n]", p->mtext) <= 0){
    return EXIT_SUCCESS;
  }

  // メッセージキューを作る
  msgkey = ftok("mrecv", 'a');
  if ((msgid = msgget(msgkey, IPC_CREAT|0666)) < 0){
    perror("msgget");
    exit(EXIT_FAILURE);
  }

  // メッセージを送る
  p->mtype = getpid();    // プロセスIDを代入する(別の値でも良い)
  msgsnd(msgid, p, sizeof(p->mtext), 0);

  return EXIT_SUCCESS;
}
