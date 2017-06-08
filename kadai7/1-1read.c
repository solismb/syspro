#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	FILE *fp;
	double x = 12345.123456789;
	double y;

	if ((fp = fopen("data1-1", "r")) == NULL) {
		perror("data1-1");
		exit (EXIT_FAILURE);
	}

	fscanf(fp, "%lf", &y);
	
	printf("error: %e\n", fabs(x - y));

	fclose(fp);
	return (EXIT_SUCCESS);
}
