#include <stdio.h>  // scanf, printf
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd, in, *pin,  len = 5;
	ssize_t ret;
	unsigned char buf[5+1], *p;
	
	if ((fd = open("testfile", O_RDONLY)) < 0) {
		perror("testfile");
		exit(EXIT_FAILURE);
	}
	
	p = buf;
	while (len != 0 && (ret = read(fd, p, len)) != 0) {
		printf("%d\n", ret);
		if (ret == -1) {
			if (errno = EINTR) continue;
			perror("read");
			break;
		}
		len -= ret;
		p += ret;
	}
	*p = '\0';
	printf("%s\n", buf);
	
	close(fd);
	
	return EXIT_SUCCESS;
}
