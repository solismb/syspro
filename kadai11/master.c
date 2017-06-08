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
    int msqid1, msqid2;
    int searchdata(long key, char *dp, int size);
    key_t msgkey1, msgkey2;
    struct msgbuf recv, send;

    msgkey1 = ftok("master", 'a');
    msgkey2 = ftok("shokai", 'z');
    msqid1  = msgget(msgkey1, IPC_CREAT|0666);
    msqid2  = msgget(msgkey2, IPC_CREAT|0666);

    while(1) {
        msgrcv(msqid1, &recv, sizeof(recv.mtext), 0, 0);  // 口座番号を受け取る
        // 預金データを探す
        if (searchdata(recv.mtype, send.mtext, sizeof(send.mtext)) == EOF) {
            // 口座がなければ 0
            snprintf(send.mtext, sizeof(send.mtext), "%ld", 0L);
        }
        send.mtype = recv.mtype;  // メッセージのタイプに相手の口座番号をセット
        msgsnd(msqid2, &send, sizeof(send.mtext), 0);  // メッセージの送信
    }
    return EXIT_SUCCESS;
}

int searchdata(long key, char *dp, int size) {
    FILE *p;
    long ydata, ynum;
    char line[256];

    p = fopen("yokinfile", "r");
    while(fgets(line, sizeof(line), p) != NULL) {
        if (sscanf(line, "%ld%ld", &ynum, &ydata) == 2) {
            if (key == ynum) {
                snprintf(dp, size, "%ld", ydata);
                fclose(p);
                return 0;
            }
        }
    }
    fclose(p);
    return EOF;
}
