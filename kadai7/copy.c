#include <stdio.h>
#include <stdlib.h>

// fgetsのバッファサイズ。実用では#include <limits.h>してLINE_MAXを使うと良い。
#define BUFSIZE 512

int main(int argc, char *argv[]){
    FILE *fpin, *fpout;
    char buf[BUFSIZE];

    // (1)---- 引数のエラーチェック
    if (argc < 3){
        fprintf (stderr, "usage: %s コピー元ファイル コピー先ファイル\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    // (2)---- コピー元を読み込みモードで開く
    if ((fpin = fopen(argv[1], "r")) == NULL){
        perror(argv[1]);
        exit (EXIT_FAILURE);
    }

    // (3)---- コピー先を書き込みモードで開く
    if ((fpout = fopen(argv[2], "w")) == NULL){
        perror(argv[2]);
        exit (EXIT_FAILURE);
    }

    // (4)---- 1行読み込んでbufに入れる
    while (fgets(buf, BUFSIZE, fpin) != NULL){
        // (5)---- bufの内容をファイルに書き込む
        fputs(buf, fpout);
    }

    // (6)---- ファイルを閉じる
    if (fclose(fpin) == EOF){
        perror(argv[1]);
        exit (EXIT_FAILURE);
    }
    if (fclose(fpout) == EOF){
        perror(argv[2]);
        exit (EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
