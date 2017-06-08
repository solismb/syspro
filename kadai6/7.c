#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>     // isspace()を使うのでincludeする

//-----------------------------------------------------------
// define
//
#define MAXSTR 256     // コマンド入力の最大文字数

//-----------------------------------------------------------
// 各関数のプロトタイプ宣言
//
int cd(char *argv[]);                   // cdコマンド
int pwd();
int myExit();                           // exit/logoutコマンド
int built_in(char *argv[]);             // 入力コマンドが組み込みコマンドなら所定の関数を実行する
int getarg(char *argv[], char *buf);    // 入力された1行を単語に分解してargvに入れる
void showprompt();                      // プロンプトを表示する
void getLine(char *command, int size);  // 1行読み込んで配列commandに入れる。最長でsize-1文字まで。

//-----------------------------------------------------------
// 構造体
//
struct builtin {
    char cmd[MAXSTR];     // 本プログラム内で実装するコマンド名
    int (*func)();        // コマンドを実装した関数へのポインタ
};
struct builtin blt_in[] = {
    {"cd",     cd},       // "cd"コマンドとその関数
	{"pwd",    pwd},
    {"exit",   myExit},   // "exit"コマンドとその関数
    {"logout", myExit},   // "logout"コマンドとその関数
    {"0", 0}              // 配列の最後を示すための番兵
};

//-----------------------------------------------------------
// 本文
//
int main(){
    char *argv[MAXSTR], command[MAXSTR];
    int st;
    WINDOW* w;

    // ncursesを設定する
    w = initscr();
    idlok(w, TRUE); 
    scrollok(stdscr, TRUE);
    cbreak();
    echo();
    nl();
    erase();

    // '\n'を"\r\n"に変換する設定を有効化する
    if (system("/bin/stty onlcr icrnl") != 0){
        fprintf(stderr, "error: stty failed");
        exit(EXIT_FAILURE);
    }

    while (1){
        getLine(command, MAXSTR);   // 入力を一行読み込んで文字配列commandに入れる
        getarg(argv, command);      // コマンド文字列commandを単語に分割してargvに入れる

        // コマンド実行する
        if (built_in(argv) < 0 && argv[0] != '\0'){
            if (fork() == 0){
                if (execv(argv[0], argv) < 0){
                    perror(argv[0]);
                    exit(EXIT_FAILURE);
                }
            } else {
                wait(&st);
            }

        }
    }
    endwin();
    delwin(w);
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------
// キーボードから一行(最長でsize-1文字まで)読み込んで配列commandに入れる
//
void getLine(char *command, int size){

    // プロンプトを表示する
    showprompt();

    //
    // 以降は各自で実装すること
    //
	getnstr(command, size);
}

//-----------------------------------------------------------
// showprompt() - プロンプトを表示する
//
void showprompt(){
    int x, y;

    getsyx(y, x);                   // カーソルの現在の座標を取得する
    move(y, 0);                     // カーソルを左端に移動
    clrtoeol();                     // カーソル位置から行末までを消去
    printw("%s> ", getenv("PWD"));  // カレントディレクトリを付けたプロンプトを表示
    refresh();                      // 表示を更新する
}

//-----------------------------------------------------------
// built_in(argv) - 本プログラムに組み込んだコマンドかどうか調べる
//                  組み込みコマンドであれば所定の関数を実行する
// [引数]
//   argv ... ユーザが入力したコマンドを単語に分解した配列。argv[0]はコマンド名
// [返り値]
//    0 ... 組み込みコマンドだった場合
//   -1 ... 組み込みコマンドではなかった場合
//
int built_in(char *argv[]){
    struct builtin *p;

    if (argv[0] == '\0'){
        return -1;
    } else {
        for (p = blt_in; *p->cmd != 0; p++){
            if (strcmp(p->cmd, argv[0]) == 0){
                // ユーザが入力したコマンド名が組み込みコマンドであれば所定の関数を呼び出す
                (p->func) (argv);
                return 0;
            }
        }
    }
    return -1;
}

//-----------------------------------------------------------
// cd(argv) - cd (change directory)コマンド
//
// [引数]
//   argv ... ユーザが入力したコマンドを単語に分解した配列。argv[0]はコマンド名
//
int cd(char *argv[]){
    static char e_value[MAXSTR];
	static char pathname[MAXSTR];

    // カレントディレクトリを変更する
    if (chdir(argv[1]) < 0){
        perror("chdir");
        return -1;
    }

	getcwd(pathname, sizeof(pathname));
	
    // 環境変数PWDの内容を更新する
    strncpy(e_value, "PWD=", sizeof(e_value));
    strncat(e_value, pathname, sizeof(e_value) - strlen(e_value) - 1);
    putenv(e_value);

    return 0;
}

int pwd() {
	static char pathname[MAXSTR];

	getcwd(pathname, sizeof(pathname));
	printw("%s\n", pathname);
	refresh();

	return 0;
}

//-----------------------------------------------------------
// myExit - exitコマンド
//
int myExit(){
    if (system("/bin/stty sane") != 0){           // 端末の設定をリセットする
        fprintf(stderr, "error: stty failed");
    }
    exit (EXIT_SUCCESS);                    // 終了する
    return 0;
}
 
//-----------------------------------------------------------
// getarg(argv, buf) - 入力文字列を空白刻みで分解して配列argvに入れる(教科書p.161)
//
// [引数]
//   argv ... ユーザが入力したコマンドを単語に分解した配列。argv[0]はコマンド名
// [返り値]
//   分解した単語数
//
int getarg(char *argv[], char *buf){
    int i;

    for (i = 0; *buf != '\0'; i++){
        while (isspace((int)*buf)){
            *buf = '\0';
            buf++;
        }
        if (*buf == '\0') break;                            // 行末に到達したら終了する
        argv[i] = buf;                                      // 単語冒頭のアドレスをargvに登録する
        while (*buf != '\0' && !isspace((int)*buf)) buf++;  // 次の空白か行末までbufを移動させる
    }
    argv[i] = NULL;
    return i;
}

