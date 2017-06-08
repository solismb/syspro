#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char answer[256], line[256];
	void prompt();

	signal(SIGALRM, prompt);
	while (1) {
			printf("Do you want to continue?\n");
			alarm(5);
            if (fgets(line, sizeof(line), stdin) != NULL) {
                alarm(0);
                if (sscanf(line, "%[^\n]", answer) < 1) {
                    prompt();
                }
                else {
                    if (answer[0] == 'n' || answer[0] == 'N') {
                        break;
                    }
                    else if (answer[0] != 'y' && answer[0] != 'Y') {
                        prompt();
                    }
                }
            }
    }

    return EXIT_SUCCESS;
}

void prompt() {
    printf("Please input Y or N.\n");
    alarm(5);

    return;
}
