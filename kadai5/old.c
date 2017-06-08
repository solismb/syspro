#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int getarg(char *argv[], char *buf);
void swap(char *argv[]);
void initArr(char *argv[], char [], char []);

int main()
{
	char *argv[256] = {0};
	char command[256], line[256];
	int st;
	static char prompt[64] = "> ";

	char *ret;
	char *envc, *envtxt;
	
	fprintf(stderr, "%s", prompt);
	while (fgets(line, sizeof(line), stdin) != NULL) {
		if (sscanf(line, "%[^\n]", command) > 0) {
			getarg(argv, command);
			if (fork() == 0) {
				if ((ret = strstr(argv[0], ".txt")) != NULL) {
					//execv("/usr/bin/vim", argv);
					swap(argv);
					envtxt = getenv("APP_txt");  // 環境変数APP_txtの値を取得
					printf("%s\n", envtxt);
					//execvp(envtxt, argv);
				}
				else if ((ret = strstr(argv[0], ".c"))   != NULL) {
					swap(argv);
					envc = getenv("APP_c");      // 環境変数APP_cの値を取得
					
					execvp(envc, argv);
				}
				else if (execv(argv[0], argv) < 0) {
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

	for (i = 0; *buf != (char)NULL; i++) {
		while (*buf == ' ') {
			*buf = (char)NULL;
			buf++;
		}
		if (*buf == (char)NULL) {
			break;
		}
		argv[i] = buf;
		while (*buf != (char)NULL && *buf != ' ') {
			buf++;
		}
	}
	argv[i] = NULL;
	
	return i;
}

void swap(char *argv[])
{
	char *temp;

	temp = argv[0];
	argv[0] = "/usr/bin/vim";
	argv[1] = temp;

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
