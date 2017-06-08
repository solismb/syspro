#include <stdio.h>
#include <stdlib.h>

// 大域変数
int ex1 = 532;
int ex2;

int main(){
	static int st1 = 100;
	static int st2;
	int local = 0;
	static char array_static[1024];
	char array_local[1024];
	char *array_dynamic;

	array_dynamic = (char *) malloc(1024);

	printf ("---- 変数 ----\n");
	printf ("ex1 : %016p\n", &ex1);
	printf ("ex2 : %016p\n", &ex2);
	printf ("st1 : %016p\n", &st1);
	printf ("st2 : %016p\n", &st2);
	printf ("local : %016p\n", &local);
	printf ("---- 配列 ----\n");
	printf ("array_static : %016p\n", array_static);
	printf ("array_local : %016p\n", array_local);
	printf ("&array_dynamic : %016p\n", &array_dynamic);
	printf ("array_dynamic : %016p\n", array_dynamic);
	printf ("---- 関数 ----\n");
	printf ("main : %016p\n", main);
	printf ("printf : %016p\n", printf);

	return EXIT_SUCCESS;
} 
