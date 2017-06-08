#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main() {
    int msqid1, msqid2;
    key_t msgkey1, msgkey2;

    msgkey1 = ftok("master", 'a');
    msgkey2 = ftok("shokai", 'z');
    msqid1  = msgget(msgkey1, IPC_CREAT|0666);
    msqid2  = msgget(msgkey2, IPC_CREAT|0666);
    
    if (msgctl(msqid1, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return EXIT_FAILURE;
    }
    if (msgctl(msqid2, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return EXIT_FAILURE;
    }

    printf("master, shokaiのmsgqを解放しました.\n");

    return EXIT_SUCCESS;
}
