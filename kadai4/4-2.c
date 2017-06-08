#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *gen_string();

//-----------------------------------------
int main(){
	char *str;
	str = gen_string();

	// STEP-2
	printf("input ay key\n");
	getchar();
	printf("generated string\t%s\n", str);
	return EXIT_SUCCESS;
}

//-----------------------------------------
char *gen_string(){
	// char array[9] -> static char array[9]
	
	// 局所変数: 宣言した関数内部でのみ参照可能.
	// 関数から抜けるときに領域は解放される.
	// よって関数から抜けると値は保持されない.
	
	// 静的変数: プログラム開始時に領域が確保される.
	// 値はプログラム終了時まで保持される.
	
	char array[9];
	int i;
	srandom(time(NULL));
	for (i = 0; i < 8; i++){
		array[i] = random() % ('z' - 'a') + 'a';
	}
	array[8] = '\0';
	// STEP-1
	return array;
 }
