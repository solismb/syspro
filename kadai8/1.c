#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

time_t start;

int main() {
	void stop();  // 関数ポインタの宣言

	time(&start);
	signal(SIGTSTP, stop);
	while(1) {
		sleep(1);
		printf(".");
		fflush(stdout);
	}
	return EXIT_FAILURE;
}

void stop() {
	time_t end;
	char input;

	time(&end);
	printf("\n");
	printf("elapsed time= %ld seconds\n", end-start);

	while(1) {
		printf("[r] restart, [q] quit\n");
		input = getchar();
	
		if (input == 'r') {
			getchar();      // 改行読み飛ばし
			time(&start);
			return;
		} else if (input == 'q') {
			exit(EXIT_SUCCESS);
		} else {
			getchar();      // 改行読み飛ばし
			printf("illegal input\n");
		}
	}
	
	exit(EXIT_SUCCESS);
}
