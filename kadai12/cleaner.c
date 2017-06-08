//
// gcc -o cleaner cleaner.c
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>
#include <unistd.h>

int main(){
    int semid;
    key_t semkey;
    struct sembuf buf[1];

    srand(time(NULL));
    semkey = ftok("seminit", 'a');
    semid = semget(semkey, 1, IPC_CREAT | 0666);
    buf[0].sem_num = 0;
    buf[0].sem_flg = 0;
    while (1){
        int i, loop;

        buf[0].sem_op = -1;
        semop(semid, buf, 1);
        loop = rand() % 5 + 1;
        for (i = 0; i < loop; i++){
            printf("\b \b");
            fflush(stdout);
            sleep(1);
        }
        buf[0].sem_op = 1;
        semop(semid, buf, 1);
        sleep(1);
    }
    return EXIT_FAILURE;
}
