#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    char line[32];
    char read_fd[3], write_fd[3];
    int number, result;
    int fd[2];
    int st;

    do {
        if (pipe(fd) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        snprintf(read_fd, sizeof(read_fd), "%d", fd[0]);
        snprintf(write_fd, sizeof(write_fd), "%d", fd[1]);
    
        if (fgets(line, sizeof(line), stdin)) {
            if (sscanf(line, "%d", &number) > 0) {
                if (number < 0) break;  // 負数の入力で終了
                
                if (fork() == 0) {
                    if (execl("7-8child", "7-8child", read_fd, write_fd, NULL) < 0) {
                        perror("execl");
                        exit(EXIT_FAILURE);
                    }
                }
                write(fd[1], &number, sizeof(number));
                wait(&st);
                close(fd[0]);
                close(fd[1]);
            }
        }
    } while(1);

    return EXIT_SUCCESS;
}
