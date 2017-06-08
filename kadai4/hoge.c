#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *gen_string();

//-----------------------------------------
int main(){
	char *str;
	char array[9];  // Add
	str = gen_string(array);  // Add

	// STEP-2
	printf("input ay key\n");
	getchar();
	printf("generated string\t%s\n", str);
	return EXIT_SUCCESS;
}

//-----------------------------------------
char *gen_string(char *array){
	//char array[9];  // Remove
	int i;
	srandom(time(NULL));
	for (i = 0; i < 8; i++){
		array[i] = random() % ('z' - 'a') + 'a';
	}
	array[8] = '\0';
	// STEP-1
	return array;
 }
