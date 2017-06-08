#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main() {
    struct msgbuf {
        long mtype;
        char mtext[256];
    };
    char line[256];
    int msqid1, msqid2;
    key_t msgkey1, msgkey2;
    struct msgbuf recv, send;

    msgkey1 = ftok("master", 'a');
    msgkey2 = ftok("shokai", 'z');
    msqid1  = msgget(msgkey1, IPC_CREAT | 0666);
    msqid2  = msgget(msgkey2, IPC_CREAT | 0666);
    printf("Enter number: ");
    fgets(line, sizeof(line), stdin);  // 口座番号を入力する
    if (sscanf(line, "%ld", &send.mtype) == 1) {  // 口座番号を
                                                  // メッセージの
                                                  // タイプにセット
        msgsnd(msqid1, &send, sizeof(send.mtext), 0);  // メッセージ送信

        // 自分の口座番号のメッセージを受信する
        msgrcv(msqid2, &recv, sizeof(recv.mtext), send.mtype, 0);
        printf("Zandaka= %s\n", recv.mtext);
    }
    return EXIT_SUCCESS;
}
        
