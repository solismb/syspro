#include <stdio.h>
#include <stdlib.h>

#include "option.h"
#include "calc.h"

int main(int argc, char *argv[])
{
	long a = 0, b = 0;
	int base = 0, ans = 0;
	char *e;

	if (argc < 4) {
		printf("引数の数が足りていません\n");
		return EXIT_FAILURE;
	}
	
	if (argc == 4) {
		base = option(argc, argv);
		a = strtol(argv[1], &e, base);
		b = strtol(argv[3], &e, base);

		ans = calc(a, argv[2][0], b);
	} else {
		base = option(argc, argv);
		a = strtol(argv[2], &e, base);
		b = strtol(argv[4], &e, base);

		ans = calc(a, argv[3][0], b);
	}

	printf("%d\n", ans);

	return 0;
}
