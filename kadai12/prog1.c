#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main(){
    char str[256];
    int semid;
    key_t semkey;
    struct sembuf buf[2];

    semkey = ftok("prog1", 'a');
    if ((semid = semget(semkey, 2, IPC_CREAT | IPC_EXCL | 0666)) < 0){
        // セマフォが既に存在するならそのID番号を取得する
        semid = semget(semkey, 2, IPC_CREAT | 0666);
    } else {
        // セマフォを新規作成したのならセマフォ値を初期化する
        semctl(semid, 0, SETVAL, 0);
        semctl(semid, 1, SETVAL, 0);
    }
    buf[0].sem_num = 0;
    buf[0].sem_flg = 0;
    buf[1].sem_num = 1;
    buf[1].sem_flg = 0;

    while (1) {
        buf[0].sem_op = 1;
        buf[1].sem_op = -1;
        semop(semid, &buf[0], 1);
        semop(semid, &buf[1], 1);
        printf("> ");
        fgets(str, 256, stdin);
    }
    
    return EXIT_FAILURE;
}
