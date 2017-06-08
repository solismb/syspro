#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main(){
  struct msgbuf {
    long mtype;
    char mtext[256];
  };
  int msgid;
  key_t msgkey;
  struct msgbuf msgdata, *p;

  p = &msgdata;
  msgkey = ftok("mrecv", 'a');
  msgid = msgget(msgkey, IPC_CREAT|0666);
  while(1){
    msgrcv(msgid, p, sizeof(p->mtext), 0, 0);
    printf("message received from %ld\n%s\n", p->mtype, p->mtext);
  }
  return EXIT_SUCCESS;
}
