#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int getarg(char *argv[], char *buf);
void swap(char *argv[]);
void initArr(char *argv[], char [], char []);
void initEnv(char []);

int main()
{
	char *argv[256] = {0};
	char command[256], line[256];
	int st;
	static char prompt[64] = "> ";

	char *ret;
	//char *envc, *envtxt;
	char *env;
	char envname[256] = "APP_";
	int i = 0;
	
	fprintf(stderr, "%s", prompt);
	while (fgets(line, sizeof(line), stdin) != NULL) {
		if (sscanf(line, "%[^\n]", command) > 0) {
			getarg(argv, command);
			if (fork() == 0) {
				if (((ret = strstr(argv[0], ".")) != NULL) && (strstr(ret, "/") == NULL)) {
					/*
					ret++;
					printf("%s\n", ret);
					printf("%s\n", argv[0]);

					strcat(envname, ret);
					printf("%s\n", envname);
					envc = getenv(envname);
					puts("before");
					//printf("%s\n", envc);
					*/
					ret++;
					strcat(envname, ret);
					env = getenv(envname);
					if (env != NULL) {
						puts(argv[0]);
						puts(argv[1]);
						puts(argv[2]);
						swap(argv);
						puts(argv[0]);
						puts(argv[1]);
						puts(argv[2]);
						execvp(env, argv);
					} else {
						printf("nsh2: command not found: %s\n", argv[0]);
						
					}
					
					initEnv(envname);	
				}
				/*
				if ((ret = strstr(argv[0], ".txt")) != NULL) {
					//execv("/usr/bin/vim", argv);
					swap(argv);
					envtxt = getenv("APP_txt");  // 環境変数APP_txtの値を取得
					
					execvp(envtxt, argv);
				}
				else if ((ret = strstr(argv[0], ".c"))   != NULL) {
					swap(argv);
					envc = getenv("APP_c");      // 環境変数APP_cの値を取得
					
					execvp(envc, argv);
				}
				*/
				else if (execvp(argv[0], argv) < 0) {
					exit (EXIT_FAILURE);
				}
			} else {
				wait(&st);
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

void swap(char *argv[])
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
	
