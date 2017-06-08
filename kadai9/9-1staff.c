#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getStaffNum() {
    int staff_num;
    
    do {
        printf("社員番号[0 ~ 4]を入力してください > ");
        scanf("%d", &staff_num);
        if (0 <= staff_num && staff_num <= 4) {
            break;
        }
        printf("対応していない番号です. 再入力してください.\n\n");
    } while(1);

    puts("");
    return staff_num;
}

void updateStatus(int *pos, int staff_num) {
    int status;
    
    do {
        printf("## 状態 ##\n0\t退社(帰宅)\n1\t在室\n2\t会議中\n3\t社外\n");
        printf("社員番号[%d]さんの状態を0 ~ 3で入力してください.\n", staff_num);
        printf("状態 > ");
        scanf("%d", &status);
        if (0 <= status && status <= 3) {
            break;
        }
        printf("対応していない状態です. 再入力してください.\n\n");
    } while(1);

    puts("");

    // 更新
    pos[staff_num] = status;
    
    printf("社員番号[%d]さんの状態を ", staff_num);
    switch(status) {
    case 0:
        printf("[退社(帰宅)]");
        break;
    case 1:
        printf("[在室]");
        break;
    case 2:
        printf("[会議中]");
        break;
    case 3:
        printf("[社外]");
        break;
    }
    printf(" に更新しました.\n");

    return;
}

int main() {
    int staff_num;
    int *head, *pos;
    int shmid, i;
    key_t shmkey;

    // 共有メモリを確保する
    shmkey = ftok("9-1staff", 'a');
    //printf("%lx\n", shmkey);
    if ((shmid = shmget(shmkey, sizeof(int) * 5, IPC_CREAT|0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("shared memory id = %d\n", shmid);

    // 共有メモリを変数pos, headに対応付ける
    if ((head = pos = shmat(shmid, 0, 0)) < 0) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // 社員の状態を共有メモリにコピーする
    staff_num = getStaffNum();
    updateStatus(pos, staff_num);
    
    shmdt(head);
    return EXIT_SUCCESS;
}
