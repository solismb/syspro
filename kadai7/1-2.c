#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fp;
	double x = 12345.123456789;

	if ((fp = fopen("data1-2", "wb")) == NULL) {
		perror("data1-2");
		exit(EXIT_FAILURE);
	}

	fwrite(&x, sizeof(double), 1, fp);
	fclose(fp);
	return (EXIT_SUCCESS);
}
