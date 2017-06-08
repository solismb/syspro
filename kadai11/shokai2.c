#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int getWorkType() {
    int work;
    
    printf("残高照会 [0]\n引き出し [1]\n> ");
    scanf("%d", &work);
    getchar();  // 改行読み飛ばし
    if (work != 0 && work != 1) {
        return -1;
    }
    
    return work;
}

long getWithdrawNum() {
    long wnum;
    
    printf("引き出す金額を入力してください> ");
    scanf("%ld", &wnum);
    getchar();  // 改行読み飛ばし
    if (wnum < 0) {
        return -1;
    }

    return wnum;
}

int main() {
    struct msgbuf {
        long mtype;
        char mtext[256];
        int work;        // 残高照会は0, 引き出しは1
        long wnum;       // 引き出し額
    };
    char line[256];
    int msqid1, msqid2;
    key_t msgkey1, msgkey2;
    struct msgbuf recv, send;
    
    msgkey1 = ftok("master2", 'a');
    msgkey2 = ftok("shokai2", 'z');
    msqid1  = msgget(msgkey1, IPC_CREAT | 0666);
    msqid2  = msgget(msgkey2, IPC_CREAT | 0666);

    send.work = getWorkType();
    if (send.work == -1) {
        printf("入力エラー. 終了します.\n");
        return EXIT_FAILURE;
    } else if (send.work == 1) {
        printf("口座番号の入力> ");
        fgets(line, sizeof(line), stdin);  // 口座番号を入力する
        send.wnum = getWithdrawNum();      // 引き出し額の入力
        if (send.wnum == -1) {
            printf("入力エラー. 終了します\n");
            return EXIT_FAILURE;
        }
    } else {
        printf("口座番号の入力> ");
        fgets(line, sizeof(line), stdin);  // 口座番号を入力する
        send.wnum = 0L;
    }
        
    if (sscanf(line, "%ld", &send.mtype) == 1) {  // 口座番号を
                                                  // メッセージの
                                                  // タイプにセット
        msgsnd(msqid1, &send, sizeof(send), 0);  // メッセージ送信

        // 自分の口座番号のメッセージを受信する
        msgrcv(msqid2, &recv, sizeof(recv), send.mtype, 0);
        if (send.work == 1) {
            printf("%ld 円のお引き出し\n", send.wnum);
            printf("残高: %s\n", recv.mtext);
        } else {
            printf("残高: %s\n", recv.mtext);
        }
    }
    return EXIT_SUCCESS;
}
        
