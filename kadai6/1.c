#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/vfs.h>

int main(int argc, char *argv[])
{
	struct statfs buf[1];
	sync();

	if (statfs(argv[1], buf) < 0) {
		fprintf(stderr, "Cannot read  super block!\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "f_type    = %ld\n", buf[0].f_type);
	fprintf(stderr, "f_bsize   = %ld\n", buf[0].f_bsize);
	fprintf(stderr, "f_blocks  = %ld\n", buf[0].f_blocks);
	fprintf(stderr, "f_bfree   = %ld\n", buf[0].f_bfree);
	fprintf(stderr, "f_bavail  = %ld\n", buf[0].f_bavail);
	fprintf(stderr, "f_files   = %ld\n", buf[0].f_files);
	fprintf(stderr, "f_ffree   = %ld\n", buf[0].f_ffree);
	fprintf(stderr, "f_fsid    = %ld\n", buf[0].f_fsid);
	fprintf(stderr, "f_namelen = %ld\n", buf[0].f_namelen);

	return EXIT_SUCCESS;
}
