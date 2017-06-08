#include <string.h>

#include "option.h"

int option(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-16") == 0)
			return HEX;
		if (strcmp(argv[i], "-2") == 0)
			return BIN;
	}

	return DEC;
}
