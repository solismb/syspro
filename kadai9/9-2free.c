#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int shmid;
    key_t shmkey;

    // 共有メモリを確保する
    shmkey = ftok("9-1staff", 'a');
    if ((shmid = shmget(shmkey, sizeof(int) * 5, 0)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("shared memory id = %d\n", shmid);

    // 共有メモリを開放する
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        perror("shmctl");
    }

    printf("9-1staffの共有メモリを解放しました.\n");

    return EXIT_SUCCESS;
}
