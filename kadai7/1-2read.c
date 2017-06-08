#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	FILE *fp;
	double x = 12345.123456789;
	double y;

	if ((fp = fopen("data1-2", "rb")) == NULL) {
		perror("data1-2");
		exit (EXIT_FAILURE);
	}

	fread(&y, sizeof(double), 1, fp);

	printf("error: %e\n", fabs(x - y));

	fclose(fp);
	return (EXIT_SUCCESS);
}
