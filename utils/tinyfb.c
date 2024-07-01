#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, const char **argv)
{
	int fd = 0;
	fd = open("/dev/fb0", O_RDWR);
	if (fd < 0) {
		perror("cannot open fb0");
		return -1;
	}
	return 0;
}
