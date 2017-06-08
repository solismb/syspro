//
// gcc -o helloworld1 helloworld1.c
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main(){
    char word[] = {"Hello World!\n"};
    int i, semid;
    key_t semkey;
    struct sembuf buf[2];

    semkey = ftok("helloworld1", 'a');
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

    for (i = 0; i < strlen(word); i++){
        buf[0].sem_op = 1;       // 0番を解放
        buf[1].sem_op = -1;      // 1番をロック
        semop(semid, &buf[0], 1);
        semop(semid, &buf[1], 1);
        printf("%c", word[i]);
        fflush(stdout);
        sleep(1);
    }
    return EXIT_SUCCESS;
}
