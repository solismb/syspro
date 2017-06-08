#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int ch;

	if ((fp = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		return EXIT_FAILURE;
	}

	while (1) {
		ch = fgetc(fp);
		if (ch == EOF)
			break;
		printf("%c", ch);
	}

	if (fclose(fp) == EOF) {
		perror(argv[1]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
