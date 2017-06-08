#include <stdio.h>  // scanf, printf
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 4  // int: 4byte

int main() {
	int fd, in, *pin,  len = SIZE;
	ssize_t ret;
	unsigned char ch, *p;

	//-------- write tmpfile
	printf("input> ");
	scanf("%d", &in);
	puts("");
	
	if ((fd = open("tmpfile", O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
		perror("tmpfile");
		exit(EXIT_FAILURE);
	}
	
	pin = &in;
	while (len != 0 && (ret = write(fd, pin, len)) != 0) {
		if (ret == -1) {
			if (errno = EINTR) continue;
			perror("read");
			break;
		}
		len -= ret;
		pin += ret;
	}
	close(fd);

	//-------- read tmpfile
	if ((fd = open("tmpfile", O_RDONLY)) < 0) {
		perror("tmpfile");
		exit(EXIT_FAILURE);
	}
	
	p = &ch;
	for (len = 0; len < SIZE; len++) {
		ret = read(fd, p, 1);
		printf("%x ", ch);
	}
	puts("");
	close(fd);
	
	return EXIT_SUCCESS;
}
