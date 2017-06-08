#include <stdio.h>
#define ADD(A, B) A + B
#define SUBSTRACT(A, B) (A - B)

int main() {
	printf("%d\n", ADD(5, 3) * 2);
	printf("%d\n", 2 * ADD(5, 3));
	printf("%d\n", SUBSTRACT(5, 3) * 2);
	
	return 0;
}
