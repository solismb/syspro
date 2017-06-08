#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int getarg(char *argv[], char *buf) {
	int i;

	for (i = 0; *buf != (char)NULL; i++) {
		while (*buf == ' ') {
			*buf = (char)NULL;
			buf++;
		}
		if (*buf == (char)NULL) {
			break;
		}
		argv[i]=buf;
		while (*buf != (char)NULL && *buf != ' ') {
			buf++;
		}
	}
	argv[i] = NULL;
	return i;
}

int main() {
	char *argv[256];
	char command[256], line[256];
	int st;
	static char prompt[64] = "> ";

	fprintf(stderr, "%s", prompt);
	while (fgets(line, sizeof(line), stdin) != NULL) {
		if (sscanf(line, "%[^\n]", command) > 0) {
			getarg(argv, command);
			if (fork() == 0) {
				if (execv(argv[0], argv) < 0) {
					exit(EXIT_FAILURE);
				}
			}
			else {
				wait(&st);
			}
		}
		fprintf(stderr, "%s", prompt);
	}

	return EXIT_SUCCESS;
}
		
