#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned short Ushort;
typedef unsigned int Uint;

typedef struct {
	char riff[4];
	Uint size;         // この値+8byteでファイルサイズ
	char wave[4];
} wavHeader;

typedef struct {
	Ushort format;     // データ形式
	Ushort channel;    // チャンネル数
	Uint sampling;     // サンプリング周波数
	Uint speed;        // データ速度
	Ushort blockSize;  // ブロックサイズ
	Ushort qbit;       // 量子化ビット
} chunkData;

void showDetail(chunkData data) {
	printf("サンプリング周波数(Hz): %d\n", data.sampling);
	printf("量子化ビット(bit)     : %d\n", data.qbit);
	printf("チャンネル数          : %d\n", data.channel);

	return;
}

int main(int argc, char *argv[]) {
	FILE *fp;
	wavHeader wHeader;
	chunkData data;
	char name[4];      // chunk名
	Uint cSize = 0;    // chunkサイズ
	Ushort ext = 0;    // 拡張領域
	int flag = 0;

	if (argc < 2) {
		fprintf(stderr, "usage: %s wavファイル\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((fp = fopen(argv[1], "rb")) == NULL) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}

	// freadでヘッダー分だけ読み飛ばす
	fread(&wHeader, sizeof(wavHeader), 1, fp);

	while (!flag) {
		// chunkのヘッダー分読み取り
		fread(name, sizeof(name), 1, fp);
		name[4] = '\0';	
		fread(&cSize, sizeof(int), 1, fp);
		
		if (strcmp(name, "fmt " ) == 0 && cSize == 16) {
			fread(&data, sizeof(chunkData), 1, fp);
			showDetail(data);
		} else if (strcmp(name, "fmt ") == 0 && cSize != 16) {
			fread(&data, sizeof(chunkData), 1, fp);
			showDetail(data);
			fread(&ext, sizeof(short), 1, fp);
			fseek(fp, (long)ext, SEEK_CUR);
		} else if (strcmp(name, "data") == 0) {
			printf("データサイズ(byte)    : %d\n", cSize);
			flag = 1;
		} else {
			fseek(fp, (long)cSize, SEEK_CUR);
		}
	}

	fclose(fp);
	
	return 0;
}
