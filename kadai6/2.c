#include <stdio.h>
#include <stdlib.h>

void ttyprintf(FILE *fp, char *str)
{
	fprintf(fp, "%s", str);

	return;
}

int main(int argc, char *argv[])
{
	FILE *fp;

	printf("%s\n", argv[1]);
	if ((fp = fopen(argv[1], "w")) == NULL) {
		fprintf(stderr, "ファイルのオープンに失敗\n");
		return EXIT_FAILURE;
	}

	ttyprintf(fp, "ttyprintf Hello!\n");

	fclose(fp);
	
	return EXIT_SUCCESS;
}
