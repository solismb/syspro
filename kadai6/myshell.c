#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int getarg(char *argv[], char *buf);
void shift(char *argv[]);
void initArr(char *argv[], char [], char []);
void initEnv(char []);

int main()
{
	char *argv[256] = {0};
	char command[256], line[256];
	int st;
	static char prompt[64] = "> ";

	char *ret;
	char *env;
	char envname[256] = "APP_";
	pid_t pid;
	
	fprintf(stderr, "%s", prompt);
	while (fgets(line, sizeof(line), stdin) != NULL) {
		if (sscanf(line, "%[^\n]", command) > 0) {
			getarg(argv, command);
			
			/* 拡張子名を取得後, それに対応する環境変数の値を取得*/
			if (((ret = strstr(argv[0], ".")) != NULL) && (strstr(ret, "/") == NULL)) {				
				ret++;
				strcat(envname, ret);
				env = getenv(envname);
				if (env != NULL) {					
					shift(argv);
					argv[0] = env;
				}
				initEnv(envname);
			}		
			pid = fork();
			if (pid == 0) {
				if (env != NULL) {
					execvp(argv[0], argv);
				} else {
					if (execvp(argv[0], argv) < 0) {
						printf("myshell: command not found: %s\n", argv[0]);
						exit (EXIT_FAILURE);
					}					
				}
			} else {
				waitpid(pid, NULL, 0);
			}
		}
		fprintf(stderr, "%s", prompt);
		initArr(argv, command, line);  // 配列初期化
	}

	return EXIT_SUCCESS;
}

int getarg(char *argv[], char *buf)
{
	int i;

	for (i = 0; *buf != '\0'; i++) {
		while (*buf == ' ') {
			*buf = '\0';
			buf++;
		}
		if (*buf == '\0') {
			break;
		}
		argv[i] = buf;
		while (*buf != '\0' && *buf != ' ') {
			buf++;
		}
	}
	argv[i] = NULL;
	
	return i;
}

void shift(char *argv[])
{
	int i = 0;

	while(argv[i] != NULL)  // 引数の数を数える
		i++;

	if ((i+1) < 256) {            // 引数を移動したとき確保領域をオーバーしないか
		for (; i >= 0; i--) {
			argv[i+1] = argv[i];  // 引数を1つずつ後ろにずらす
		}
	}

	argv[0] = "";

	return;
}

void initArr(char *argv[], char command[], char line[])
{
	int i;
	for (i = 0; i < 256; i++) {
		argv[i] = 0;
		command[i] = 0;
		line[i] = 0;
	}

	return;
}

void initEnv(char envname[]) {
	int i;

	for (i = 0; i < 256; i++)
		envname[i] = 0;

	strcpy(envname, "APP_");

	return;
}
