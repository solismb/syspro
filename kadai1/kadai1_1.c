#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	if ((fp = fopen(argv[1], "w")) == NULL) {
			perror(argv[1]);
			return EXIT_FAILURE;
	}
	fprintf(fp, "hello\n");

	if (fclose(fp) == EOF) {
		perror(argv[1]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

		
