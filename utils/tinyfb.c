#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

int main(int argc, const char **argv)
{
	printf("argc: %d, argv: %s\n", argc, argv[0]);
	int fd = 0;
	fd = open("/dev/fb0", O_RDWR);
	if (fd < 0) {
		perror("cannot open fb0");
		return -1;
	}
	return 0;
}
