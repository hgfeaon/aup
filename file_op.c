#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

char file_header[] = "this is the file header msg.";
char file_end[] = "now we reach the file end.";

int main() {
	printf("size of off_t: %ld\n", sizeof(off_t));
	printf("max file open number: %ld\n", sysconf(_SC_OPEN_MAX));
	printf("max name length: %d\n", _POSIX_NAME_MAX);
	printf("max path length: %d\n", _POSIX_PATH_MAX);

	int fd = open("tmpfile", O_RDWR | O_CREAT | O_TRUNC);

	if (fd < 0) {
		perror("file operation open");
		return 0;
	}

	int head_len = strlen(file_header);
	int end_len  = strlen(file_end);

	if (write(fd, file_header, head_len) != head_len) {
		perror("write file header msg failed.");
	}

	if (lseek(fd, 16384, SEEK_SET) == -1) {
		perror("lseek failed.");
	}

	if (write(fd, file_end, end_len) != end_len) {
		perror("write file end msg failed.");
	}

	if (close(fd) < 0) {
		perror("file operation close");
	}
	return 0;
}
