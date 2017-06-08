#include <stdio.h>
//
// gcc -o writer writer.c
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main(){
    int semid;
    key_t semkey;
    struct sembuf buf[1];

    semkey = ftok("seminit", 'a');
    semid = semget(semkey, 1, IPC_CREAT | 0666);
    buf[0].sem_num = 0;
    buf[0].sem_flg = 0;
    while (1){
        int i;

        buf[0].sem_op = -1;
        semop(semid, buf, 1);
        for (i = 0; i < 5; i++){
            printf("%d", i);
            fflush(stdout);
            sleep(1);
        }
        buf[0].sem_op = 1;
        semop(semid, buf, 1);
        sleep(1);
    }
    return EXIT_FAILURE;
}
