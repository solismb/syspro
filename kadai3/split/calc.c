#include <stdio.h>

#include "calc.h"

int calc(long a, char ope, long b)
{
	switch(ope) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		printf("error\n");
		return -1;
	}
}
