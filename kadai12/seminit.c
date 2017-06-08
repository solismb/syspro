//
// gcc -o seminit seminit.c
//
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int main(){
    int semid;
    key_t semkey;

    semkey = ftok("seminit", 'a');
    semid = semget(semkey, 1, IPC_CREAT|0666);
    semctl(semid, 0, SETVAL, 1);
    return EXIT_SUCCESS;
}
