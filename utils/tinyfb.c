#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <fb.h>

int main(int argc, const char **argv)
{
	printf("argc: %d, argv: %s\n", argc, argv[0]);
	int fd = 0;
	fd = open("/dev/fb0", O_RDWR);
	if (fd < 0) {
		printf("cannot open fb0");
		return -1;
	}

	static struct fb_var_screeninfo vi;
	static struct fb_fix_screeninfo fi;
	
	if (ioctl(fd, FBIOGET_VSCREENINFO, &vi) < 0) {
		printf("failed to get fb0 info");
		close(fd);
		return -1;
	}
	printf("FBIOGET_VSCREENINFO: xres: %d, yres: %d\n", vi.xres, vi.yres);
 
	/*if (ioctl(fd, FBIOPUT_VSCREENINFO, &vi) < 0) {
		printf("failed to put fb0 info");
		close(fd);
		return -1;
	}
	printf("FBIOPUT_VSCREENINFO\n");*/
 
	if (ioctl(fd, FBIOGET_FSCREENINFO, &fi) < 0) {
	        printf("failed to get fb0 info");
	        close(fd);
	        return -1;
	}
	// fi.smem_len   framebuffer的长度
	// fi.line_length: 1920*16/8 = 3840  一行的字节数
	printf("FBIOGET_FSCREENINFO: smem_len: %d, line_length: %d\n", fi.smem_len, fi.line_length);

	void *bits = NULL;
	bits = mmap(0, fi.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (bits == MAP_FAILED) {
	        printf("failed to mmap framebuffer\n");
	        close(fd);
	        return -1;
	}
	munmap(bits, fi.smem_len);

	
	return 0;
}
