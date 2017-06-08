#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu() {
    int num;

    do {
        printf("#### 行動管理ボード ####\n");

        printf("1 : 行動状況の表示\n");
        printf("2 : 行動状況の変更\n");
        printf("3 : 終了\n");
    
        printf("対応する番号を入力 > ");
        scanf("%d", &num);

        if (1 <= num && num <= 3) {
            return num;
        }

        printf("\nError : 対応する番号を入力してください\n");

    } while(1);
    
    return 0;
}

int main() {
    int staff[5], *staff_ptr;
    char *head, *pos;
    int shmid;
    key_t shmkey;
    int i, in_tmp;
    int select;

    /*
    // 共有メモリを確保する
    shmkey = ftok("9-1", 'a');
    printf("%lx\n", shmkey);
    if ((shmid = shmget(shmkey, sizeof(in_data), IPC_CREAT|0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("shared memory id = %d\n", shmid);

    // 共有メモリを変数pos, headに対応付ける(アタッチする)
    if ((head = pos = shmat(shmid, 0, 0)) < 0) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    */

    do {
        select = menu();
        switch(select) {
        case 1:
            printf("社員の行動状況\n");
            break;
        case 2:
            printf("状況の変更\n");
            break;
        case 3:
            printf("終了\n");
            return EXIT_SUCCESS;
        }

    } while(1);

    return EXIT_SUCCESS;
}
