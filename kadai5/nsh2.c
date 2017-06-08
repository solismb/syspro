#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int getarg(char *argv[], char *buf);
void swap(char *argv[]);
void initArr(char *argv[], char [], char []);
int getExtension(char *envp[], char *name[]);
void initExt(char [], char []);

int main(int ac, char *av[], char *envp[])
{
	char *argv[256] = {0};
	char command[256], line[256];
	int st;
	static char prompt[64] = "> ";

	char *ret;
	char *env;
	char envname[256] = "APP_";
	char *envc, *envtxt;
	char *name[256] = {0};
	char ext[256];
	int extnum = 0;
	int i;
	char *copy[256];

	for (i = 0; envp[i] != NULL; i++)
		copy[i] = envp[i];
	
	envtxt = getenv("APP_txt");
	printf("env: %s\n", envtxt);
	extnum = getExtension(copy, name);
	ext[0] = '.';
	envtxt = getenv("APP_txt");
	printf("env: %s\n", envtxt);

	fprintf(stderr, "%s", prompt);
	while (fgets(line, sizeof(line), stdin) != NULL) {
		if (sscanf(line, "%[^\n]", command) > 0) {
			getarg(argv, command);
			if (fork() == 0) {	
				for (i = 0; i < extnum; i++) {
					strcat(ext, name[i]);
					printf("ext: %s\n", ext);
					//initExt(ext);
					if ((ret = strstr(argv[0], ext)) != NULL) {
						printf("inif\n");
						swap(argv);
						strcat(envname, name[i]);
						printf("envname: %s\n", envname);
						env = getenv(envname);
						printf("%s\n", env);
						execvp(env, argv);
					}
					initExt(ext, envname);
				}
				

				/*
				if ((ret = strstr(argv[0], strcat(".", name))) != NULL) {
					
					printf("%s\n",envc);
					swap(argv);
					env = getenv(strcat("APP_", name));
					execvp(env, argv);
				}
				*/
			
				/*
				if ((ret = strstr(argv[0], ".txt")) != NULL) {
					//execv("/usr/bin/vim", argv);
					swap(argv);
					envtxt = getenv("APP_txt");  // 環境変数APP_txtの値を取得
					printf("%s\n", envtxt);
					//execvp(envtxt, argv);
				}

				if (execv(argv[0], argv) < 0) {
					exit (EXIT_FAILURE);
				}
				*/
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

int getExtension(char *copy[], char *name[]) {
	int i, j = 0;
	char *extension;
	//char *copy[256];

	for (i = 0; copy[i] != NULL; i++){		
		if (strstr(copy[i], "APP_") != NULL) {
			extension = strchr(copy[i], '_');
			extension++;
			strtok(extension, "=");
			printf("g %s\n", extension);
			name[j] = extension;
			j++;
		}
	}

	return j;
}

void initExt(char ext[], char envname[]) {
	int i;
	
	for (i = 0; i < 256; i++) {
		ext[i] = 0;
		envname[i] = 0;
	}

	ext[0] = '.';
	strcpy(envname, "APP_");
	
	return;
}
