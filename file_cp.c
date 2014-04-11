#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char buffer[16 * 1024];

int main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stderr, "usage:\n\t%s <buffer_size>\n", argv[0]);
		return 0;
	}

	int buffer_size = 0;
	sscanf(argv[1], "%d", &buffer_size);

	if (buffer_size > sizeof(buffer)) {
		fprintf(stderr, "buffer size too big. max: %ld\n", sizeof(buffer));
		return 0;
	}
	
	int bytes_read = 0;

	while ((bytes_read = read(STDIN_FILENO, buffer, buffer_size)) > 0) {
		if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
			fprintf(stderr, "write error.\n");
		}
	}

	if (bytes_read < 0) {
		fprintf(stderr, "read error.\n");
	}

	return 0;
}
