#include <stdio.h>
#include <string.h>

int main() {
	char str[] = "hoge=fuga";

	char *hoge, *fuga;

	hoge = strtok(str, "=");
	//fuga = strtok(NULL, "=");

	printf("hoge : %s\n", hoge);
	//printf("fuga : %s\n", fuga);

	return 0;
}
