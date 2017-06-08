#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printStatus(int *pos) {
    int i;

    printf("## 状態 ##\n");
    for (i = 0; i < 5; i++) {
        printf("社員[%d]  ", i);
        
        switch(pos[i]) {
        case 0:
            printf("退社(帰宅)\n");
            break;
        case 1:
            printf("在室\n");
            break;
        case 2:
            printf("会議中\n");
            break;
        case 3:
            printf("社外\n");
            break;
        default:
            printf("不明\n");
            break;
        }
    }
    
    return;
}

int main() {
    int *head, *pos;
    int shmid, i;
    key_t shmkey;

    // 共有メモリを確保する
    shmkey = ftok("9-1staff", 'a');
    if ((shmid = shmget(shmkey, sizeof(int) * 5, 0)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("shared memory id = %d\n", shmid);

    // 共有メモリを変数pos, headに対応付ける
    if ((head = pos = shmat(shmid, 0, 0)) < 0) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // 行動状況の表示
    printStatus(pos);

    shmdt(head);
    return EXIT_SUCCESS;
}
