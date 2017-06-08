#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main() {
    struct msgbuf {
        long mtype;
        char mtext[256];
        int work;
        long wnum;
    };
    int msqid1, msqid2;
    int searchdata(long key, char *dp, int size);
    int withdraw(long key, char *dp, long wnum, int size);
    key_t msgkey1, msgkey2;
    struct msgbuf recv, send;

    msgkey1 = ftok("master2", 'a');
    msgkey2 = ftok("shokai2", 'z');
    msqid1  = msgget(msgkey1, IPC_CREAT|0666);
    msqid2  = msgget(msgkey2, IPC_CREAT|0666);

    while(1) {
        msgrcv(msqid1, &recv, sizeof(recv), 0, 0);  // 口座番号を受け取る

        if (recv.work == 1) {
            if(withdraw(recv.mtype, send.mtext, recv.wnum, sizeof(send.mtext)) == EOF) {
                snprintf(send.mtext, sizeof(send.mtext), "%ld", 0L);
            }
        } else {
            // 預金データを探す
            if (searchdata(recv.mtype, send.mtext, sizeof(send.mtext)) == EOF) {
                // 口座がなければ 0
                snprintf(send.mtext, sizeof(send.mtext), "%ld", 0L);
            }
        }
        send.mtype = recv.mtype;  // メッセージのタイプに相手の口座番号をセット
        msgsnd(msqid2, &send, sizeof(send), 0);  // メッセージの送信
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

int withdraw(long key, char *dp, long wnum, int size) {
    FILE *p;
    long ydata[256], ynum[256];
    char line[256];
    int flag = 1, i = 0, j;

    p = fopen("yokinfile", "r");
    while(fgets(line, sizeof(line), p) != NULL) {
        if (sscanf(line, "%ld%ld", &ynum[i], &ydata[i]) == 2) {
            if (key ==  ynum[i]) {
                if (ydata[i] < wnum) {
                    snprintf(dp, size, "残高を超えた入力です.");
                    flag = 1;
                } else {
                    ydata[i] = ydata[i] - wnum;
                    snprintf(dp, size, "%ld", ydata[i]);
                    flag = 0;
                }
            }
            i++;
        }
    }
    fclose(p);
    
    p = fopen("yokinfile", "w");
    for (j = 0; j < i; j++) {
        fprintf(p, "%ld %ld\n", ynum[j], ydata[j]);
    }
    fclose(p);
    
    return ((flag != EOF)? flag : EOF);
}
