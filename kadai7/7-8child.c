#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int number, result;
    int read_fd;

    // 引数の文字列を整数に変換
    read_fd = atoi(argv[1]);

    // パイプラインからデータを読み込む
    read(read_fd, &number, sizeof(number));

    result = number * number;
    printf("%d x %d = %d\n", number, number, result);

    close(read_fd);

    return EXIT_SUCCESS;
}
