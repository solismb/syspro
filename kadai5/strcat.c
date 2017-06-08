#include <stdio.h>
#include <string.h>

int main(){
	char pt[256] = ".";
	char *str = "c";
	char *hoge;

	printf ("%s\n", pt);
	printf ("%s\n", str);
	hoge = strcat(".", str);
	printf("%s\n", hoge);
	

	return 0;
}
	
