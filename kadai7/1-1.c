#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fp;
	double x = 12345.123456789;

	if ((fp = fopen("data1-1", "w")) == NULL) {
		perror("data1-1");
		exit(EXIT_FAILURE);
	}

	fprintf(fp, "%10.4f\n", x);
	fclose(fp);
	return (EXIT_SUCCESS);
}
